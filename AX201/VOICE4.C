/*
   ·q¬÷ Â‰b žË¥
   SoundBlaster : DMA ¸å­· ¤w¤ó.

   32000 byte Ça‹¡· ¤áÌáŸi 8ˆ ¬a¶wÐaµa ÇA· ÑwÈ¡ ¸å­·Ða“e Ïa¡‹aœ‘.
   Signel Voice.

   Voice ÑÁ·©µA¬á ¯©¹A •A·¡Èa À÷Ça—i e·i ÇAµA ¬s·³Ðaµa, 'Ë¢' ­¡Ÿ¡Ÿi
   ´ô´‘.
*/

#include <alloc.h>
#include <string.h>
#include <dos.h>
#include <io.h>
#include <fcntl.h>
#include "voice.h"
#include "dmaIO.h"

#define _BUF_EMPTY_		0
#define _BUF_READY_		1
#define _EMPTY_SLOT_	-1
#define MAXBUFSIZE		16000
#define NUMBUFFER		10
#define QueueSize		(NUMBUFFER * 2)

union _long {
	unsigned long onelong;
	unsigned char bytes[4];
} Long;
struct _frag {
	int status;
	unsigned char *address;
	unsigned long linear;
	unsigned int length;
	unsigned int bytes;
} Fragments[QueueSize];
int FragmentCount;

/* ¬a§i· ¥¡É· I/O ¤å»¡µÁ IRQ, DMA Àé */
int SBLBaseIO=0x220;	/* default sound blaster Base IO Address */
int SBLIRQ=0x5;			/* default sound blaster hardware interrupt */
int SBLDMAChannel=0x1;	/* default sound blaster DMA channel */
unsigned int SampleRate=8000;
unsigned int VoiceVolume=10;
int FragmentQueue[QueueSize];   /* ·q¬÷·i Â‰bÐi •A·¡Èa §iœâ—i· ÇA */
int QueueFront=0,QueueRear=0;
int VoiceFlag = VOICE_IDLE;		/* ·q¬÷ Â‰b ¬wÉA ¥e® */
int VoiceHardWare = NO_VOICE;	/* ·q¬÷ Â‰b Ða—a¶Á´á */
void far interrupt (*OldHandler)()=NULL;	/* ¬a§i ·¥ÈáœóËa ¥¡‰Å¶w */
char *VoiceBuffer[NUMBUFFER];
char TempBuffer[MAXBUFSIZE];
int BufferCount,BufferPos;      /* Ñe¸ ¸¬—º—·¥ •A·¡Èa §iœâ· ¤åÑ¡µÁ ¶áÃ¡  */
int Invalid=0;
int SBL_CommandError=0;

/*
**  ÇAˆa §¡´á·¶“e»¡Ÿi ˆñ¬aÐe”a.
*/
int VOC_IsQueueEmpty(void)
{
	return (QueueFront == QueueRear);
}

/*
**  ÇAˆa ¡¡– Àµa¹a ·¶“e»¡Ÿi ˆñ¬a
*/
int VOC_IsQueueFull(void)
{
	return (((QueueFront + 1) % QueueSize) == QueueRear);
}

/*
**  ÇA·  … ´|µA ·¶“e •A·¡Èa §iœâ· ¤åÑ¡Ÿi ´i´a…”a.
*/
int VOC_QueueTop(void)
{
	if( VOC_IsQueueEmpty() ) return -1;
	else return FragmentQueue[QueueRear];
}

/*
**  ÇAµA ¬¡¶… ·q¬÷ •A·¡Èa §iœâ·i ÂˆaÐe”a.
*/
void VOC_InsertQueue(int fragnum)
{
	Fragments[fragnum].status = _BUF_READY_;
	FragmentQueue[QueueFront] = fragnum;
	QueueFront = ++QueueFront % QueueSize;
}

/*
**  ÇAµA¬á ˆa¸w µ¡œ–E •A·¡Èa §iœâ·i ¹AˆáÐe”a.
*/
void VOC_DeleteQueue(void)
{
	Fragments[FragmentQueue[QueueRear]].status = _BUF_EMPTY_;
	Fragments[FragmentQueue[QueueRear]].bytes = 0;
	QueueRear = ++QueueRear % QueueSize;
}

/*
**  Ñe¸ DMA¡ ¸å­·Ðe •A·¡Èa· ´··i ´i´a…”a.
*/
unsigned int VOC_GetDMACount(void)
{
	unsigned int remainbytes;
	remainbytes = (unsigned int) DMA_GetDMACounter( SBLDMAChannel );
	if( remainbytes == 0xFFFF ) remainbytes = 0;
	return remainbytes;
}

/*
**  ¬a§i DMAŸi ·¡¶wÐaµa ·q¬÷·i Â‰b¯¡Ç¥”a.
*/
int VOC_sayDMAvoice(unsigned long address,unsigned int length)
{
    DMA_DisableDREQ(SBLDMAChannel);     /*   å¸á DMAŸi º—»¡¯¡Ç¥”a.  */
	if( DMA_Run( address, length, SBLDMAChannel, 1 ) != 0 ) {
                                        /*  DMAŸi ˆa•·¯¡Ç¡‰¡ µAœáˆa a¡e
                                            ¥¢ŠáÐe”a.               */
		VoiceFlag = VOICE_IDLE;
		return -1;
	}
    SBL_Command( DMA_8BIT_DAC );        /* 8§¡Ëa DMA DAC ¡ww */
    SBL_Command( length & 0xff );       /* ·q¬÷‹©·¡ ¬é¸÷ */
	SBL_Command( length >> 8 );
	VoiceFlag = VOICE_BUSY;
	return 0;
}

/*
**  – ·q¬÷ •A·¡ÈaŸi length eÇq ¬ã´áº…”a.
*/
void VOC_mixvoice(unsigned char *dst,unsigned char *src,unsigned int length)
{
	unsigned int i;
	int d1;
	for(i=0;i<length;i++,dst++,src++) {
		d1 = (int) *dst + (int) *src;
		d1 >>= 1;
        *dst = d1;          /*  – •A·¡ÈaŸi ”áÐa‰¡ ”a¯¡ 2¡ a’… ˆt·i
                                ¸á¸wÐe”a.   */
	}
}

/*
**  bufferµA ·¶“e ·q¬÷ •A·¡ÈaŸi bytes eÇq Ñe¸· ·q¬÷ •A·¡Èa §iœâµA ¸á¸wÐe”a.
*/
void VOC_savedata(unsigned char *buffer,unsigned int bytes)
{
	unsigned int bufpos,gap;
	bufpos = 0;
    while( bytes ) {    /*  ¸á¸wÐ´¡ Ði •A·¡Èaˆa ·¶“e •·´e  */
		gap = Fragments[BufferCount].length - BufferPos;
                        /*  Ñe¸ •A·¡Èa §iœâ· q·e ‰·ˆe·i ‰¬e */
        if( bytes > gap ) {     /*  q·e ‰·ˆe·¡ ”á ¸â”a¡e       */
			VOC_mixvoice( Fragments[BufferCount].address + BufferPos,
				buffer + bufpos, gap );
			Fragments[BufferCount].bytes = Fragments[BufferCount].length;
                                /*  q·e ‰·ˆe eÇq e Ñe¸ §iœâµA Âˆa    */
			switch( Fragments[BufferCount].status ) {
			case _BUF_EMPTY_:
				VOC_InsertQueue( BufferCount );
                                /*  Ñe¸ §iœâ·¡ ÇAµA ´ô“e ‰w¶ Âˆa     */
				break;
			case _BUF_READY_:
				if( VOC_QueueTop() == BufferCount ) {
					SBL_Command( HALT_DMA );
					VOC_sayDMAvoice( Fragments[BufferCount].linear + BufferPos,
						gap );
                }               /*  Ñe¸ §iœâ·¡ ÇAµA ·¶´ö”a¡e, DMA ¸å­·œ··¡
                                    ¤aŽá´ö·a£a¡ º—»¡Ða‰¡ ”a¯¡ ¸å­·Ðe”a.    */
			}
			BufferPos = 0;
			BufferCount = ++BufferCount % FragmentCount;
                                /*  ”a·q •A·¡Èa §iœâ·i ˆaŸ¡Ç¥”a.    */
            bytes -= gap, bufpos += gap;
		}
        else {                  /*  q·e ‰·ˆe·¡ Â—¦…Ða”a¡e          */
			VOC_mixvoice( Fragments[BufferCount].address + BufferPos,
				buffer + bufpos, bytes );
                                /*  ¡¡– ¸á¸wÐe”a.                  */
			switch( Fragments[BufferCount].status ) {
			case _BUF_EMPTY_:
				VOC_InsertQueue( BufferCount );
				break;
			case _BUF_READY_:
				if( VOC_QueueTop() == BufferCount ) {
					SBL_Command( HALT_DMA );
					VOC_sayDMAvoice( Fragments[BufferCount].linear + BufferPos,
						bytes );
				}
			}
			BufferPos += bytes;
			if( Fragments[BufferCount].bytes < BufferPos )
				Fragments[BufferCount].bytes = BufferPos;
			bytes = 0;
		}
	}
	if( Fragments[BufferCount].status == _BUF_EMPTY_ )
        VOC_InsertQueue( BufferCount );     /*  Ñe¸ •A·¡Èa §iœâ·¡ ÇAµA
                                            ¹¥¸Ða»¡ ´g·a¡e ÂˆaÐe”a.   */
	if( BufferPos >= Fragments[BufferCount].length ) {
		BufferPos = 0;
		BufferCount = ++BufferCount % FragmentCount;
    }                                       /*  •A·¡Èa §iœâ· {·¡¡e ”a·q
                                            •A·¡Èa §iœâ·i ˆaŸ¡Ç¡•¡¢ Ðe”a.  */
}

/*
**  ÑÁ·©µA¬á Ðe ¤a·¡ËaŸi ˆa¹aµ¥”a.
*/
unsigned char VOC_readbyte(int fd)
{
	unsigned char onebyte;
	_read( fd, &onebyte, 1 );
	return onebyte;
}

/*
**  VOC ÑÁ·©µA¬á ·q¬÷ •A·¡Èa e·i Àx´a´á ·q¬÷ •A·¡Èa §iœâµA ¸á¸wÐe”a.
*/
int VOC_readvoice(char *filename)
{
	int fd,ended;
	unsigned int bytes;
	unsigned long blocklength;
	unsigned char command;
	fd = _open( filename, O_RDONLY );
	if( fd == -1 ) return -1;
	bytes = _read( fd, TempBuffer, 22 );
	lseek( fd, * (unsigned int *)(TempBuffer + 20), SEEK_SET );
	ended = 0;
	while( !ended ) {
		command = VOC_readbyte( fd );
		switch( command ) {
		case 0:         /*      End of voice file..     */
			ended = 1;
			break;
		case 1:         /*      Voice data..            */
		case 2:         /*      Continuous...           */
			Long.bytes[0] = VOC_readbyte( fd );
			Long.bytes[1] = VOC_readbyte( fd );
			Long.bytes[2] = VOC_readbyte( fd );
			Long.bytes[3] = 0;
			if( command == 1 ) {
				Long.onelong -= 2L;			/*      exclude 2 byte  */
				VOC_readbyte( fd );         /*      Sampling Rate   */
				VOC_readbyte( fd );         /*      Packe Mode.     */
			}
			while( Long.onelong ) {
				if( Long.onelong > MAXBUFSIZE )
					bytes = _read( fd, TempBuffer, MAXBUFSIZE );
				else bytes = _read( fd, TempBuffer, Long.onelong );
				VOC_savedata( TempBuffer, bytes );
				Long.onelong -= bytes;
			}
			break;
		case 3:         /*      Silent voices..         */
		case 4:         /*      Mark...                 */
		case 5:         /*      String..                */
		case 6:         /*      Block Start..           */
		case 7:         /*      Block End..             */
			_close( fd );
			return -1;
		}
	}
	_close( fd );
	return 0;
}

/*
**  ·q¬÷·i Â‰bÐa“e žË¥.
*/
int VOC_Play(char *filename)
{
	if( VoiceHardWare == NO_VOICE ) return -1;
	if( VoiceFlag == VOICE_IDLE ) BufferCount = 0, BufferPos = 0;
        /*  Ñe¸ ·q¬÷·¡ Â‰bº—·¡ ´a“¡œa¡e Àá·q •A·¡Èa §iœâ·i ˆaŸ¡Ç¥”a.  */
	else {
		BufferCount = VOC_QueueTop();
		BufferPos = VOC_GetDMACount();
        /*  Ñe¸ ·q¬÷ Â‰bº—·¡¡e Â‰bº—·¥ •A·¡Èa §iœâ· ¤åÑ¡µÁ ¶áÃ¡Ÿi
            ´i´a…”a.       */
	}
	if( VOC_readvoice( filename ) == -1 ) return -1;
        /*  VOC ÑÁ·©·i ·ª´áµ¥”a.        */
	if( VoiceFlag == VOICE_IDLE ) {
		VOC_sayDMAvoice( Fragments[FragmentQueue[QueueRear]].linear,
			Fragments[FragmentQueue[QueueRear]].bytes );
        /*  Ñe¸ ·q¬÷·¡ Â‰bº—·¡ ´a“¡¡e ·ª´áµ¥ •A·¡ÈaŸi Â‰bÐe”a.   */
	}
	return 0;
}

/*
**  ¬a§i·i ¶áÐe ·q¬÷ ·¥ÈáœóËa žË¥
*/
void far interrupt SBLHandler(void)
{
	int i,j;
	disable();
    inportb( SBLBaseIO + 0xe );     /*  acknowledge interrupt */
    SBL_Command( HALT_DMA );        /*  DMAŸi º—»¡Ða•¡¢ Ðe”a.  */
    j = VOC_QueueTop();             /*  ÇAµA¬á Â‰bº—·¡´ö”å •A·¡Èa §iœâ     */
    VOC_DeleteQueue();              /*  ¸å­··¡ {e §iœâ·i ¹AˆáÐe”a.        */
	if( VOC_IsQueueEmpty() ) VoiceFlag = VOICE_IDLE;
                                    /*  ”á ·¡¬w §iœâ·¡ ´ô·a¡e ¹·ža          */
	else {
		i = VOC_QueueTop();
		VOC_sayDMAvoice( Fragments[i].linear, Fragments[i].bytes );
                                    /*  Â‰bÐ´¡ Ði •A·¡Èa §iœâ·i ¸¬—      */
	}
	memset( Fragments[j].address, 0, Fragments[j].length );
                                    /*  ¸å­··¡ {e”å §iœâ·i 0·a¡ À¶¡º…”a.
                                        0·a¡ À¶»¡ ´g·a¡e aº—µA ·q¬÷·i
                                        ¬ã·i ˜, ¸s·q·¡ ¬ã·© ®•¡ ·¶”a.     */
    outportb( 0x20, 0x20 );         /*  8259A PICµA‰A Ða—a¶Á´á ·¥ÈáœóËaˆa
                                        ¹·žaÐaµv·q·i ´iŸ¥”a.                */
	enable();
}

/*
**  µeºº—·¥ ·q¬÷·i ˆw¹A¡ ¸÷»¡ ¯¡Ç¥”a.
*/
int VOC_Silent(void)
{
	if( VoiceHardWare == NO_VOICE || VoiceFlag == VOICE_IDLE ) return -1;
	SBL_Command( HALT_DMA );
	VoiceFlag = VOICE_IDLE;
	return 0;
}

/*
**  ·q¬÷·¡ —¡»¡Èa·¡»·–E ¬‘Ïi ºÌa®Ÿi ¬é¸÷Ðe”a.
*/
void VOC_SetSampleRate(sr)
unsigned int sr;
{
	unsigned char index;
    SBL_Command( FREQ_DIVISER );        /*  ¬a§i ºÌa® ¦…ºˆt ¬é¸÷ */
	index = (unsigned char) (256 - 1000000L / sr);
    SBL_Command( index );
}

/*
**  Â‰b·q¬÷· ¥¡ŸQ·i ¹¡¸éÐe”a.
   ·³bˆt
	 vl : ¹ÁÃb ¥©ŸQˆt (0-15)
	 vr : ¶Ãb ¥©ŸQˆt (0-15)
   ¬a§iÏa¡·¥‰w¶ £¢¬áŸi ·¡¶wÐaµa ¥©ŸQ·i ¹¡¸éÐe”a.
*/
void SBL_PCMVolume(unsigned int vl,unsigned int vr)
{
	int i,vol;
	if( vl > 15 ) vl = 15;
	if( vr > 15 ) vr = 15;
	if( VoiceHardWare == NO_VOICE ) return;
/*
    e´¢ ¬a§i Ïa¡·¥ ‰w¶ ¥©ŸQ ¹¡¸÷ ˆa“w
*/
	setSBLProMixer( SBLPRO_VOICE_VOLUME, vr, vl );
/*       Right Speaker Volume  <---|     |---> Left Speaker Volume */
}

/*
**  Ði”w¤h·e ˆb •A·¡Èa §iœâ·i DMA ¸å­·ˆa“wÐe •A·¡Èa §iœâ·a¡ a’‰¡
**  º­¡µÁ Ça‹¡Ÿi ‰¬eÐe”a.
*/
void VOC_calcaddr(void)
{
	int i;
	long page,add16;
	long physical;
	unsigned long Address[2];
	unsigned int Length[2];
	unsigned int segment,offset;
	struct _frag *fragment;
	for(FragmentCount=i=0;i<NUMBUFFER;i++) {
		physical = ((long)(FP_OFF(VoiceBuffer[i]))) +
			(((long)(FP_SEG(VoiceBuffer[i]))) << 4);
		page  = ( physical & 0x00FF0000L );
		add16 = ( physical & 0x0000FFFFL );
		Address[0] = physical;
		Length[0] = MAXBUFSIZE;
		fragment = &Fragments[FragmentCount];
		if( add16 + MAXBUFSIZE > 0x10000L )
		{
			Address[0] = page + 0x10000L;
			Length[0] = ( (physical + MAXBUFSIZE) & 0xFFFF );
			Length[1] = MAXBUFSIZE - Length[0];
			Address[1] = physical;
			fragment->status = _BUF_EMPTY_;
			segment = Address[1] >> 4;
			offset = Address[1] & 0x000F;
			fragment->address = MK_FP( segment, offset );
			fragment->linear = Address[1];
			fragment->length = Length[1];
			fragment->bytes = 0;
			FragmentCount++, fragment++;
		}
		fragment->status = _BUF_EMPTY_;
		segment = Address[0] >> 4;
		offset = Address[0] & 0x000F;
		fragment->address = MK_FP( segment, offset );
		fragment->linear = Address[0];
		fragment->length = Length[0];
		fragment->bytes = 0;
		FragmentCount++;
	}
}

/*
**  ·q¬÷ •A·¡ÈaŸi ¸á¸wÐi •A·¡Èa §iœâ·i Ði”w¤h“e”a.
*/
int VOC_getmemory(void)
{
	int i,flag;
	for(i=flag=0;i<NUMBUFFER;i++) {
		VoiceBuffer[i] = (char *) malloc( MAXBUFSIZE );
		if( VoiceBuffer[i] == NULL ) flag++;
		else memset( VoiceBuffer[i], 0, MAXBUFSIZE );
	}
    if( flag ) {
		for(i=0;i<NUMBUFFER;i++)
			if( VoiceBuffer[i] ) free( VoiceBuffer[i] );
		return -1;
	}
	return 0;
}

/*
**  VOC ÑÁ·© Â‰b·i ¶áÐe Á¡‹¡ÑÁ ®Ð—.
*/
int VOC_Init(void)
{
	if( SBL_AutoDetect() == -1 ) return -1;
        /*  ¬a¶…—a §iœa¯aÈá Äa—a ˆñ¬a   */
	if( VOC_getmemory() ) return -1;
        /*  ·q¬÷ •A·¡Èa §iœâ·i Ði”w     */
	disable();
	OldHandler = getvect( 0x08 + SBLIRQ );
    setvect( 0x08 + SBLIRQ, SBLHandler );
        /* ¬a§i ·¥ÈáœóËa žË¥ ¬é¸÷ */
	outportb( 0x21, inportb( 0x21 ) & ~(1 << SBLIRQ) );
    VOC_SetSampleRate( SampleRate );
        /* ¬a§i ¬‘ÏiŸ· ºÌa® ¬é¸÷ */
	enable();
	VoiceHardWare = SOUNDBLASTER;
	VOC_SetVolume( VoiceVolume );
	VOC_calcaddr();
	VOC_SetSampleRate( 8000 );
	SBL_Speaker( 1 );
	return 0;
}

/*
**  VOC ÑÁ·© Â‰b·i ¶áÐe Ïa¡‹aœ‘·i ¹·ža¯¡Ç¥”a.
*/
void VOC_Close(void)
{
	int i;
	if( VoiceHardWare == NO_VOICE ) return;
    SBL_Speaker( 0 );       /* ¬a§i ¯aÏ¡ÄáŸi e”a. */
	for(i=0;i<NUMBUFFER;i++) {
		if( VoiceBuffer[i] ) free( VoiceBuffer[i] );
        /*  ¡A¡¡Ÿ¡ Ð¹A     */
	}
	disable();
    setvect( 0x08 + SBLIRQ, OldHandler );   /* ·¥ÈáœóËa ¥BÈáŸi –A•©Ÿ¥”a. */
	if( SBLIRQ != 2 ) outportb( 0x21, inportb( 0x21 ) | (1 << SBLIRQ) );
	enable();
	VoiceFlag = VOICE_IDLE;
}

/*
**  ¬a§i· ¯aÏ¡ÄáŸi Åaˆáa e”a.
*/
void SBL_Speaker(unsigned char flag)
{
	if( flag ) SBL_Command( SBL_SPEAKER_ON );
	else SBL_Command( SBL_SPEAKER_OFF );
}

/*
**  º´á»¥ ¬a¶…—a §iœa¯aÈá· I/O ¤å»¡Ÿi ·¡¶wÐaµa Ÿ¡­[Ðe”a.
*/
int SBL_Reset(int BaseIO)
{
	int i,j;
    outportb( BaseIO + SBL_RESET, SBL_RESET_CMD );
        /* ¬a§iµA Ÿ¡­[ ¡ww´áŸi ¥¡…”a. */
	for(i=0;i<100;i++) j = inportb( BaseIO + SBL_RESET );
    outportb( BaseIO + SBL_RESET, 0 );
        /* ¬a§i Ÿ¡­[ */
	for(i=0;i<1024;i++) {
		if( inportb( BaseIO + SBL_DATA_AVAIL ) & 0x80 ) {
			/* ¬a§i ·¥¯¢ˆt AAhˆa ·ªÓ¡“e»¡ ÑÂ·¥ Ðe”a. */
			for(j=0;j<1024;j++) {
				if( inportb( BaseIO + SBL_READ_DATA ) == 0xAA ) return 1;
			}
			return -1;
		}
	}
	return -1;
}

/*
**  ¬a§iµA ¡ww´áŸi ¥¡“e žË¥
*/
int SBL_sendcommand(D)
unsigned char D;
{
	asm mov dx,SBLBaseIO
	asm add dx,SBL_READ_STATUS
	asm mov cx,2000h
	asm mov bl,D
waitLoop:
	asm in  al,dx
	asm test al,80h
	asm jz  writeCommand
	asm loop waitLoop
	asm mov ax,-1
	asm jmp end
writeCommand:
	asm mov al,bl
	asm out dx,al
	asm mov ax,1
end:
	return(_AX);
}

/*
**  SBL_sendcommand Ÿi ·¡¶wÐaµa ¬a§iµA ¡ww´áŸi ¥¡…”a.
*/
SBL_Command(D)
unsigned char D ;
{
	if( SBL_sendcommand( D ) < 0 ) SBL_CommandError++;
	return 1;
}

/* ¬a§i ·¥ÈáœóËa ¤åÑ¡Ÿi Àx‹¡¶áÐe žË¥ */
void far interrupt _int2(void)
{
	disable();
	inportb( SBLBaseIO + 0xe );		/* acknowledge interrupt */
	outportb( 0x20, 0x20 );
	SBLIRQ = 2;
	enable();
}

/* ¬a§i ·¥ÈáœóËa ¤åÑ¡Ÿi Àx‹¡¶áÐe žË¥ */
void far interrupt _int5(void)
{
	disable();
	inportb( SBLBaseIO + 0xe );		/* acknowledge interrupt */
	outportb( 0x20, 0x20 );
	SBLIRQ = 5;
	enable();
}

/* ¬a§i ·¥ÈáœóËa ¤åÑ¡Ÿi Àx‹¡¶áÐe žË¥ */
void far interrupt _int7(void)
{
	disable();
	inportb( SBLBaseIO + 0xe );		/* acknowledge interrupt */
	outportb( 0x20, 0x20 );
	SBLIRQ = 7;
	enable();
}

/*
**  ¬a§i I/O ¤å»¡, IRQ ¤åÑ¡, DMA Àé ¸a•· ˆñ¬a
*/
int SBL_AutoDetect(void)
{
	int i,flag;
	int old8259mask;
	void far interrupt (*Oldint2)();	/* ·¥ÈáœóËa 2 ¥¡‰Å¶w */
	void far interrupt (*Oldint5)();	/* ·¥ÈáœóËa 5 ¥¡‰Å¶w */
	void far interrupt (*Oldint7)();	/* ·¥ÈáœóËa 7 ¥¡‰Å¶w */

	VoiceHardWare = SOUNDBLASTER;
	SBLBaseIO = SBLDMAChannel = SBLIRQ = -1;
/* 220h µA¬á 270h Œa»¡ ¬a§i·i Ÿ¡­[¯¡Ç¡¡e¬á BaseIO¤å»¡Ÿi Àx“e”a. */
	flag = 0;
	for(i=0x210;i<=0x270;i+=0x10) {
		if( SBL_Reset( i ) == 1 ) {
			flag = 1;
			SBLBaseIO = i;
			break;
		}
	}
	if( flag == 0 ) return -1;
	Oldint2 = getvect( 0x8 + 2 );
	setvect( 0x8 + 2, _int2 );
	Oldint5 = getvect( 0x8 + 5 );
	setvect( 0x8 + 5, _int5 );
	Oldint7 = getvect( 0x8 + 7 );
	setvect( 0x8 + 7, _int7 );
/* ¬a§i·¡ ¬a¶wÐa“e IRQ 2,5,7· ·¥ÈáœóËaŸi ˆa“wÐa‰A Ðe”a. */
	old8259mask = inportb( 0x21 );
	outportb( 0x21, 0x5b );	/* 0101 1011 */
/* ·¥ÈáœóËaŸi Àx‹¡ ¶áÐ¬á ”á£¡ ·¥ÈáœóËaŸi ¤i¬—¯¡Ç¡“e ¡ww·i ¥¡…”a. */
	SBL_Command( 0xf2 );	/* interrupt request */
	waitmSec( 400 );		/* ·¥ÈáœóËaˆa ¤i¬—Ði˜Œa»¡ 400 £©Ÿ¡Á¡ ‹¡”aŸ¥”a. */
	SBL_Speaker( 0 );		/* speaker off */
	VOC_SetSampleRate( 8000 );
/* DMA Àé·i Àx‹¡¶áÐ¬á ¬a§i·¡ ¬a¶wÐa“e DMA Àé 1,3·i ·¡¶w ·q¬÷ ¤i¬— */
	DMA_Run( 0x30000L, 100, 1, 1 );
	DMA_Run( 0x30000L, 100, 3, 1 );
	SBL_Command( DMA_8BIT_DAC );
	SBL_Command( 2 );
	SBL_Command( 0 );
	waitmSec( 400 );
/* ¬éÃ¡–E DMA Àé· Äa¶…Èáˆt·e 3 ˆq­¡Ðe”a. */
	if( DMA_GetDMACounter( 3 ) == 97 ) SBLDMAChannel = 3;
	if( DMA_GetDMACounter( 1 ) == 97 ) SBLDMAChannel = 1;
	SBL_Command( HALT_DMA );
/* ·¥ÈáœóËa ¥¢Šá */
	outportb( 0x21, old8259mask );
	setvect( 0x8 + 2, Oldint2 );
	setvect( 0x8 + 5, Oldint5 );
	setvect( 0x8 + 7, Oldint7 );
	if( (SBLDMAChannel != -1) && (SBLIRQ != -1) ) return 1;
	else return -1;
}

/*
**  £©Ÿ¡Á¡ ”e¶á¡ ¯¡ˆe »¡µe·i Ðe”a. (AT ·¡¬wµA¬á e ˆa“w)
**  mSec : £©Ÿ¡Á¡ 1000mSec -> 1Á¡
*/
void waitmSec(mSec)
unsigned int mSec;
{
	long tick;
	tick = (32768L * (long) mSec) / 1000L;
		/* Á¡”e¶áŸi Ìé¯a ”e¶á¡ ¤aŽ…”a. */
/*
   |-| |-| |-| |-| |-| |-| |-| |-| |   <- 61h ¤å»¡ §¡Ëa 4
   | |_| |_| |_| |_| |_| |_| |_| |_|
			Ðeº‹¡ 32Khz
*/
	for(;tick>0;tick--) {
		while( inportb( 0x61 ) & 0x10 ) ;
		while( !(inportb( 0x61 ) & 0x10) ) ;
	}
}

/*
**  ·q¬÷ ÑÁ·© Â‰b· ·qœ··i ¬é¸÷Ðe”a.
*/
void VOC_SetVolume(unsigned int vol)
{
	if( vol > 15 ) return;
	SBL_PCMVolume( vol, vol );
	VoiceVolume = vol;
}

/*
**  ·q¬÷ ÑÁ·© Â‰b· Ñe¸ ·qœ··i ´i´a…”a.
*/
unsigned int VOC_GetVolume(void)
{
	return VoiceVolume;
}

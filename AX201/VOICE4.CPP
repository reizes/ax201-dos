

#define _BUF_EMPTY_		0
#define _BUF_READY_		1
#define _EMPTY_SLOT_	-1
#define MAXBUFSIZE		16000
#define NUMBUFFER		10
#define QueueSize		(NUMBUFFER * 2)

union _long {
	unsigned int onelong;
	unsigned char bytes[4];
} Long;
struct _frag {
	short int status;
	unsigned char *address;
	unsigned int linear;
	unsigned short int length;
	unsigned short int bytes;
} Fragments[QueueSize];
int FragmentCount;

unsigned short int VoiceVolume=10;
short int FragmentQueue[QueueSize];   /* �q���i �b�i �A���a �i��i�� �A */
short int QueueFront=0,QueueRear=0;
static void (__interrupt __far *OldHandler)();	/* �a�i ������a ���Ŷw */
static void __interrupt __far SBLHandler();
char *VoiceBuffer[NUMBUFFER];
char TempBuffer[MAXBUFSIZE];
short int BufferCount,BufferPos;      /* �e�� �������� �A���a �i�ⷁ ��ѡ�� ��á  */
int Invalid=0;
int SBL_CommandError=0;


int VOC_IsQueueEmpty(void)
{
	return (QueueFront == QueueRear);
}

int VOC_IsQueueFull(void)
{
	return (((QueueFront + 1) % QueueSize) == QueueRear);
}

int VOC_QueueTop(void)
{
	if( VOC_IsQueueEmpty() ) return -1;
	else return FragmentQueue[QueueRear];
}

void VOC_InsertQueue(int fragnum)
{
	Fragments[fragnum].status = _BUF_READY_;
	FragmentQueue[QueueFront] = fragnum;
	QueueFront = ++QueueFront % QueueSize;
}

void VOC_DeleteQueue(void)
{
	Fragments[FragmentQueue[QueueRear]].status = _BUF_EMPTY_;
	Fragments[FragmentQueue[QueueRear]].bytes = 0;
	QueueRear = ++QueueRear % QueueSize;
}

unsigned short int VOC_GetDMACount(void)
{
	unsigned short int remainbytes;
	remainbytes = (unsigned short int) DMA_GetDMACounter( SBLDMAChannel );
	if( remainbytes == 0xFFFF ) remainbytes = 0;
	return remainbytes;
}

int VOC_sayDMAvoice(unsigned int address,unsigned short int length)
{
    DMA_DisableDREQ(SBLDMAChannel);     /*  ��� DMA�i ������ǥ�a.  */
	if( DMA_Run( address, length, SBLDMAChannel, 1 ) != 0 ) {
                                        /*  DMA�i �a����ǡ�� �A��a �a�e
                                            �����e�a.               */
		VoiceFlag = VOICE_IDLE;
		return -1;
	}
    SBL_Command( DMA_8BIT_DAC );        /* 8���a DMA DAC �w�w */
    SBL_Command( length & 0xff );       /* �q������ ��� */
	SBL_Command( length >> 8 );
	VoiceFlag = VOICE_BUSY;
	return 0;
}

void VOC_mixvoice(unsigned char *dst,unsigned char *src,unsigned short int length)
{
	unsigned int i;
	short int d1;
	for(i=0;i<length;i++,dst++,src++) {
		d1 = (short int) *dst + (short int) *src;
		d1 >>= 1;
        *dst = d1;          /*  �� �A���a�i ���a�� �a�� 2�� �a�� �t�i
                                ��w�e�a.   */
	}
}

void VOC_savedata(unsigned char *buffer,unsigned short int bytes)
{
	unsigned short int bufpos,gap;
	bufpos = 0;
    while( bytes ) {    /*  ��wЁ�� �i �A���a�a ���e ���e  */
		gap = Fragments[BufferCount].length - BufferPos;
                        /*  �e�� �A���a �i�ⷁ �q�e ���e�i ���e */
        if( bytes > gap ) {     /*  �q�e ���e�� �� ��a�e       */
			VOC_mixvoice(Fragments[BufferCount].address + BufferPos,buffer + bufpos, gap );

			Fragments[BufferCount].bytes = Fragments[BufferCount].length;
                                /*  �q�e ���e�e�q�e �e�� �i��A �a    */
			switch( Fragments[BufferCount].status ) {
			case _BUF_EMPTY_:
				VOC_InsertQueue( BufferCount );
                                /*  �e�� �i�ⷡ �A�A ���e �w�� �a     */
				break;
			case _BUF_READY_:
				if( VOC_QueueTop() == BufferCount ) {
					SBL_Command( HALT_DMA );
					VOC_sayDMAvoice( Fragments[BufferCount].linear + BufferPos,
						gap );
                }               /*  �e�� �i�ⷡ �A�A �����a�e, DMA �孷����
                                    �a����a�a�� �����a�� �a�� �孷�e�a.    */
			}
			BufferPos = 0;
			BufferCount = ++BufferCount % FragmentCount;
                                /*  �a�q �A���a �i��i �a��ǥ�a.    */
            bytes -= gap, bufpos += gap;
		}
        else {                  /*  �q�e ���e�� ���a�a�e          */
			VOC_mixvoice( Fragments[BufferCount].address + BufferPos,
				buffer + bufpos, bytes );
                                /*  ���� ��w�e�a.                  */
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
        VOC_InsertQueue( BufferCount );     /*  �e�� �A���a �i�ⷡ �A�A
                                            �����a�� �g�a�e �a�e�a.   */
	if( BufferPos >= Fragments[BufferCount].length ) {
		BufferPos = 0;
		BufferCount = ++BufferCount % FragmentCount;
    }                                       /*  �A���a �i�ⷁ �{���e �a�q
                                            �A���a �i��i �a��ǡ���� �e�a.  */
}

unsigned char VOC_readbyte(int fd)
{
	unsigned char onebyte;
	onebyte=read(fd,&onebyte,1);
	return onebyte;
}

/*
**  VOC �����A�� �q�� �A���a�e�i �x�a���� �q�� �A���a �i��A ��w�e�a.
*/
int VOC_readvoice(char *filename)
{
	short int ended;
int fd;
	unsigned short int bytes;
	unsigned int blocklength;
	unsigned char command;
	fd = open( filename,O_RDONLY);
Long.onelong=filelength(fd);
	if( fd == -1 ) return -1;
	bytes = read(fd,TempBuffer, 22 );
Long.onelong-=22;
	lseek( fd, *(unsigned int *)(TempBuffer+20), SEEK_SET );
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
Long.onelong-=3;
			if( command == 1 ) {
				Long.onelong -= 2;			/*      exclude 2 byte  */
				VOC_readbyte( fd );         /*      Sampling Rate   */
				VOC_readbyte( fd );         /*      Packe Mode.     */
			}
			while( Long.onelong ) {
				if( Long.onelong > MAXBUFSIZE )
					bytes = read(fd,TempBuffer, MAXBUFSIZE);
				else bytes = read( fd,TempBuffer, Long.onelong );
				VOC_savedata((unsigned char *)TempBuffer, bytes );
				Long.onelong -= bytes;
			}
			break;
		case 3:         /*      Silent voices..         */
		case 4:         /*      Mark...                 */
		case 5:         /*      String..                */
		case 6:         /*      Block Start..           */
		case 7:         /*      Block End..             */
			close( fd );
			return -1;
		}
	}
	close( fd );
	return 0;
}

int VOC_Play(char *filename)
{
	if( VoiceHardWare == NO_VOICE ) return -1;
	if( VoiceFlag == VOICE_IDLE ) BufferCount = 0, BufferPos = 0;
        /*  �e�� �q���� �b���� �a���a�e ��q �A���a �i��i �a��ǥ�a.  */
	else {
		BufferCount = VOC_QueueTop();
		BufferPos = VOC_GetDMACount();
	}

	if( VOC_readvoice( filename ) == -1 ) return -1;
/*
	if( VoiceFlag == VOICE_IDLE ) {
		VOC_sayDMAvoice( Fragments[FragmentQueue[QueueRear]].linear,
			Fragments[FragmentQueue[QueueRear]].bytes );
	}*/
	return 0;
}

static void  __interrupt __far SBLHandler(void)
{
	short int i,j;
	_disable();
    inp( SBLBaseIO + 0xe );     /*  acknowledge interrupt */
    SBL_Command( HALT_DMA );        /*  DMA�i �����a���� �e�a.  */
    j = VOC_QueueTop();             /*  �A�A�� �b�������� �A���a �i��     */
    VOC_DeleteQueue();              /*  �孷�� �{�e �i��i �A���e�a.        */
	if( VOC_IsQueueEmpty() ) VoiceFlag = VOICE_IDLE;
                                    /*  �� ���w �i�ⷡ ���a�e ���a          */
	else {
		i = VOC_QueueTop();
		VOC_sayDMAvoice( Fragments[i].linear, Fragments[i].bytes );
                                    /*  �bЁ�� �i �A���a �i��i ����      */
	}
	memset( Fragments[j].address, 0, Fragments[j].length );
                                    /*  �孷�� �{�e�� �i��i 0�a�� �������a.
                                        0�a�� ������ �g�a�e �a���A �q���i
                                        ��i ��, �s�q�� �㷩 ���� ���a.     */
    outp( 0x20, 0x20 );         /*  8259A PIC�A�A �a�a���� ������a�a
                                        ���a�a�v�q�i �i���a.                */
	_enable();
}

int VOC_Silent(void)
{
	if( VoiceHardWare == NO_VOICE || VoiceFlag == VOICE_IDLE ) return -1;
	SBL_Command( HALT_DMA );
	VoiceFlag = VOICE_IDLE;
	return 0;
}

void VOC_SetSampleRate(unsigned short int sr)
{
	unsigned char index;
    SBL_Command( FREQ_DIVISER );        /*  �a�i ���a�� �����t ��� */
	index = (unsigned char) (256 - 1000000 / sr);
    SBL_Command( index );
}

void SBL_PCMVolume(unsigned short int vl,unsigned short int vr)
{
	short int i,vol;
	if( vl > 15 ) vl = 15;
	if( vr > 15 ) vr = 15;
	if( VoiceHardWare == NO_VOICE ) return;
	setSBLProMixer( SBLPRO_VOICE_VOLUME, vr, vl );

}

void VOC_calcaddr(void)
{
	short int i;
	int page,add16;
	int physical;
	unsigned int Address[2];
	unsigned short int Length[2];
	unsigned short int segment,offset;
	struct _frag *fragment;
	for(FragmentCount=i=0;i<NUMBUFFER;i++) {
		physical = ((int)(FP_OFF(VoiceBuffer[i]))) +
			(((int)(FP_SEG(VoiceBuffer[i]))) << 4);
		page  = ( physical & 0x00FF0000 );
		add16 = ( physical & 0x0000FFFF );
		Address[0] = physical;
		Length[0] = MAXBUFSIZE;
		fragment = &Fragments[FragmentCount];
		if( add16 + MAXBUFSIZE > 0x10000 )
		{
			Address[0] = page + 0x10000;
			Length[0] = ( (physical + MAXBUFSIZE) & 0xFFFF );
			Length[1] = MAXBUFSIZE - Length[0];
			Address[1] = physical;
			fragment->status = _BUF_EMPTY_;
			segment = Address[1] >> 4;
			offset = Address[1] & 0x000F;
			fragment->address =(unsigned char*)MK_FP( segment, offset );
			fragment->linear = Address[1];
			fragment->length = Length[1];
			fragment->bytes = 0;
			FragmentCount++, fragment++;
		}
		fragment->status = _BUF_EMPTY_;
		segment = Address[0] >> 4;
		offset = Address[0] & 0x000F;
		fragment->address =(unsigned char*) MK_FP( segment, offset );
		fragment->linear = Address[0];
		fragment->length = Length[0];
		fragment->bytes = 0;
		FragmentCount++;
	}
}

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

int VOC_Init(void)
{
  if( SBL_AutoDetect() == -1 ) return -1;
  if( VOC_getmemory() ) return -1;

 _disable();
 OldHandler =_dos_getvect( 0x08 + SBLIRQ );
 _dos_setvect( 0x08 + SBLIRQ, SBLHandler );
 outp( 0x21, inp( 0x21 ) & ~(1 << SBLIRQ) );
 VOC_SetSampleRate( SampleRate );
 _enable();
 VoiceHardWare = SOUNDBLASTER;
 VOC_SetVolume( VoiceVolume );
 VOC_calcaddr();
 VOC_SetSampleRate( 8000 );
 SBL_Speaker( 1 );
 return 0;
}

void VOC_Close(void)
{
	int i;
	if( VoiceHardWare == NO_VOICE ) return;
    SBL_Speaker( 0 );       /* �a�i �aϡ��i �e�a. */
	for(i=0;i<NUMBUFFER;i++) {
		if( VoiceBuffer[i] ) free( VoiceBuffer[i] );
        /*  �A���� Ё�A     */
	}
	_disable();
    _dos_setvect( 0x08 + SBLIRQ, OldHandler );   /* ������a �B��i �A�����a. */
	if( SBLIRQ != 2 ) outp( 0x21, inp( 0x21 ) | (1 << SBLIRQ) );
	_enable();
	VoiceFlag = VOICE_IDLE;
}

void SBL_Speaker(unsigned char flag)
{
	if( flag ) SBL_Command( SBL_SPEAKER_ON );
	else SBL_Command( SBL_SPEAKER_OFF );
}

int SBL_Reset(short int BaseIO)
{
	short int i,j;
    outp( BaseIO + SBL_RESET, SBL_RESET_CMD );
        /* �a�i�A ���[ �w�w��i �����a. */
	for(i=0;i<100;i++) j = inp( BaseIO + SBL_RESET );
    outp( BaseIO + SBL_RESET, 0 );
        /* �a�i ���[ */
	for(i=0;i<1024;i++) {
		if( inp( BaseIO + SBL_DATA_AVAIL ) & 0x80 ) {
			/* �a�i �����t AAh�a ��ӡ�e�� �·� �e�a. */
			for(j=0;j<1024;j++) {
				if( inp( BaseIO + SBL_READ_DATA ) == 0xAA ) return 1;
			}
			return -1;
		}
	}
	return -1;
}


/*
**  SBL_sendcommand �i ���w�a�a �a�i�A �w�w��i �����a.
*/
SBL_Command(unsigned char D)
{
	if( SBL_sendcommand( D ) < 0 ) SBL_CommandError++;
	return 1;
}

void __interrupt __far _int2(void)
{
	_disable();
	inp( SBLBaseIO + 0xe );		/* acknowledge interrupt */
	outp( 0x20, 0x20 );
	SBLIRQ = 2;
 _enable();
}
	void __interrupt __far _int5(void)
 {
	_disable();
	inp( SBLBaseIO + 0xe );		/* acknowledge interrupt */
	outp( 0x20, 0x20 );
	SBLIRQ = 5;
	_enable();
}

/* �a�i ������a ��ѡ�i �x�����e ��˥ */
void __interrupt __far _int7(void)
{
	_disable();
	inp( SBLBaseIO + 0xe );		/* acknowledge interrupt */
	outp( 0x20, 0x20 );
	SBLIRQ = 7;
	_enable();
}

int SBL_AutoDetect(void)
{
	short int i,flag;
	short int old8259mask;
	void __interrupt __far (*Oldint2)();	/* ������a 2 ���Ŷw */
	void __interrupt __far (*Oldint5)();	/* ������a 5 ���Ŷw */
	void __interrupt __far (*Oldint7)();	/* ������a 7 ���Ŷw */

	VoiceHardWare = SOUNDBLASTER;
	SBLBaseIO = SBLDMAChannel = SBLIRQ = -1;
/* 220h �A�� 270h �a�� �a�i�i ���[��ǡ�e�� BaseIO�廡�i �x�e�a. */
	flag = 0;
	for(i=0x210;i<=0x270;i+=0x10) {
		if( SBL_Reset( i ) == 1 ) {
			flag = 1;
			SBLBaseIO = i;
			break;
		}
	}
	if( flag == 0 ) return -1;
	Oldint2 = _dos_getvect( 0x8 + 2 );
	_dos_setvect( 0x8 + 2, _int2 );
	Oldint5 = _dos_getvect( 0x8 + 5 );
	_dos_setvect( 0x8 + 5, _int5 );
	Oldint7 = _dos_getvect( 0x8 + 7 );
	_dos_setvect( 0x8 + 7, _int7 );
/* �a�i�� �a�w�a�e IRQ 2,5,7�� ������a�i �a�w�a�A �e�a. */
	old8259mask = inp( 0x21 );
	outp( 0x21, 0x5b );	/* 0101 1011 */
/* ������a�i �x�� ��Ё�� �ᣡ ������a�i �i����ǡ�e �w�w�i �����a. */
	SBL_Command( 0xf2 );	/* interrupt request */
	waitmSec( 400 );		/* ������a�a �i���i���a�� 400 ������ ���a���a. */
	SBL_Speaker( 0 );		/* speaker off */
	VOC_SetSampleRate( 8000 );
/* DMA ����i �x����Ё�� �a�i�� �a�w�a�e DMA ���� 1,3�i ���w �q�� �i�� */
	DMA_Run( 0x30000L, 100, 1, 1 );
	DMA_Run( 0x30000L, 100, 3, 1 );
	SBL_Command( DMA_8BIT_DAC );
	SBL_Command( 2 );
	SBL_Command( 0 );
	waitmSec( 400 );
/* ��á�E DMA ���鷁 �a����t�e 3 �q���e�a. */
	if( DMA_GetDMACounter( 3 ) == 97 ) SBLDMAChannel = 3;
	if( DMA_GetDMACounter( 1 ) == 97 ) SBLDMAChannel = 1;
	SBL_Command( HALT_DMA );
/* ������a ���� */
	outp( 0x21, old8259mask );
	_dos_setvect( 0x8 + 2, Oldint2 );
	_dos_setvect( 0x8 + 5, Oldint5 );
	_dos_setvect( 0x8 + 7, Oldint7 );
	if( (SBLDMAChannel != -1) && (SBLIRQ != -1) ) return 1;
	else return -1;
}

void waitmSec(unsigned short int mSec)
{
	int tick;
	tick = (32768L * (int) mSec) / 1000L;
	for(;tick>0;tick--) {
		while( inp( 0x61 ) & 0x10 ) ;
		while( !(inp( 0x61 ) & 0x10) ) ;
	}
}

void VOC_SetVolume(unsigned short int vol)
{
	if( vol > 15 ) return;
	SBL_PCMVolume( vol, vol );
	VoiceVolume = vol;
}

unsigned int VOC_GetVolume(void)
{
	return VoiceVolume;
}

#include <dos.h>

/*
   ¬a§i Ñ¡ÑÅ¶w DMA ·¡¶w ·q¬÷ Â‰b Ïa¡‹aœ‘ v1.0

   º¥e¸wÃ¡  ¸å­·¶aŠ ¡¡—aŸi ·¡¶wÐaµa ¬a§iµA¬á PCM ·i ¤i¬— ¯¡Ç¥”a.

               DMA ¶aŠ(¬‘ÏiŸ· ºÌa®µA  x‰A)
            <----------------------------------
   HOST                                           ¬a§i Ñ¡ÑÅ Äa—a
            ---------------------------------->
                   •A·¡Èa ¸å­·                          |
                                                        |--> ·q¬÷ Â‰b
*/

#include "dmaIO.h"

#define DMA0_BASE    0x00  /* DMA 0 ¥A·¡¯a ´á—aA¯a */
#define DMA1_BASE    0xC0  /* DMA 1 ¥A·¡¯a ´á—aA¯a */

#define DMA_STATUS   0x08  /* DMA ¬wÈ ´á—aA¯a */
#define DMA_COMMAND  0x08  /* DMA ¡ww ´á—aA¯a */
#define DMA_MASK     0x0A  /* DMA ¶aŠ MASK ´á—aA¯a */
#define DMA_MODE     0x0B  /* DMA ¸å­· ¡¡—a ´á—aA¯a */
#define DMA_FF_CLR   0x0C  /* DMA ¦ (High/low Byte) Flip-Flop Clear ´á—aA¯a */

#define DMA_CHANNEL  0x00  /* DMA Àé ¡A¡¡Ÿ¡ ´á—aA¯a */
#define DMA_RUN_BYTE 0x01  /* DMA Àé ¡A¡¡Ÿ¡ Äa¶…Èá ´á—aA¯a */

#define CMD_DMA_MASK_SET  0x04 /* DMA DREQ MASK SET ¡ww´á */
#define CMD_DMA_MASK_CLR  0x00 /* DMA DREQ MASK CLEAR ¡ww´á */
#define CMD_DMA_SINGLE_WRITE     0x44 /* º¥e¸wÃ¡ -> Memory ˆe ¸å­· ¡ww´á */
#define CMD_DMA_SINGLE_READ      0x48 /* Memory -> º¥e¸wÃ¡ˆe ¸å­· ¡ww´á */
                                      
/* AT 24 §¡Ëa ¸é”  ´á—aA¯aº— ¬w¶á 8 §¡Ëa ¸á¸w I/O ´á—aA¯a */
static unsigned char DMA_ChannelPage[4] = { 0x87,0x83,0x81,0x82 };

/*
   DMA ·¡¶w •A·¡Èa  ¸å­· žË¥

   aptr : ¡A¡¡Ÿ¡· ¸é” ´á—aA¯a
		  ­A‹a åËaµÁ µ¡Ïa­[ Ñw¯¢· ´á—aA¯aˆa ´a“¡‰¡ 32§¡Ëa ¸é” ´á—aA¯a·±
		  ( ÑÂ¸w ¡A¡¡Ÿ¡· µwµb•¡ ˆa“wÐa”a.)
   length : ¸å­·Ði ¤a·¡Ëa®  ( ÂA” 65535ˆ )
   channel : ·¡¶wÐi DMA Àé
   dir  : ¸å­·Ði ¤wÐ·
		  0 ·©‰w¶ º¥e¸wÃ¡ -> HOST MEMORY
		  1 ·©‰w¶ HOST MEMORY -> º¥e¸wÃ¡

   DMA ¸å­· ¡¡—a“e º¥e¸wÃ¡ ¸å­·¶aŠ¡¡—a·¡”a.

   Ÿ¡Èåˆt
	   (-1) : Àé· ˆt·¡ »¡¸÷Ðe ¤ñ¶áŸi ñ´ö”a. (ˆa¶w Àé 0-3)
	   (-2) : ¸å­·Ði ¤a·¡Ëa®ˆa ´á—aA¯a µ¡¤áÏi¡¶Ÿi ¤i¬— ¯¡Ç¥”a.
		 0  : ¸÷¬w¸â·a¡ ®Ð—·¡ –A´ö”a.

*/

int DMA_Run(unsigned long aptr,unsigned int length,unsigned char channel,
	unsigned char dir)
{
	unsigned char page,low16Add,high16Add;
	unsigned int  DMAPort,cmd;
	long avail;
    if( length == 0 ) return -1;    /*  DMA ¸å­·œ··i ˆñ¬a  */
    if( channel > 3 ) return -1;    /*  Àé ¤åÑ¡Ÿi ˆñ¬a   */

/*
	32 §¡Ëa ¸é” ´á—aA¯aµA¬á ÍA·¡»¡ 8 §¡Ëa ¬wÐa¶á 8 §¡Ëa ´á—aA¯a ÂÂ‰

   31             24              16                8             0
   |---------------|---------------|---------------|---------------|
   | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
   +---------------|---------------|---------------|---------------|
				   \---- page -----/\- high16Add --/\- low16Add  --/
						  |
	   Page Select Port --|               DMA Base Address Port

   32§¡Ëa ¸é” ´á—aA¯aº— ÂA¬w¶á  8 §¡Ëa“e ¢¯¡.
   ˆa¶w ´á—aA¯a“e 24§¡Ëa¡ 16MByte µwµb·i Îa¯¡Ði® ·¶·q
*/
	page = (unsigned char) (aptr >> 16);
	low16Add  = (unsigned char) (aptr & 0xFF);
	high16Add = (unsigned char) ((aptr >> 8) & 0xFF);
        /*  ÍA·¡»¡, ´á—aA¯a ¬w¶á ¤a·¡Ëa, Ða¶á ¤a·¡ËaŸi ‰¬e    */

/*
   DMA ÄåËa©œáˆa 16§¡Ëa· ´á—aA¯a ¤ñ¶áµA¬á ¸å­··¡ ˆa“wÐa£a¡ IBM PC·
   32 §¡Ëa ´á—aA¯a µwµb·i Ði”wÐi® ´ô·a£a¡, ¬w¶á 8 §¡ËaŸi ÍA·¡»¡¡ ˜a¡
   ›´á‘A´á ·¡¢…¹AŸi Ð‰iÐe”a.
   ¸å­·º—µA“e ÍA·¡»¡ ˆt·i »wˆa ¯¡Ç©® ´ô·a£a¡ ¸å­·Ða“e •¡º—µA ÍA·¡»¡Ÿi
   »wˆa ¯¡Åa´¡ Ði‰w¶µA“e  ¸i¡µ–E ‰i‰Áˆa ¤i¬—Ðe”a.
   µŸi —i´á ¸é”´á—aA¯a 0x3B000 µA ¸á¸w–E ·q¬÷•A·¡Èa· ‹©·¡ˆa 0xC000 ·¡¡e
   ¸é”´á—aA¯a 0x3BC00 - 0x48FFF · ¶w·i ¸å­·Ð´¡ Ða£a¡ ÍA·¡»¡ˆa 3µA¬á
   4¡ ¤aŽå”a. ·¡œáÐe ‰w¶“e ¸å­··¡ ¦‰ˆa“wÐa”a.
   ¸å­··¡ ˆa“wÐeˆaŸi ˆñ¬a
*/
	avail = (unsigned long) (0x10000L - (aptr & 0xFFFFL));
	if( avail < length ) return -2;
        /*  Ñe¸ ´á—aA¯aµA¬á ÂA” ¸å­· ˆa“wÐe •A·¡Èaˆa ¸å­·Ð´¡ Ði •A·¡Èa¥¡”a
            ¸â”a¡e ¸å­·¦‰ˆa“wÐa”a.  */
    if( dir ) cmd = CMD_DMA_SINGLE_READ;    /*  ·ª‹¡    */
    else cmd = CMD_DMA_SINGLE_WRITE;        /*  ™¡“e ³a‹¡   */
	cmd += channel;
	DMAPort = channel << 1;
	outportb( DMA_ChannelPage[channel], page );	/* Àé Page Address Set */
	outportb( DMA_FF_CLR, 0 );	/* DMA ¦ ¬w/Ða¶á ¬åÈ‚ Flip-Flop Reset */
	outportb( DMAPort, low16Add );		/* DMA Base Low  8 Bit Address Set */
	outportb( DMAPort, high16Add );		/* DMA Base High 8 Bit Address Set */
	DMAPort++;
	outportb( DMAPort, length & 0xFF );	/* DMA Base Low  8 Bit Counter Set */
	outportb( DMAPort, length >> 8 );	/* DMA Base High 8 Bit Counter Set */
	outportb( DMA_MODE, cmd );			/* DMA Mode Ÿi Single Mode ¡ ­AË· */
										/* Address »wˆa ¤wÐ· */
	outportb( DMA_MASK, CMD_DMA_MASK_CLR + channel );
										/* DMA Request Enable */
	return 0;
}

/*
   º¥e¸wÃ¡· DMA ¸å­·¶aŠŸi ¦‰ˆa“wÐa‰A Ðe”a.

   channel : DMA Àé

   Ÿ¡Èåˆt  : 0 ¸÷¬w ¹·ža
			-1 DMA Àé· ˆt·¡ »¡¸÷Ðe ˆt·i ñ´ö·q

   +-------------------------------+
   | X | X | X | X | X | 2 | 1 | 0 |
   |-------------------|-|-|-------|
	\__________________/ | \_______/
	   Don't Care Bits   |     |
						 |     |   |---  00 : Select DMA Channel 0
						 |     |---|---  01 : Select DMA Channel 1
   0 : Disable DMA Request         |---  10 : Select DMA Channel 2
   1 : Enable  DMA Request         |---  11 : Select DMA Channel 3
*/
int DMA_DisableDREQ(unsigned char channel)
{
	if( channel > 3 ) return -1;
	outportb( DMA_MASK, CMD_DMA_MASK_SET + channel );
	return 0;
}

/*
  »¡¸÷Ðe Àé· DMAŸi ˆa“wÐa‰A Ðe”a.

  ·³bˆt : DMA Àé ¤åÑ¡ (0-3)
*/
int DMA_EnableDREQ(unsigned char channel)
{
	if( channel > 3 ) return -1;
	outportb( DMA_MASK, CMD_DMA_MASK_CLR + channel );
	return 0;
}

/*
  »¡¸÷Ðe Àé· DMA Äa¶…Èá ˆt·i ·ª´áµ¥”a

   ·³bˆt : DMA Àé ¤åÑ¡ (0-3)
   Ÿ¡Èåˆt : DMA Äa¶…Èáˆt
*/
unsigned int DMA_GetDMACounter(unsigned char channel)
{
	unsigned int low,high,DMAPort;
	if( channel > 3 ) return -1;
	outportb( DMA_FF_CLR, 0 );		/* DMA ¦ ¬w/Ða¶á ¬åÈ‚ Flip-Flop Reset */
	DMAPort = (channel << 1) + 1;	/* I/O ´á—aA¯a ‰¬e */
	low  = inportb( DMAPort );		/* DMA Äa¶…Èá Ða¶á 8 §¡Ëa */
	high = inportb( DMAPort );		/* DMA Äa¶…Èá ¬w¶á 8 §¡Ëa */
	return (low | (high << 8));
}

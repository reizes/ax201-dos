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

int DMA_Run(unsigned int aptr,unsigned short int length,unsigned char channel,
	unsigned char dir)
{
	unsigned char page,low16Add,high16Add;
	unsigned int  DMAPort,cmd;
	int avail;
    if( length == 0 ) return -1;    /*  DMA ¸å­·œ··i ˆñ¬a  */
    if( channel > 3 ) return -1;    /*  Àé ¤åÑ¡Ÿi ˆñ¬a   */

	page = (unsigned char) (aptr >> 16);
	low16Add  = (unsigned char) (aptr & 0xFF);
	high16Add = (unsigned char) ((aptr >> 8) & 0xFF);
	avail = (unsigned int) (0x10000 - (aptr & 0xFFFF));
	if( avail < length ) return -2;
    if( dir ) cmd = CMD_DMA_SINGLE_READ;    /*  ·ª‹¡    */
    else cmd = CMD_DMA_SINGLE_WRITE;        /*  ™¡“e ³a‹¡   */
	cmd += channel;
	DMAPort = channel << 1;
	outp( DMA_ChannelPage[channel], page );	/* Àé Page Address Set */
	outp( DMA_FF_CLR, 0 );	/* DMA ¦ ¬w/Ða¶á ¬åÈ‚ Flip-Flop Reset */
	outp( DMAPort, low16Add );		/* DMA Base Low  8 Bit Address Set */
	outp( DMAPort, high16Add );		/* DMA Base High 8 Bit Address Set */
	DMAPort++;
	outp( DMAPort, length & 0xFF );	/* DMA Base Low  8 Bit Counter Set */
	outp( DMAPort, length >> 8 );	/* DMA Base High 8 Bit Counter Set */
	outp( DMA_MODE, cmd );			/* DMA Mode Ÿi Single Mode ¡ ­AË· */
										/* Address »wˆa ¤wÐ· */
	outp( DMA_MASK, CMD_DMA_MASK_CLR + channel );
										/* DMA Request Enable */
	return 0;
}

int DMA_DisableDREQ(unsigned char channel)
{
	if( channel > 3 ) return -1;
	outp( DMA_MASK, CMD_DMA_MASK_SET + channel );
	return 0;
}

int DMA_EnableDREQ(unsigned char channel)
{
	if( channel > 3 ) return -1;
	outp( DMA_MASK, CMD_DMA_MASK_CLR + channel );
	return 0;
}

unsigned int DMA_GetDMACounter(unsigned char channel)
{
	unsigned short int low,high,DMAPort;
	if( channel > 3 ) return -1;
	outp( DMA_FF_CLR, 0 );		/* DMA ¦ ¬w/Ða¶á ¬åÈ‚ Flip-Flop Reset */
	DMAPort = (channel << 1) + 1;	/* I/O ´á—aA¯a ‰¬e */
	low  = inp( DMAPort );		/* DMA Äa¶…Èá Ða¶á 8 §¡Ëa */
	high = inp( DMAPort );		/* DMA Äa¶…Èá ¬w¶á 8 §¡Ëa */
	return (low | (high << 8));
}

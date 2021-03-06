#define DMA0_BASE    0x00  /* DMA 0 �A���a ��a�A�a */
#define DMA1_BASE    0xC0  /* DMA 1 �A���a ��a�A�a */

#define DMA_STATUS   0x08  /* DMA �wȁ ��a�A�a */
#define DMA_COMMAND  0x08  /* DMA �w�w ��a�A�a */
#define DMA_MASK     0x0A  /* DMA �a�� MASK ��a�A�a */
#define DMA_MODE     0x0B  /* DMA �孷 ���a ��a�A�a */
#define DMA_FF_CLR   0x0C  /* DMA ���� (High/low Byte) Flip-Flop Clear ��a�A�a */

#define DMA_CHANNEL  0x00  /* DMA ���� �A���� ��a�A�a */
#define DMA_RUN_BYTE 0x01  /* DMA ���� �A���� �a���� ��a�A�a */

#define CMD_DMA_MASK_SET  0x04 /* DMA DREQ MASK SET �w�w�� */
#define CMD_DMA_MASK_CLR  0x00 /* DMA DREQ MASK CLEAR �w�w�� */
#define CMD_DMA_SINGLE_WRITE     0x44 /* ���e�wá -> Memory �e �孷 �w�w�� */
#define CMD_DMA_SINGLE_READ      0x48 /* Memory -> ���e�wá�e �孷 �w�w�� */

/* AT 24 ���a �锁  ��a�A�a�� �w�� 8 ���a ��w I/O ��a�A�a */
static unsigned char DMA_ChannelPage[4] = { 0x87,0x83,0x81,0x82 };

int DMA_Run(unsigned int aptr,unsigned short int length,unsigned char channel,
	unsigned char dir)
{
	unsigned char page,low16Add,high16Add;
	unsigned int  DMAPort,cmd;
	int avail;
    if( length == 0 ) return -1;    /*  DMA �孷���i ��a  */
    if( channel > 3 ) return -1;    /*  ���� ��ѡ�i ��a   */

	page = (unsigned char) (aptr >> 16);
	low16Add  = (unsigned char) (aptr & 0xFF);
	high16Add = (unsigned char) ((aptr >> 8) & 0xFF);
	avail = (unsigned int) (0x10000 - (aptr & 0xFFFF));
	if( avail < length ) return -2;
    if( dir ) cmd = CMD_DMA_SINGLE_READ;    /*  ����    */
    else cmd = CMD_DMA_SINGLE_WRITE;        /*  ���e �a��   */
	cmd += channel;
	DMAPort = channel << 1;
	outp( DMA_ChannelPage[channel], page );	/* ���� Page Address Set */
	outp( DMA_FF_CLR, 0 );	/* DMA ���� �w/�a�� ��Ȃ Flip-Flop Reset */
	outp( DMAPort, low16Add );		/* DMA Base Low  8 Bit Address Set */
	outp( DMAPort, high16Add );		/* DMA Base High 8 Bit Address Set */
	DMAPort++;
	outp( DMAPort, length & 0xFF );	/* DMA Base Low  8 Bit Counter Set */
	outp( DMAPort, length >> 8 );	/* DMA Base High 8 Bit Counter Set */
	outp( DMA_MODE, cmd );			/* DMA Mode �i Single Mode �� �A˷ */
										/* Address �w�a �wз */
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
	outp( DMA_FF_CLR, 0 );		/* DMA ���� �w/�a�� ��Ȃ Flip-Flop Reset */
	DMAPort = (channel << 1) + 1;	/* I/O ��a�A�a ���e */
	low  = inp( DMAPort );		/* DMA �a���� �a�� 8 ���a */
	high = inp( DMAPort );		/* DMA �a���� �w�� 8 ���a */
	return (low | (high << 8));
}

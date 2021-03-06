#include <dos.h>

/*
   �a�i ѡ�Ŷw DMA ���w �q�� �b �a���a�� v1.0

   ���e�wá  �孷�a�� ���a�i ���w�a�a �a�i�A�� PCM �i �i�� ��ǥ�a.

               DMA �a��(���i�� ���a���A �x�A)
            <----------------------------------
   HOST                                           �a�i ѡ�� �a�a
            ---------------------------------->
                   �A���a �孷                          |
                                                        |--> �q�� �b
*/

#include "dmaIO.h"

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

/*
   DMA ���w �A���a  �孷 ��˥

   aptr : �A������ �锁 ��a�A�a
		  �A�a���a�� ���a�[ �w���� ��a�A�a�a �a���� 32���a �锁 ��a�A�a��
		  ( �¸w �A������ �w�b�� �a�w�a�a.)
   length : �孷�i �a���a��  ( �A�� 65535�� )
   channel : ���w�i DMA ����
   dir  : �孷�i �wз
		  0 ���w�� ���e�wá -> HOST MEMORY
		  1 ���w�� HOST MEMORY -> ���e�wá

   DMA �孷 ���a�e ���e�wá �孷�a�����a���a.

   ����t
	   (-1) : ���鷁 �t�� �����e ���i ����a. (�a�w ���� 0-3)
	   (-2) : �孷�i �a���a���a ��a�A�a �����i�����i �i�� ��ǥ�a.
		 0  : ���w��a�� ��З�� �A���a.

*/

int DMA_Run(unsigned long aptr,unsigned int length,unsigned char channel,
	unsigned char dir)
{
	unsigned char page,low16Add,high16Add;
	unsigned int  DMAPort,cmd;
	long avail;
    if( length == 0 ) return -1;    /*  DMA �孷���i ��a  */
    if( channel > 3 ) return -1;    /*  ���� ��ѡ�i ��a   */

/*
	32 ���a �锁 ��a�A�a�A�� �A���� 8 ���a �w�a�� 8 ���a ��a�A�a 

   31             24              16                8             0
   |---------------|---------------|---------------|---------------|
   | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
   +---------------|---------------|---------------|---------------|
				   \---- page -----/\- high16Add --/\- low16Add  --/
						  |
	   Page Select Port --|               DMA Base Address Port

   32���a �锁 ��a�A�a�� �A�w��  8 ���a�e ����.
   �a�w ��a�A�a�e 24���a�� 16MByte �w�b�i �a���i�� ���q
*/
	page = (unsigned char) (aptr >> 16);
	low16Add  = (unsigned char) (aptr & 0xFF);
	high16Add = (unsigned char) ((aptr >> 8) & 0xFF);
        /*  �A����, ��a�A�a �w�� �a���a, �a�� �a���a�i ���e    */

/*
   DMA ���a����a 16���a�� ��a�A�a ���A�� �孷�� �a�w�a�a�� IBM PC��
   32 ���a ��a�A�a �w�b�i �i�w�i�� ���a�a��, �w�� 8 ���a�i �A������ �a��
   ����A�� �����A�i Ё�i�e�a.
   �孷���A�e �A���� �t�i �w�a ��ǩ�� ���a�a�� �孷�a�e �����A �A�����i
   �w�a ���a�� �i�w���A�e  �i���E �i���a �i���e�a.
   ���i �i�� �锁��a�A�a 0x3B000 �A ��w�E �q���A���a�� �����a 0xC000 ���e
   �锁��a�A�a 0x3BC00 - 0x48FFF �� ���w�i �孷Ё�� �a�a�� �A�����a 3�A��
   4�� �a��a. �����e �w���e �孷�� ���a�w�a�a.
   �孷�� �a�w�e�a�i ��a
*/
	avail = (unsigned long) (0x10000L - (aptr & 0xFFFFL));
	if( avail < length ) return -2;
        /*  �e�� ��a�A�a�A�� �A�� �孷 �a�w�e �A���a�a �孷Ё�� �i �A���a���a
            ��a�e �孷���a�w�a�a.  */
    if( dir ) cmd = CMD_DMA_SINGLE_READ;    /*  ����    */
    else cmd = CMD_DMA_SINGLE_WRITE;        /*  ���e �a��   */
	cmd += channel;
	DMAPort = channel << 1;
	outportb( DMA_ChannelPage[channel], page );	/* ���� Page Address Set */
	outportb( DMA_FF_CLR, 0 );	/* DMA ���� �w/�a�� ��Ȃ Flip-Flop Reset */
	outportb( DMAPort, low16Add );		/* DMA Base Low  8 Bit Address Set */
	outportb( DMAPort, high16Add );		/* DMA Base High 8 Bit Address Set */
	DMAPort++;
	outportb( DMAPort, length & 0xFF );	/* DMA Base Low  8 Bit Counter Set */
	outportb( DMAPort, length >> 8 );	/* DMA Base High 8 Bit Counter Set */
	outportb( DMA_MODE, cmd );			/* DMA Mode �i Single Mode �� �A˷ */
										/* Address �w�a �wз */
	outportb( DMA_MASK, CMD_DMA_MASK_CLR + channel );
										/* DMA Request Enable */
	return 0;
}

/*
   ���e�wá�� DMA �孷�a���i ���a�w�a�A �e�a.

   channel : DMA ����

   ����t  : 0 ���w ���a
			-1 DMA ���鷁 �t�� �����e �t�i ����q

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
  �����e ���鷁 DMA�i �a�w�a�A �e�a.

  ���b�t : DMA ���� ��ѡ (0-3)
*/
int DMA_EnableDREQ(unsigned char channel)
{
	if( channel > 3 ) return -1;
	outportb( DMA_MASK, CMD_DMA_MASK_CLR + channel );
	return 0;
}

/*
  �����e ���鷁 DMA �a���� �t�i ���ᵥ�a

   ���b�t : DMA ���� ��ѡ (0-3)
   ����t : DMA �a����t
*/
unsigned int DMA_GetDMACounter(unsigned char channel)
{
	unsigned int low,high,DMAPort;
	if( channel > 3 ) return -1;
	outportb( DMA_FF_CLR, 0 );		/* DMA ���� �w/�a�� ��Ȃ Flip-Flop Reset */
	DMAPort = (channel << 1) + 1;	/* I/O ��a�A�a ���e */
	low  = inportb( DMAPort );		/* DMA �a���� �a�� 8 ���a */
	high = inportb( DMAPort );		/* DMA �a���� �w�� 8 ���a */
	return (low | (high << 8));
}

/* DMAIO.C procedure */
int DMA_Run(unsigned int aptr,unsigned short int len,unsigned char ch,
    unsigned char dir);
int DMA_DisableDREQ(unsigned char channel);
int DMA_EnableDREQ(unsigned char channel);
unsigned int DMA_GetDMACounter(unsigned char channel);


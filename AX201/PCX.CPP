// 1996.1.13
// PCX Library


void set_pal(BYTE color,BYTE r,BYTE g,BYTE b);
void get_pal(BYTE color,BYTE *r,BYTE *g,BYTE *b);
void set_block_pal(BYTE *buf,BYTE st_color,int su);
void get_block_pal(BYTE *buf,BYTE st_color,int su);
void pcx_read(int number,char *fname);
void pcx_read(int number,char *fname)
 {
  BYTE pal[768];

  struct HEADER {
   BYTE marker,version,code,bpp;
   WORD x1,y1,x2,y2,hres,vres;
   BYTE palette[48];
   BYTE vmode,nplanes;
   WORD bpl;
   WORD palinfo;
   WORD shres,svres;
   BYTE unused[54];
   } header;
  WORD c,i;
  BYTE *offset;
  FILE *fp;
  offset=so_list[number].screen;
  if ((fp=fopen(fname,"rb"))==NULL) {
//     printf("Open error %s file",fname);
    }
  fread(&header,sizeof(header),1,fp);
  do{
     c=(fgetc(fp)&0xff);
     if((c&0xc0)==0xc0) {
      i=c&0x3f;
      c=fgetc(fp);
      while(i--) *(offset++)=c;
      }
     else *(offset++)=c;
    } while(offset<(so_list[number].screen+64000));
  fseek(fp,-769L,SEEK_END);
  fgetc(fp);
  fread(pal,1,768,fp);
  fclose(fp);
  for (i=0;i<768;i++) pal[i]>>=2;
  set_block_pal(pal,0,256);
 }
void set_pal(BYTE color,BYTE r,BYTE g,BYTE b)
 {
  outp(0x3c8,color);
  outp(0x3c9,r);
  outp(0x3c9,g);
  outp(0x3c9,b);
 }
void get_pal(BYTE color,BYTE *r,BYTE *g,BYTE *b)
 {
  outp(0x3c7,color);
  *r=inp(0x3c9);
  *g=inp(0x3c9);
  *b=inp(0x3c9);
 }
void set_block_pal(BYTE *buf,BYTE st_color,int su)
 {
  int i;
  outp(0x3c8,st_color);
  for(i=0;i<su*3;i++)
   outp(0x3c9,*(buf+i));
 }
void get_block_pal(BYTE *buf,BYTE st_color,int su)
 {
  int i;
  outp(0x3c7,st_color);
  for (i=0;i<su*3;i++)
   *(buf+i)=inp(0x3c9);
 }




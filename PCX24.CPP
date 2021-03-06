// 1996.8.5
// PCX Library  Version 5   24bit color

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

void pcx_read(unsigned char *number,char *fname,int hres);
void pcx_read(unsigned char *number,char *fname,int hres)
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
  WORD i,count=0;
  BYTE c;
  unsigned char *offset,*buffer;
  int color_count=2,j=0,row,col,pass;
  FILE *fp;
  if ((fp=fopen(fname,"rb"))==NULL) {
     printf("\nOpen error %s file\n",fname);exit(1);
    }
  fread(&header,sizeof(header),1,fp);
  if (header.marker!=0x0a) {printf("\n This file is not .PCX file....\n");fclose(fp);exit(1);}
  if (header.version<5) { printf("\n pcx_read() support only 24bit format...\n");fclose(fp);exit(1);}
  buffer=number; offset=(unsigned char *)malloc((header.x2-header.x1+1)*3);
  for (row=header.y1;row<header.y2-header.y1+1;row++)
   {
    for (col=header.x1;col<(header.x2-header.x1+1)*3;)
     {
      c=(fgetc(fp)&0xff);
      if ((c&0xc0)!=0xc0) pass=1;
       else { pass=c&0x3f; c=(fgetc(fp)&0xff); }
      memset(&offset[col],c,pass);
      col+=pass;
     }
    for (i=0;i<3;i++) {
     for (j=2-i;j<(header.x2-header.x1+1)*3;j+=3) {
      *(buffer+j)=offset[count];
      count++;
      }
     }
    buffer+=(header.x2-header.x1+1)*3;count=0;
   }
 free(offset);
  fclose(fp);
 }
// 1996.8.6   Programming by N.G.H
void _24to15 (unsigned char *source, short *dest,int size);  // size : number of pixels esi,edi,ecx
// eax : r ebx : g edx : b
 #pragma aux _24to15= \
  "      pushad "\
  " _l1: xor eax,eax "\
  "      xor ebx,ebx "\
  "      xor edx,edx "\
  "      mov al,[esi] "\
  "      inc esi " \
  "      mov bl,[esi] "\
  "      inc esi "\
  "      mov dl,[esi] "\
  "      inc esi "\
  "      shr eax,3 "\
  "      shr ebx,3" \
  "      shr edx,3" \
  "      shl edx,10"\
  "      shl ebx,5"\
  "      or eax,ebx" \
  "      or eax,edx" \
  "      mov [edi],ax" \
  "      add edi,2"\
  "      loop _l1 "\
  "      popad "\
  parm [esi] [edi] [ecx]\
  modify [eax ebx ecx edx esi edi];

// 1996.8.6
int rgd_write(char *fn,short *source,int x,int y)
 {
  FILE *fp;
  struct header {
    char id[10];
    BYTE version,bpd;
    WORD x,y;
    BYTE reserved[50];
    } h;
  strcpy(h.id,"RunE");
  h.version=1;h.bpd=2; //version 1 : 15/16bit color
  h.x=(WORD)x;h.y=(WORD)y;
  memset(h.reserved,0,50);
  strcat(fn,".rgd");
  fp=fopen(fn,"rb");
  if (fp!=NULL) {fclose(fp);return -1;}  // Already exist file.....
  fp=fopen(fn,"wb");
  if (fp==NULL) return -2; // File creation error.....
  fwrite(&h,sizeof(header),1,fp);
  fwrite(source,x*y*2,1,fp);
  fclose(fp);
  return 0;
 }
int rgd_read(char *fn,short *source,int &x,int &y)
 {
  FILE *fp;
  struct header {
    char id[10];
    BYTE version,bpd;
    WORD x,y;
    BYTE reserved[50];
    } h;
  fp=fopen(fn,"rb");
  if (fp==NULL) return -1;  // File open error....
  fread(&h,sizeof(header),1,fp);
  if (strcmp(h.id,"RunE")!=0) return -2; // Do not RGD file....
  if ((h.version!=1)||(h.bpd!=2)) return -3; // Do not version 1...
  x=h.x; y=h.y;
  fread(source,x*y*2,1,fp);
  fclose(fp);
  return 0;
 }

// Original Source ..... _24to15 Function

/* {
  WORD r=0,g=0,b=0,color=0;
  int i;double rr,gg,bb;
  for (i=0;i<size;i++)
   {
//    bb=(double)*(source)/255.0; gg=(double)*(source+1)/255.0; rr=(double)*(source+2)/255.0;
    b=(*(source)>>3); g=(*(source+1)>>3); r=(*(source+2)>>3);
//    r=(short)(31.0*rr); g=(short)(31.0*gg); b=(short)(31.0*bb);
    r=r<<10; g=g<<5; //b=b<<1;
    color=r|g|b;
    *dest=color;
    dest++; source+=3;
   }
 }*/

//  .. RUNE ..    Sprite Compiler...
//                   Reizes...
//       1996. 3. 23.    Nam gi hoon.
// Sprite Compiler......

#include <iostream.h>
#include <dos.h>
#include <i86.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <math.h>

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

static int width,height;

char *make_spr_name(char *in_name);
char *make_src_name(char *in_name);
int yesno();
int compress(BYTE *in_data,BYTE *out_data,int x,int y,int w);
void sprite_compil(char *file_name,BYTE *data,int length);

void main()
 {
  FILE *src_fp;
  char *src_name,*h_name,*temp;
  BYTE *data,*compdata;
  int mode,tile_x,tile_y,data_length;
  int screen_w;

  printf("\nInput visual screen width : ");
  cin >>screen_w;
do {
  printf("\nInput the *.src file name : ");
  cin>>temp;
  src_name=make_src_name(temp);
  h_name=make_spr_name(temp);

  src_fp=fopen(src_name,"rb");
  if (src_fp==NULL) { printf("\nFile Open error.... ");exit(1); }
  fseek(src_fp,0,SEEK_SET);
  mode=fgetc(src_fp);
  fread(&tile_x,4,1,src_fp);
  fread(&tile_y,4,1,src_fp);
  width=tile_x;height=tile_y;
  data=(BYTE *)malloc(tile_x*tile_y);
  fread(data,tile_x*tile_y,1,src_fp);
  fclose(src_fp);
  printf("\nOriginal Data is %d Bytes ",tile_x*tile_y+9);
  printf("\nData compressing....");
  compdata=(BYTE *)malloc((tile_x*tile_y)*2);
  data_length=compress(data,compdata,tile_x,tile_y,screen_w);
  printf("\nCompressed Data is %d Bytes ",data_length);
  free(data);
  printf("\nSprite Compiling....");
  sprite_compil(h_name,compdata,data_length);
  free(compdata);
  printf("\nProcessing finished...");
 }while(yesno());
  printf("\n Good bye.... ..RUNE.. 1996  ");
 }

void sprite_compil(char *file_name,BYTE *data,int length)
 {
  FILE *h_fp;
  BYTE *buffer;
  int i,zero_count,*zero_pointer,code_length;
  buffer=data;

  h_fp=fopen(file_name,"wb");
  if (h_fp==0) {printf("\nFile Open error....."); exit(1);}
  fseek(h_fp,0,SEEK_SET);
  for(i=0;i<length;) {
   if (*buffer!=0) { fputc(0xc6,h_fp);    // mov [ebx],xx
                     fputc(0x03,h_fp);
                     fputc(*buffer,h_fp);
                     fputc(0x43,h_fp);   // inc ebx
                     buffer++;i++;
                     code_length+=4;
                   }
    else { buffer++;i++;
           zero_pointer=(int *)buffer;
           zero_count=*zero_pointer;
           if (zero_count<=0xff) { fputc(0x83,h_fp);   // add ebx,xx
                                   fputc(0xc3,h_fp);
                                   fputc((BYTE)zero_count,h_fp);
                                   code_length+=3;
                                 }
             else { fputc(0x81,h_fp);   // add ebx,xxxx
                    fputc(0xc3,h_fp);
                    fwrite(&zero_count,4,1,h_fp);
                    code_length+=6;
                  }
           buffer+=sizeof(int);i+=sizeof(int);
         }
   }
//  fputc(0x5b,h_fp);  // pop ebx
  fputc(0xc3,h_fp);  // ret
  code_length+=2;
  fwrite(&width,4,1,h_fp);
  fwrite(&height,4,1,h_fp);
  fwrite(&code_length,4,1,h_fp);
  fclose(h_fp);
 }

int compress(BYTE *in_data,BYTE *out_data,int x,int y,int w)
 {
  int index=0,zero_count=0,*zero_pos;
  int i,j,length=0;
  BYTE *temp,k;

  temp=out_data;
  for (i=0;i<y;i++) {
   for(j=0;j<x;j++) {
    k=*(BYTE *)((DWORD)in_data+j+i*x);
    if (k==0) {zero_count++;}
     else {
           if (zero_count==0) {*temp=k;temp++;length++;}
            else { *temp=0;temp++;length++;
                   zero_pos=(int *)temp;
                   *zero_pos=zero_count;
                   zero_count=0;
                   temp+=sizeof(int);length+=sizeof(int);
                   *temp=k;temp++;length++;
                 }
          }
   }  // for  j
   zero_count+=(w-x);
  } // for i
  return length;
 }




char *make_src_name(char *in_name)
 {
  int i,length,point_pos;
  char *out_name;

  length=strlen(in_name);
  out_name=(char *)malloc(14);
  for(i=0;i<length;i++) {
   if (*(in_name+i)=='.') {point_pos=i;break;}
   point_pos=length;
   }
  for(i=0;i<point_pos;i++)
   *(out_name+i)=*(in_name+i);
   *(out_name+point_pos)='.';
   *(out_name+point_pos+1)='s';
   *(out_name+point_pos+2)='r';
   *(out_name+point_pos+3)='c';
   *(out_name+point_pos+4)=NULL;
  return out_name;
 }
char *make_spr_name(char *in_name)
 {
  int i,length,point_pos;
  char *out_name;

  length=strlen(in_name);
  out_name=(char *)malloc(14);
  for(i=0;i<length;i++) {
   if (*(in_name+i)=='.') {point_pos=i;break;}
   point_pos=length;
   }
  for(i=0;i<point_pos;i++)
   *(out_name+i)=*(in_name+i);
   *(out_name+point_pos)='.';
   *(out_name+point_pos+1)='c';
   *(out_name+point_pos+2)='o';
   *(out_name+point_pos+3)='d';
   *(out_name+point_pos+4)=NULL;
  return out_name;
 }

int yesno()
 {
  char *yn;
  printf("\nDo you want continue processing ? ");
  cin >> yn;
  if ((yn[0]=='Y')||(yn[0]=='y')) return 1;
  return 0;
 }

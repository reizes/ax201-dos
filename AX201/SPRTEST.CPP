// 1996.1.12     ..RUNE..      Reizes Nam Gi Hoon...
// 1996.1.18     Addition
// 1996.1.19     Addition
// 1996.1.21     Addition, Edition
// 1996.1.22     Addition, Edition, Optimizing  ~ 1.23
// 1996.1.23     Edition    -> Graphic Primitive/Initialize Function Finished
// 1996.2.6      Addition, Edition
// 1996.3.       Tile & Sprite Cutter Program
// 1996.3.14     Cutter finished...
// 1996.3.20     SRC view.....
// 1996.3.23     Sprite Test...

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

static unsigned int off;

void set_offset();
#pragma aux set_offset= \
 "mov ebx,off "\
 modify[ebx];

void push_ebx();
#pragma aux push_ebx= \
 "push ebx "\
 modify[ebx];

void pop_ebx();
#pragma aux pop_ebx= \
 "pop ebx "\
 modify[ebx];

void (*sprite)();

void set_block_pal(BYTE *buf,BYTE st_color,int su)
 {
  int i;
  outp(0x3c8,st_color);
  for(i=0;i<su*3;i++)
   outp(0x3c9,*(buf+i));
 }

void set_videomode(short mode)
 {
  union REGS r;
  r.w.ax=mode;
  int386(0x10,&r,&r);
 }
void main(void)
 {
  unsigned int offset;
  int x,y,code_length,width,height;
  BYTE pal[768];
  char *filename,*pal_name;
  void *code;
  FILE *cod_fp,*pal_fp;

  printf("\nInput Palette file name : ");
  cin >> pal_name;
  printf("\nInput Sprite code name (*.cod) : ");
  cin >> filename;
  pal_fp=fopen(pal_name,"rb");
  fseek(pal_fp,0,SEEK_SET);
  fread(pal,768,1,pal_fp);
  fclose(pal_fp);
  cod_fp=fopen(filename,"rb");
  fseek(cod_fp,-12,SEEK_END);
  fread(&width,4,1,cod_fp);
  fread(&height,4,1,cod_fp);
  fread(&code_length,4,1,cod_fp);
  fseek(cod_fp,0,SEEK_SET);
  code=malloc(code_length);
  fread(code,code_length,1,cod_fp);
  fclose(cod_fp);
  sprite=(void (*)())code;
  set_videomode(0x13);
  set_block_pal(pal,0,256);
  x=100;y=100;
  for(x=0;x<200;x+=20) {
   for(y=0;y<150;y+=20) {
  x=(x>(320-width)) ? 320-width : x;
  y=(y>(200-height)) ? 200-height : y;
  off=0xa0000+x+y*320;
  push_ebx();
  set_offset();
  sprite();
  pop_ebx();
/*  x=50;y=50;
  off=0xa0000+x+y*320;
  push_ebx();
  set_offset();
  sprite();
  pop_ebx(); */
  }
 }
  getch();
  set_videomode(3);
  free(code);
  printf("Good bye....");

 }




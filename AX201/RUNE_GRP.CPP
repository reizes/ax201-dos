//      Watcom C/C++  Graphic Library Source
//
//                                   ..RUNE..
//                                           1996.1.23 Reizes
//                                                  Nam Gi Hoon
//
// 1996.1.12  ..RUNE..      Reizes Nam Gi Hoon...
// 1996.1.18     Addition
// 1996.1.19     Addition
// 1996.1.21     Addition, Edition
// 1996.1.22     Addition, Edition, Optimizing  ~ 1.23
// 1996.1.23     Edition    -> Graphic Primitive/Initialize Function Finished
// 1996.1.23     Making Library

#include <dos.h>
#include <i86.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <math.h>

#define TEXTMODE 3
#define _320x200 0x13
#define _640x400 0x100
#define _640x480 0x101
#define _800x600 0x103
#define _1024x768 0x105

#define MAX_SO 40
#define IMAGE   0
#define SPRITE  1
#define UNUSED 255
#define _SO     0
#define _VRAM   1
#define BUFFER  0

#define _COPY   0
#define _XOR    1
#define _AND    2
#define _OR     4

#define pset(X,Y,C) {if ((X>=so_list[active_so].width)||(Y>=so_list[active_so].height)||(X<0)||(Y<0)) {;} else pset_sub(X,Y,C);}
#define set_active_so(X) {active_so=X;}
#define set_logic(X) {logic_flag=X;}
#define set_trans_color(C) {trans_color=C;}

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

extern short win_granularity;
static short bank_n;
static DWORD TEMP;
static BYTE win_A_attr;
extern BYTE active_so=0,move_for=_SO,logic_flag=0,trans_color=0,buffer_so;
extern BYTE *buffer_address,*offset_n;
static int d_x,d_y;
static DWORD d_w,d_h,vh,vv,win_g,temp_add,temp_add2;

typedef struct {
 DWORD EDI,ESI,EBP,reserved;
 DWORD EBX,EDX,ECX,EAX;
 WORD flags;
 WORD ES,DS,FS,GS,IP,CS,SP,SS;
 } RMI;

typedef struct {
 BYTE attrib;
 DWORD width,height;
 int view_x,view_y;
 DWORD view_width,view_height;
 int disp_x,disp_y;
 BYTE *screen;
 } SO;

typedef struct {
 WORD modeattr;
 BYTE winAattr,winBattr;
 WORD win_granularity;
 WORD win_size;
 WORD win_aseg,win_bseg;
 void (*win_func)();
 WORD bytePerScanLine;
 WORD h_resol,v_resol;
 BYTE char_width,char_height;
 BYTE num_of_planes;
 BYTE bitPerPixel;
 BYTE num_of_banks;
 BYTE memory_model;
 BYTE banksize;
 } VESAINFO;

extern VESAINFO _vi;
extern SO so_list[MAX_SO];

int get_vesainfo(VESAINFO *vi,WORD mode);
void set_videomode(short mode);
int set_vesamode(short mode);
void *real_malloc(DWORD *selector,WORD size);
void real_free(WORD selector);
void int_real(BYTE int_no,RMI *in_reg);
int get_vesainfo(VESAINFO *vi,WORD mode);
void print_vesainfo(VESAINFO *vi);
int set_page(short page);
int creat_so(int number,DWORD width,DWORD height,BYTE attrib);
int delete_so(int number);
void move_image_to_buffer(int number);
void move_sprite_to_buffer(int number);
void view();
void pset_sub(int x,int y,BYTE color);
void clear_so(int number,BYTE color);
void _hline(int x1,int x2,int y,BYTE color);
void _vline(int x,int y1,int y2,BYTE color);
void box(int x1,int y1,int x2,int y2,BYTE color);
void line(int x1,int y1,int x2,int y2,BYTE color);
void circle_fill(int x1,int y1,int r,BYTE color);
void circle(int x1,int y1,int r,BYTE color);
void box_fill(int x1,int y1,int x2,int y2,BYTE color);
void init(int mode);
void ending(void);
void set_buffer(int x,int w,int h);
void set_display(int NUM,int X,int Y);
void set_view(int NUM,int X,int Y,int W,int H);
int view_so(int number);

int view_so(int number)
 {
  if (so_list[number].attrib==UNUSED) return -1;
  if (so_list[number].attrib==SPRITE) {move_sprite_to_buffer(number);return 0;}
  if (so_list[number].attrib==IMAGE)  {move_image_to_buffer(number);return 0;}
  return -1;
 }

void set_view(int NUM,int X,int Y,int W,int H)
 {
  so_list[NUM].view_x=X;
  so_list[NUM].view_y=Y;
  so_list[NUM].view_width=W;
  so_list[NUM].view_height=H;
  if (NUM==buffer_so) {
    d_w=W;  d_h=H;
                      }
 }

void set_display(int NUM,int X,int Y)
 {
  so_list[NUM].disp_x=X;
  so_list[NUM].disp_y=Y;
  if (NUM==buffer_so) {
                        d_x=X;d_y=Y;
                      }
 }

void set_buffer(int x,int w,int h)
 {
  buffer_so=x;
  if (so_list[x].attrib==UNUSED) creat_so(x,w,h,IMAGE);
  buffer_address=so_list[x].screen;
  d_x=(DWORD)so_list[x].disp_x;
  d_y=(DWORD)so_list[x].disp_y;
  d_w=(DWORD)so_list[x].view_width;
  d_h=(DWORD)so_list[x].view_height;
  vh=_vi.h_resol;
  vv=_vi.v_resol;
 }
void circle(int x1,int y1,int r,BYTE color)
 {
  int x,y,d,de,dse;
  if (r==0) {pset(x1,y1,color); return;}
  x=0;y=r;
  d=1-r;dse=-2*r+5;de=3;
  pset(x1+r,y1,color); pset(x1-r,y1,color);
  pset(x1,y1+r,color); pset(x1,y1-r,color);

  for(;y>=x;)
   { x++;
     if(d<0) d+=de;
      else { d+=dse;dse+=2;y--;}
     de+=2;dse+=2;
  pset(x1+x,y1+y,color); pset(x1+y,y1+x,color);
  pset(x1-x,y1+y,color); pset(x1-y,y1+x,color);
  pset(x1+x,y1-y,color); pset(x1+y,y1-x,color);
  pset(x1-x,y1-y,color); pset(x1-y,y1-x,color);
  }
 }
void circle_fill(int x1,int y1,int r,BYTE color)
 {
  int x,y,d,de,dse;
  if (r==0) {pset(x1,y1,color); return;}
  x=0;y=r;
  d=1-r;dse=-2*r+5;de=3;
  _hline(x1-r,x1+r,y1,color);
 for(;y>=x;)
  {
   x++;
   if (d<0) d+=de;
    else {d+=dse;dse+=2;y--;}
   de+=2;dse+=2;

   _hline(x1-x,x1+x,y1+y,color);
   _hline(x1-x,x1+x,y1-y,color);
   _hline(x1-y,x1+y,y1+x,color);
   _hline(x1-y,x1+y,y1-x,color);
     }
 }

void line(int x1,int y1,int x2,int y2,BYTE color)
 {
  int x_delta,y_delta,i,distance,x_step,y_step,x=0,y=0,sx,sy;

  x_delta=x2-x1;
  y_delta=y2-y1;
  sx=x1;sy=y1;
  if((x_delta==0)&&(y_delta==0)) {pset(x1,y1,color); return;}
  if (x_delta==0) {_vline(x1,y1,y2,color); return;}
  if (y_delta==0) {_hline(x1,x2,y1,color); return;}
  if (x_delta>0) x_step=1;
   else {x_step=-1;x_delta=x1-x2;}
  if (y_delta>0) y_step=1;
   else {y_step=-1;y_delta=y1-y2;}

  distance=(x_delta>y_delta) ? x_delta : y_delta;

  for (i=0;i<distance;i++) {
   pset(sx,sy,color);
   x+=x_delta;
   y+=y_delta;
   if (x>distance) { x-=distance; sx+=x_step; }
   if (y>distance) { y-=distance; sy+=y_step; }
   }
 }


void box(int x1,int y1,int x2,int y2,BYTE color)
 {
  _hline(x1,x2,y1,color);
  _hline(x1,x2,y2,color);
  _vline(x1,y1,y2,color);
  _vline(x2,y1,y2,color);
 }
void box_fill(int x1,int y1,int x2,int y2,BYTE color)
 {
  int i;
  for (i=y1;i<=y2;i++)
   _hline(x1,x2,i,color);
 }
void _hline(int x1,int x2,int y,BYTE color)
 {
  int i;
  BYTE *start_add;

  if (y<0) return;
  if (x1==x2) {pset(x1,y,color);return;}
  if (x1>x2) {i=x1;x1=x2;x2=i;}
  if (x1<0) x1=0;
  if (x2>=so_list[active_so].width) x2=so_list[active_so].width-1;
  if (logic_flag==_COPY) {start_add=(BYTE *)(y*so_list[active_so].width+x1+(DWORD)so_list[active_so].screen);
                          memset(start_add,color,x2-x1+1); return;
                         }
  for (i=x1;i<=x2;i++)
   pset_sub(i,y,color);
 }
void _vline(int x,int y1,int y2,BYTE color)
 {
  int i;
  if(x<0) return;
  if(y1==y2) {pset(x,y1,color);return;}
  if (y1>y2) {i=y1;y1=y2;y2=i;}
  if (y1<0) y1=0;
  if (y2>=so_list[active_so].height) y2=so_list[active_so].height-1;
  for (i=y1;i<=y2;i++)
   pset_sub(x,i,color);
 }

void clear_so(int number,BYTE color)
 {
  memset(so_list[number].screen,color,so_list[number].width*so_list[number].height);
 }
void pset_sub(int x,int y,BYTE color)
 {
  BYTE *add;

  add=(BYTE *)(y*so_list[active_so].width+x+(DWORD)so_list[active_so].screen);
  if (logic_flag==_COPY) {*add=color;return;}
  if (logic_flag==_XOR) {*add^=color;return;}
  if (logic_flag==_OR) {*add|=color;return;}
  if (logic_flag==_AND) {*add&=color;return;}
 }
void view()
 {
  static int i,bank;
  static BYTE *address,*_320_address;
  static DWORD view_w,view_h;
  address=buffer_address;
  bank=_vi.num_of_banks;

  view_w=d_w;view_h=d_h;
  if (bank==1) {    //1
                if ((d_w==320)&&(d_h==200)&&(d_x==0)&&(d_y==0))
                 {memmove((BYTE *)0xa0000,address,64000); return; }
                 else {
                       if ((d_x+d_w)>=vh) view_w=vh-d_x;
                       if ((d_y+d_h)>=vv) view_h=vv-d_y;
                       _320_address=(BYTE *)(d_y*320+d_x+0xa0000);//2
                       for (i=0;i<view_h;i++) { //3
                             memmove(_320_address,address,view_w);
                             _320_address+=320; address+=so_list[buffer_so].width;
                            } //3
                       return; } //2
               }
 if ((d_w==vh)&&(d_h==vv)&&(d_x==0)&&(d_y==0)) {
   for (i=0;i<bank;i++)
    {
     set_page(i);
     memmove((BYTE *)0xa0000,address,0xffff);
     address+=0x10000;
    } return; }
  else {
       if ((d_x+d_w)>=vh) view_w=vh-d_x;
       if ((d_y+d_h)>=vv) view_h=vv-d_y;
       win_g=_vi.win_granularity;
       TEMP=d_y*vh+d_x;
       bank_n=TEMP/(win_g<<10);
       offset_n=(BYTE *)(0xa0000+((TEMP%win_g)<<10));
       set_page(bank_n);
       for(i=0;i<view_h;i++) {
       temp_add=(DWORD)(offset_n+view_w);
       if (temp_add>0xaffff) {temp_add2=temp_add-0xaffff;
                              memmove(offset_n,address,view_w-temp_add2);
                              bank_n++;set_page(bank_n);offset_n=(BYTE *)(temp_add2+0xa0000);
                              memmove((BYTE *)0xa0000,address+view_w-temp_add2,temp_add2);
                              address+=view_w;}
        else {memmove(offset_n,address,view_w); offset_n+=view_w;address+=view_w;
              if(offset_n>(BYTE *)0xaffff) {bank_n++; set_page(bank_n); offset_n-=0x0ffff; }
             }// ELSE
       }//for
  }//else
 }
void move_image_to_buffer(int number)
 {
  static int i;
  static BYTE *address,*address_buff;
  static int dis_x,dis_y,vwx,vwy;
  static DWORD vi_w,vi_h;

  dis_x=so_list[number].disp_x;
  dis_y=so_list[number].disp_y;
  vi_w=so_list[number].view_width;
  vi_h=so_list[number].view_height;
  vwx=so_list[number].view_x;
  vwy=so_list[number].view_y;

  if (vwx<0) {vi_w+=vwx;vwx=0;}
  if (vwy<0) {vi_h+=vwy;vwy=0;}
  if ((vwx+vi_w)>=so_list[number].width) vi_w=so_list[number].width-vwx;
  if ((vwy+vi_h)>=so_list[number].height) vi_h=so_list[number].height-vwy;

  address=(BYTE *)((vwy*so_list[number].width)+vwx+(DWORD)(so_list[number].screen));
  address_buff=(BYTE *)((dis_y*so_list[buffer_so].width)+dis_x+(DWORD)buffer_address);

  if ((dis_x==0)&&(dis_y==0)&&(vi_w==so_list[buffer_so].width)&&(vi_h==so_list[buffer_so].height))
        {
         memmove(address_buff,address,so_list[buffer_so].width*so_list[buffer_so].height);
         return;
        }
  if (dis_x<0) {vi_w+=dis_x;dis_x=0;}
  if (dis_y<0) {vi_h+=dis_y;dis_y=0;}
  if ((dis_x+vi_w)>=so_list[buffer_so].width)
    { vi_w=so_list[buffer_so].width-dis_x; }
  if ((dis_y+vi_h)>=so_list[buffer_so].height)
    { vi_h=so_list[buffer_so].height-dis_y; }
  if ((vi_w<=0)||(vi_h<=0)) return;
  for (i=0;i<vi_h;i++)
   {
    memmove(address_buff,address,vi_w);
    address_buff+=so_list[buffer_so].width;
    address+=so_list[number].width;
   }
 }

void move_sprite_to_buffer(int number)
 {
  static int i,j;
  static int dis_x,dis_y,vwx,vwy;
  static DWORD vi_w,vi_h;
  static BYTE *address,*address_buff,*temp,*temp_buff;

  dis_x=so_list[number].disp_x;
  dis_y=so_list[number].disp_y;
  vi_w=so_list[number].view_width;
  vi_h=so_list[number].view_height;
  vwx=so_list[number].view_x;
  vwy=so_list[number].view_y;

  if (vwx<0) {vi_w+=vwx;vwx=0;}
  if (vwy<0) {vi_h+=vwy;vwy=0;}
  if ((vwx+vi_w)>=so_list[number].width)  vi_w=so_list[number].width-vwx;
  if ((vwy+vi_h)>=so_list[number].height)  vi_h=so_list[number].height-vwy;
  if (dis_x<0) {vi_w+=dis_x;dis_x=0;}
  if (dis_y<0) {vi_h+=dis_y;dis_y=0;}
  if ((dis_x+vi_w)>=so_list[buffer_so].width)
    vi_w=so_list[buffer_so].width-dis_x;
  if ((dis_y+vi_h)>=so_list[buffer_so].height)
    vi_h=so_list[buffer_so].height-dis_y;
  if ((vi_w<=0)||(vi_h<=0)) return;
  address=(BYTE *)((vwy*so_list[number].width)+vwx+(DWORD)(so_list[number].screen));
  address_buff=(BYTE *)((dis_y*so_list[buffer_so].width)+dis_x+(DWORD)buffer_address);

  for (i=0;i<vi_h;i++)
   {
    temp=address; temp_buff=address_buff;
    for (j=0;j<vi_w;j++)
     { if (*temp!=trans_color) *temp_buff=*temp;
       temp_buff++; temp++;
     }
    address_buff+=so_list[buffer_so].width;
    address+=so_list[number].width;
   }
 }

void set_videomode(short mode)
 {
  union REGS r;
  r.w.ax=mode;
  int386(0x10,&r,&r);
  if (mode=0x13)
   {
    _vi.h_resol=320; _vi.v_resol=200;
    _vi.win_size=64; _vi.win_granularity=64;
    _vi.win_aseg=0xa000; _vi.win_bseg=0xa000;
    _vi.num_of_banks=1; _vi.banksize=64;
   }
 }
int set_vesamode(short mode)
 {
  union REGS r;
  r.w.ax=0x4f02;
  r.w.bx=mode;
  int386(0x10,&r,&r);
  if (r.h.al!=0x4f || r.h.ah!=0) return -1;
  if (get_vesainfo(&_vi,mode)==-1) return -1;
  switch(mode)
   {
    case _640x400 : _vi.num_of_banks=4;break;
    case _640x480 : _vi.num_of_banks=5;break;
    case _800x600 : _vi.num_of_banks=7;break;
    case _1024x768 : _vi.num_of_banks=12;break;
   }
  return 0;
 }
void *real_malloc(DWORD *selector,WORD size)
 {
  union REGS regs;

  regs.w.ax=0x0100;
  regs.w.bx=((size+15)>>4);
  int386(0x31,&regs,&regs);
  if (regs.x.cflag) return NULL;
  *selector=regs.x.edx;
  return (void *)((regs.x.eax&0xffff)<<4);
 }
void real_free(WORD selector)
 {
  union REGS regs;
  regs.x.eax=0x0101;
  regs.x.edx=selector;
  int386(0x31,&regs,&regs);
 }
void int_real(BYTE int_no,RMI *in_reg)
 {
  union REGS regs;
  struct SREGS sregs;

  regs.x.eax=0x0300;
  regs.x.ebx=int_no;
  regs.w.cx=0;
  sregs.es=FP_SEG(in_reg);
  regs.x.edi=FP_OFF(in_reg);
  int386x(0x31,&regs,&regs,&sregs);
 }
int get_vesainfo(VESAINFO *vi,WORD mode)
 {
  BYTE *buff;
  RMI rmi_call;
  DWORD selector;
  buff=(BYTE *)real_malloc(&selector,1024);
  if (buff==NULL) return -1;
  memset(&rmi_call,0,sizeof(RMI));
  rmi_call.EAX=0x4f01;
  rmi_call.ECX=mode;
  rmi_call.EDI=0;
  rmi_call.ES=((DWORD)buff>>4) & 0xffff;
  int_real(0x10,&rmi_call);
  memcpy(vi,buff,sizeof(VESAINFO));
  real_free(selector);
  win_granularity = vi->win_granularity;
  win_A_attr=vi->winAattr;
  return 0;
 }
void print_vesainfo(VESAINFO *vi)
 {
  printf("Display Size : %4d x %4d , %dBits\n",vi->h_resol,vi->v_resol,vi->bitPerPixel);
  printf("Window Size : %4d Kbyte\n",vi->win_size);
  printf("Window A,B Segment : %04x   %04x\n",vi->win_aseg,vi->win_bseg);
  printf("Window Granularity : %4d Kbyte \n",vi->win_granularity);
  printf("Window A,B Attribute : %04x   %04x\n",vi->winAattr,vi->winBattr);
  printf("Window Control Function Pointer : %08x\n",vi->win_func);
 }

int creat_so(int number,DWORD width,DWORD height,BYTE attrib)
 {
  if ((number>=MAX_SO)||(so_list[number].attrib!=UNUSED)) return -1;
  so_list[number].attrib=attrib;
  so_list[number].width=width;
  so_list[number].height=height;
  so_list[number].view_x=0;
  so_list[number].view_y=0;
  so_list[number].view_width=width;
  so_list[number].view_height=height;
  so_list[number].disp_x=0;
  so_list[number].disp_y=0;
  so_list[number].screen=(BYTE *)malloc(width*height);
  if (so_list[number].screen==NULL) return -1;
  memset(so_list[number].screen,0,width*height);
  return 0;
 }
int delete_so(int number)
 {
  if (number>=MAX_SO) return -1;
  so_list[number].attrib=0;
  so_list[number].width=0;
  so_list[number].height=0;
  so_list[number].view_x=0;
  so_list[number].view_y=0;
  so_list[number].view_width=0;
  so_list[number].view_height=0;
  so_list[number].disp_x=0;
  so_list[number].disp_y=0;
  free(so_list[number].screen);
  so_list[number].screen=NULL;
  so_list[number].attrib=UNUSED;
  return 0;
 }

int set_page(short page)
 {
  union REGS r;
  static WORD cbn=0;

  if (cbn==page) return 1;

  r.w.ax=0x4f05;
  r.w.bx=0;
  r.w.dx=page;
  int386(0x10,&r,&r);
  if (r.h.al==0x4f && r.h.ah==0) {cbn=page;return 0 ;}
  return -1;
 }
void init(int mode)
 {
  int i;

  if (mode==_320x200) set_videomode(mode);
   else set_vesamode(mode);
  for (i=0;i<MAX_SO;i++) so_list[i].attrib=UNUSED;
  set_buffer(0,_vi.h_resol,_vi.v_resol);
  set_trans_color(0);
  set_active_so(0);
  set_logic(_COPY);
 }
void ending(void)
 {
  delete_so(buffer_so);
  set_videomode(TEXTMODE);
 }



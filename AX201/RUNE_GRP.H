//        Watcom C/C++  Graphic Library Header File...
//
//                                  ..RUNE..
//                                             1996.1.23 Reizes
//                                                    Nam Gi Hoon
//
// 1996.1.12  ..RUNE..      Reizes Nam Gi Hoon...
// 1996.1.18     Addition
// 1996.1.19     Addition
// 1996.1.21     Addition, Edition
// 1996.1.22     Addition, Edition, Optimizing  ~ 1.23
// 1996.1.23     Edition    -> Graphic Primitive/Initialize Function Finished
// 1996.1.23     Making Library
// 1996.1.23    Separate Header File...

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

static short win_granularity;
static BYTE active_so=0,move_for=_SO,logic_flag=0,trans_color=0,buffer_so;
static BYTE *buffer_address,*offset_n;

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

static VESAINFO _vi;
static SO so_list[MAX_SO];

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



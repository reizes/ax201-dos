
#include <dos.h>
#include <i86.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

typedef struct {
 DWORD EDI,ESI,EBP,reserved;
 DWORD EBX,EDX,ECX,EAX;
 WORD flags;
 WORD ES,DS,FS,GS,IP,CS,SP,SS;
 } RMI;

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

int get_vesainfo(VESAINFO *vi,WORD mode);
void set_videomode(short mode);
int set_vesamode(short mode);
void *real_malloc(DWORD *selector,WORD size);
void real_free(WORD selector);
void int_real(BYTE int_no,RMI *in_reg);
void print_vesainfo(VESAINFO *vi);
int set_page(short page);

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
  int386 (0x10,&r,&r);
  if (r.h.al!=0x4f || r.h.ah!=0) return -1;
  if (get_vesainfo(&_vi,mode)==-1) return -1;
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


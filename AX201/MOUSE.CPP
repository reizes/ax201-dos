// 1996.2.12
//                  ..RUNE..
//
//
// Mouse Library for WATCOM C/C++    by Reizes...NGH   1996.
//

#include <i86.h>
#include <dos.h>

#define L_BUTTON 0x0001
#define R_BUTTON 0x0002
#define M_BUTTON 0x0004
#define M_MOVE   0x0001
#define M_L_PRESS 0x0002
#define M_L_RELEASE 0x0004
#define M_R_PRESS   0x0008
#define M_R_RELEASE 0x0010
#define M_M_PRESS   0x0020
#define M_M_RELEASE 0x0040


int is_mouse()
 {
  union REGS r;
  r.w.ax=0;
  int386(0x33,&r,&r);
  if (r.w.ax==0xffff) return 1;
  else return 0;
 }
void set_mouse_on()
 {
  union REGS r;
  r.w.ax=1;
  int386(0x33,&r,&r);
 }
void set_mouse_off()
 {
  union REGS r;
  r.w.ax=2;
  int386(0x33,&r,&r);
 }
int get_mouse_xy(int *x,int *y,short button)
 {
  union REGS r;
  r.w.ax=3;
  int386(0x33,&r,&r);
  *x=(r.w.cx);
  *y=(r.w.dx);
  return (r.w.bx & button);
 }
void set_mouse_xy(short x,short y)
 {
  union REGS r;
  r.w.ax=4;
  r.w.cx=x;
  r.w.dx=y;
  int386(0x33,&r,&r);
 }
void set_mouse_sens(short hor,short ver)
 {
  union REGS r;
  r.w.ax=0x0f;
  r.w.cx=hor;
  r.w.dx=ver;
  int386(0x33,&r,&r);
 }
void set_mouse_accel(short accel)
 {
  union REGS r;
  r.w.ax=0x13;
  r.w.dx=accel;
  int386(0x33,&r,&r);
 }
void set_event(int mask,void ( *handler)())
 {
  RMI r;

  memset(&r,0,sizeof(RMI));
  r.EAX=0x0c;
  r.ECX=mask;
  r.ES=FP_SEG(handler);
  r.EDX=FP_OFF(handler);
  int_real(0x33,&r);
 }




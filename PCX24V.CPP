// VESA 2.0 Test
// 320x200x64k  Linear Mode ...    .. RunE ..    1996.8.1
#include <iostream.h>
#include "rglvesa2.h"
#include "pcx24.cpp"
#include "fade15.cpp"

short far *Screen;

void main()
 {
  unsigned short color; int i,j,x=320,y=200;
  char *fn; unsigned char *source,*s; short *dest,*d;
//  d=dest=(short *)malloc(320*200*2);
  s=source=(unsigned char *)malloc(320*200*3);
//  init_fade_table();
  printf("\n Input PCX File : ");cin >> fn;
  pcx_read(source,fn,320); //_24to15(source,dest,64000);
//  rgd_write("test",d,320,200);
//  rgd_read("rl1.rgd",s,x,y);
  set_vesamode(0x10f,1); Screen= (short far *)Linear_pointer;
//  for (j=0;j<33;j+=4) {
//  fade_buffer(s,d,64000,j);
   move_screen((short *)s,96000);
//  }
  getch();
//  for (j=32;j>-1;j-=4) {
//  fade_screen(s,64000,j);
//  }
//  end_fade();
  free(s);
//  free(d);
  set_videomode(3);
  print_vesainfo(&_vi);
 }


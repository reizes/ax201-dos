// VESA 2.0 Test
// 320x200x64k  Linear Mode ...    .. RunE ..    1996.8.1
#include <iostream.h>
#include <i86.h>
#include "rglvesa2.h"
#include "pcx24.cpp"
#include "fade15.cpp"

short far *Screen;

void rlogo()
 {
  int i,j,x=320,y=200;
  char *fn; short *s;
  s=(short *)malloc(320*200*2*5);
  rgd2_read("rlogo.rgd",s,x,y);
  for (j=0;j<32;j+=2)
   fade_screen(s,64000,j);
  delay(1000);
  for (i=0;i<5;i++)
    { move_screen(s+(i*320*200),64000);
      delay(90);
    }
  delay(300);
  for (i=4;i>-1;i--)
    { move_screen(s+(i*320*200),64000);
      delay(90);
    }
  delay(1000);
  for (j=32;j>-1;j-=2)
   fade_screen(s,64000,j);
  free(s);
 }

void main()
 {
  set_vesamode(0x10d,1); Screen= (short far *)Linear_pointer;
  init_fade_table();
  rlogo();
  end_fade();
  set_videomode(3);
  printf("\n Bye ... 1996.8.12   .. RunE ..    Nam gi Hoon...");
 }

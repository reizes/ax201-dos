// VESA 2.0 Test
// 320x200x64k  Linear Mode ...    .. RunE ..    1996.8.1
#include <iostream.h>
#include "rglvesa2.h"
#include "pcx24.cpp"

short far *Screen;

void main()
 {
  unsigned short color; int i,j,x=320,y=200;
  char fn[15],dn[15]; unsigned char *source,*s; short *dest,*d;
  d=dest=(short *)malloc(320*200*2);
  s=source=(unsigned char *)malloc(320*200*3);
  printf("\n Input PCX File : ");cin >> fn;
  printf("\n Input RGD File : ");cin >> dn;
  pcx_read(source,fn,320); _24to15(source,dest,64000);
  rgd_write(dn,dest,320,200);
  free(s);
  free(d);
 }


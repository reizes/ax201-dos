// ..RUNE.. Reizes
// 1996.3.24
// Resource Manager

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

int yesno()
 {
  char *yn;
  printf("\nDo you want addition to existed resource file ? ");
  cin >> yn;
  if ((yn[0]=='Y')||(yn[0]=='y')) return 1;
  return 0;
 }
int yesno2()
 {
  char *yn;
  printf("\nDo you want continue addition ? ");
  cin >> yn;
  if ((yn[0]=='Y')||(yn[0]=='y')) return 1;
  return 0;
 }

void main()
 {
  FILE *fp,*res;
  int i,data;
  char *filename,*resname;

  printf("\nInput Resource file name : ");
  cin >> resname;
  if (yesno()) res=fopen(resname,"ab");
   else res=fopen(resname,"wb");
  if (res==NULL) {printf("\nResource file error....");exit(1);}
 do {
  printf("\nInput filename to addition : ");
  cin >> filename;
  fp=fopen(filename,"rb");
  if (fp==NULL) {printf("\nFile open error....");exit(1);}
  do {
    data=fgetc(fp);
    fputc(data,res);
   }while(feof(fp)==0);
   fputc('R',res);
   fputc('U',res);
   fputc('N',res);
   fputc('E',res);
   fclose(fp);
 }while(yesno2());
 fclose(res);
 printf("\nGood bye...      ..RUNE.. 1996 ");
}


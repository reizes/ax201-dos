//  .. RUNE ..    Palette Manager...
//                   Reizes...
//       1996. 3. 18.    Nam gi hoon.
// Pal_flag   0 : usuable  /  1 : Unused  /  2 : Pal.Scroll

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

char *make_obj_name(char *in_name);
char *make_dat_name(char *in_name);
int yesno();
int yesno2();

void main(void)
 {
  char *temp,*filename,*objname,*palname;
  BYTE pal[256][3],pal_flag[256],*data,dat_pal[256][3],c;
  FILE *in_fp,*out_fp,*pal_fp;
  int i,j,k,mode,tile_x,tile_y,use_color;

  BYTE common_pal[16][3] = { 0,0,0,0,0,42,0,42,0,0,42,42,42,0,0
                            ,42,0,42,42,21,0,42,42,42,21,21,21
                            ,21,21,63,21,63,21,21,63,63,63,21,
                            21,63,21,63,63,63,21,63,63,63};

  for(i=0;i<256;i++) {pal[i][0]=0xff;
                      pal[i][1]=0xff;
                      pal[i][2]=0xff;
                     }
  for(i=0;i<256;i++) pal_flag[i]=0;

  for(i=0;i<16;i++)
    {
     pal[i][0]=common_pal[i][0];
     pal[i][1]=common_pal[i][1];
     pal[i][2]=common_pal[i][2];
    }
  printf("\nInput the Palette File Name : ");
  cin>>palname;
  if (yesno2()) {
                pal_fp=fopen(palname,"rb");
                if (pal_fp==NULL) {printf("\n File open error...");exit(1);}
                fseek(pal_fp,0,SEEK_SET);
                fread(pal,768,1,pal_fp);
                fclose(pal_fp);
                for(i=0;i<255;i++) {
                 if ((pal[i][0]==0)&&(pal[i][1]==0)&&(pal[i][2]==0)&&(pal[i+1][0]==0)&&(pal[i+1][1]==0)&&(pal[i+1][2]==0))
                  { pal[i][0]=0xff;pal[i][1]=0xff;pal[i][2]=0xff;
                    pal[i+1][0]=0xff;pal[i+1][1]=0xff;pal[i+1][2]=0xff;}
                 }
               }
 do{
  printf("\nInput *.dat file : ");
  cin>>temp;
  filename=make_dat_name(temp);
  objname=make_obj_name(filename);
  in_fp=fopen(filename,"rb");
  if (in_fp==NULL) {printf(" Error *.dat File.....  "); exit(1); }
  fseek(in_fp,0,SEEK_SET);
  mode=fgetc(in_fp);
  fread(&tile_x,4,1,in_fp);
  fread(&tile_y,4,1,in_fp);
  data=(BYTE *)malloc(tile_x*tile_y);
  fread(data,tile_x*tile_y,1,in_fp);
  fread(dat_pal,768,1,in_fp);
  fclose(in_fp);
  for(i=0;i<256;i++) {
   if(dat_pal[i][0]==0xff) {use_color=i;break;}
   use_color=i;
  }
  printf("This %s file  %d Color used.... ",filename,use_color);
  switch (mode) {
    case 0 :
    case 1 : /* tile & Sprite */
             printf(" \nThis File is Tile or Sprite... ");
             for (i=0;i<tile_y;i++) {  // 3
              for (j=0;j<tile_x;j++) { // 2
               c=*(data+j+(i*tile_x));
               for(k=0;k<256;k++) { // 1
                if ((pal_flag[k]==0)&&(pal[k][0]==dat_pal[c][0])&&(pal[k][1]==dat_pal[c][1])&&(pal[k][2]==dat_pal[c][2]))
                 { *(data+j+(i*tile_x))=k; break; }
                if (pal[k][0]==0xff) { pal_flag[k]=0;
                                       pal[k][0]=dat_pal[c][0];
                                       pal[k][1]=dat_pal[c][1];
                                       pal[k][2]=dat_pal[c][2];
                                       *(data+j+(i*tile_x))=k;
                                       break;
                                     }
                } // 1
               } // 2
              } // 3
             break;
    case 2 : /* Palette Scroll Define */
             printf("\nThis data is Palette scroll.... use color \n");
             for (i=0;i<256;i++) {
              if(pal[i][0]==0xff) {
               for (j=0;j<use_color;j++) {
                printf(" %d,",i+j);
                pal_flag[i+j]=2;
                pal[i+j][0]=dat_pal[j][0];
                pal[i+j][1]=dat_pal[j][1];
                pal[i+j][2]=dat_pal[j][2];
                }
               break;
              }
             }
             break;
    case 3 : /* Usuable Palette Define */
             for (i=0;i<256;i++) {
              if(pal[i][0]==0xff) {
               for (j=0;j<use_color;j++) {
                pal_flag[i+j]=0;
                pal[i+j][0]=dat_pal[j][0];
                pal[i+j][1]=dat_pal[j][1];
                pal[i+j][2]=dat_pal[j][2];
                }
               break;
              }
             }
             break;

    case 4 : /* Unusuable Palette Define */
             for (i=0;i<256;i++) {
              if(pal[i][0]==0xff) {
               for (j=0;j<use_color;j++) {
                pal_flag[i+j]=1;
                pal[i+j][0]=dat_pal[j][0];
                pal[i+j][1]=dat_pal[j][1];
                pal[i+j][2]=dat_pal[j][2];
                }
               break;
              }
             }
             break;
   } // switch
  for(i=0;i<256;i++)
   if(pal[i][0]==0xff) break;
  printf("\n Total %d / 256 Colors used....",i);
  if ((mode==0)||(mode==1)) {
   out_fp=fopen(objname,"wb");
   if (out_fp==NULL) {printf("\nOut File error....");exit(1);}
   fseek(out_fp,0,SEEK_SET);
   fputc(mode,out_fp);
   fwrite(&tile_x,4,1,out_fp);
   fwrite(&tile_y,4,1,out_fp);
   fwrite(data,tile_x*tile_y,1,out_fp);
   fclose(out_fp);
  } // if
  free(data);
 } while(yesno());
  for(i=0;i<256;i++) {
   if(pal[i][0]==0xff) { pal[i][0]=0;
                         pal[i][1]=0;
                         pal[i][2]=0;
                       }
   }
  pal_fp=fopen(palname,"wb");
  if(pal_fp==NULL) {printf("\n Palette file making error....");exit(1);}
  fseek(pal_fp,0,SEEK_SET);
  fwrite(pal,768,1,pal_fp);
  fclose(pal_fp);
  printf("\n Processing End......");
 }

char *make_obj_name(char *in_name)
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
char *make_dat_name(char *in_name)
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
   *(out_name+point_pos+1)='d';
   *(out_name+point_pos+2)='a';
   *(out_name+point_pos+3)='t';
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
int yesno2()
 {
  char *yn;
  printf("\nDo you want existed palette ? ");
  cin >> yn;
  if ((yn[0]=='Y')||(yn[0]=='y')) return 1;
  return 0;
 }

// ..RUNE.. 1996.3.25 Sprite behavior maker...
// Nam gi hoon

#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <iostream.h>
#include <i86.h>
#include <stdlib.h>
#include <string.h>

void main()
 {
  FILE *data,*map,*datb;
  char *dataa,*datab,*tile_map;
  int map_x,map_y,map2_x,map2_y;
  int temps;
  unsigned char *temp,*map_data;

  printf("\nInput the *.dat file a: ");
  cin>>dataa;
  printf("\nInput the *.dat file b: ");
  cin>>datab;
  printf("\nInput the *.ax file : ");
  cin>>tile_map;

  data=fopen("ene1.dat","rb");
  if (data==NULL) {printf("\n*.dat file A error...");exit(1);}
  datb=fopen(datab,"rb");
  if (datb==NULL) {printf("\n*.dat file B error...");exit(1);}
  map=fopen(tile_map,"wb");
  if (map==NULL) {printf("\n*.ax file error...");exit(1);}
  temps=fgetc(data);
  temps=fgetc(datb);
  fread(&map_x,4,1,data);
  fread(&map_y,4,1,data);
  fread(&map2_x,4,1,datb);
  fread(&map2_y,4,1,datb);
  temp=(unsigned char *)malloc(map_x);
  fread(temp,map_x,1,data);
  fread(temp,map2_x,1,data);
  map_data=(unsigned char *)malloc(map_x*(map_y+map2_y-2));
  fread(map_data,map_x*(map_y-1),1,data);
  fread(map_data+map_x*(map_y-2),map_x*(map2_y-1),1,datb);
  fclose(data);
  fclose(datb);
  map_y+=map2_y;
  fwrite(&map_x,4,1,map);
  fwrite(&map_y,4,1,map);
  fwrite(map_data,map_x*map_y,1,map);
  fclose(map);
  free(temp);
  free(map_data);
  printf("\n Good bye...");
 }




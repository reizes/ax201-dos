// ..RUNE.. 1996.3.25 Tile map maker...
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
  FILE *dat,*map;
  char *data,*tile_map;
  int map_x,map_y;
  int temps;
  unsigned char *temp,*map_data;

  printf("\nInput the *.dat file : ");
  cin>>data;
  printf("\nInput the *.map file : ");
  cin>>tile_map;

  dat=fopen(data,"rb");
  if (dat==NULL) {printf("\n*.dat file error...");exit(1);}
  map=fopen(tile_map,"wb");
  if (map==NULL) {printf("\n*.map file error...");exit(1);}
  temps=fgetc(dat);
  fread(&map_x,4,1,dat);
  fread(&map_y,4,1,dat);
  temp=(unsigned char *)malloc(map_x);
  fread(temp,map_x,1,dat);
  map_data=(unsigned char *)malloc(map_x*(map_y-1));
  fread(map_data,map_x*(map_y-1),1,dat);
  fclose(dat);
  fwrite(&map_x,4,1,map);
  fwrite(&map_y,4,1,map);
  fwrite(map_data,map_x*(map_y-1),1,map);
  fclose(map);
  free(temp);
  free(map_data);
  printf("\n Good bye...");
 }




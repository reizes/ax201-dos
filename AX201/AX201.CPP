// ..RUNE..     Reizes Nam gi hoon
//                  1996. 3. 24
//   AX-201   Shooting Game

#include <iostream.h>
#include <dos.h>
#include <i86.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <math.h>
#include "key.h"
#include "sound.h"

#define tile_line_print(ST,END,NO,OFF) tile_print4(bg[NO].width,END-ST+1,(DWORD)(bg[NO].tile_data+(bg[NO].width*ST)),OFF,760-(bg[NO].width));
#define check_col(AX,AW,AY,AH,BX,BW,BY,BH) ((abs(AX-BX)<((AW>>1)+(BW>>1)))&&(abs(AY-BY)<((AH>>1)+(BH>>1))))
typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

typedef struct {
                      BYTE *tile_data;
                      int width,height;
                 } tile;
typedef struct {
                int width,height;
                void (*code)();
               } sprite;

Module *music,*die,*title,*end;
Sample *shoot,*boom_s,*get_item_s,*appear,*ax_bomb_s,*e_bomb_s,*e_boom_s,*e_s;
Sample *click;

//static object space;
static sprite space[3],item[12],enemy[6],bomb[8],font[2],boom[8],boss,l_num[10],s_num[10];
static sprite bonus,cont,stage1,gameover;
static BYTE *visual_page;
static BYTE *base;
static BYTE pal[768],pal_temp[768];
static   BYTE bpal[768];
static WORD Port;
static BYTE IRQ,DRQ;
static tile bg[10];
static int scroll_status=0,scroll_flag=0,game_flag=0,delay_timer=0,scroll_speed=0,scroll_speed_temp;
static int scroll_timer=16,scroll_v=0,v_flag=0;
static int cont_counter=0,game_end=0,temp=0,p_flag=0;
static long int loop_counter=0,die_point=0,game_counter=0;
//static BYTE map[8][199];
static BYTE *map,*ene;
// width/byte,height,buff,off,space
static unsigned int spr_off;

void set_offset();
#pragma aux set_offset= \
 "mov ebx,spr_off "\
 modify[ebx];

void push_ebx();
#pragma aux push_ebx= \
 "push ebx "\
 modify[ebx];

void pop_ebx();
#pragma aux pop_ebx= \
 "pop ebx "\
 modify[ebx];

void scroll_init();
void view_screen(DWORD);
#pragma aux view_screen=\
 "   mov edi,0xa0000"\
 "   mov ecx,200 "\
 "z: push ecx    "\
 "   mov ecx,80  "\
 "   rep movsd   "\
 "   add esi,440 "\
 "   pop ecx     "\
 "   loop z      "\
parm [esi] \
modify [ecx esi edi];

#include "key.cpp"

void tile_print4(int ,int ,DWORD ,DWORD ,int );
#pragma aux tile_print4= \
 "    shr eax,2   "\
 "    mov ecx,ebx "\
 " a: push ecx    "\
 "    mov ecx,eax "\
 "    rep movsd   "\
 "    add edi,edx "\
 "    pop ecx     "\
 "    loop a      "\
 parm [eax] [ebx] [esi] [edi] [edx] \
 modify [eax ebx ecx esi edi edx] ;

void tile_print2(int ,int ,DWORD ,DWORD ,int );
#pragma aux tile_print2= \
 "    shr eax,1     "\
 "    mov ecx,ebx "\
 " b: push ecx    "\
 "    mov ecx,eax "\
 "    rep movsw   "\
 "    add edi,edx "\
 "    pop ecx     "\
 "    loop b      "\
 parm [eax] [ebx] [esi] [edi] [edx] \
 modify [eax ebx ecx esi edi edx] ;


void tile_print(int ,int ,DWORD ,DWORD ,int );
#pragma aux tile_print= \
 "    mov ecx,ebx "\
 " c: push ecx    "\
 "    mov ecx,eax "\
 "    rep movsb   "\
 "    add edi,edx "\
 "    pop ecx     "\
 "    loop c      "\
 parm [eax] [ebx] [esi] [edi] [edx] \
 modify [eax ebx ecx esi edi edx] ;

void key_control();
void destruct_ax_bullet(int num);
void process_ax_bullet();
void make_ax_bullet(int x,int y);
void protect_ax_201();
void make_ax_bomb(int x,int y);
void view_ax_bomb();
void destruct_ax_bomb(int num);
void process_ax_bomb();
void enemy_destruct(int num);
void set_block_pal(BYTE *buf,BYTE st_color,int su);
void enemy_control(int num) ;
void view_info();
void scroll_fast(int dot,int flag);
void scroll(int tile_flag);
void view_ax_201();
void view_ax_bullet();
void destruct_enemy(int num,int power);
void destruct_e_bomb(int num);
void set_videomode(short mode);
void make_enemy() ;
#include "ax-obj.cpp"
void set_scroll_speed(int A)
 { if (A<10) {v_flag=1;scroll_v=10-A;}
   else {scroll_speed=A-10;
   scroll_speed_temp=A-10;}
 }

int pal_fade_blash(int delay)
{
 int i,j,flag=1;

 for (i=0;i<768;i++) {
  pal_temp[i]++;
  if (pal_temp[i]>255) pal_temp[i]=255;
  }
 for (i=0;i<768;i++) if (pal_temp[i]!=255) flag=0;

 set_block_pal(pal_temp,0,256);
 for (i=0;i<delay;i++) {;;}
 return flag;
}
void pal_fade_control(BYTE *in_buff,BYTE *buff,int per)
 {
  int i;
  for (i=0;i<256;i++) {
   *(buff++)=((int)in_buff[i*3+0]*(int)per)/100;
   *(buff++)=((int)in_buff[i*3+1]*(int)per)/100;
   *(buff++)=((int)in_buff[i*3+2]*(int)per)/100;
  }
 }

void set_block_pal(BYTE *buf,BYTE st_color,int su)
 {
  int i;
  outp(0x3c8,st_color);
  for(i=0;i<su*3;i++)
   outp(0x3c9,*(buf+i));
 }

void set_videomode(short mode)
 {
  union REGS r;
  r.w.ax=mode;
  int386(0x10,&r,&r);
 }

void read_pal()
 {
  FILE *fp;
  fp=fopen("pal.ax","rb");
  if (fp==NULL) {printf("\nPalette file error...");exit(1);}
  fread(pal,768,1,fp);
  fclose(fp);
 }
void read_sprite()
 {
  int i,code_length;
  FILE *fp;
  void *co;
  char *sp[3]={"space1.cod","space2.cod","space3.cod"};
  char *it[12]={"item4.cod","item3.cod","item2.cod","item1.cod","item8.cod","item7.cod"
               ,"item6.cod","item5.cod","item12.cod","item11.cod","item10.cod","item9.cod"};
  char *en[6]={"enemy1.cod","enemy2.cod","enemy3.cod","enemy4.cod","enemy5.cod","enemy6.cod"};
  char *bom[8]={"bomb1.cod","bomb2.cod","bomb3.cod","bomb4.cod","bomb5.cod","bomb6.cod","bomb7.cod","bomb8.cod"};
  char *fon[2]={"font1.cod","font2.cod"};
  char *boo[8]={"boom1.cod","boom2.cod","boom3.cod","boom4.cod","boom5.cod","boom6.cod","boom8.cod","boom7.cod"};
  char *bos="boss1.cod";
  char *l1[10]={"l0.cod","l1.cod","l2.cod","l3.cod","l4.cod","l5.cod","l6.cod","l7.cod","l8.cod","l9.cod"};
  char *s1[10]={"0.cod","1.cod","2.cod","3.cod","4.cod","5.cod","6.cod","7.cod","8.cod","9.cod"};

  for(i=0;i<3;i++) {
   fp=fopen(sp[i],"rb");
   fseek(fp,-12,SEEK_END);
   fread(&space[i].width,4,1,fp);
   fread(&space[i].height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   space[i].code=(void (*)())co;
  }
  for(i=0;i<12;i++) {
   fp=fopen(it[i],"rb");
   fseek(fp,-12,SEEK_END);
   fread(&item[i].width,4,1,fp);
   fread(&item[i].height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   item[i].code=(void (*)())co;
  }
  for(i=0;i<6;i++) {
   fp=fopen(en[i],"rb");
   fseek(fp,-12,SEEK_END);
   fread(&enemy[i].width,4,1,fp);
   fread(&enemy[i].height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   enemy[i].code=(void (*)())co;
  }
  for(i=0;i<8;i++) {
   fp=fopen(bom[i],"rb");
   fseek(fp,-12,SEEK_END);
   fread(&bomb[i].width,4,1,fp);
   fread(&bomb[i].height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   bomb[i].code=(void (*)())co;
  }
  for(i=0;i<2;i++) {
   fp=fopen(fon[i],"rb");
   fseek(fp,-12,SEEK_END);
   fread(&font[i].width,4,1,fp);
   fread(&font[i].height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   font[i].code=(void (*)())co;
  }
  for(i=0;i<8;i++) {
   fp=fopen(boo[i],"rb");
   fseek(fp,-12,SEEK_END);
   fread(&boom[i].width,4,1,fp);
   fread(&boom[i].height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   boom[i].code=(void (*)())co;
  }
  for(i=0;i<1;i++) {
   fp=fopen(bos,"rb");
   fseek(fp,-12,SEEK_END);
   fread(&boss.width,4,1,fp);
   fread(&boss.height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   boss.code=(void (*)())co;
  }
  for(i=0;i<10;i++) {
   fp=fopen(l1[i],"rb");
   fseek(fp,-12,SEEK_END);
   fread(&l_num[i].width,4,1,fp);
   fread(&l_num[i].height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   l_num[i].code=(void (*)())co;
  }
  for(i=0;i<10;i++) {
   fp=fopen(s1[i],"rb");
   fseek(fp,-12,SEEK_END);
   fread(&s_num[i].width,4,1,fp);
   fread(&s_num[i].height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   s_num[i].code=(void (*)())co;
  }
   fp=fopen("bonus.cod","rb");
   fseek(fp,-12,SEEK_END);
   fread(&bonus.width,4,1,fp);
   fread(&bonus.height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   bonus.code=(void (*)())co;
   fp=fopen("continue.cod","rb");
   fseek(fp,-12,SEEK_END);
   fread(&cont.width,4,1,fp);
   fread(&cont.height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   cont.code=(void (*)())co;
   fp=fopen("stage1.cod","rb");
   fseek(fp,-12,SEEK_END);
   fread(&stage1.width,4,1,fp);
   fread(&stage1.height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   stage1.code=(void (*)())co;
   fp=fopen("gameover.cod","rb");
   fseek(fp,-12,SEEK_END);
   fread(&gameover.width,4,1,fp);
   fread(&gameover.height,4,1,fp);
   fread(&code_length,4,1,fp);
   fseek(fp,0,SEEK_SET);
   co=malloc(code_length);
   if (co==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(co,code_length,1,fp);
   fclose(fp);
   gameover.code=(void (*)())co;
 }
void pcx_read(char *fname)
 {

  struct HEADER {
   BYTE marker,version,code,bpp;
   WORD x1,y1,x2,y2,hres,vres;
   BYTE palette[48];
   BYTE vmode,nplanes;
   WORD bpl;
   WORD palinfo;
   WORD shres,svres;
   BYTE unused[54];
   } header;
  WORD c,i;
  BYTE *offset,*temp;
  FILE *fp;
  offset=(BYTE *)0xa0000;
  if ((fp=fopen(fname,"rb"))==NULL) {
//     printf("Open error %s file",fname);
    }
  fread(&header,sizeof(header),1,fp);
  do{
     c=(fgetc(fp)&0xff);
     if((c&0xc0)==0xc0) {
      i=c&0x3f;
      c=fgetc(fp);
      while(i--) *(offset++)=c;
      }
     else *(offset++)=c;
    } while(offset<(BYTE *)(0xa0000+64000));
  fseek(fp,-769L,SEEK_END);
  fgetc(fp);
  fread(bpal,1,768,fp);
  fclose(fp);
  for (i=0;i<768;i++) bpal[i]>>=2;
  set_block_pal(bpal,0,256);
 }
void read_map()
 {
  int map_x,map_y;
  FILE *fp;
  fp=fopen("map.ax","rb");
  if(fp==NULL) {printf("\nMap file error....");exit(1);}
  fread(&map_x,4,1,fp);
  fread(&map_y,4,1,fp);
  map=(BYTE *)malloc(map_x*map_y);
  if (map==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(map,map_x*map_y,1,fp);
  fclose(fp);
 }
void read_ene()
 {
  int map_x,map_y;
  FILE *fp;
  fp=fopen("ene.ax","rb");
  if(fp==NULL) {printf("\nEnemy file error....");exit(1);}
  fread(&map_x,4,1,fp);
  fread(&map_y,4,1,fp);
  ene=(BYTE *)malloc(map_x*map_y);
  if (ene==NULL) {printf("\nNot enough memory...");exit(1);}
   fread(ene,map_x*map_y,1,fp);
  fclose(fp);
 }
void read_tile()
 {
  int i,temp;
  FILE *tile;
  BYTE index[5];

  tile=fopen("tile.ax","rb");
  if (tile==NULL) {printf("\nTile file error...");exit(1);}

 for(i=0;i<10;i++)
   {
    temp=fgetc(tile);
    fread(&(bg[i].width),4,1,tile);
    fread(&(bg[i].height),4,1,tile);
    bg[i].tile_data=(BYTE *)malloc(bg[i].width*bg[i].height);
    if (bg[i].tile_data==NULL) {printf("\nNot enough memory...");exit(1);}
     fread(bg[i].tile_data,bg[i].width*bg[i].height,1,tile);
    fread(index,5,1,tile);
   }
   fclose(tile);
   scroll_init();
 }
void free_tile()
 { int i;
  for (i=0;i<10;i++) free(bg[i].tile_data);
 }
void scroll_init()
 {
  int i;
  BYTE *temp;
  for (i=7;i<10;i++) {
   temp=(BYTE *)malloc(bg[i].width*bg[i].height*2);
   if (temp==NULL) {printf("\nNot enough memory...");exit(1);}
    memmove(temp,bg[i].tile_data,bg[i].width*bg[i].height);
   memmove(temp+(bg[i].width*bg[i].height),bg[i].tile_data,bg[i].width*bg[i].height);
   free(bg[i].tile_data);
   bg[i].tile_data=temp;
   bg[i].height*=2;
   }
 }

void tile_scroll(int d)
 {
  static int spilit_flag=0;
  static int start1=177,middle1=377,start2=0,end=0;
  tile_line_print(start1,middle1,7,(DWORD)base);
  tile_line_print(start1,middle1,8,(DWORD)base+239);
  if (!spilit_flag) {start1-=d; middle1-=d;}
  if (start1<0) { spilit_flag=1;start1=378-d;end=middle1;middle1=377;start2=0;}
  if (spilit_flag) {
          tile_line_print(start2,end,7,(DWORD)base+152000-(end*760));
          tile_line_print(start2,end,8,(DWORD)base+152239-(end*760));
          end-=d;start1-=d;
          if (end<0) spilit_flag=0;
          }
 }
void tile_scroll_c(int d)
 {
  static int spilit_flag=0;
  static int start1=177,middle1=377,start2=0,end=0;
  loop_counter++;
  tile_line_print(start1,middle1,9,(DWORD)base+80);
  if (!spilit_flag) {start1-=d; middle1-=d;}
  if (start1<0) { spilit_flag=1;start1=378-d;end=middle1;middle1=377;start2=0;}
  if (spilit_flag) {
          tile_line_print(start2,end,9,(DWORD)base+152080-(end*760));
          end-=d;start1-=d;
          if (end<0) spilit_flag=0;
          }
 }
void init_sound()
 {
  MODDetectCard(&Port,&IRQ,&DRQ);
  music=MODLoadModule("atlantic.mod");
  die=MODLoadModule("cd_star.mod");
  title=MODLoadModule("giveinp.mod");
  end=MODLoadModule("eon.mod");
  boom_s=MODLoadSample("pung2.wav");
  shoot=MODLoadSample("beam.wav");
  get_item_s=MODLoadSample("item.wav");
  appear=MODLoadSample("beamup2.wav");
  ax_bomb_s=MODLoadSample("bomb.wav");
  e_bomb_s=MODLoadSample("bomb2.wav");
  e_boom_s=MODLoadSample("bei2.wav");
  e_s=MODLoadSample("entbeep.wav");
 click=MODLoadSample("click21.wav");
}

void init()
 {
  int i;
  printf("\nInput the game speed (Normal 10) :");
  cin>>i;
  if (i==1234) {i=10;p_flag=1;}
  set_scroll_speed(i);
  printf("\n Init Sound.....");
  init_sound();
  printf("\nReading Palette...");
  read_pal();
  printf("\nReading Tile....");
  read_tile();
  printf("\nReading Map....");
  read_map();
  printf("\nReading Enemy.....");
  read_ene();
  printf("\nReading Sprite....");
  read_sprite();
  printf("\nInit....");
  visual_page=(BYTE *)malloc(760*460);
  if (visual_page==NULL) {printf("\nNot enough memory....");exit(1);}
  base=visual_page+220+130*760;
  init_key();
  init_ax_201();
  for (i=0;i<100;i++)
    enemy_list[i].use=-1;
  for (i=0;i<200;i++)  e_bullet_list[i].use=-1;
  for (i=0;i<50;i++)
    ax_bullet_list[i].use=-1;
  for (i=0;i<100;i++) e_bomb_list[i].use=-1;
  for(i=0;i<50;i++) ax_bomb_list[i].use=-1;
  init_value();
 }
void ending()
 {
  int i;
  MODStopModule();
  MODFreeModule(music);
  MODFreeModule(die);
  MODFreeModule(title);
  MODFreeModule(end);
  MODFreeSample(boom_s);
  MODFreeSample(shoot);
  MODFreeSample(get_item_s);
  MODFreeSample(appear);
  MODFreeSample(ax_bomb_s);
  MODFreeSample(e_bomb_s);
  MODFreeSample(e_boom_s);
  MODFreeSample(e_s);
  MODFreeSample(click);

  free_tile();
  free(visual_page);
  free(map);
  for(i=0;i<3;i++) free(space[i].code);
  for(i=0;i<12;i++) free(item[i].code);
  for(i=0;i<6;i++) free(enemy[i].code);
  for(i=0;i<8;i++) free(bomb[i].code);
  for(i=0;i<2;i++) free(font[i].code);
  for(i=0;i<8;i++) free(boom[i].code);
  free(boss.code);
  for(i=0;i<10;i++) free(l_num[i].code);
  for(i=0;i<10;i++) free(s_num[i].code);
  free(bonus.code);
  free(cont.code);
  free(stage1.code);
  free(gameover.code);
  del_key();
 }

void map_print(int d)
 {
  static int tile_index=0;
  static int scroll_counter=-80;
  int i,j;
  DWORD offset;

 for (j=0;j<6;j++) {
  for (i=0;i<8;i++)
    { if (*(map+i+(tile_index+j)*8)) {
         offset=(DWORD)base+(i*40)+182400-(j*30400)+(scroll_counter*760);
         tile_print4(40,40,(DWORD)bg[*(map+i+(tile_index+j)*8)-1].tile_data,offset,720);
        }
    }
  }
  scroll_counter+=d;
  if(scroll_counter>-40) {scroll_counter=-80;tile_index++;scroll_flag=1;}
  scroll_status=tile_index;
 }
void process_scroll(int dot,int flag)
 {
  if (v_flag) scroll_fast(dot,flag);
   else scroll(flag);
 }
void scroll_fast(int dot,int flag)
 {
  tile_scroll_c(dot*scroll_v);
  tile_scroll(dot*2*scroll_v);
  if (flag) map_print(dot*4*scroll_v);
 }
void scroll(int tile_flag)
 {
  if (scroll_speed>0) { tile_scroll_c(0);tile_scroll(0);
                        if (tile_flag) map_print(0);
                        scroll_speed--;
                        return; }
  if (scroll_timer%4==0) tile_scroll_c(1);
   else tile_scroll_c(0);
  if (scroll_timer%2==0) tile_scroll(1);
   else tile_scroll(0);
  if (tile_flag) map_print(1);
   scroll_timer--;
  if (scroll_timer<0) scroll_timer=16;
   scroll_speed=scroll_speed_temp;
 }
void print_cont(int cont_counter)
 {
    spr_off=(DWORD)base+81+90*760;
         push_ebx();
            set_offset();
           (cont.code)();
               pop_ebx();
    spr_off=(DWORD)base+210+93*760;
            push_ebx();
             set_offset();
         (l_num[9-cont_counter].code)();
            pop_ebx();
  }
void game_cont()
 {
  if (scan[_ESC]) {MODStopModule();game_end=1;}
  if (scan[_SPACE]) {die_point=0;game_flag=0; delay_timer=loop_counter;
                     ax_boom_flag=1;
                     ax_201.control_flag=0;
                     ax_201.dasu=5;
                     ax_201.score=0;
                     ax_201.x=145;
                     ax_201.y=180;
                     MODStopModule();
                     MODPlayModule(music,8,22222,Port,IRQ,DRQ,PM_TIMER);
                   }
  print_cont(cont_counter);
  if ((game_counter%80)!=0) return;
  MODPlaySample(5,click);
  cont_counter++;
  if (cont_counter==10) game_end=1;
 }
void tit()
 {
  int i,j;
  MODPlayModule(title,8,22222,Port,IRQ,DRQ,PM_TIMER);
  scan[_SPACE]=0;
  for(i=100;i>=0;i--) {pal_fade_control(bpal,pal_temp,i);
                       set_block_pal(pal_temp,0,256);
                       for(j=1;j<500;j++) {;;}
                      }
  pcx_read("title.ax");
  for(i=0;i<=100;i++) {pal_fade_control(bpal,pal_temp,i);
                       set_block_pal(pal_temp,0,256);
                       for(j=1;j<500;j++) {;;}
                      }
  do {
  ;
  }while(scan[_SPACE]==0);
  for(i=100;i>=0;i--) {pal_fade_control(bpal,pal_temp,i);
                       set_block_pal(pal_temp,0,256);
                       for(j=1;j<500;j++) {;;}
                      }
  MODStopModule();
 }

void main()
 {
  int x,y,i,j,k,cont_counter=0;

  init();
  set_videomode(0x13);
  tit();
  set_block_pal(pal,0,256);
  for (i=0;i<768;i++) pal_temp[i]=pal[i];
  MODPlayModule(music,8,22222,Port,IRQ,DRQ,PM_TIMER);
  do {
         if (game_counter<=100) {pal_fade_control(pal,pal_temp,game_counter);
                                 set_block_pal(pal_temp,0,256);
                                }
         if (game_counter<500) process_scroll(1,0);
             else {
                    if (scroll_status<392) process_scroll(1,1);
                      else {
                             tile_scroll_c(0);tile_scroll(0);
                             map_print(0);
                           }
                 }
                       make_enemy();
                       process_boom();
                       process_enemy();
                       process_e_bomb_boom();
                       process_e_bullet();
                       process_ax_bomb();
                       process_ax_bullet();
                       process_item();
                       protect_ax_201();
                       process();
                       view_e_bomb_boom();
                       view_item();
                       view_boom();
                       view_e_bullet();
                       view_enemy();
    if (game_flag!=-1) {key_control();
                       view_ax_201();}
                       view_ax_bullet();
                       view_ax_bomb();
                       view_info();
    if (die_point!=0) ax_201.view=-1;
    if (((game_counter-die_point)<500)&&(die_point!=0))
                          { spr_off=(DWORD)base+89+90*760;
                            push_ebx();
                            set_offset();
                            (gameover.code)();
                            pop_ebx();
                          }
    if (((game_counter-die_point)>550)&&(die_point!=0)) game_cont();
    if (game_counter<500) {spr_off=(DWORD)base+105+91*760;
                            push_ebx();
                            set_offset();
                            (stage1.code)();
                            pop_ebx();
                           }
    if (scan[_ESC]) break;
    view_screen((DWORD)base);
    game_counter++;
  } while(game_end==0);
  MODStopModule();
  for(i=100;i>=0;i--) {pal_fade_control(pal,pal_temp,i);
                       set_block_pal(pal_temp,0,256);
                       for(j=1;j<500;j++) {;;}
                      }
  pcx_read("ending.ax");
  for(i=0;i<=100;i++) {pal_fade_control(bpal,pal_temp,i);
                       set_block_pal(pal_temp,0,256);
                       for(j=1;j<500;j++) {;;}
                      }
  MODPlayModule(end,8,22222,Port,IRQ,DRQ,PM_TIMER);
  do {
  ;
  }while(scan[_SPACE]==0);
  MODStopModule();
  ending();
  printf("\nThis game is imperfect.....Please wait....");
  set_videomode(3);
}
void key_control()
 {
  int key_flag=0;
   if (ax_201.control_flag) {
    if (scan[_LEFT]) { ax_201.x-=2;ax_201.frame=2;key_flag=1;
                      if (ax_201.x<0) ax_201.x=0;
                     }
    if (scan[_UP]) { ax_201.y-=2;
                    if (ax_201.y<0) ax_201.y=0;
                   }
    if (scan[_RIGHT]) { ax_201.x+=2;ax_201.frame=1;key_flag=1;
                    if (ax_201.x>(320-ax_201.sx)) ax_201.x=320-ax_201.sx;
                      }
    if (scan[_DOWN]) {ax_201.y+=2;
                    if (ax_201.y>(200-ax_201.sy)) ax_201.y=200-ax_201.sy;
                      }
    if (scan[_ALT]) {scan[_ALT]=0;make_ax_bullet(ax_201.x+(ax_201.sx>>1)-(ax_201.power<<1),ax_201.y-11);}
    if (scan[_CTRL]){scan[_CTRL]=0;make_ax_bomb(ax_201.x,ax_201.y);}
    if (!key_flag) ax_201.frame=0;
    }
    ax_201.sx=space[ax_201.frame].width;
    ax_201.sy=space[ax_201.frame].height;
  }
void protect_ax_201()
 {
  if (ax_201.protect_timer<0) {ax_201.view=0;return;}
  if (ax_201.timer<0) {ax_201.view= (ax_201.view==0) ? -1 : 0;ax_201.timer=3;ax_201.protect_timer--;}
  ax_201.timer--;
 }

void make_ax_bomb(int x,int y)
 {
  int i,flag=0;
  ax_201.bombs--;
  if (ax_201.bombs<0) return;
  for(i=0;i<50;i++) if(ax_bomb_list[i].use==-1) {flag=1;break;}
  if (flag==0) return;
  ax_bomb_list[i].use=0;
  ax_bomb_list[i].frame=7;
  ax_bomb_list[i].x=x-bomb[7].width;
  ax_bomb_list[i].y=y-bomb[7].height;
  ax_bomb_list[i].sx=bomb[7].width;
  ax_bomb_list[i].sy=bomb[7].height;
  ax_bomb_list[i].for_x=-1;
  ax_bomb_list[i].for_y=-2;
  ax_bomb_list[i].v=2;
  ax_bomb_list[i].power=50;
  for(i=0;i<50;i++) if(ax_bomb_list[i].use==-1) {flag=1;break;}
  if (flag==0) return;
  ax_bomb_list[i].use=0;
  ax_bomb_list[i].frame=7;
  ax_bomb_list[i].x=x+ax_201.sx;
  ax_bomb_list[i].y=y-bomb[7].height;
  ax_bomb_list[i].sx=bomb[7].width;
  ax_bomb_list[i].sy=bomb[7].height;
  ax_bomb_list[i].for_x=1;
  ax_bomb_list[i].for_y=-2;
  ax_bomb_list[i].v=2;
  ax_bomb_list[i].power=50;
  for(i=0;i<50;i++) if(ax_bomb_list[i].use==-1) {flag=1;break;}
  if (flag==0) return;
  ax_bomb_list[i].use=0;
  ax_bomb_list[i].frame=7;
  ax_bomb_list[i].x=x-(bomb[7].width-ax_201.sx);
  ax_bomb_list[i].y=y-bomb[7].height;
  ax_bomb_list[i].sx=bomb[7].width;
  ax_bomb_list[i].sy=bomb[7].height;
  ax_bomb_list[i].for_x=0;
  ax_bomb_list[i].for_y=-2;
  ax_bomb_list[i].v=2;
  ax_bomb_list[i].power=50;
  MODPlaySample(6,ax_bomb_s);
  // Sound....
 }

void view_ax_bomb()
 {
  int i;
  for (i=0;i<50;i++) {if (ax_bomb_list[i].use==0)
                       { spr_off=(DWORD)base+ax_bomb_list[i].x+ax_bomb_list[i].y*760;
                         push_ebx();
                         set_offset();
                         (bomb[ax_bomb_list[i].frame].code)();
                         pop_ebx();
                       }  //if
                     } //for
 }

void destruct_ax_bomb(int num)
 {
  ax_bomb_list[num].use=-1;
 }
void process_ax_bomb()
 {
  int i,j;
  for (i=0;i<50;i++) {
   if (ax_bomb_list[i].use==0) { ax_bomb_list[i].x+=(ax_bomb_list[i].for_x);
                                 ax_bomb_list[i].y+=(ax_bomb_list[i].for_y);
                                  if ((ax_bomb_list[i].y)<-40) destruct_ax_bomb(i);
                                  for(j=0;j<100;j++) {
                                   if (enemy_list[j].use==0) {
                                      if (check_col(ax_bomb_list[i].x,ax_bomb_list[i].sx,ax_bomb_list[i].y,ax_bomb_list[i].sy,
                                          enemy_list[j].x,enemy_list[j].sx,enemy_list[j].y,enemy_list[j].sy))
                                        { destruct_enemy(j,ax_bomb_list[i].power);}
                                      }//if
                                    }//for
                                  for(j=0;j<200;j++) {
                                   if (e_bullet_list[j].use==0) {
                                      if (check_col(ax_bomb_list[i].x,ax_bomb_list[i].sx,ax_bomb_list[i].y,ax_bomb_list[i].sy,
                                          e_bullet_list[j].x,e_bullet_list[j].sx,e_bullet_list[j].y,e_bullet_list[j].sy))
                                         { destruct_e_bullet(j);}
                                       } //if
                                   } //for
                                  for(j=0;j<100;j++) {
                                   if (e_bomb_list[j].use==0) {
                                      if (check_col(ax_bomb_list[i].x,ax_bomb_list[i].sx,ax_bomb_list[i].y,ax_bomb_list[i].sy,
                                          e_bomb_list[j].x,e_bomb_list[j].sx,e_bomb_list[j].y,e_bomb_list[j].sy))
                                         { destruct_e_bomb(j);}
                                       } //if
                                   }//for
                                } //if
  } //for
 }


void view_ax_201()
 {
    if (ax_201.view==-1) return;
    spr_off=(DWORD)base+ax_201.x+ax_201.y*760;
    push_ebx();
    set_offset();
    (space[ax_201.frame].code)();
    pop_ebx();
 }

void view_ax_bullet()
 {
  int i;
  for (i=0;i<50;i++) {if (ax_bullet_list[i].use==0)
                       { spr_off=(DWORD)base+ax_bullet_list[i].x+ax_bullet_list[i].y*760;
                         push_ebx();
                         set_offset();
                         (bomb[ax_bullet_list[i].frame].code)();
                         pop_ebx();
                       }  //if
                     } //for
 }

void destruct_ax_bullet(int num)
 {
  // sound....
  ax_bullet_list[num].use=-1;
 }

void process_ax_bullet()
 {
  int i,j;
  for (i=0;i<50;i++) {
   if (ax_bullet_list[i].use==0) { ax_bullet_list[i].y-=(ax_bullet_list[i].v);
                                  if ((ax_bullet_list[i].y)<-(ax_bullet_list[i].sy)) destruct_ax_bullet(i);
                                  for(j=0;j<100;j++) {
                                   if (enemy_list[j].use==0) {
                                      if (check_col(ax_bullet_list[i].x,ax_bullet_list[i].sx,ax_bullet_list[i].y,ax_bullet_list[i].sy,
                                          enemy_list[j].x,enemy_list[j].sx,enemy_list[j].y,enemy_list[j].sy))
                                        { destruct_enemy(j,ax_bullet_list[i].power);destruct_ax_bullet(i);}
                                      }//if
                                   } //for
                                  for(j=0;j<50;j++) {
                                   if (e_bomb_list[j].use==0) {
                                      if (check_col(ax_bullet_list[i].x,ax_bullet_list[i].sx,ax_bullet_list[i].y,ax_bullet_list[i].sy,
                                          e_bomb_list[j].x,e_bomb_list[j].sx,e_bomb_list[j].y,e_bomb_list[j].sy))
                                         { destruct_e_bomb(j);destruct_ax_bullet(i);}
                                       } //if
                                   }//for
                                } //if
  } //for
 }


void make_ax_bullet(int x,int y)
 {
  int i,flag=0;
  MODPlaySample(7,shoot);
  for (i=0;i<50;i++) if (ax_bullet_list[i].use==-1) {flag=1;break;}
  if (flag==0) return;
  ax_bullet_list[i].use=0;
  ax_bullet_list[i].frame=ax_201.power-1; // power of weapon
  ax_bullet_list[i].x=x;
  ax_bullet_list[i].y=y;
  ax_bullet_list[i].sx=bomb[ax_bullet_list[i].frame].width;
  ax_bullet_list[i].sy=bomb[ax_bullet_list[i].frame].height;
  ax_bullet_list[i].v=3;
  ax_bullet_list[i].power=ax_power[ax_201.power-1];
  // Sound....
 }
void destruct_enemy(int num,int power)
 {
  enemy_list[num].hp-=power;
  if (enemy_list[num].hp<=0) {MODPlaySample(5,click);
                             ax_201.score+=enemy_list[num].score;
                             make_boom(enemy_list[num].x,enemy_list[num].y);
                             if (enemy_list[num].id==1) make_item(enemy_list[num].x,enemy_list[num].y);
                             enemy_list[num].use=-1;
                             }
  else {/*sound*/}
 }
void view_info()
 {
  int i,frame=0;
  char jumsu[20];

  for(i=0;i<ax_201.bombs;i++)
                       { spr_off=(DWORD)base+i*10+136820;
                         push_ebx();
                         set_offset();
                         (font[0].code)();
                         pop_ebx();
                       }
  for(i=0;i<ax_201.dasu;i++)
                       { spr_off=(DWORD)base+i*15+3820;
                         push_ebx();
                         set_offset();
                         (font[1].code)();
                         pop_ebx();
                       }
  itoa(ax_201.score,jumsu,10);
  for(i=0;i<strlen(jumsu);i++)
                       { spr_off=(DWORD)base+i*10+4020;
                         frame=jumsu[i]-'0';
                         push_ebx();
                         set_offset();
                         (s_num[frame].code)();
                         pop_ebx();
                       }
}



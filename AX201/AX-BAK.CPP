// Object class ....  ..Rune..
typedef struct {
                int frame;
                int x,y;
                int timer;
                int protect_timer;
                int control_flag; // 1 : enable , 0 : disable
                int old_x,old_y;
                int v;
                int hp;
                int score;
                int sx,sy;
                int dasu; // least spaces..
                int bombs;
                int power; // power of weapon
               } ax_object;
typedef struct {
                int use; // 0 : use -1 : no
                int frame;
                int x,y;
                int sx,sy;
                int hp;
                int v;
                int for_x,for_y;
                int power;
               } bullet_object;
typedef struct {
                int use;
                int frame;
                int id;  // if item....
                int score;
                int x,y;
                int timer;
                int old_x,old_y;
                int v;
                int sx,sy;
                int hp;
                int *way;
                int need_bullet;
                int move_counter;
               } enemy_object;

static ax_object ax_201;
static enemy_object enemy_list[64];
static bullet_object e_bullet_list[64];
static bullet_object ax_bullet_list[30];
static bullet_object ax_bomb_list[10];
static bullet_object e_bomb_list[30];
static int way_type_0[8]={3,3,0,-20,-100,-100,0,225};  // speed,datas number,data,...
static int way_type_1[8]={3,3,80,-20,-100,-100,80,225};
static int way_type_2[8]={3,3,160,-20,-100,-100,160,225};
static int way_type_3[8]={3,3,240,-20,-100,-100,240,225};
static int way_type_4[8]={3,3,300,-20,-100,-100,300,225};
static int way_type_5[16]={2,7,0,-20,60,108,123,80,89,35,17,117,-100,-100,160,225};
static int way_type_6[16]={2,7,300,-20,260,110,197,82,231,37,303,119,-100,-100,160,225};
static int way_type_7[14]={2,6,0,-20,0,150,-100,-100,300,150,300,60,80,-25};
static int way_type_8[14]={2,6,300,-20,300,150,-100,-100,0,150,0,60,240,-25};
static int way_type_9[14]={2,6,300,-20,0,60,200,120,100,150,-100,-100,0,225};
static int way_type_10[14]={2,6,0,-20,300,60,100,120,200,150,-100,-100,300,225};
static int way_type_11[10]={2,4,0,-20,0,60,-100,-100,160,225};
static int way_type_12[10]={2,4,300,-20,300,60,-100,-100,160,225};
static int *way[13]={way_type_0,way_type_1,way_type_2,way_type_3,way_type_4,way_type_5,way_type_6,way_type_7,
                     way_type_8,way_type_9,way_type_10,way_type_11,way_type_12};
static int way_status[13];
static int way_temp[2560];
static int enemy_scroll[200];
static int enemy_dash[10]={0,1,2,3,3,5,6,7,9,9}; // by ax-201
static int enemy_often[10]={10,15,20,20,25,30,40,50,50}; // by dash
static int enemy_bullet[10]={1,1,2,3,3,5,6,7,9,9}; //by dash
static int item_often[10]={2,2,3,5,5,7,7,7,3,3}; //by ax-201
static int enemy_score[6]={100,150,200,200,250,500};
static int enemy_hp[6]={1,1,5,10,20,70};
static int ax_power[5]={1,2,3,5,7};
static int now_enemy=0;

int make_way(int x1,int y1,int x2,int y2,int *buffer);
void make_enemy();
void view_enemy();
void delete_enemy(int num);
void process_enemy();
void make_e_bullet(int num);

void destruct_e_bullet(int num)
 {
 ;
 }
void make_enemy()
 {
  int i,j,v,dash,enemy_no,way_type,move_count=0;
  int point_su,x1,x2,y1,y2;
  v=((enemy_scroll[scroll_status]*3+ax_201.dasu*2+ax_201.power)/5)%10;
  dash=enemy_dash[v];
  if (now_enemy>enemy_often[dash]) return;
  for (i=0;i<64;i++) if (enemy_list[i].use==-1) break;
  for (j=0;j<64;j++) { if (check_col(enemy_list[i].x,enemy_list[i].sx,enemy_list[i].y,enemy_list[i].sy,
                         enemy_list[j].x,enemy_list[j].sx,enemy_list[j].y,enemy_list[j].sy)&&(i!=j))
                        return;
                     }
  now_enemy++;
  enemy_no=(v+dash)%6;
  enemy_list[i].use=0;
  enemy_list[i].frame=enemy_no;
  if ((v+dash)%item_often[dash]==0) enemy_list[i].id=v%3;  //item
   else enemy_list[i].id=-1;  //No item
  enemy_list[i].score=enemy_score[enemy_no];
  enemy_list[i].sx=enemy[enemy_no].width;
  enemy_list[i].sy=enemy[enemy_no].height;
  enemy_list[i].hp=enemy_hp[enemy_no];
  way_type=(v+dash)%13;
  way_status[way_type]++;
  if (way_status[way_type]>5) { for (j=0;j<13;j++) {if (way_status[j]<6) break;}
                                way_type=j;way_status[j]++;
                              }
  enemy_list[i].need_bullet=enemy_bullet[dash];
  enemy_list[i].move_counter=0;
  point_su=(way[way_type])[1];
  enemy_list[i].x=(way[way_type])[2];
  enemy_list[i].y=(way[way_type])[3];
  enemy_list[i].v=(way[way_type])[0];
  enemy_list[i].way=(int *)malloc(40000);
  for (j=0;j<point_su-1;j++)
   {
    x1=(way[way_type])[j+2];y1=(way[way_type])[j+3];
    x2=(way[way_type])[j+4];y2=(way[way_type])[j+5];
    if ((x1==-100)&&(y1==-100)) {x1=ax_201.x;y1=ax_201.y;}
    if ((x2==-100)&&(y2==-100)) {x2=ax_201.x;y2=ax_201.y;}
    move_count+=(make_way(x1,y1,x2,y2,enemy_list[i].way+move_count)*2);
   }
}

void view_enemy()
 {
  int i;
  for (i=0;i<64;i++) {
   if (enemy_list[i].use==0) {
                         spr_off=(DWORD)base+enemy_list[i].x+enemy_list[i].y*760;
                         push_ebx();
                         set_offset();
                         (enemy[enemy_list[i].frame].code)();
                         pop_ebx();
                         }
  }
 }
void delete_enemy(int num)
 {
  enemy_list[num].use=-1;
  free(enemy_list[num].way);
  now_enemy--;
  way_status[enemy_list[num].way_type]--;
 }
void destruct_ax_201()
 {
 ;
 }

void process_enemy()
 {
  int i;
  for(i=0;i<64;i++) {
   if (enemy_list[i].use==0) {
    enemy_list[i].move_counter++;
    enemy_list[i].x+=enemy_list[i].way[enemy_list[i].move_counter]*enemy_list[i].v;
    enemy_list[i].y+=enemy_list[i].way[enemy_list[i].move_counter+1]*enemy_list[i].v;
    if ((enemy_list[i].y<-24)||(enemy_list[i].y>224)) delete_enemy(i);
    if ((enemy_list[i].move_counter%10)==0) { if (enemy_list[i].need_bullet>0) make_e_bullet(i);
                              }
    if (check_col(enemy_list[i].x,enemy_list[i].sx,enemy_list[i].y,enemy_list[i].sy,
                  ax_201.x,ax_201.sx,ax_201.y,ax_201.sy))
    {destruct_ax_201();destruct_enemy(i,10);}
   } // if
  } // for
}
void make_e_bullet(int num)
 {
 ;
 }
void init_value()
 {
  int i;
  for(i=0;i<20;i++) enemy_scroll[i]=0;
  for(i=20;i<40;i++) enemy_scroll[i]=2;
  for(i=40;i<60;i++) enemy_scroll[i]=4;
  for(i=60;i<80;i++) enemy_scroll[i]=6;
  for(i=80;i<120;i++) enemy_scroll[i]=10;
  for(i=120;i<140;i++) enemy_scroll[i]=7;
  for(i=140;i<170;i++) enemy_scroll[i]=5;
  for(i=170;i<200;i++) enemy_scroll[i]=0;
  for(i=0;i<13;i++) way_status[i]=0;
 }

void init_ax_201()
 {
  ax_201.score=0;
  ax_201.frame=0;
  ax_201.x=145;
  ax_201.y=180;
  ax_201.timer=0;
  ax_201.protect_timer=10;
  ax_201.control_flag=1;
  ax_201.v=0;
  ax_201.hp=1;
  ax_201.sx=space[0].width;
  ax_201.sy=space[0].height;
  ax_201.dasu=3;
  ax_201.bombs=3;
  ax_201.power=1;
 }
int make_way(int x1,int y1,int x2,int y2,int *buffer)
 {
  int z;
  int x_delta,y_delta,i,distance,x_step,y_step,x=0,y=0,sx,sy;
  int *buff,length=0,buff_index=0,*temp;
  temp=buffer;
  x_delta=x2-x1;
  y_delta=y2-y1;
  sx=x1;sy=y1;
  if((x_delta==0)&&(y_delta==0)) {*temp=0;temp++;*(temp)=0;length++; return 1;}
  if (x_delta==0) {for(z=0;z<y_delta;z++) {*(temp)=0;temp++;*(temp)=1;temp++;length++;}
                    return y_delta;}
  if (y_delta==0) {for(z=0;z<x_delta;z++) {*(temp)=1;temp++;*(temp)=0;temp++;length++;}
                    return x_delta;}
  if (x_delta>0) x_step=1;
   else {x_step=-1;x_delta=x1-x2;}
  if (y_delta>0) y_step=1;
   else {y_step=-1;y_delta=y1-y2;}

  distance=(x_delta>y_delta) ? x_delta : y_delta;

  for (i=0;i<distance;i++) {
   x+=x_delta;
   y+=y_delta;
   if (x>distance) { x-=distance; sx+=x_step; *temp=x_step;temp++;} else {*temp=0;temp++;}
   if (y>distance) { y-=distance; sy+=y_step; *temp=y_step;temp++;} else {*temp=0;temp++;}
   }
   return distance;
 }



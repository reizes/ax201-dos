// Object class ....  ..Rune..
typedef struct {
                int frame;
                int x,y;
                int timer;
                int protect_timer;
                int control_flag; // 1 : enable , 0 : disable
                int v;
                int view;
                int hp;
                int score;
                int sx,sy;
                int dasu; // least spaces..
                int bombs;
                int power; // power of weapon
               } ax_object;

typedef struct {
                int use;
                int frame;
                int timer;
                int x,y;
               } boom_object;
typedef struct {
                int use; // 0 : use -1 : no
                int frame;
                int x,y;
                int sx,sy;
                int hp;
                int v;
                int for_x,for_y;
                int wh_x,wh_y;
                int power;
               } bullet_object;
typedef struct {
                int use;
                int frame;
                int id;  // if item....
                int score;
                int x,y;
                int timer,timer_count;
                int v;
                int sx,sy;
                int hp;
                int way_point[2][4];
                int need_bullet;
                int move_counter;
               } enemy_object;

static ax_object ax_201;
static enemy_object enemy_list[100];
static enemy_object item_list[100];
static bullet_object e_bullet_list[200];
static bullet_object ax_bullet_list[50];
static bullet_object ax_bomb_list[50];
static bullet_object e_bomb_list[100];
static boom_object e_bomb_boom[100];
static int ax_boom_flag=0;
static int enemy_scroll[200];
static int enemy_dash[10]={0,1,2,3,3,5,6,7,9,9}; // by ax-201
static int enemy_bullet[10]={1,1,2,3,3,5,6,7,9,9}; //by dash
static int ax_power[5]={1,2,3,5,7};
static int start_x[8]={0,40,80,120,160,200,240,300};
static boom_object boom_list[100];
void make_enemy();
void destruct_e_bullet(int num);
void destruct_e_bomb(int num);
void process_1(int num);
void process_2(int num);
void process_3(int num);
void process_4(int num);
void process_e_bullet();
void view_e_bullet();
void destruct_e_bullet(int num);
void view_enemy();
void delete_enemy(int num);
void process_enemy();
void make_e_bullet(int num,int type);
void type_1_set(int num,int x);
void type_2_set(int num,int x);
void make_boom(int x,int y);
void process_boom();
void destruct_boom(int num);
void view_boom();
void make_e_bomb_boom(int x,int y);
void process_e_bomb_boom();
void destruct_e_bomb_boom(int num);
void view_e_bomb_boom();
void type_3_set(int num,int x);
void type_4_set(int num,int x);
void type_5_set(int num,int x);
void type_6_set(int num,int x);
static void (*type_set[6])(int num,int x);
void new_ax_201();

void process()
 {
  if (ax_boom_flag==1) ax_201.view=-1;
  if (((loop_counter-delay_timer)<80)||(ax_boom_flag==0)) return;
  new_ax_201();
  ax_boom_flag=0;
 }

void destruct_ax_201()
 {
 if (p_flag==0) ax_201.dasu--;
 ax_201.view=-1;
 if (ax_201.dasu<0) {game_flag=-1;die_point=game_counter;
                     MODStopModule();
                     MODPlayModule(die,8,22222,Port,IRQ,DRQ,PM_TIMER);
                    }
 make_boom(ax_201.x,ax_201.y);
 delay_timer=loop_counter;
 ax_boom_flag=1;
 ax_201.control_flag=0;
 }
void new_ax_201()
 {
  MODPlaySample(5,appear);
  ax_201.control_flag=1;
  ax_201.view=0;
  ax_201.protect_timer=30;
  ax_201.timer=3;
  ax_201.bombs=3;
  ax_201.power=1;
 }
void make_item(int x,int y)
 {
  int i,a,flag=0;
  a=(loop_counter*100+ax_201.dasu*100+ax_201.score*2+ax_201.power*100)/100;
  for (i=0;i<100;i++) if (item_list[i].use==-1) {flag=1;break;}
  if (flag==0) return;
  item_list[i].use=0;
  item_list[i].id=a%3;;  // if item....0:power1:bomb2:money
  item_list[i].frame=item_list[i].id*4;
  item_list[i].x=x;
  item_list[i].y=y;
  item_list[i].timer=5;
  item_list[i].timer_count=5;
  item_list[i].v=2;
  item_list[i].sx=14;
  item_list[i].sy=7;
  if (a%4==2) {item_list[i].way_point[0][0]=0;item_list[i].way_point[1][0]=0;item_list[i].way_point[0][1]=300;item_list[i].way_point[1][1]=180;item_list[i].way_point[0][2]=160;item_list[i].way_point[1][2]=-25;}
  if (a%4==1){item_list[i].way_point[0][0]=0;item_list[i].way_point[1][0]=180;item_list[i].way_point[0][1]=160;item_list[i].way_point[1][1]=50;item_list[i].way_point[0][2]=0;item_list[i].way_point[1][2]=-25;}
  if (a%4==0){item_list[i].way_point[0][0]=300;item_list[i].way_point[1][0]=180;item_list[i].way_point[0][1]=160;item_list[i].way_point[1][1]=50;item_list[i].way_point[0][2]=300;item_list[i].way_point[1][2]=-25;}
  if (a%4==3){item_list[i].way_point[0][0]=0;item_list[i].way_point[1][0]=50;item_list[i].way_point[0][1]=300;item_list[i].way_point[1][1]=50;item_list[i].way_point[0][2]=300;item_list[i].way_point[1][2]=-25;}
  item_list[i].move_counter=0;
 }
void delete_item(int i)
 {
  item_list[i].use=-1;
 }
void view_item()
 {
   int i;
  for (i=0;i<100;i++) {
   if (item_list[i].use==0) {
                         spr_off=(DWORD)base+item_list[i].x+item_list[i].y*760;
                         push_ebx();
                         set_offset();
                         (item[item_list[i].frame].code)();
                         pop_ebx();
                         }
  }
}
void get_item(int id)
 {
  MODPlaySample(6,get_item_s);
  if (id==0) {ax_201.power++;
             if (ax_201.power>5) ax_201.power=5;
             }
  if (id==2) {ax_201.bombs++;
             if (ax_201.bombs>10) ax_201.bombs=10;
             }
  if (id==1) ax_201.score+=500;
 }


void process_item()
 {
  int i,ax,ay;
  for (i=0;i<100;i++) {
     if ((item_list[i].use==0)&&(item_list[i].timer_count<=0))
         {
            item_list[i].timer_count=item_list[i].timer;
            item_list[i].frame++;
            if (item_list[i].frame>item_list[i].id*4+3) item_list[i].frame=item_list[i].id*4;
            ax=item_list[i].way_point[0][item_list[i].move_counter];
            ay=item_list[i].way_point[1][item_list[i].move_counter];
            if (item_list[i].x<ax) item_list[i].x+=item_list[i].v;
            if (item_list[i].x>ax) item_list[i].x-=item_list[i].v;
            if (item_list[i].y<ay) item_list[i].y+=item_list[i].v;
            if (item_list[i].y>ay) item_list[i].y-=item_list[i].v;
            if ((abs(item_list[i].x-ax)<=3)&&(abs(item_list[i].y-ay)<=3)) { item_list[i].move_counter ++;
                                                                            }
            if (item_list[i].y<-20) delete_item(i);
            if (check_col(item_list[i].x,item_list[i].sx,item_list[i].y,item_list[i].sy,
                  ax_201.x,ax_201.sx,ax_201.y,ax_201.sy)&&(ax_201.view==0))
              { delete_item(i);get_item(item_list[i].id);}
         } //if
      else item_list[i].timer_count--;
   } //for
 }


void make_boom(int x,int y)
 {
  MODPlaySample(5,boom_s);
  int i,flag;
  for (i=0;i<100;i++) if (boom_list[i].use==-1) {flag=1;break;}
  if (flag==0) return;
  boom_list[i].use=0;
  boom_list[i].frame=1;
  boom_list[i].x=x;
  boom_list[i].y=y;
  boom_list[i].timer=3;
 }
void process_boom()
 {
  int i;
  for (i=0;i<100;i++) {
   boom_list[i].timer--;
   if ((boom_list[i].use==0)&&(boom_list[i].timer<0)) {
      boom_list[i].frame++;
      if (boom_list[i].frame>6) destruct_boom(i);
      boom_list[i].timer=3;
      }
    }
 }
void destruct_boom(int num)
 {
  boom_list[num].use=-1;
 }
void view_boom()
 {
   int i;
  for (i=0;i<100;i++) {
   if (boom_list[i].use==0) {
                         spr_off=(DWORD)base+boom_list[i].x+boom_list[i].y*760;
                         push_ebx();
                         set_offset();
                         (boom[boom_list[i].frame].code)();
                         pop_ebx();
                         }
  }
}


void make_enemy()
 {
  int i,j,flag=0;
  BYTE k;
  if (scroll_flag==0) return;
  scroll_flag=0;
  for (i=0;i<8;i++) {

   k=*(ene+scroll_status*8+i);
   if (k!=0) {
     for(j=0;j<100;j++) {
          if (enemy_list[j].use==-1) {flag=1;break;}
           }
      if (flag) (type_set[k-1])(j,i);
       } // if
  } // for
}
void process_enemy()
 {
  int i,ax,ay,a;
  a=(loop_counter*100+ax_201.dasu*100+ax_201.score*2+ax_201.power*100)/100;
  for (i=0;i<100;i++)
   { if ((enemy_list[i].use==0)&&(enemy_list[i].timer_count<=0))
         {
            enemy_list[i].timer_count=enemy_list[i].timer;
            ax=enemy_list[i].way_point[0][enemy_list[i].move_counter];
            ay=enemy_list[i].way_point[1][enemy_list[i].move_counter];
            if (enemy_list[i].x<ax) enemy_list[i].x+=enemy_list[i].v;
            if (enemy_list[i].x>ax) enemy_list[i].x-=enemy_list[i].v;
            if (enemy_list[i].y<ay) enemy_list[i].y+=enemy_list[i].v;
            if (enemy_list[i].y>ay) enemy_list[i].y-=enemy_list[i].v;
            if ((abs(enemy_list[i].x-ax)<=3)&&(abs(enemy_list[i].y-ay)<=3)) { if (enemy_list[i].frame==0)
                                                                              enemy_list[i].move_counter ++;
                                                                            }
            if (enemy_list[i].y>220) delete_enemy(i);
            if ((enemy_list[i].need_bullet>0)&&((a%15)==enemy_list[i].frame)) {make_e_bullet(i,enemy_list[i].frame);enemy_list[i].need_bullet--;}
            if (check_col(enemy_list[i].x,enemy_list[i].sx,enemy_list[i].y,enemy_list[i].sy,
                  ax_201.x,ax_201.sx,ax_201.y,ax_201.sy)&&(ax_201.view==0))
              { destruct_enemy(i,10);
                if (ax_201.protect_timer<0) destruct_ax_201();
              }
         } //if
      else enemy_list[i].timer_count--;
   } //for
 }

void type_1_set(int num,int x)
 {
  int a;
  a=(loop_counter*100+ax_201.dasu*100+ax_201.score*2+ax_201.power*100)/100;
  enemy_list[num].use=0;
  enemy_list[num].frame=0;
  if (a%15==0) enemy_list[num].id=1;  // if item....
    else enemy_list[num].id=0;
  enemy_list[num].score=100;
  enemy_list[num].x=start_x[x];
  enemy_list[num].y=-enemy[0].height;
  enemy_list[num].timer=0;
  enemy_list[num].v=1;
  enemy_list[num].sx=enemy[0].width;
  enemy_list[num].sy=enemy[0].height;
  enemy_list[num].hp=1;
  if (a%4==0) {enemy_list[num].way_point[0][0]=250;enemy_list[num].way_point[1][0]=100;enemy_list[num].way_point[0][1]=50;enemy_list[num].way_point[1][1]=150;enemy_list[num].way_point[0][2]=ax_201.x;enemy_list[num].way_point[1][2]=225;}
  if (a%4==1){enemy_list[num].way_point[0][0]=50;enemy_list[num].way_point[1][0]=100;enemy_list[num].way_point[0][1]=250;enemy_list[num].way_point[1][1]=150;enemy_list[num].way_point[0][2]=ax_201.x;enemy_list[num].way_point[1][2]=225;}
  if (a%4==2){enemy_list[num].way_point[0][0]=0;enemy_list[num].way_point[1][0]=100;enemy_list[num].way_point[0][1]=160;enemy_list[num].way_point[1][1]=150;enemy_list[num].way_point[0][2]=ax_201.x;enemy_list[num].way_point[1][2]=225;}
  if (a%4==3){enemy_list[num].way_point[0][0]=300;enemy_list[num].way_point[1][0]=100;enemy_list[num].way_point[0][1]=160;enemy_list[num].way_point[1][1]=150;enemy_list[num].way_point[0][2]=ax_201.x;enemy_list[num].way_point[1][2]=225;}
  enemy_list[num].need_bullet=3;
  enemy_list[num].move_counter=0;
 }
void type_2_set(int num,int x)
 {
  int a;
  a=(loop_counter*100+ax_201.dasu*100+ax_201.score*2+ax_201.power*100)/100;
  enemy_list[num].use=0;
  enemy_list[num].frame=1;
  if (a%15==0) enemy_list[num].id=1;  // if item....
    else enemy_list[num].id=0;
  enemy_list[num].score=150;
  enemy_list[num].x=start_x[x];
  enemy_list[num].y=-enemy[0].height;
  enemy_list[num].timer=0;
  enemy_list[num].v=2;
  enemy_list[num].sx=enemy[0].width;
  enemy_list[num].sy=enemy[0].height;
  enemy_list[num].hp=1;
  enemy_list[num].way_point[0][0]=ax_201.x;enemy_list[num].way_point[1][0]=225;
  enemy_list[num].need_bullet=2;
  enemy_list[num].move_counter=0;
 }
void type_3_set(int num,int x)
 {
  int a;
  a=(loop_counter*100+ax_201.dasu*100+ax_201.score*2+ax_201.power*100)/100;
  enemy_list[num].use=0;
  enemy_list[num].frame=2;
  if (a%12==0) enemy_list[num].id=1;  // if item....
    else enemy_list[num].id=0;
  enemy_list[num].score=200;
  enemy_list[num].x=start_x[x];
  enemy_list[num].y=-enemy[0].height;
  enemy_list[num].timer=2;
  enemy_list[num].v=1;
  enemy_list[num].sx=enemy[0].width;
  enemy_list[num].sy=enemy[0].height;
  enemy_list[num].hp=5;
  enemy_list[num].way_point[0][0]=ax_201.x;enemy_list[num].way_point[1][0]=225;
  enemy_list[num].need_bullet=enemy_bullet[enemy_dash[a%10]];
  enemy_list[num].move_counter=0;
 }
void type_4_set(int num,int x)
 {
  int a;
  a=(loop_counter*100+ax_201.dasu*100+ax_201.score*2+ax_201.power*100)/100;
  enemy_list[num].use=0;
  enemy_list[num].frame=3;
  if (a%12==0) enemy_list[num].id=1;  // if item....
    else enemy_list[num].id=0;
  enemy_list[num].score=250;
  enemy_list[num].x=start_x[x];
  enemy_list[num].y=-enemy[0].height;
  enemy_list[num].timer=2;
  enemy_list[num].v=1;
  enemy_list[num].sx=enemy[0].width;
  enemy_list[num].sy=enemy[0].height;
  enemy_list[num].hp=10;
  enemy_list[num].way_point[0][0]=start_x[x];enemy_list[num].way_point[1][0]=225;
  enemy_list[num].need_bullet=enemy_bullet[enemy_dash[a%10]];
  enemy_list[num].move_counter=0;
 }
void type_5_set(int num,int x)
 {
  int a;
  a=(loop_counter*100+ax_201.dasu*100+ax_201.score*2+ax_201.power*100)/100;
  enemy_list[num].use=0;
  enemy_list[num].frame=4;
  if (a%10==0) enemy_list[num].id=1;  // if item....
    else enemy_list[num].id=0;
  enemy_list[num].score=250;
  enemy_list[num].x=start_x[x];
  enemy_list[num].y=-enemy[0].height;
  enemy_list[num].timer=4;
  enemy_list[num].v=1;
  enemy_list[num].sx=enemy[0].width;
  enemy_list[num].sy=enemy[0].height;
  enemy_list[num].hp=20;
  enemy_list[num].way_point[0][0]=start_x[x];enemy_list[num].way_point[1][0]=225;
  enemy_list[num].need_bullet=enemy_bullet[enemy_dash[a%10]];
  enemy_list[num].move_counter=0;
 }
void type_6_set(int num,int x)
 {
  int a;
  a=(loop_counter*100+ax_201.dasu*100+ax_201.score*2+ax_201.power*100)/100;
  enemy_list[num].use=0;
  enemy_list[num].frame=5;
  if (a%8==0) enemy_list[num].id=1;  // if item....
    else enemy_list[num].id=0;
  enemy_list[num].score=500;
  enemy_list[num].x=start_x[x];
  enemy_list[num].y=-enemy[0].height;
  enemy_list[num].timer=7;
  enemy_list[num].v=1;
  enemy_list[num].sx=enemy[0].width;
  enemy_list[num].sy=enemy[0].height;
  enemy_list[num].hp=70;
  enemy_list[num].way_point[0][0]=start_x[x];enemy_list[num].way_point[1][0]=225;
  enemy_list[num].need_bullet=0;
  enemy_list[num].move_counter=0;
  MODPlaySample(6,e_s);
 }

void view_enemy()
 {
  int i;
  for (i=0;i<100;i++) {
   if (enemy_list[i].use==0) {
                         spr_off=(DWORD)base+enemy_list[i].x+enemy_list[i].y*760;
                         push_ebx();
                         set_offset();
                         (enemy[enemy_list[i].frame].code)();
                         pop_ebx();
                         }
  }
 }
void view_e_bullet()
 {
  int i;
  for (i=0;i<200;i++) {
   if (e_bullet_list[i].use==0) {
                         spr_off=(DWORD)base+e_bullet_list[i].x+e_bullet_list[i].y*760;
                         push_ebx();
                         set_offset();
                         (bomb[e_bullet_list[i].frame].code)();
                         pop_ebx();
                         }
  }
  for (i=0;i<100;i++) {
   if (e_bomb_list[i].use==0) {
                         spr_off=(DWORD)base+e_bomb_list[i].x+e_bomb_list[i].y*760;
                         push_ebx();
                         set_offset();
                         (bomb[e_bomb_list[i].frame].code)();
                         pop_ebx();
                         }
  }
 }
void delete_enemy(int num)
 {
  enemy_list[num].use=-1;
 }

void destruct_e_bullet(int num)
 {
  e_bullet_list[num].use=-1;
 }
void destruct_e_bomb(int i)
 {
  ax_201.score+=10;
  make_e_bomb_boom(e_bomb_list[i].x,e_bomb_list[i].y);
  e_bomb_list[i].use=-1;
 }
void make_e_bomb_boom(int x,int y)
 {
  MODPlaySample(5,e_boom_s);
//  MODPlaySample(7,boom_s);
  int i,flag;
  for (i=0;i<100;i++) if (e_bomb_boom[i].use==-1) {flag=1;break;}
  if (flag==0) return;
  e_bomb_boom[i].use=0;
  e_bomb_boom[i].frame=7;
  e_bomb_boom[i].x=x;
  e_bomb_boom[i].y=y;
  e_bomb_boom[i].timer=3;
 }
void process_e_bomb_boom()
 {
  int i;
  for (i=0;i<100;i++) {
   e_bomb_boom[i].timer--;
   if ((e_bomb_boom[i].use==0)&&(e_bomb_boom[i].timer<0)) {
      e_bomb_boom[i].frame++;
      if (e_bomb_boom[i].frame>7) destruct_e_bomb_boom(i);
      }
    }
 }
void destruct_e_bomb_boom(int num)
 {
  e_bomb_boom[num].use=-1;
 }
void view_e_bomb_boom()
 {
   int i;
  for (i=0;i<100;i++) {
   if (e_bomb_boom[i].use==0) {
                         spr_off=(DWORD)base+e_bomb_boom[i].x+e_bomb_boom[i].y*760;
                         push_ebx();
                         set_offset();
                         (boom[7].code)();
                         pop_ebx();
                         }
  }
}
void process_e_bullet()
 {
  int i;
  for (i=0;i<200;i++)
   {
     if (e_bullet_list[i].use==0)
            {
               if ((e_bullet_list[i].for_x==0)&&(e_bullet_list[i].for_y==0))
                {
                 if (e_bullet_list[i].x<e_bullet_list[i].wh_x) e_bullet_list[i].x++;
                 if (e_bullet_list[i].x>e_bullet_list[i].wh_x) e_bullet_list[i].x--;
                 if (e_bullet_list[i].y<e_bullet_list[i].wh_y) e_bullet_list[i].y++;
                 if (e_bullet_list[i].y>e_bullet_list[i].wh_y) e_bullet_list[i].y--;
                 if ((e_bullet_list[i].x==e_bullet_list[i].wh_x)
                     &&(e_bullet_list[i].y==e_bullet_list[i].wh_y))
                     e_bullet_list[i].for_y=1;
                }
              else {
                     e_bullet_list[i].x+=(e_bullet_list[i].for_x);
                     e_bullet_list[i].y+=(e_bullet_list[i].for_y);
                    }
               if ((e_bullet_list[i].x>320)||(e_bullet_list[i].x<-5)) destruct_e_bullet(i);
               if ((e_bullet_list[i].y>200)||(e_bullet_list[i].y<-5)) destruct_e_bullet(i);
               if (check_col(e_bullet_list[i].x,e_bullet_list[i].sx,e_bullet_list[i].y,e_bullet_list[i].sy,
                  ax_201.x,ax_201.sx,ax_201.y,ax_201.sy)&&(ax_201.view==0))
                 {destruct_e_bullet(i);
                  if (ax_201.protect_timer<0) destruct_ax_201();
                 }
            }//if
   }//for
  for (i=0;i<100;i++)
   {
     if (e_bomb_list[i].use==0)
       {
              if ((e_bomb_list[i].for_x==0)&&(e_bomb_list[i].for_y==0)) {
               if (e_bomb_list[i].x<e_bomb_list[i].wh_x) e_bomb_list[i].x++;
               if (e_bomb_list[i].x>e_bomb_list[i].wh_x) e_bomb_list[i].x--;
               if (e_bomb_list[i].y<e_bomb_list[i].wh_y) e_bomb_list[i].y++;
               if (e_bomb_list[i].y>e_bomb_list[i].wh_y) e_bomb_list[i].y--;
               if ((e_bomb_list[i].x==e_bomb_list[i].wh_x)&&(e_bomb_list[i].y==e_bomb_list[i].wh_y))
               e_bomb_list[i].for_y=1;
              }
               else {
                     e_bomb_list[i].x+=e_bomb_list[i].for_x;
                     e_bomb_list[i].y+=e_bomb_list[i].for_y;
                    }
               if ((e_bomb_list[i].x>320)||(e_bomb_list[i].x<-5)) destruct_e_bomb(i);
               if ((e_bomb_list[i].y>200)||(e_bomb_list[i].y<-5)) destruct_e_bomb(i);
              if (check_col(e_bomb_list[i].x,e_bomb_list[i].sx,e_bomb_list[i].y,e_bomb_list[i].sy,
                  ax_201.x,ax_201.sx,ax_201.y,ax_201.sy)&&(ax_201.view==0))
                 {destruct_e_bomb(i);
                 if (ax_201.protect_timer<0) destruct_ax_201();
                 }
              }//if
   }//for
 }




void make_e_bullet(int num,int type)
 {
  switch (type) {
   case 0:
   case 1: process_1(num);break;
   case 2: process_2(num);break;
   case 3: process_4(num);break;
   case 4: process_3(num);break;
   case 5: break;
   }
 }

void process_1(int num)
 {   int i,a,b,flag=0;
     // Sound...
           for (i=0;i<200;i++) if (e_bullet_list[i].use==-1) {flag=1;break;}
           if (flag==0) return;
           e_bullet_list[i].use=0; // 0 : use -1 : no
           e_bullet_list[i].frame=6;
           e_bullet_list[i].x=enemy_list[num].x+(enemy_list[num].sx>>1);
           e_bullet_list[i].y=enemy_list[num].y+(enemy_list[num].sy>>1);
           e_bullet_list[i].sx=bomb[6].width;
           e_bullet_list[i].sy=bomb[6].height;
           e_bullet_list[i].v=1;
           if (e_bullet_list[i].x<=ax_201.x)  e_bullet_list[i].for_x=1;
            else  e_bullet_list[i].for_x=-1;
           if (e_bullet_list[i].y<=ax_201.y)  e_bullet_list[i].for_y=1;
            else  e_bullet_list[i].for_y=-1;
           e_bullet_list[i].wh_x=ax_201.x;
           e_bullet_list[i].wh_y=ax_201.y;
 }
void process_2(int num)
 {  int i,a,b,flag=0;
    MODPlaySample(6,e_bomb_s);
    // Sound...
           for (i=0;i<100;i++) if (e_bomb_list[i].use==-1) {flag=1;break;}
           if (flag==0) return;
           e_bomb_list[i].use=0; // 0 : use -1 : no
           e_bomb_list[i].frame=5;
           e_bomb_list[i].x=enemy_list[num].x+(enemy_list[num].sx>>1);
           e_bomb_list[i].y=enemy_list[num].y+(enemy_list[num].sy>>1);
           e_bomb_list[i].sx=bomb[5].width;
           e_bomb_list[i].sy=bomb[5].height;
           e_bomb_list[i].v=1;
           e_bomb_list[i].wh_x=ax_201.x;
           e_bomb_list[i].wh_y=ax_201.y;
           if (e_bomb_list[i].x<=ax_201.x)  e_bomb_list[i].for_x=1;
            else  e_bomb_list[i].for_x=-1;
           if (e_bomb_list[i].y<=ax_201.y)  e_bomb_list[i].for_y=1;
            else  e_bomb_list[i].for_y=-1;
 }
void process_3(int num)
  {
    int i,flag=0;
    //Sound...
           for (i=0;i<200;i++) if (e_bullet_list[i].use==-1) {flag=1;break;}
           if (flag==0) return;
           e_bullet_list[i].use=0; // 0 : use -1 : no
           e_bullet_list[i].frame=6;
           e_bullet_list[i].x=enemy_list[num].x+(enemy_list[num].sx>>1);
           e_bullet_list[i].y=enemy_list[num].y+(enemy_list[num].sy>>1);
           e_bullet_list[i].sx=bomb[6].width;
           e_bullet_list[i].sy=bomb[6].height;
           e_bullet_list[i].v=1;
           e_bullet_list[i].for_x=0;
           e_bullet_list[i].for_y=2;
           flag=0;
           for (i=0;i<200;i++) if (e_bullet_list[i].use==-1) {flag=1;break;}
           if (flag==0) return;
           e_bullet_list[i].use=0; // 0 : use -1 : no
           e_bullet_list[i].frame=6;
           e_bullet_list[i].x=enemy_list[num].x+(enemy_list[num].sx>>1);
           e_bullet_list[i].y=enemy_list[num].y+(enemy_list[num].sy>>1);
           e_bullet_list[i].sx=bomb[6].width;
           e_bullet_list[i].sy=bomb[6].height;
           e_bullet_list[i].v=1;
           e_bullet_list[i].for_x=1;
           e_bullet_list[i].for_y=2;
           flag=0;
           for (i=0;i<200;i++) if (e_bullet_list[i].use==-1) {flag=1;break;}
           if (flag==0) return;
           e_bullet_list[i].use=0; // 0 : use -1 : no
           e_bullet_list[i].frame=6;
           e_bullet_list[i].x=enemy_list[num].x+(enemy_list[num].sx>>1);
           e_bullet_list[i].y=enemy_list[num].y+(enemy_list[num].sy>>1);
           e_bullet_list[i].sx=bomb[6].width;
           e_bullet_list[i].sy=bomb[6].height;
           e_bullet_list[i].v=1;
           e_bullet_list[i].for_x=-1;
           e_bullet_list[i].for_y=2;
}
void process_4(int num)
{
 int i,flag=0;
    MODPlaySample(6,e_bomb_s);
           for (i=0;i<100;i++) if (e_bomb_list[i].use==-1) {flag=1;break;}
           if (flag==0) return;
           e_bomb_list[i].use=0; // 0 : use -1 : no
           e_bomb_list[i].frame=5;
           e_bomb_list[i].x=enemy_list[num].x+(enemy_list[num].sx>>1);
           e_bomb_list[i].y=enemy_list[num].y+(enemy_list[num].sy>>1);
           e_bomb_list[i].sx=bomb[5].width;
           e_bomb_list[i].sy=bomb[5].height;
           e_bomb_list[i].v=1;
           e_bomb_list[i].for_x=2;
           e_bomb_list[i].for_y=0;
           flag=0;
           for (i=0;i<100;i++) if (e_bomb_list[i].use==-1) {flag=1;break;}
           if (flag==0) return;
           e_bomb_list[i].use=0; // 0 : use -1 : no
           e_bomb_list[i].frame=5;
           e_bomb_list[i].x=enemy_list[num].x+(enemy_list[num].sx>>1);
           e_bomb_list[i].y=enemy_list[num].y+(enemy_list[num].sy>>1);
           e_bomb_list[i].sx=bomb[5].width;
           e_bomb_list[i].sy=bomb[5].height;
           e_bomb_list[i].v=1;
           e_bomb_list[i].for_x=-2;
           e_bomb_list[i].for_y=0;
           flag=0;
           for (i=0;i<100;i++) if (e_bomb_list[i].use==-1) {flag=1;break;}
           if (flag==0) return;
           e_bomb_list[i].use=0; // 0 : use -1 : no
           e_bomb_list[i].frame=5;
           e_bomb_list[i].x=enemy_list[num].x+(enemy_list[num].sx>>1);
           e_bomb_list[i].y=enemy_list[num].y+(enemy_list[num].sy>>1);
           e_bomb_list[i].sx=bomb[5].width;
           e_bomb_list[i].sy=bomb[5].height;
           e_bomb_list[i].v=1;
           e_bomb_list[i].for_x=0;
           e_bomb_list[i].for_y=2;
           flag=0;
           for (i=0;i<100;i++) if (e_bomb_list[i].use==-1) {flag=1;break;}
           if (flag==0) return;
           e_bomb_list[i].use=0; // 0 : use -1 : no
           e_bomb_list[i].frame=5;
           e_bomb_list[i].x=enemy_list[num].x+(enemy_list[num].sx>>1);
           e_bomb_list[i].y=enemy_list[num].y+(enemy_list[num].sy>>1);
           e_bomb_list[i].sx=bomb[5].width;
           e_bomb_list[i].sy=bomb[5].height;
           e_bomb_list[i].v=1;
           e_bomb_list[i].for_x=0;
           e_bomb_list[i].for_y=-2;
}
void init_value()
 {
  int i;
  type_set[0]=type_1_set;
  type_set[1]=type_2_set;
  type_set[2]=type_3_set;
  type_set[3]=type_4_set;
  type_set[4]=type_5_set;
  type_set[5]=type_6_set;
  for (i=0;i<100;i++)
   { boom_list[i].use=-1;item_list[i].use=-1;}
 }

void init_ax_201()
 {
  ax_201.score=0;
  ax_201.frame=0;
  ax_201.view=0;
  ax_201.x=145;
  ax_201.y=180;
  ax_201.timer=3;
  ax_201.protect_timer=30;
  ax_201.control_flag=1;
  ax_201.v=0;
  ax_201.hp=1;
  ax_201.sx=space[0].width;
  ax_201.sy=space[0].height;
  ax_201.dasu=5;
  ax_201.bombs=3;
  ax_201.power=1;
  MODPlaySample(5,appear);
 }


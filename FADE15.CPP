// 1996.8.7
//     15bit color Fade in/ Fade out Function
//         by Reizes   (Nam Gi Hoon)
//                                         .. RunE ..

static unsigned char *fade_look_up_table;

inline void end_fade(void)
 {
  free(fade_look_up_table);
 }

void init_fade_table(void)
 {
  int i,j;unsigned char *f;
  f=fade_look_up_table=(unsigned char *)malloc(1056*2);
  for (i=0;i<33;i++) {
   for (j=0;j<32;j++) {
     //*(fade_look_up_table+j+(i<<5))=(short)((j*i)>>5);
     *f=(unsigned char)((j*i)>>5); f++; }
   }
 }

void clear(int c,int size); //eax ecx
#pragma aux clear= \
       " push edi "\
       " push ebx "\
       " push es "\
       " les edi,Linear_pointer"\
       " mov ebx,eax "\
       " shr ecx,1"\
       " shl ebx,16 "\
       " or eax,ebx "\
       " rep stosd "\
       " pop es "\
       " pop ebx "\
       " pop edi "\
 parm [eax] [ecx] \
 modify [eax ebx edi ecx ];

// rat : 0-32 ..  size : x*y
void fade_buffer(short *source,short *dest,int size,int rat); // esi edi ecx ebx
#pragma aux fade_buffer= \
    "     pushad "\
    "     mov edx,fade_look_up_table "\
    "     shl ebx,5 "\
    "     add edx,ebx "\
    "_l1: mov ax,[esi]"\
    "     shr eax,10  "\
    "     add eax,edx "\
    "     mov al,[eax] "\
    "     and eax,31 "\
    "     shl eax,10 "\
    "     mov ebx,eax "\
\
    "     mov ax,[esi]"\
    "     shr eax,5  "\
    "     and eax,31 "\
    "     add eax,edx "\
    "     mov al,[eax] "\
    "     and eax,31 "\
    "     shl eax,5" \
    "     or ebx,eax "\
\
    "     mov ax,[esi]"\
    "     and eax,31 "\
    "     add eax,edx "\
    "     mov al,[eax] "\
    "     and eax,31 "\
    "     or ebx,eax "\
    "     mov [edi],ebx "\
    "     add esi,2"\
    "     add edi,2"\
    "     loop _l1 "\
    "     popad   "\
 parm [esi] [edi] [ecx] [ebx] \
 modify [esi edi eax ebx ecx edx] ;

void fade_screen(short *source,int size,int rat); // esi ecx ebx
#pragma aux fade_screen= \
    "     pushad "\
    "     mov edx,fade_look_up_table "\
    "     shl ebx,5 "\
    "     lgs edi,Linear_pointer "\
    "     add edx,ebx "\
    "_l1: mov ax,[esi]"\
    "     shr eax,10  "\
    "     add eax,edx "\
    "     mov al,[eax] "\
    "     and eax,31 "\
    "     shl eax,10 "\
    "     mov ebx,eax "\
\
    "     mov ax,[esi]"\
    "     shr eax,5  "\
    "     and eax,31 "\
    "     add eax,edx "\
    "     mov al,[eax] "\
    "     and eax,31 "\
    "     shl eax,5" \
    "     or ebx,eax "\
\
    "     mov ax,[esi]"\
    "     and eax,31 "\
    "     add eax,edx "\
    "     mov al,[eax] "\
    "     and eax,31 "\
    "     or ebx,eax "\
    "     mov gs:[edi],ebx "\
    "     add esi,2"\
    "     add edi,2"\
    "     loop _l1 "\
    "     popad   "\
 parm [esi] [ecx] [ebx] \
 modify [esi edi eax ebx ecx edx gs] ;

void move_buffer(short *source,short *dest,int size); // esi edi ecx
#pragma aux move_buffer= \
    " shr ecx,1 "\
    " rep movsd "\
parm [esi] [edi] [ecx]\
modify [esi edi ecx ];

void move_screen(short *source,int size); // esi ecx
#pragma aux move_screen= \
     " push es " \
     " push edi "  \
     " les edi,Linear_pointer "\
     " shr ecx,1 "\
     " rep movsd "\
     " pop edi "\
     " pop es "\
parm [esi] [ecx]\
modify [edi ecx esi ];



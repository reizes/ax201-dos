static unsigned char put_color[16];

void put_byte_sub(unsigned int ,char *,int ,unsigned char );
 #pragma aux put_byte_sub= \
  " lpa: push ecx "\
  "      mov bl,[esi] "\
  "      mov ecx,8 "\
  " lpb: shl bl,1 "\
  "      jnc next "\
  "      mov [edi],al "\
  "next: inc edi "\
  "      loop lpb "\
  "      pop ecx "\
  "      inc esi "\
  "      loop lpa "\
 parm [edi] [esi] [ecx] [al] \
 modify [eax ebx ecx esi edi];
void put_byte(unsigned int offset,char *buff,int m,int n)
 {
  int i;
  for (i=0;i<n;i++)
   { put_byte_sub(offset,buff,m,put_color[i]);
     offset+=so_list[active_so].width;
     buff+=8*m;
   }
 }




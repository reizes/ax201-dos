// .. RUNE .. 1996  Compiled Sprite Code
 void space1(unsigned int);
#pragma aux space1 = \
 "push ebx " \
 "add ebx,12 " \
  "mov [ebx],40" \
  "inc ebx " \
  "add ebx,319 " \
  "mov [ebx],48" \
  "inc ebx " \
  "add ebx,318 " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],48" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "add ebx,317 " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],48" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "add ebx,316 " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],51" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "add ebx,315 " \
  "pop ebx" \
  "ret "\
parm [ebx] \
modify [ebx] ;
/*  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],51" \
  "inc ebx " \
  "mov [ebx],52" \
  "inc ebx " \
  "mov [ebx],51" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "add ebx,314 " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],51" \
  "inc ebx " \
  "mov [ebx],48" \
  "inc ebx " \
  "mov [ebx],51" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "add ebx,312 " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],48" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "add ebx,313 " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "add ebx,316 " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "add ebx,317 " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "add ebx,316 " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "add ebx,315 " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "add ebx,305 " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],23" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "add ebx,296 " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],25" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],48" \
  "inc ebx " \
  "mov [ebx],48" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],48" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "add ebx,299 " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],25" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],48" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "add ebx,303 " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],28" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "add ebx,309 " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "add ebx,314 " \
  "mov [ebx],41" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \
  "mov [ebx],40" \
  "inc ebx " \
  "mov [ebx],38" \
  "inc ebx " \
  "mov [ebx],36" \
  "inc ebx " \*/



Module: C:\LANGUAGE\WC\BINB\CUTTER.CPP
Group: 'DGROUP' CONST,CONST2,_DATA,_BSS

Segment: _TEXT  DWORD USE32  00001d7c bytes  
 0000                    void near pcx_read( int, char near * ):
 0000  68 98 03 00 00                    push    00000398H
 0005  e8 00 00 00 00                    call    __CHK
 000a  53                                push    ebx
 000b  51                                push    ecx
 000c  56                                push    esi
 000d  57                                push    edi
 000e  55                                push    ebp
 000f  81 ec 80 03 00 00                 sub     esp,00000380H
 0015  89 c5                             mov     ebp,eax
 0017  89 d7                             mov     edi,edx
 0019  89 c1                             mov     ecx,eax
 001b  c1 e0 03                          shl     eax,03H
 001e  01 e8                             add     eax,ebp
 0020  8b b4 81 21 00 00 
       00                                mov     esi,__22ij7SO near so_list[]+21H[ecx+eax*4]
 0027  ba 00 00 00 00                    mov     edx,offset L143
 002c  89 f8                             mov     eax,edi
 002e  e8 00 00 00 00                    call    fopen_
 0033  89 c7                             mov     edi,eax
 0035  89 f9                             mov     ecx,edi
 0037  bb 01 00 00 00                    mov     ebx,00000001H
 003c  ba 80 00 00 00                    mov     edx,00000080H
 0041  8d 84 24 00 03 00 
       00                                lea     eax,+300H[esp]
 0048  e8 00 00 00 00                    call    fread_
 004d  89 e9                             mov     ecx,ebp
 004f  c1 e1 03                          shl     ecx,03H
 0052  01 e9                             add     ecx,ebp
 0054  c1 e1 02                          shl     ecx,02H
 0057  01 e9                             add     ecx,ebp
 0059  89 f8             L1              mov     eax,edi
 005b  e8 00 00 00 00                    call    fgetc_
 0060  89 c3                             mov     ebx,eax
 0062  30 e7                             xor     bh,ah
 0064  30 e4                             xor     ah,ah
 0066  24 c0                             and     al,0c0H
 0068  66 3d c0 00                       cmp     ax,00c0H
 006c  75 1c                             jne     L3
 006e  89 da                             mov     edx,ebx
 0070  30 fe                             xor     dh,bh
 0072  80 e2 3f                          and     dl,3fH
 0075  89 f8                             mov     eax,edi
 0077  e8 00 00 00 00                    call    fgetc_
 007c  89 c3                             mov     ebx,eax
 007e  4a                L2              dec     edx
 007f  66 83 fa ff                       cmp     dx,0ffffH
 0083  74 08                             je      L4
 0085  88 1e                             mov     [esi],bl
 0087  46                                inc     esi
 0088  eb f4                             jmp     L2
 008a  88 1e             L3              mov     [esi],bl
 008c  46                                inc     esi
 008d  8b 81 21 00 00 00 L4              mov     eax,__22ij7SO near so_list[]+21H[ecx]
 0093  05 00 fa 00 00                    add     eax,0000fa00H
 0098  39 c6                             cmp     esi,eax
 009a  72 bd                             jb      L1
 009c  bb 02 00 00 00                    mov     ebx,00000002H
 00a1  ba ff fc ff ff                    mov     edx,0fffffcffH
 00a6  89 f8                             mov     eax,edi
 00a8  e8 00 00 00 00                    call    fseek_
 00ad  89 f8                             mov     eax,edi
 00af  e8 00 00 00 00                    call    fgetc_
 00b4  89 f9                             mov     ecx,edi
 00b6  bb 00 03 00 00                    mov     ebx,00000300H
 00bb  ba 01 00 00 00                    mov     edx,00000001H
 00c0  89 e0                             mov     eax,esp
 00c2  e8 00 00 00 00                    call    fread_
 00c7  89 f8                             mov     eax,edi
 00c9  e8 00 00 00 00                    call    fclose_
 00ce  31 c0                             xor     eax,eax
 00d0  eb 05                             jmp     L6
 00d2  c0 2c 34 02       L5              shr     byte ptr [esp+esi],02H
 00d6  40                                inc     eax
 00d7  31 f6             L6              xor     esi,esi
 00d9  66 89 c6                          mov     si,ax
 00dc  81 fe 00 03 00 00                 cmp     esi,00000300H
 00e2  7c ee                             jl      L5
 00e4  bb 00 01 00 00                    mov     ebx,00000100H
 00e9  31 d2                             xor     edx,edx
 00eb  89 e0                             mov     eax,esp
 00ed  e8 00 00 00 00                    call    void near set_block_pal( char unsigned near *, char unsigned, int )
 00f2  81 c4 80 03 00 00                 add     esp,00000380H
 00f8  5d                L7              pop     ebp
 00f9  5f                                pop     edi
 00fa  5e                                pop     esi
 00fb  59                                pop     ecx
 00fc  5b                                pop     ebx
 00fd  c3                                ret     
 00fe                    void near set_pal( char unsigned, char unsigned, char unsigned, char unsigned ):
 00fe  68 04 00 00 00                    push    00000004H
 0103  e8 00 00 00 00                    call    __CHK
 0108  88 d4                             mov     ah,dl
 010a  ba c8 03 00 00                    mov     edx,000003c8H
 010f  ee                                out     dx,al
 0110  88 e0                             mov     al,ah
 0112  ba c9 03 00 00                    mov     edx,000003c9H
 0117  ee                                out     dx,al
 0118  88 d8                             mov     al,bl
 011a  ee                                out     dx,al
 011b  88 c8                             mov     al,cl
 011d  ee                                out     dx,al
 011e  c3                                ret     
 011f                    void near get_pal( char unsigned, char unsigned near *, char unsigned near *, char unsigned near * ):
 011f  68 08 00 00 00                    push    00000008H
 0124  e8 00 00 00 00                    call    __CHK
 0129  56                                push    esi
 012a  89 d6                             mov     esi,edx
 012c  ba c7 03 00 00                    mov     edx,000003c7H
 0131  ee                                out     dx,al
 0132  ba c9 03 00 00                    mov     edx,000003c9H
 0137  29 c0                             sub     eax,eax
 0139  ec                                in      al,dx
 013a  88 06                             mov     [esi],al
 013c  29 c0                             sub     eax,eax
 013e  ec                                in      al,dx
 013f  88 03                             mov     [ebx],al
 0141  29 c0                             sub     eax,eax
 0143  ec                                in      al,dx
 0144  88 01                             mov     [ecx],al
 0146  5e                                pop     esi
 0147  c3                                ret     
 0148                    void near set_block_pal( char unsigned near *, char unsigned, int ):
 0148  68 10 00 00 00                    push    00000010H
 014d  e8 00 00 00 00                    call    __CHK
 0152  51                                push    ecx
 0153  56                                push    esi
 0154  57                                push    edi
 0155  89 c7                             mov     edi,eax
 0157  88 d0                             mov     al,dl
 0159  ba c8 03 00 00                    mov     edx,000003c8H
 015e  ee                                out     dx,al
 015f  31 c9                             xor     ecx,ecx
 0161  89 de                             mov     esi,ebx
 0163  c1 e6 02                          shl     esi,02H
 0166  29 de                             sub     esi,ebx
 0168  89 fb                             mov     ebx,edi
 016a  ba c9 03 00 00                    mov     edx,000003c9H
 016f  eb 05                             jmp     L9
 0171  8a 03             L8              mov     al,[ebx]
 0173  ee                                out     dx,al
 0174  43                                inc     ebx
 0175  41                                inc     ecx
 0176  39 f1             L9              cmp     ecx,esi
 0178  7c f7                             jl      L8
 017a  5f                                pop     edi
 017b  5e                                pop     esi
 017c  59                                pop     ecx
 017d  c3                                ret     
 017e                    void near get_block_pal( char unsigned near *, char unsigned, int ):
 017e  68 10 00 00 00                    push    00000010H
 0183  e8 00 00 00 00                    call    __CHK
 0188  51                                push    ecx
 0189  56                                push    esi
 018a  57                                push    edi
 018b  89 c7                             mov     edi,eax
 018d  88 d0                             mov     al,dl
 018f  ba c7 03 00 00                    mov     edx,000003c7H
 0194  ee                                out     dx,al
 0195  31 c9                             xor     ecx,ecx
 0197  89 de                             mov     esi,ebx
 0199  c1 e6 02                          shl     esi,02H
 019c  29 de                             sub     esi,ebx
 019e  89 fb                             mov     ebx,edi
 01a0  ba c9 03 00 00                    mov     edx,000003c9H
 01a5  eb 07                             jmp     L11
 01a7  29 c0             L10             sub     eax,eax
 01a9  ec                                in      al,dx
 01aa  88 03                             mov     [ebx],al
 01ac  43                                inc     ebx
 01ad  41                                inc     ecx
 01ae  39 f1             L11             cmp     ecx,esi
 01b0  7c f5                             jl      L10
 01b2  5f                                pop     edi
 01b3  5e                                pop     esi
 01b4  59                                pop     ecx
 01b5  c3                                ret     
 01b6                    void near init_key():
 01b6  68 10 00 00 00                    push    00000010H
 01bb  e8 00 00 00 00                    call    __CHK
 01c0  53                                push    ebx
 01c1  51                                push    ecx
 01c2  52                                push    edx
 01c3  bb 80 00 00 00                    mov     ebx,00000080H
 01c8  31 d2                             xor     edx,edx
 01ca  b8 00 00 00 00                    mov     eax,offset char unsigned near scan[]
 01cf  e8 00 00 00 00                    call    memset_
 01d4  bb 80 00 00 00                    mov     ebx,00000080H
 01d9  31 d2                             xor     edx,edx
 01db  b8 00 00 00 00                    mov     eax,offset char unsigned near asci[]
 01e0  e8 00 00 00 00                    call    memset_
 01e5  b8 09 00 00 00                    mov     eax,00000009H
 01ea  e8 00 00 00 00                    call    _dos_getvect_
 01ef  66 89 15 04 00 00 
       00                                mov     void (far * near old_int09)()+4H,dx
 01f6  a3 00 00 00 00                    mov     void (far * near old_int09)(),eax
 01fb  8c c9                             mov     cx,cs
 01fd  bb 00 00 00 00                    mov     ebx,offset void far new_int09()
 0202  b8 09 00 00 00                    mov     eax,00000009H
 0207  e8 00 00 00 00                    call    _dos_setvect_
 020c  5a                                pop     edx
 020d  59                                pop     ecx
 020e  5b                                pop     ebx
 020f  c3                                ret     
 0210                    void near del_key():
 0210  68 0c 00 00 00                    push    0000000cH
 0215  e8 00 00 00 00                    call    __CHK
 021a  53                                push    ebx
 021b  51                                push    ecx
 021c  66 8b 0d 04 00 00 
       00                                mov     cx,void (far * near old_int09)()+4H
 0223  8b 1d 00 00 00 00                 mov     ebx,void (far * near old_int09)()
 0229  b8 09 00 00 00                    mov     eax,00000009H
 022e  e8 00 00 00 00                    call    _dos_setvect_
 0233  59                                pop     ecx
 0234  5b                                pop     ebx
 0235  c3                                ret     
 0236                    void far new_int09():
 0236  60                                pushad  
 0237  1e                                push    ds
 0238  06                                push    es
 0239  0f a0                             push    fs
 023b  0f a8                             push    gs
 023d  89 e5                             mov     ebp,esp
 023f  fc                                cld     
 0240  e8 00 00 00 00                    call    __GETDS
 0245  fa                                cli     
 0246  ba 60 00 00 00                    mov     edx,00000060H
 024b  29 c0                             sub     eax,eax
 024d  ec                                in      al,dx
 024e  88 c6                             mov     dh,al
 0250  88 c2                             mov     dl,al
 0252  80 e2 7f                          and     dl,7fH
 0255  25 ff 00 00 00                    and     eax,000000ffH
 025a  3d 80 00 00 00                    cmp     eax,00000080H
 025f  7d 20                             jge     L12
 0261  31 c0                             xor     eax,eax
 0263  88 d0                             mov     al,dl
 0265  31 db                             xor     ebx,ebx
 0267  8a 98 00 00 00 00                 mov     bl,char unsigned near scan[][eax]
 026d  85 db                             test    ebx,ebx
 026f  75 10                             jne     L12
 0271  b6 01                             mov     dh,01H
 0273  88 b0 00 00 00 00                 mov     char unsigned near scan[][eax],dh
 0279  88 b0 00 00 00 00                 mov     char unsigned near asci[][eax],dh
 027f  eb 15                             jmp     L13
 0281  31 c0             L12             xor     eax,eax
 0283  88 f0                             mov     al,dh
 0285  83 f8 7f                          cmp     eax,0000007fH
 0288  7e 0c                             jle     L13
 028a  31 c0                             xor     eax,eax
 028c  88 d0                             mov     al,dl
 028e  30 d2                             xor     dl,dl
 0290  88 90 00 00 00 00                 mov     char unsigned near scan[][eax],dl
 0296  b0 20             L13             mov     al,20H
 0298  ba 20 00 00 00                    mov     edx,00000020H
 029d  ee                                out     dx,al
 029e  fb                                sti     
 029f  fc                                cld     
 02a0  0f a9                             pop     gs
 02a2  0f a1                             pop     fs
 02a4  07                                pop     es
 02a5  1f                                pop     ds
 02a6  61                                popad   
 02a7  cf                                iretd   
 02a8                    void near put_byte( int unsigned, char unsigned near *, int, int ):
 02a8  68 20 00 00 00                    push    00000020H
 02ad  e8 00 00 00 00                    call    __CHK
 02b2  56                                push    esi
 02b3  57                                push    edi
 02b4  55                                push    ebp
 02b5  83 ec 0c                          sub     esp,0000000cH
 02b8  50                                push    eax
 02b9  89 d5                             mov     ebp,edx
 02bb  89 5c 24 04                       mov     +4H[esp],ebx
 02bf  89 4c 24 08                       mov     +8H[esp],ecx
 02c3  31 d2                             xor     edx,edx
 02c5  89 d8                             mov     eax,ebx
 02c7  c1 e0 03                          shl     eax,03H
 02ca  89 44 24 0c                       mov     +0cH[esp],eax
 02ce  eb 3c                             jmp     L18
 02d0  8a 82 00 00 00 00 L14             mov     al,char unsigned near put_color[][edx]
 02d6  8b 4c 24 04                       mov     ecx,+4H[esp]
 02da  89 ee                             mov     esi,ebp
 02dc  8b 3c 24                          mov     edi,[esp]
 02df  51                L15             push    ecx
 02e0  8a 1e                             mov     bl,[esi]
 02e2  b9 08 00 00 00                    mov     ecx,00000008H
 02e7  d0 e3             L16             shl     bl,1
 02e9  73 02                             jae     L17
 02eb  88 07                             mov     [edi],al
 02ed  47                L17             inc     edi
 02ee  e2 f7                             loop    L16
 02f0  59                                pop     ecx
 02f1  46                                inc     esi
 02f2  e2 eb                             loop    L15
 02f4  31 c0                             xor     eax,eax
 02f6  a0 00 00 00 00                    mov     al,char unsigned near active_so
 02fb  6b c0 25                          imul    eax,25H
 02fe  8b 80 01 00 00 00                 mov     eax,__22ij7SO near so_list[]+1H[eax]
 0304  01 04 24                          add     [esp],eax
 0307  03 6c 24 0c                       add     ebp,+0cH[esp]
 030b  42                                inc     edx
 030c  3b 54 24 08       L18             cmp     edx,+8H[esp]
 0310  7c be                             jl      L14
 0312  83 c4 10                          add     esp,00000010H
 0315  5d                                pop     ebp
 0316  5f                                pop     edi
 0317  5e                                pop     esi
 0318  c3                                ret     
 0319                    int near view_so( int ):
 0319  68 0c 00 00 00                    push    0000000cH
 031e  e8 00 00 00 00                    call    __CHK
 0323  53                                push    ebx
 0324  52                                push    edx
 0325  89 c2                             mov     edx,eax
 0327  89 c3                             mov     ebx,eax
 0329  c1 e0 03                          shl     eax,03H
 032c  01 d0                             add     eax,edx
 032e  8a 84 83 00 00 00 
       00                                mov     al,__22ij7SO near so_list[][ebx+eax*4]
 0335  25 ff 00 00 00                    and     eax,000000ffH
 033a  3d ff 00 00 00                    cmp     eax,000000ffH
 033f  74 1e                             je      L21
 0341  83 f8 01                          cmp     eax,00000001H
 0344  75 0c                             jne     L20
 0346  89 d0                             mov     eax,edx
 0348  e8 00 00 00 00                    call    void near move_sprite_to_buffer( int )
 034d  31 c0             L19             xor     eax,eax
 034f  5a                                pop     edx
 0350  5b                                pop     ebx
 0351  c3                                ret     
 0352  85 c0             L20             test    eax,eax
 0354  75 09                             jne     L21
 0356  89 d0                             mov     eax,edx
 0358  e8 00 00 00 00                    call    void near move_image_to_buffer( int )
 035d  eb ee                             jmp     L19
 035f  b8 ff ff ff ff    L21             mov     eax,0ffffffffH
 0364  5a                                pop     edx
 0365  5b                                pop     ebx
 0366  c3                                ret     
 0367                    void near set_view( int, int, int, int, int ):
 0367  68 0c 00 00 00                    push    0000000cH
 036c  e8 00 00 00 00                    call    __CHK
 0371  56                                push    esi
 0372  57                                push    edi
 0373  89 c6                             mov     esi,eax
 0375  89 d7                             mov     edi,edx
 0377  c1 e0 03                          shl     eax,03H
 037a  01 f0                             add     eax,esi
 037c  c1 e0 02                          shl     eax,02H
 037f  01 f0                             add     eax,esi
 0381  89 90 09 00 00 00                 mov     __22ij7SO near so_list[]+9H[eax],edx
 0387  89 98 0d 00 00 00                 mov     __22ij7SO near so_list[]+0dH[eax],ebx
 038d  89 88 11 00 00 00                 mov     __22ij7SO near so_list[]+11H[eax],ecx
 0393  8b 54 24 0c                       mov     edx,+0cH[esp]
 0397  89 90 15 00 00 00                 mov     __22ij7SO near so_list[]+15H[eax],edx
 039d  31 c0                             xor     eax,eax
 039f  a0 00 00 00 00                    mov     al,char unsigned near buffer_so
 03a4  39 c6                             cmp     esi,eax
 03a6  75 0c                             jne     L22
 03a8  89 0d 00 00 00 00                 mov     int unsigned near d_w,ecx
 03ae  89 15 00 00 00 00                 mov     int unsigned near d_h,edx
 03b4  5f                L22             pop     edi
 03b5  5e                                pop     esi
 03b6  c2 04 00                          ret     0004H
 03b9                    void near set_display( int, int, int ):
 03b9  68 0c 00 00 00                    push    0000000cH
 03be  e8 00 00 00 00                    call    __CHK
 03c3  51                                push    ecx
 03c4  56                                push    esi
 03c5  89 c1                             mov     ecx,eax
 03c7  89 d6                             mov     esi,edx
 03c9  89 c2                             mov     edx,eax
 03cb  c1 e0 03                          shl     eax,03H
 03ce  01 c8                             add     eax,ecx
 03d0  89 b4 82 19 00 00 
       00                                mov     __22ij7SO near so_list[]+19H[edx+eax*4],esi
 03d7  89 9c 82 1d 00 00 
       00                                mov     __22ij7SO near so_list[]+1dH[edx+eax*4],ebx
 03de  31 c0                             xor     eax,eax
 03e0  a0 00 00 00 00                    mov     al,char unsigned near buffer_so
 03e5  39 c1                             cmp     ecx,eax
 03e7  75 0c                             jne     L23
 03e9  89 35 00 00 00 00                 mov     int near d_x,esi
 03ef  89 1d 00 00 00 00                 mov     int near d_y,ebx
 03f5  5e                L23             pop     esi
 03f6  59                                pop     ecx
 03f7  c3                                ret     
 03f8                    void near set_buffer( int, int, int ):
 03f8  68 10 00 00 00                    push    00000010H
 03fd  e8 00 00 00 00                    call    __CHK
 0402  51                                push    ecx
 0403  56                                push    esi
 0404  50                                push    eax
 0405  89 d6                             mov     esi,edx
 0407  8a 04 24                          mov     al,[esp]
 040a  a2 00 00 00 00                    mov     char unsigned near buffer_so,al
 040f  8b 14 24                          mov     edx,[esp]
 0412  89 d0                             mov     eax,edx
 0414  c1 e0 03                          shl     eax,03H
 0417  01 d0                             add     eax,edx
 0419  8a 84 82 00 00 00 
       00                                mov     al,__22ij7SO near so_list[][edx+eax*4]
 0420  25 ff 00 00 00                    and     eax,000000ffH
 0425  3d ff 00 00 00                    cmp     eax,000000ffH
 042a  75 0c                             jne     L24
 042c  31 c9                             xor     ecx,ecx
 042e  89 f2                             mov     edx,esi
 0430  8b 04 24                          mov     eax,[esp]
 0433  e8 00 00 00 00                    call    int near creat_so( int, int unsigned, int unsigned, char unsigned )
 0438  8b 14 24          L24             mov     edx,[esp]
 043b  89 d0                             mov     eax,edx
 043d  c1 e0 03                          shl     eax,03H
 0440  01 d0                             add     eax,edx
 0442  c1 e0 02                          shl     eax,02H
 0445  01 d0                             add     eax,edx
 0447  8b 90 21 00 00 00                 mov     edx,__22ij7SO near so_list[]+21H[eax]
 044d  89 15 00 00 00 00                 mov     char unsigned near * near buffer_address,edx
 0453  8b 90 19 00 00 00                 mov     edx,__22ij7SO near so_list[]+19H[eax]
 0459  89 15 00 00 00 00                 mov     int near d_x,edx
 045f  8b 90 1d 00 00 00                 mov     edx,__22ij7SO near so_list[]+1dH[eax]
 0465  89 15 00 00 00 00                 mov     int near d_y,edx
 046b  8b 90 11 00 00 00                 mov     edx,__22ij7SO near so_list[]+11H[eax]
 0471  89 15 00 00 00 00                 mov     int unsigned near d_w,edx
 0477  8b 80 15 00 00 00                 mov     eax,__22ij7SO near so_list[]+15H[eax]
 047d  a3 00 00 00 00                    mov     int unsigned near d_h,eax
 0482  31 c0                             xor     eax,eax
 0484  66 a1 12 00 00 00                 mov     ax,__3a58ujVESAINFO near _vi+12H
 048a  a3 00 00 00 00                    mov     int unsigned near vh,eax
 048f  31 c0                             xor     eax,eax
 0491  66 a1 14 00 00 00                 mov     ax,__3a58ujVESAINFO near _vi+14H
 0497  a3 00 00 00 00                    mov     int unsigned near vv,eax
 049c  83 c4 04                          add     esp,00000004H
 049f  5e                                pop     esi
 04a0  59                                pop     ecx
 04a1  c3                                ret     
 04a2                    void near line( int, int, int, int, char unsigned ):
 04a2  68 2c 00 00 00                    push    0000002cH
 04a7  e8 00 00 00 00                    call    __CHK
 04ac  56                                push    esi
 04ad  57                                push    edi
 04ae  55                                push    ebp
 04af  83 ec 1c                          sub     esp,0000001cH
 04b2  89 dd                             mov     ebp,ebx
 04b4  89 0c 24                          mov     [esp],ecx
 04b7  31 ff                             xor     edi,edi
 04b9  89 7c 24 18                       mov     +18H[esp],edi
 04bd  89 1d 00 00 00 00                 mov     int near current_x,ebx
 04c3  89 0d 00 00 00 00                 mov     int near current_y,ecx
 04c9  29 c3                             sub     ebx,eax
 04cb  89 5c 24 0c                       mov     +0cH[esp],ebx
 04cf  89 cb                             mov     ebx,ecx
 04d1  29 d3                             sub     ebx,edx
 04d3  89 5c 24 10                       mov     +10H[esp],ebx
 04d7  89 c1                             mov     ecx,eax
 04d9  89 d6                             mov     esi,edx
 04db  83 7c 24 0c 00                    cmp     dword ptr +0cH[esp],00000000H
 04e0  75 5e                             jne     L25
 04e2  83 7c 24 10 00                    cmp     dword ptr +10H[esp],00000000H
 04e7  75 57                             jne     L25
 04e9  a3 00 00 00 00                    mov     int near current_x,eax
 04ee  89 15 00 00 00 00                 mov     int near current_y,edx
 04f4  31 c1                             xor     ecx,eax
 04f6  8a 0d 00 00 00 00                 mov     cl,char unsigned near active_so
 04fc  89 cb                             mov     ebx,ecx
 04fe  c1 e3 03                          shl     ebx,03H
 0501  01 cb                             add     ebx,ecx
 0503  c1 e3 02                          shl     ebx,02H
 0506  01 cb                             add     ebx,ecx
 0508  3b 83 01 00 00 00                 cmp     eax,__22ij7SO near so_list[]+1H[ebx]
 050e  0f 83 33 01 00 00                 jae     L38
 0514  3b 93 05 00 00 00                 cmp     edx,__22ij7SO near so_list[]+5H[ebx]
 051a  0f 83 27 01 00 00                 jae     L38
 0520  85 c0                             test    eax,eax
 0522  0f 8c 1f 01 00 00                 jl      L38
 0528  85 d2                             test    edx,edx
 052a  0f 8c 17 01 00 00                 jl      L38
 0530  31 db                             xor     ebx,ebx
 0532  8a 5c 24 2c                       mov     bl,+2cH[esp]
 0536  e8 00 00 00 00                    call    void near pset_sub( int, int, char unsigned )
 053b  e9 07 01 00 00                    jmp     L38
 0540  83 7c 24 0c 00    L25             cmp     dword ptr +0cH[esp],00000000H
 0545  75 13                             jne     L26
 0547  31 c9                             xor     ecx,ecx
 0549  8a 4c 24 2c                       mov     cl,+2cH[esp]
 054d  8b 1c 24                          mov     ebx,[esp]
 0550  e8 00 00 00 00                    call    void near _vline( int, int, int, char unsigned )
 0555  e9 ed 00 00 00                    jmp     L38
 055a  83 7c 24 10 00    L26             cmp     dword ptr +10H[esp],00000000H
 055f  75 14                             jne     L27
 0561  31 c9                             xor     ecx,ecx
 0563  8a 4c 24 2c                       mov     cl,+2cH[esp]
 0567  89 d3                             mov     ebx,edx
 0569  89 ea                             mov     edx,ebp
 056b  e8 00 00 00 00                    call    void near _hline( int, int, int, char unsigned )
 0570  e9 d2 00 00 00                    jmp     L38
 0575  83 7c 24 0c 00    L27             cmp     dword ptr +0cH[esp],00000000H
 057a  7e 0a                             jle     L28
 057c  c7 44 24 04 01 00 
       00 00                             mov     dword ptr +4H[esp],00000001H
 0584  eb 0e                             jmp     L29
 0586  c7 44 24 04 ff ff 
       ff ff             L28             mov     dword ptr +4H[esp],0ffffffffH
 058e  29 e8                             sub     eax,ebp
 0590  89 44 24 0c                       mov     +0cH[esp],eax
 0594  83 7c 24 10 00    L29             cmp     dword ptr +10H[esp],00000000H
 0599  7e 0a                             jle     L30
 059b  c7 44 24 08 01 00 
       00 00                             mov     dword ptr +8H[esp],00000001H
 05a3  eb 11                             jmp     L31
 05a5  c7 44 24 08 ff ff 
       ff ff             L30             mov     dword ptr +8H[esp],0ffffffffH
 05ad  8b 2c 24                          mov     ebp,[esp]
 05b0  29 ea                             sub     edx,ebp
 05b2  89 54 24 10                       mov     +10H[esp],edx
 05b6  8b 44 24 0c       L31             mov     eax,+0cH[esp]
 05ba  8b 54 24 10                       mov     edx,+10H[esp]
 05be  39 d0                             cmp     eax,edx
 05c0  7e 04                             jle     L32
 05c2  89 c5                             mov     ebp,eax
 05c4  eb 02                             jmp     L33
 05c6  89 d5             L32             mov     ebp,edx
 05c8  31 db             L33             xor     ebx,ebx
 05ca  89 5c 24 14                       mov     +14H[esp],ebx
 05ce  eb 04                             jmp     L35
 05d0  ff 44 24 14       L34             inc     dword ptr +14H[esp]
 05d4  3b 6c 24 14       L35             cmp     ebp,+14H[esp]
 05d8  0f 8e 69 00 00 00                 jle     L38
 05de  89 0d 00 00 00 00                 mov     int near current_x,ecx
 05e4  89 35 00 00 00 00                 mov     int near current_y,esi
 05ea  31 c0                             xor     eax,eax
 05ec  a0 00 00 00 00                    mov     al,char unsigned near active_so
 05f1  6b c0 25                          imul    eax,25H
 05f4  3b 88 01 00 00 00                 cmp     ecx,__22ij7SO near so_list[]+1H[eax]
 05fa  73 1f                             jae     L36
 05fc  3b b0 05 00 00 00                 cmp     esi,__22ij7SO near so_list[]+5H[eax]
 0602  73 17                             jae     L36
 0604  85 c9                             test    ecx,ecx
 0606  7c 13                             jl      L36
 0608  85 f6                             test    esi,esi
 060a  7c 0f                             jl      L36
 060c  31 db                             xor     ebx,ebx
 060e  8a 5c 24 2c                       mov     bl,+2cH[esp]
 0612  89 f2                             mov     edx,esi
 0614  89 c8                             mov     eax,ecx
 0616  e8 00 00 00 00                    call    void near pset_sub( int, int, char unsigned )
 061b  03 7c 24 0c       L36             add     edi,+0cH[esp]
 061f  8b 44 24 10                       mov     eax,+10H[esp]
 0623  01 44 24 18                       add     +18H[esp],eax
 0627  39 ef                             cmp     edi,ebp
 0629  7e 06                             jle     L37
 062b  29 ef                             sub     edi,ebp
 062d  03 4c 24 04                       add     ecx,+4H[esp]
 0631  8b 44 24 18       L37             mov     eax,+18H[esp]
 0635  39 c5                             cmp     ebp,eax
 0637  7d 97                             jge     L34
 0639  89 c2                             mov     edx,eax
 063b  29 ea                             sub     edx,ebp
 063d  89 54 24 18                       mov     +18H[esp],edx
 0641  03 74 24 08                       add     esi,+8H[esp]
 0645  eb 89                             jmp     L34
 0647  83 c4 1c          L38             add     esp,0000001cH
 064a  5d                L39             pop     ebp
 064b  5f                                pop     edi
 064c  5e                                pop     esi
 064d  c2 04 00                          ret     0004H
 0650                    void near box( int, int, int, int, char unsigned ):
 0650  68 18 00 00 00                    push    00000018H
 0655  e8 00 00 00 00                    call    __CHK
 065a  56                                push    esi
 065b  57                                push    edi
 065c  55                                push    ebp
 065d  50                                push    eax
 065e  52                                push    edx
 065f  89 df                             mov     edi,ebx
 0661  89 cd                             mov     ebp,ecx
 0663  89 1d 00 00 00 00                 mov     int near current_x,ebx
 0669  89 0d 00 00 00 00                 mov     int near current_y,ecx
 066f  0f b6 74 24 18                    movzx   esi,byte ptr +18H[esp]
 0674  89 f1                             mov     ecx,esi
 0676  89 d3                             mov     ebx,edx
 0678  89 fa                             mov     edx,edi
 067a  e8 00 00 00 00                    call    void near _hline( int, int, int, char unsigned )
 067f  89 f1                             mov     ecx,esi
 0681  89 eb                             mov     ebx,ebp
 0683  89 fa                             mov     edx,edi
 0685  8b 44 24 04                       mov     eax,+4H[esp]
 0689  e8 00 00 00 00                    call    void near _hline( int, int, int, char unsigned )
 068e  89 f1                             mov     ecx,esi
 0690  89 eb                             mov     ebx,ebp
 0692  8b 14 24                          mov     edx,[esp]
 0695  8b 44 24 04                       mov     eax,+4H[esp]
 0699  e8 00 00 00 00                    call    void near _vline( int, int, int, char unsigned )
 069e  89 f1                             mov     ecx,esi
 06a0  89 eb                             mov     ebx,ebp
 06a2  8b 14 24                          mov     edx,[esp]
 06a5  89 f8                             mov     eax,edi
 06a7  e8 00 00 00 00                    call    void near _vline( int, int, int, char unsigned )
 06ac  83 c4 08                          add     esp,00000008H
 06af  eb 99                             jmp     L39
 06b1                    void near box_fill( int, int, int, int, char unsigned ):
 06b1  68 14 00 00 00                    push    00000014H
 06b6  e8 00 00 00 00                    call    __CHK
 06bb  56                                push    esi
 06bc  57                                push    edi
 06bd  55                                push    ebp
 06be  83 ec 04                          sub     esp,00000004H
 06c1  89 c5                             mov     ebp,eax
 06c3  89 d6                             mov     esi,edx
 06c5  89 df                             mov     edi,ebx
 06c7  89 0c 24                          mov     [esp],ecx
 06ca  89 1d 00 00 00 00                 mov     int near current_x,ebx
 06d0  89 0d 00 00 00 00                 mov     int near current_y,ecx
 06d6  eb 12                             jmp     L41
 06d8  31 c9             L40             xor     ecx,ecx
 06da  8a 4c 24 14                       mov     cl,+14H[esp]
 06de  89 f3                             mov     ebx,esi
 06e0  89 fa                             mov     edx,edi
 06e2  89 e8                             mov     eax,ebp
 06e4  e8 00 00 00 00                    call    void near _hline( int, int, int, char unsigned )
 06e9  46                                inc     esi
 06ea  3b 34 24          L41             cmp     esi,[esp]
 06ed  7e e9                             jle     L40
 06ef  83 c4 04                          add     esp,00000004H
 06f2  e9 53 ff ff ff                    jmp     L39
 06f7                    void near _hline( int, int, int, char unsigned ):
 06f7  68 10 00 00 00                    push    00000010H
 06fc  e8 00 00 00 00                    call    __CHK
 0701  56                                push    esi
 0702  57                                push    edi
 0703  83 ec 04                          sub     esp,00000004H
 0706  89 d7                             mov     edi,edx
 0708  89 de                             mov     esi,ebx
 070a  88 0c 24                          mov     [esp],cl
 070d  85 db                             test    ebx,ebx
 070f  0f 8c ef 00 00 00                 jl      L49
 0715  31 c9                             xor     ecx,ecx
 0717  8a 0d 00 00 00 00                 mov     cl,char unsigned near active_so
 071d  89 cb                             mov     ebx,ecx
 071f  c1 e3 03                          shl     ebx,03H
 0722  01 cb                             add     ebx,ecx
 0724  c1 e3 02                          shl     ebx,02H
 0727  01 cb                             add     ebx,ecx
 0729  8b 93 05 00 00 00                 mov     edx,__22ij7SO near so_list[]+5H[ebx]
 072f  39 d6                             cmp     esi,edx
 0731  0f 83 cd 00 00 00                 jae     L49
 0737  39 f8                             cmp     eax,edi
 0739  75 40                             jne     L42
 073b  a3 00 00 00 00                    mov     int near current_x,eax
 0740  89 35 00 00 00 00                 mov     int near current_y,esi
 0746  3b 83 01 00 00 00                 cmp     eax,__22ij7SO near so_list[]+1H[ebx]
 074c  0f 83 b2 00 00 00                 jae     L49
 0752  39 d6                             cmp     esi,edx
 0754  0f 83 aa 00 00 00                 jae     L49
 075a  85 c0                             test    eax,eax
 075c  0f 8c a2 00 00 00                 jl      L49
 0762  85 f6                             test    esi,esi
 0764  0f 8c 9a 00 00 00                 jl      L49
 076a  31 db                             xor     ebx,ebx
 076c  8a 1c 24                          mov     bl,[esp]
 076f  89 f2                             mov     edx,esi
 0771  e8 00 00 00 00                    call    void near pset_sub( int, int, char unsigned )
 0776  e9 89 00 00 00                    jmp     L49
 077b  7e 06             L42             jle     L43
 077d  89 c2                             mov     edx,eax
 077f  89 f8                             mov     eax,edi
 0781  89 d7                             mov     edi,edx
 0783  85 c0             L43             test    eax,eax
 0785  7d 02                             jge     L44
 0787  31 c0                             xor     eax,eax
 0789  31 c9             L44             xor     ecx,ecx
 078b  8a 0d 00 00 00 00                 mov     cl,char unsigned near active_so
 0791  89 cb                             mov     ebx,ecx
 0793  c1 e3 03                          shl     ebx,03H
 0796  01 cb                             add     ebx,ecx
 0798  c1 e3 02                          shl     ebx,02H
 079b  01 cb                             add     ebx,ecx
 079d  8b 8b 01 00 00 00                 mov     ecx,__22ij7SO near so_list[]+1H[ebx]
 07a3  39 cf                             cmp     edi,ecx
 07a5  72 03                             jb      L45
 07a7  8d 79 ff                          lea     edi,-1H[ecx]
 07aa  31 d2             L45             xor     edx,edx
 07ac  8a 15 00 00 00 00                 mov     dl,char unsigned near logic_flag
 07b2  85 d2                             test    edx,edx
 07b4  75 37                             jne     L46
 07b6  31 c9                             xor     ecx,ecx
 07b8  8a 0d 00 00 00 00                 mov     cl,char unsigned near active_so
 07be  89 cb                             mov     ebx,ecx
 07c0  c1 e3 03                          shl     ebx,03H
 07c3  01 cb                             add     ebx,ecx
 07c5  c1 e3 02                          shl     ebx,02H
 07c8  01 cb                             add     ebx,ecx
 07ca  0f af b3 01 00 00 
       00                                imul    esi,__22ij7SO near so_list[]+1H[ebx]
 07d1  8d 0c 06                          lea     ecx,[esi+eax]
 07d4  03 8b 21 00 00 00                 add     ecx,__22ij7SO near so_list[]+21H[ebx]
 07da  89 fb                             mov     ebx,edi
 07dc  29 c3                             sub     ebx,eax
 07de  43                                inc     ebx
 07df  31 d2                             xor     edx,edx
 07e1  8a 14 24                          mov     dl,[esp]
 07e4  89 c8                             mov     eax,ecx
 07e6  e8 00 00 00 00                    call    memset_
 07eb  eb 17                             jmp     L49
 07ed  89 c1             L46             mov     ecx,eax
 07ef  eb 0f                             jmp     L48
 07f1  31 db             L47             xor     ebx,ebx
 07f3  8a 1c 24                          mov     bl,[esp]
 07f6  89 f2                             mov     edx,esi
 07f8  89 c8                             mov     eax,ecx
 07fa  e8 00 00 00 00                    call    void near pset_sub( int, int, char unsigned )
 07ff  41                                inc     ecx
 0800  39 f9             L48             cmp     ecx,edi
 0802  7e ed                             jle     L47
 0804  83 c4 04          L49             add     esp,00000004H
 0807  5f                                pop     edi
 0808  5e                                pop     esi
 0809  c3                                ret     
 080a                    void near _vline( int, int, int, char unsigned ):
 080a  68 14 00 00 00                    push    00000014H
 080f  e8 00 00 00 00                    call    __CHK
 0814  56                                push    esi
 0815  57                                push    edi
 0816  55                                push    ebp
 0817  83 ec 04                          sub     esp,00000004H
 081a  89 c6                             mov     esi,eax
 081c  89 df                             mov     edi,ebx
 081e  88 0c 24                          mov     [esp],cl
 0821  85 c0                             test    eax,eax
 0823  0f 8c 9b 00 00 00                 jl      L56
 0829  31 c9                             xor     ecx,ecx
 082b  8a 0d 00 00 00 00                 mov     cl,char unsigned near active_so
 0831  89 cb                             mov     ebx,ecx
 0833  c1 e3 03                          shl     ebx,03H
 0836  01 cb                             add     ebx,ecx
 0838  c1 e3 02                          shl     ebx,02H
 083b  01 cb                             add     ebx,ecx
 083d  8b 8b 01 00 00 00                 mov     ecx,__22ij7SO near so_list[]+1H[ebx]
 0843  39 c8                             cmp     eax,ecx
 0845  0f 83 79 00 00 00                 jae     L56
 084b  39 fa                             cmp     edx,edi
 084d  75 2f                             jne     L50
 084f  a3 00 00 00 00                    mov     int near current_x,eax
 0854  89 15 00 00 00 00                 mov     int near current_y,edx
 085a  39 c8                             cmp     eax,ecx
 085c  0f 83 62 00 00 00                 jae     L56
 0862  3b 93 05 00 00 00                 cmp     edx,__22ij7SO near so_list[]+5H[ebx]
 0868  73 5a                             jae     L56
 086a  85 c0                             test    eax,eax
 086c  7c 56                             jl      L56
 086e  85 d2                             test    edx,edx
 0870  7c 52                             jl      L56
 0872  31 db                             xor     ebx,ebx
 0874  8a 1c 24                          mov     bl,[esp]
 0877  e8 00 00 00 00                    call    void near pset_sub( int, int, char unsigned )
 087c  eb 46                             jmp     L56
 087e  7e 06             L50             jle     L51
 0880  89 d3                             mov     ebx,edx
 0882  89 fa                             mov     edx,edi
 0884  89 df                             mov     edi,ebx
 0886  85 d2             L51             test    edx,edx
 0888  7d 02                             jge     L52
 088a  31 d2                             xor     edx,edx
 088c  31 c9             L52             xor     ecx,ecx
 088e  8a 0d 00 00 00 00                 mov     cl,char unsigned near active_so
 0894  89 cb                             mov     ebx,ecx
 0896  c1 e3 03                          shl     ebx,03H
 0899  01 cb                             add     ebx,ecx
 089b  c1 e3 02                          shl     ebx,02H
 089e  01 cb                             add     ebx,ecx
 08a0  8b ab 05 00 00 00                 mov     ebp,__22ij7SO near so_list[]+5H[ebx]
 08a6  39 ef                             cmp     edi,ebp
 08a8  72 03                             jb      L53
 08aa  8d 7d ff                          lea     edi,-1H[ebp]
 08ad  89 d1             L53             mov     ecx,edx
 08af  eb 0f                             jmp     L55
 08b1  31 db             L54             xor     ebx,ebx
 08b3  8a 1c 24                          mov     bl,[esp]
 08b6  89 ca                             mov     edx,ecx
 08b8  89 f0                             mov     eax,esi
 08ba  e8 00 00 00 00                    call    void near pset_sub( int, int, char unsigned )
 08bf  41                                inc     ecx
 08c0  39 f9             L55             cmp     ecx,edi
 08c2  7e ed                             jle     L54
 08c4  83 c4 04          L56             add     esp,00000004H
 08c7  5d                                pop     ebp
 08c8  5f                                pop     edi
 08c9  5e                                pop     esi
 08ca  c3                                ret     
 08cb                    void near clear_so( int, char unsigned ):
 08cb  68 0c 00 00 00                    push    0000000cH
 08d0  e8 00 00 00 00                    call    __CHK
 08d5  53                                push    ebx
 08d6  51                                push    ecx
 08d7  88 d1                             mov     cl,dl
 08d9  89 c2                             mov     edx,eax
 08db  c1 e0 03                          shl     eax,03H
 08de  01 d0                             add     eax,edx
 08e0  c1 e0 02                          shl     eax,02H
 08e3  01 d0                             add     eax,edx
 08e5  8b 90 01 00 00 00                 mov     edx,__22ij7SO near so_list[]+1H[eax]
 08eb  8b 98 05 00 00 00                 mov     ebx,__22ij7SO near so_list[]+5H[eax]
 08f1  0f af da                          imul    ebx,edx
 08f4  89 ca                             mov     edx,ecx
 08f6  81 e2 ff 00 00 00                 and     edx,000000ffH
 08fc  8b 80 21 00 00 00                 mov     eax,__22ij7SO near so_list[]+21H[eax]
 0902  e8 00 00 00 00                    call    memset_
 0907  59                                pop     ecx
 0908  5b                                pop     ebx
 0909  c3                                ret     
 090a                    void near pset_sub( int, int, char unsigned ):
 090a  68 0c 00 00 00                    push    0000000cH
 090f  e8 00 00 00 00                    call    __CHK
 0914  51                                push    ecx
 0915  56                                push    esi
 0916  89 c1                             mov     ecx,eax
 0918  89 d6                             mov     esi,edx
 091a  31 d2                             xor     edx,edx
 091c  8a 15 00 00 00 00                 mov     dl,char unsigned near active_so
 0922  89 d0                             mov     eax,edx
 0924  c1 e0 03                          shl     eax,03H
 0927  01 d0                             add     eax,edx
 0929  0f af b4 82 01 00 
       00 00                             imul    esi,__22ij7SO near so_list[]+1H[edx+eax*4]
 0931  01 f1                             add     ecx,esi
 0933  8b 84 82 21 00 00 
       00                                mov     eax,__22ij7SO near so_list[]+21H[edx+eax*4]
 093a  01 c8                             add     eax,ecx
 093c  31 d2                             xor     edx,edx
 093e  8a 15 00 00 00 00                 mov     dl,char unsigned near logic_flag
 0944  85 d2                             test    edx,edx
 0946  75 05                             jne     L57
 0948  88 18                             mov     [eax],bl
 094a  5e                                pop     esi
 094b  59                                pop     ecx
 094c  c3                                ret     
 094d  83 fa 01          L57             cmp     edx,00000001H
 0950  75 05                             jne     L58
 0952  30 18                             xor     [eax],bl
 0954  5e                                pop     esi
 0955  59                                pop     ecx
 0956  c3                                ret     
 0957  83 fa 04          L58             cmp     edx,00000004H
 095a  75 05                             jne     L59
 095c  08 18                             or      [eax],bl
 095e  5e                                pop     esi
 095f  59                                pop     ecx
 0960  c3                                ret     
 0961  83 fa 02          L59             cmp     edx,00000002H
 0964  75 02                             jne     L60
 0966  20 18                             and     [eax],bl
 0968  5e                L60             pop     esi
 0969  59                                pop     ecx
 096a  c3                                ret     
 096b                    void near view():
 096b  68 1c 00 00 00                    push    0000001cH
 0970  e8 00 00 00 00                    call    __CHK
 0975  53                                push    ebx
 0976  51                                push    ecx
 0977  52                                push    edx
 0978  56                                push    esi
 0979  57                                push    edi
 097a  55                                push    ebp
 097b  a1 00 00 00 00                    mov     eax,char unsigned near * near buffer_address
 0980  a3 00 00 00 00                    mov     char unsigned near * near void near view()::.0::address,eax
 0985  31 c0                             xor     eax,eax
 0987  a0 1a 00 00 00                    mov     al,__3a58ujVESAINFO near _vi+1aH
 098c  a3 00 00 00 00                    mov     int near void near view()::.0::bank,eax
 0991  a1 00 00 00 00                    mov     eax,int unsigned near d_w
 0996  a3 00 00 00 00                    mov     int unsigned near void near view()::.0::view_w,eax
 099b  a1 00 00 00 00                    mov     eax,int unsigned near d_h
 09a0  a3 00 00 00 00                    mov     int unsigned near void near view()::.0::view_h,eax
 09a5  83 3d 00 00 00 00 
       01                                cmp     dword ptr int near void near view()::.0::bank,00000001H
 09ac  0f 85 01 01 00 00                 jne     L67
 09b2  81 3d 00 00 00 00 
       40 01 00 00                       cmp     dword ptr int unsigned near d_w,00000140H
 09bc  75 33                             jne     L61
 09be  3d c8 00 00 00                    cmp     eax,000000c8H
 09c3  75 2c                             jne     L61
 09c5  83 3d 00 00 00 00 
       00                                cmp     dword ptr int near d_x,00000000H
 09cc  75 23                             jne     L61
 09ce  83 3d 00 00 00 00 
       00                                cmp     dword ptr int near d_y,00000000H
 09d5  75 1a                             jne     L61
 09d7  8b 15 00 00 00 00                 mov     edx,char unsigned near * near void near view()::.0::address
 09dd  bb 00 fa 00 00                    mov     ebx,0000fa00H
 09e2  b8 00 00 0a 00                    mov     eax,000a0000H
 09e7  e8 00 00 00 00                    call    memmove_
 09ec  e9 bb 00 00 00                    jmp     L66
 09f1  a1 00 00 00 00    L61             mov     eax,int near d_x
 09f6  03 05 00 00 00 00                 add     eax,int unsigned near d_w
 09fc  8b 0d 00 00 00 00                 mov     ecx,int unsigned near vh
 0a02  39 c8                             cmp     eax,ecx
 0a04  72 0f                             jb      L62
 0a06  89 c8                             mov     eax,ecx
 0a08  8b 35 00 00 00 00                 mov     esi,int near d_x
 0a0e  29 f0                             sub     eax,esi
 0a10  a3 00 00 00 00                    mov     int unsigned near void near view()::.0::view_w,eax
 0a15  a1 00 00 00 00    L62             mov     eax,int near d_y
 0a1a  03 05 00 00 00 00                 add     eax,int unsigned near d_h
 0a20  8b 2d 00 00 00 00                 mov     ebp,int unsigned near vv
 0a26  39 e8                             cmp     eax,ebp
 0a28  72 0f                             jb      L63
 0a2a  89 e8                             mov     eax,ebp
 0a2c  8b 15 00 00 00 00                 mov     edx,int near d_y
 0a32  29 d0                             sub     eax,edx
 0a34  a3 00 00 00 00                    mov     int unsigned near void near view()::.0::view_h,eax
 0a39  8b 15 00 00 00 00 L63             mov     edx,int near d_y
 0a3f  89 d0                             mov     eax,edx
 0a41  c1 e0 02                          shl     eax,02H
 0a44  01 d0                             add     eax,edx
 0a46  c1 e0 06                          shl     eax,06H
 0a49  03 05 00 00 00 00                 add     eax,int near d_x
 0a4f  05 00 00 0a 00                    add     eax,000a0000H
 0a54  a3 00 00 00 00                    mov     char unsigned near * near void near view()::.0::_320_address,eax
 0a59  31 c9                             xor     ecx,ecx
 0a5b  89 0d 00 00 00 00                 mov     int near void near view()::.0::i,ecx
 0a61  eb 3c                             jmp     L65
 0a63  8b 1d 00 00 00 00 L64             mov     ebx,int unsigned near void near view()::.0::view_w
 0a69  8b 15 00 00 00 00                 mov     edx,char unsigned near * near void near view()::.0::address
 0a6f  a1 00 00 00 00                    mov     eax,char unsigned near * near void near view()::.0::_320_address
 0a74  e8 00 00 00 00                    call    memmove_
 0a79  31 c0                             xor     eax,eax
 0a7b  a0 00 00 00 00                    mov     al,char unsigned near buffer_so
 0a80  6b c0 25                          imul    eax,25H
 0a83  81 05 00 00 00 00 
       40 01 00 00                       add     dword ptr char unsigned near * near void near view()::.0::_320_address,00000140H
 0a8d  8b 80 01 00 00 00                 mov     eax,__22ij7SO near so_list[]+1H[eax]
 0a93  01 05 00 00 00 00                 add     char unsigned near * near void near view()::.0::address,eax
 0a99  ff 05 00 00 00 00                 inc     dword ptr int near void near view()::.0::i
 0a9f  a1 00 00 00 00    L65             mov     eax,int near void near view()::.0::i
 0aa4  3b 05 00 00 00 00                 cmp     eax,int unsigned near void near view()::.0::view_h
 0aaa  72 b7                             jb      L64
 0aac  5d                L66             pop     ebp
 0aad  5f                                pop     edi
 0aae  5e                                pop     esi
 0aaf  5a                                pop     edx
 0ab0  59                                pop     ecx
 0ab1  5b                                pop     ebx
 0ab2  c3                                ret     
 0ab3  a1 00 00 00 00    L67             mov     eax,int unsigned near d_w
 0ab8  3b 05 00 00 00 00                 cmp     eax,int unsigned near vh
 0abe  75 65                             jne     L70
 0ac0  a1 00 00 00 00                    mov     eax,int unsigned near d_h
 0ac5  3b 05 00 00 00 00                 cmp     eax,int unsigned near vv
 0acb  75 58                             jne     L70
 0acd  8b 35 00 00 00 00                 mov     esi,int near d_x
 0ad3  85 f6                             test    esi,esi
 0ad5  75 4e                             jne     L70
 0ad7  83 3d 00 00 00 00 
       00                                cmp     dword ptr int near d_y,00000000H
 0ade  75 45                             jne     L70
 0ae0  89 35 00 00 00 00                 mov     int near void near view()::.0::i,esi
 0ae6  eb 2e                             jmp     L69
 0ae8  0f bf 05 00 00 00 
       00                L68             movsx   eax,word ptr int near void near view()::.0::i
 0aef  e8 00 00 00 00                    call    int near set_page( short )
 0af4  8b 15 00 00 00 00                 mov     edx,char unsigned near * near void near view()::.0::address
 0afa  bb ff ff 00 00                    mov     ebx,0000ffffH
 0aff  b8 00 00 0a 00                    mov     eax,000a0000H
 0b04  e8 00 00 00 00                    call    memmove_
 0b09  66 ff 05 02 00 00 
       00                                inc     word ptr char unsigned near * near void near view()::.0::address+2H
 0b10  ff 05 00 00 00 00                 inc     dword ptr int near void near view()::.0::i
 0b16  a1 00 00 00 00    L69             mov     eax,int near void near view()::.0::i
 0b1b  3b 05 00 00 00 00                 cmp     eax,int near void near view()::.0::bank
 0b21  7c c5                             jl      L68
 0b23  eb 87                             jmp     L66
 0b25  a1 00 00 00 00    L70             mov     eax,int near d_x
 0b2a  03 05 00 00 00 00                 add     eax,int unsigned near d_w
 0b30  8b 15 00 00 00 00                 mov     edx,int unsigned near vh
 0b36  39 d0                             cmp     eax,edx
 0b38  72 0f                             jb      L71
 0b3a  89 d0                             mov     eax,edx
 0b3c  8b 1d 00 00 00 00                 mov     ebx,int near d_x
 0b42  29 d8                             sub     eax,ebx
 0b44  a3 00 00 00 00                    mov     int unsigned near void near view()::.0::view_w,eax
 0b49  a1 00 00 00 00    L71             mov     eax,int near d_y
 0b4e  03 05 00 00 00 00                 add     eax,int unsigned near d_h
 0b54  8b 35 00 00 00 00                 mov     esi,int unsigned near vv
 0b5a  39 f0                             cmp     eax,esi
 0b5c  72 0f                             jb      L72
 0b5e  89 f0                             mov     eax,esi
 0b60  8b 3d 00 00 00 00                 mov     edi,int near d_y
 0b66  29 f8                             sub     eax,edi
 0b68  a3 00 00 00 00                    mov     int unsigned near void near view()::.0::view_h,eax
 0b6d  31 c0             L72             xor     eax,eax
 0b6f  66 a1 04 00 00 00                 mov     ax,__3a58ujVESAINFO near _vi+4H
 0b75  a3 00 00 00 00                    mov     int unsigned near win_g,eax
 0b7a  8b 15 00 00 00 00                 mov     edx,int near d_y
 0b80  0f af 15 00 00 00 
       00                                imul    edx,int unsigned near vh
 0b87  a1 00 00 00 00                    mov     eax,int near d_x
 0b8c  01 c2                             add     edx,eax
 0b8e  89 15 00 00 00 00                 mov     int unsigned near TEMP,edx
 0b94  8b 1d 00 00 00 00                 mov     ebx,int unsigned near win_g
 0b9a  c1 e3 0a                          shl     ebx,0aH
 0b9d  31 d2                             xor     edx,edx
 0b9f  a1 00 00 00 00                    mov     eax,int unsigned near TEMP
 0ba4  f7 f3                             div     ebx
 0ba6  66 a3 00 00 00 00                 mov     short near bank_n,ax
 0bac  a1 00 00 00 00                    mov     eax,int unsigned near TEMP
 0bb1  31 d2                             xor     edx,edx
 0bb3  8b 1d 00 00 00 00                 mov     ebx,int unsigned near win_g
 0bb9  f7 f3                             div     ebx
 0bbb  89 d0                             mov     eax,edx
 0bbd  c1 e0 0a                          shl     eax,0aH
 0bc0  05 00 00 0a 00                    add     eax,000a0000H
 0bc5  a3 00 00 00 00                    mov     char unsigned near * near offset_n,eax
 0bca  0f bf 05 00 00 00 
       00                                movsx   eax,word ptr short near bank_n
 0bd1  e8 00 00 00 00                    call    int near set_page( short )
 0bd6  31 c9                             xor     ecx,ecx
 0bd8  89 0d 00 00 00 00                 mov     int near void near view()::.0::i,ecx
 0bde  eb 55                             jmp     L75
 0be0  89 d3             L73             mov     ebx,edx
 0be2  8b 15 00 00 00 00                 mov     edx,char unsigned near * near void near view()::.0::address
 0be8  e8 00 00 00 00                    call    memmove_
 0bed  a1 00 00 00 00                    mov     eax,int unsigned near void near view()::.0::view_w
 0bf2  8b 2d 00 00 00 00                 mov     ebp,char unsigned near * near offset_n
 0bf8  01 c5                             add     ebp,eax
 0bfa  89 2d 00 00 00 00                 mov     char unsigned near * near offset_n,ebp
 0c00  01 05 00 00 00 00                 add     char unsigned near * near void near view()::.0::address,eax
 0c06  81 fd ff ff 0a 00                 cmp     ebp,000affffH
 0c0c  76 21                             jbe     L74
 0c0e  66 8b 15 00 00 00 
       00                                mov     dx,short near bank_n
 0c15  42                                inc     edx
 0c16  66 89 15 00 00 00 
       00                                mov     short near bank_n,dx
 0c1d  0f bf c2                          movsx   eax,dx
 0c20  e8 00 00 00 00                    call    int near set_page( short )
 0c25  81 2d 00 00 00 00 
       ff ff 00 00                       sub     dword ptr char unsigned near * near offset_n,0000ffffH
 0c2f  ff 05 00 00 00 00 L74             inc     dword ptr int near void near view()::.0::i
 0c35  a1 00 00 00 00    L75             mov     eax,int near void near view()::.0::i
 0c3a  3b 05 00 00 00 00                 cmp     eax,int unsigned near void near view()::.0::view_h
 0c40  0f 83 66 fe ff ff                 jae     L66
 0c46  a1 00 00 00 00                    mov     eax,char unsigned near * near offset_n
 0c4b  8b 15 00 00 00 00                 mov     edx,int unsigned near void near view()::.0::view_w
 0c51  8d 1c 10                          lea     ebx,[eax+edx]
 0c54  89 1d 00 00 00 00                 mov     int unsigned near temp_add,ebx
 0c5a  81 fb ff ff 0a 00                 cmp     ebx,000affffH
 0c60  0f 86 7a ff ff ff                 jbe     L73
 0c66  8d 93 01 00 f5 ff                 lea     edx,-0affffH[ebx]
 0c6c  89 15 00 00 00 00                 mov     int unsigned near temp_add2,edx
 0c72  8b 1d 00 00 00 00                 mov     ebx,int unsigned near void near view()::.0::view_w
 0c78  29 d3                             sub     ebx,edx
 0c7a  8b 15 00 00 00 00                 mov     edx,char unsigned near * near void near view()::.0::address
 0c80  e8 00 00 00 00                    call    memmove_
 0c85  66 8b 1d 00 00 00 
       00                                mov     bx,short near bank_n
 0c8c  43                                inc     ebx
 0c8d  66 89 1d 00 00 00 
       00                                mov     short near bank_n,bx
 0c94  0f bf c3                          movsx   eax,bx
 0c97  e8 00 00 00 00                    call    int near set_page( short )
 0c9c  a1 00 00 00 00                    mov     eax,int unsigned near temp_add2
 0ca1  05 00 00 0a 00                    add     eax,000a0000H
 0ca6  a3 00 00 00 00                    mov     char unsigned near * near offset_n,eax
 0cab  8b 1d 00 00 00 00                 mov     ebx,int unsigned near temp_add2
 0cb1  8b 15 00 00 00 00                 mov     edx,char unsigned near * near void near view()::.0::address
 0cb7  03 15 00 00 00 00                 add     edx,int unsigned near void near view()::.0::view_w
 0cbd  29 da                             sub     edx,ebx
 0cbf  b8 00 00 0a 00                    mov     eax,000a0000H
 0cc4  e8 00 00 00 00                    call    memmove_
 0cc9  a1 00 00 00 00                    mov     eax,int unsigned near void near view()::.0::view_w
 0cce  01 05 00 00 00 00                 add     char unsigned near * near void near view()::.0::address,eax
 0cd4  e9 56 ff ff ff                    jmp     L74
 0cd9                    void near move_image_to_buffer( int ):
 0cd9  68 1c 00 00 00                    push    0000001cH
 0cde  e8 00 00 00 00                    call    __CHK
 0ce3  53                                push    ebx
 0ce4  51                                push    ecx
 0ce5  52                                push    edx
 0ce6  56                                push    esi
 0ce7  57                                push    edi
 0ce8  55                                push    ebp
 0ce9  89 c2                             mov     edx,eax
 0ceb  c1 e0 03                          shl     eax,03H
 0cee  01 d0                             add     eax,edx
 0cf0  c1 e0 02                          shl     eax,02H
 0cf3  01 d0                             add     eax,edx
 0cf5  8b 98 19 00 00 00                 mov     ebx,__22ij7SO near so_list[]+19H[eax]
 0cfb  89 1d 00 00 00 00                 mov     int near void near move_image_to_buffer( int )::.0::dis_x,ebx
 0d01  8b 98 1d 00 00 00                 mov     ebx,__22ij7SO near so_list[]+1dH[eax]
 0d07  89 1d 00 00 00 00                 mov     int near void near move_image_to_buffer( int )::.0::dis_y,ebx
 0d0d  8b 98 11 00 00 00                 mov     ebx,__22ij7SO near so_list[]+11H[eax]
 0d13  89 1d 00 00 00 00                 mov     int unsigned near void near move_image_to_buffer( int )::.0::vi_w,ebx
 0d19  8b 98 15 00 00 00                 mov     ebx,__22ij7SO near so_list[]+15H[eax]
 0d1f  89 1d 00 00 00 00                 mov     int unsigned near void near move_image_to_buffer( int )::.0::vi_h,ebx
 0d25  8b 98 09 00 00 00                 mov     ebx,__22ij7SO near so_list[]+9H[eax]
 0d2b  89 1d 00 00 00 00                 mov     int near void near move_image_to_buffer( int )::.0::vwx,ebx
 0d31  8b 80 0d 00 00 00                 mov     eax,__22ij7SO near so_list[]+0dH[eax]
 0d37  a3 00 00 00 00                    mov     int near void near move_image_to_buffer( int )::.0::vwy,eax
 0d3c  85 db                             test    ebx,ebx
 0d3e  7d 0e                             jge     L76
 0d40  01 1d 00 00 00 00                 add     int unsigned near void near move_image_to_buffer( int )::.0::vi_w,ebx
 0d46  31 f6                             xor     esi,esi
 0d48  89 35 00 00 00 00                 mov     int near void near move_image_to_buffer( int )::.0::vwx,esi
 0d4e  8b 3d 00 00 00 00 L76             mov     edi,int near void near move_image_to_buffer( int )::.0::vwy
 0d54  85 ff                             test    edi,edi
 0d56  7d 0f                             jge     L77
 0d58  89 f8                             mov     eax,edi
 0d5a  01 3d 00 00 00 00                 add     int unsigned near void near move_image_to_buffer( int )::.0::vi_h,edi
 0d60  31 f8                             xor     eax,edi
 0d62  a3 00 00 00 00                    mov     int near void near move_image_to_buffer( int )::.0::vwy,eax
 0d67  89 d0             L77             mov     eax,edx
 0d69  c1 e0 03                          shl     eax,03H
 0d6c  01 d0                             add     eax,edx
 0d6e  c1 e0 02                          shl     eax,02H
 0d71  01 d0                             add     eax,edx
 0d73  8b 1d 00 00 00 00                 mov     ebx,int near void near move_image_to_buffer( int )::.0::vwx
 0d79  03 1d 00 00 00 00                 add     ebx,int unsigned near void near move_image_to_buffer( int )::.0::vi_w
 0d7f  8b b0 01 00 00 00                 mov     esi,__22ij7SO near so_list[]+1H[eax]
 0d85  39 f3                             cmp     ebx,esi
 0d87  72 0f                             jb      L78
 0d89  89 f0                             mov     eax,esi
 0d8b  8b 3d 00 00 00 00                 mov     edi,int near void near move_image_to_buffer( int )::.0::vwx
 0d91  29 f8                             sub     eax,edi
 0d93  a3 00 00 00 00                    mov     int unsigned near void near move_image_to_buffer( int )::.0::vi_w,eax
 0d98  89 d0             L78             mov     eax,edx
 0d9a  c1 e0 03                          shl     eax,03H
 0d9d  01 d0                             add     eax,edx
 0d9f  c1 e0 02                          shl     eax,02H
 0da2  01 d0                             add     eax,edx
 0da4  8b 1d 00 00 00 00                 mov     ebx,int near void near move_image_to_buffer( int )::.0::vwy
 0daa  03 1d 00 00 00 00                 add     ebx,int unsigned near void near move_image_to_buffer( int )::.0::vi_h
 0db0  8b 88 05 00 00 00                 mov     ecx,__22ij7SO near so_list[]+5H[eax]
 0db6  39 cb                             cmp     ebx,ecx
 0db8  72 0f                             jb      L79
 0dba  89 c8                             mov     eax,ecx
 0dbc  8b 35 00 00 00 00                 mov     esi,int near void near move_image_to_buffer( int )::.0::vwy
 0dc2  29 f0                             sub     eax,esi
 0dc4  a3 00 00 00 00                    mov     int unsigned near void near move_image_to_buffer( int )::.0::vi_h,eax
 0dc9  89 d0             L79             mov     eax,edx
 0dcb  c1 e0 03                          shl     eax,03H
 0dce  01 d0                             add     eax,edx
 0dd0  c1 e0 02                          shl     eax,02H
 0dd3  01 d0                             add     eax,edx
 0dd5  8b 1d 00 00 00 00                 mov     ebx,int near void near move_image_to_buffer( int )::.0::vwy
 0ddb  0f af 98 01 00 00 
       00                                imul    ebx,__22ij7SO near so_list[]+1H[eax]
 0de2  03 1d 00 00 00 00                 add     ebx,int near void near move_image_to_buffer( int )::.0::vwx
 0de8  8b 80 21 00 00 00                 mov     eax,__22ij7SO near so_list[]+21H[eax]
 0dee  01 c3                             add     ebx,eax
 0df0  89 1d 00 00 00 00                 mov     char unsigned near * near void near move_image_to_buffer( int )::.0::address,ebx
 0df6  31 c0                             xor     eax,eax
 0df8  a0 00 00 00 00                    mov     al,char unsigned near buffer_so
 0dfd  89 c1                             mov     ecx,eax
 0dff  c1 e1 03                          shl     ecx,03H
 0e02  01 c1                             add     ecx,eax
 0e04  c1 e1 02                          shl     ecx,02H
 0e07  01 c1                             add     ecx,eax
 0e09  a1 00 00 00 00                    mov     eax,int near void near move_image_to_buffer( int )::.0::dis_y
 0e0e  0f af 81 01 00 00 
       00                                imul    eax,__22ij7SO near so_list[]+1H[ecx]
 0e15  8b 1d 00 00 00 00                 mov     ebx,int near void near move_image_to_buffer( int )::.0::dis_x
 0e1b  01 c3                             add     ebx,eax
 0e1d  a1 00 00 00 00                    mov     eax,char unsigned near * near buffer_address
 0e22  01 c3                             add     ebx,eax
 0e24  89 1d 00 00 00 00                 mov     char unsigned near * near void near move_image_to_buffer( int )::.0::address_buff,ebx
 0e2a  83 3d 00 00 00 00 
       00                                cmp     dword ptr int near void near move_image_to_buffer( int )::.0::dis_x,00000000H
 0e31  75 3f                             jne     L80
 0e33  83 3d 00 00 00 00 
       00                                cmp     dword ptr int near void near move_image_to_buffer( int )::.0::dis_y,00000000H
 0e3a  75 36                             jne     L80
 0e3c  a1 00 00 00 00                    mov     eax,int unsigned near void near move_image_to_buffer( int )::.0::vi_w
 0e41  8b a9 01 00 00 00                 mov     ebp,__22ij7SO near so_list[]+1H[ecx]
 0e47  39 e8                             cmp     eax,ebp
 0e49  75 27                             jne     L80
 0e4b  a1 00 00 00 00                    mov     eax,int unsigned near void near move_image_to_buffer( int )::.0::vi_h
 0e50  3b 81 05 00 00 00                 cmp     eax,__22ij7SO near so_list[]+5H[ecx]
 0e56  75 1a                             jne     L80
 0e58  89 eb                             mov     ebx,ebp
 0e5a  0f af d8                          imul    ebx,eax
 0e5d  8b 15 00 00 00 00                 mov     edx,char unsigned near * near void near move_image_to_buffer( int )::.0::address
 0e63  a1 00 00 00 00                    mov     eax,char unsigned near * near void near move_image_to_buffer( int )::.0::address_buff
 0e68  e8 00 00 00 00                    call    memmove_
 0e6d  e9 3a fc ff ff                    jmp     L66
 0e72  8b 0d 00 00 00 00 L80             mov     ecx,int near void near move_image_to_buffer( int )::.0::dis_x
 0e78  85 c9                             test    ecx,ecx
 0e7a  7d 0e                             jge     L81
 0e7c  01 0d 00 00 00 00                 add     int unsigned near void near move_image_to_buffer( int )::.0::vi_w,ecx
 0e82  31 ff                             xor     edi,edi
 0e84  89 3d 00 00 00 00                 mov     int near void near move_image_to_buffer( int )::.0::dis_x,edi
 0e8a  8b 2d 00 00 00 00 L81             mov     ebp,int near void near move_image_to_buffer( int )::.0::dis_y
 0e90  85 ed                             test    ebp,ebp
 0e92  7d 0e                             jge     L82
 0e94  01 2d 00 00 00 00                 add     int unsigned near void near move_image_to_buffer( int )::.0::vi_h,ebp
 0e9a  31 c9                             xor     ecx,ecx
 0e9c  89 0d 00 00 00 00                 mov     int near void near move_image_to_buffer( int )::.0::dis_y,ecx
 0ea2  31 db             L82             xor     ebx,ebx
 0ea4  8a 1d 00 00 00 00                 mov     bl,char unsigned near buffer_so
 0eaa  89 d8                             mov     eax,ebx
 0eac  c1 e0 03                          shl     eax,03H
 0eaf  01 d8                             add     eax,ebx
 0eb1  c1 e0 02                          shl     eax,02H
 0eb4  01 d8                             add     eax,ebx
 0eb6  8b 1d 00 00 00 00                 mov     ebx,int near void near move_image_to_buffer( int )::.0::dis_x
 0ebc  03 1d 00 00 00 00                 add     ebx,int unsigned near void near move_image_to_buffer( int )::.0::vi_w
 0ec2  8b b8 01 00 00 00                 mov     edi,__22ij7SO near so_list[]+1H[eax]
 0ec8  39 fb                             cmp     ebx,edi
 0eca  72 0f                             jb      L83
 0ecc  89 f8                             mov     eax,edi
 0ece  8b 2d 00 00 00 00                 mov     ebp,int near void near move_image_to_buffer( int )::.0::dis_x
 0ed4  29 e8                             sub     eax,ebp
 0ed6  a3 00 00 00 00                    mov     int unsigned near void near move_image_to_buffer( int )::.0::vi_w,eax
 0edb  31 db             L83             xor     ebx,ebx
 0edd  8a 1d 00 00 00 00                 mov     bl,char unsigned near buffer_so
 0ee3  89 d8                             mov     eax,ebx
 0ee5  c1 e0 03                          shl     eax,03H
 0ee8  01 d8                             add     eax,ebx
 0eea  c1 e0 02                          shl     eax,02H
 0eed  01 d8                             add     eax,ebx
 0eef  8b 1d 00 00 00 00                 mov     ebx,int near void near move_image_to_buffer( int )::.0::dis_y
 0ef5  03 1d 00 00 00 00                 add     ebx,int unsigned near void near move_image_to_buffer( int )::.0::vi_h
 0efb  8b b0 05 00 00 00                 mov     esi,__22ij7SO near so_list[]+5H[eax]
 0f01  39 f3                             cmp     ebx,esi
 0f03  72 0f                             jb      L84
 0f05  89 f0                             mov     eax,esi
 0f07  8b 3d 00 00 00 00                 mov     edi,int near void near move_image_to_buffer( int )::.0::dis_y
 0f0d  29 f8                             sub     eax,edi
 0f0f  a3 00 00 00 00                    mov     int unsigned near void near move_image_to_buffer( int )::.0::vi_h,eax
 0f14  83 3d 00 00 00 00 
       00                L84             cmp     dword ptr int unsigned near void near move_image_to_buffer( int )::.0::vi_w,00000000H
 0f1b  0f 86 8b fb ff ff                 jbe     L66
 0f21  83 3d 00 00 00 00 
       00                                cmp     dword ptr int unsigned near void near move_image_to_buffer( int )::.0::vi_h,00000000H
 0f28  0f 86 7e fb ff ff                 jbe     L66
 0f2e  31 db                             xor     ebx,ebx
 0f30  89 1d 00 00 00 00                 mov     int near void near move_image_to_buffer( int )::.0::i,ebx
 0f36  89 d1                             mov     ecx,edx
 0f38  c1 e1 03                          shl     ecx,03H
 0f3b  01 d1                             add     ecx,edx
 0f3d  c1 e1 02                          shl     ecx,02H
 0f40  01 d1                             add     ecx,edx
 0f42  eb 3e                             jmp     L86
 0f44  8b 1d 00 00 00 00 L85             mov     ebx,int unsigned near void near move_image_to_buffer( int )::.0::vi_w
 0f4a  8b 15 00 00 00 00                 mov     edx,char unsigned near * near void near move_image_to_buffer( int )::.0::address
 0f50  a1 00 00 00 00                    mov     eax,char unsigned near * near void near move_image_to_buffer( int )::.0::address_buff
 0f55  e8 00 00 00 00                    call    memmove_
 0f5a  31 c0                             xor     eax,eax
 0f5c  a0 00 00 00 00                    mov     al,char unsigned near buffer_so
 0f61  6b c0 25                          imul    eax,25H
 0f64  8b 80 01 00 00 00                 mov     eax,__22ij7SO near so_list[]+1H[eax]
 0f6a  01 05 00 00 00 00                 add     char unsigned near * near void near move_image_to_buffer( int )::.0::address_buff,eax
 0f70  8b 81 01 00 00 00                 mov     eax,__22ij7SO near so_list[]+1H[ecx]
 0f76  01 05 00 00 00 00                 add     char unsigned near * near void near move_image_to_buffer( int )::.0::address,eax
 0f7c  ff 05 00 00 00 00                 inc     dword ptr int near void near move_image_to_buffer( int )::.0::i
 0f82  a1 00 00 00 00    L86             mov     eax,int near void near move_image_to_buffer( int )::.0::i
 0f87  3b 05 00 00 00 00                 cmp     eax,int unsigned near void near move_image_to_buffer( int )::.0::vi_h
 0f8d  72 b5                             jb      L85
 0f8f  e9 18 fb ff ff                    jmp     L66
 0f94                    void near move_sprite_to_buffer( int ):
 0f94  68 1c 00 00 00                    push    0000001cH
 0f99  e8 00 00 00 00                    call    __CHK
 0f9e  53                                push    ebx
 0f9f  51                                push    ecx
 0fa0  52                                push    edx
 0fa1  56                                push    esi
 0fa2  57                                push    edi
 0fa3  55                                push    ebp
 0fa4  89 c2                             mov     edx,eax
 0fa6  c1 e0 03                          shl     eax,03H
 0fa9  01 d0                             add     eax,edx
 0fab  c1 e0 02                          shl     eax,02H
 0fae  01 d0                             add     eax,edx
 0fb0  8b 98 19 00 00 00                 mov     ebx,__22ij7SO near so_list[]+19H[eax]
 0fb6  89 1d 00 00 00 00                 mov     int near void near move_sprite_to_buffer( int )::.0::dis_x,ebx
 0fbc  8b 98 1d 00 00 00                 mov     ebx,__22ij7SO near so_list[]+1dH[eax]
 0fc2  89 1d 00 00 00 00                 mov     int near void near move_sprite_to_buffer( int )::.0::dis_y,ebx
 0fc8  8b 98 11 00 00 00                 mov     ebx,__22ij7SO near so_list[]+11H[eax]
 0fce  89 1d 00 00 00 00                 mov     int unsigned near void near move_sprite_to_buffer( int )::.0::vi_w,ebx
 0fd4  8b 98 15 00 00 00                 mov     ebx,__22ij7SO near so_list[]+15H[eax]
 0fda  89 1d 00 00 00 00                 mov     int unsigned near void near move_sprite_to_buffer( int )::.0::vi_h,ebx
 0fe0  8b 98 09 00 00 00                 mov     ebx,__22ij7SO near so_list[]+9H[eax]
 0fe6  89 1d 00 00 00 00                 mov     int near void near move_sprite_to_buffer( int )::.0::vwx,ebx
 0fec  8b 80 0d 00 00 00                 mov     eax,__22ij7SO near so_list[]+0dH[eax]
 0ff2  a3 00 00 00 00                    mov     int near void near move_sprite_to_buffer( int )::.0::vwy,eax
 0ff7  85 db                             test    ebx,ebx
 0ff9  7d 0e                             jge     L87
 0ffb  01 1d 00 00 00 00                 add     int unsigned near void near move_sprite_to_buffer( int )::.0::vi_w,ebx
 1001  31 f6                             xor     esi,esi
 1003  89 35 00 00 00 00                 mov     int near void near move_sprite_to_buffer( int )::.0::vwx,esi
 1009  8b 3d 00 00 00 00 L87             mov     edi,int near void near move_sprite_to_buffer( int )::.0::vwy
 100f  85 ff                             test    edi,edi
 1011  7d 0f                             jge     L88
 1013  89 f8                             mov     eax,edi
 1015  01 3d 00 00 00 00                 add     int unsigned near void near move_sprite_to_buffer( int )::.0::vi_h,edi
 101b  31 f8                             xor     eax,edi
 101d  a3 00 00 00 00                    mov     int near void near move_sprite_to_buffer( int )::.0::vwy,eax
 1022  89 d0             L88             mov     eax,edx
 1024  c1 e0 03                          shl     eax,03H
 1027  01 d0                             add     eax,edx
 1029  c1 e0 02                          shl     eax,02H
 102c  01 d0                             add     eax,edx
 102e  8b 1d 00 00 00 00                 mov     ebx,int near void near move_sprite_to_buffer( int )::.0::vwx
 1034  03 1d 00 00 00 00                 add     ebx,int unsigned near void near move_sprite_to_buffer( int )::.0::vi_w
 103a  8b b0 01 00 00 00                 mov     esi,__22ij7SO near so_list[]+1H[eax]
 1040  39 f3                             cmp     ebx,esi
 1042  72 0f                             jb      L89
 1044  89 f0                             mov     eax,esi
 1046  8b 3d 00 00 00 00                 mov     edi,int near void near move_sprite_to_buffer( int )::.0::vwx
 104c  29 f8                             sub     eax,edi
 104e  a3 00 00 00 00                    mov     int unsigned near void near move_sprite_to_buffer( int )::.0::vi_w,eax
 1053  89 d0             L89             mov     eax,edx
 1055  c1 e0 03                          shl     eax,03H
 1058  01 d0                             add     eax,edx
 105a  c1 e0 02                          shl     eax,02H
 105d  01 d0                             add     eax,edx
 105f  8b 1d 00 00 00 00                 mov     ebx,int near void near move_sprite_to_buffer( int )::.0::vwy
 1065  03 1d 00 00 00 00                 add     ebx,int unsigned near void near move_sprite_to_buffer( int )::.0::vi_h
 106b  8b 88 05 00 00 00                 mov     ecx,__22ij7SO near so_list[]+5H[eax]
 1071  39 cb                             cmp     ebx,ecx
 1073  72 0f                             jb      L90
 1075  89 c8                             mov     eax,ecx
 1077  8b 35 00 00 00 00                 mov     esi,int near void near move_sprite_to_buffer( int )::.0::vwy
 107d  29 f0                             sub     eax,esi
 107f  a3 00 00 00 00                    mov     int unsigned near void near move_sprite_to_buffer( int )::.0::vi_h,eax
 1084  8b 3d 00 00 00 00 L90             mov     edi,int near void near move_sprite_to_buffer( int )::.0::dis_x
 108a  85 ff                             test    edi,edi
 108c  7d 0f                             jge     L91
 108e  89 f8                             mov     eax,edi
 1090  01 3d 00 00 00 00                 add     int unsigned near void near move_sprite_to_buffer( int )::.0::vi_w,edi
 1096  31 f8                             xor     eax,edi
 1098  a3 00 00 00 00                    mov     int near void near move_sprite_to_buffer( int )::.0::dis_x,eax
 109d  8b 1d 00 00 00 00 L91             mov     ebx,int near void near move_sprite_to_buffer( int )::.0::dis_y
 10a3  85 db                             test    ebx,ebx
 10a5  7d 0e                             jge     L92
 10a7  01 1d 00 00 00 00                 add     int unsigned near void near move_sprite_to_buffer( int )::.0::vi_h,ebx
 10ad  31 f6                             xor     esi,esi
 10af  89 35 00 00 00 00                 mov     int near void near move_sprite_to_buffer( int )::.0::dis_y,esi
 10b5  31 db             L92             xor     ebx,ebx
 10b7  8a 1d 00 00 00 00                 mov     bl,char unsigned near buffer_so
 10bd  89 d8                             mov     eax,ebx
 10bf  c1 e0 03                          shl     eax,03H
 10c2  01 d8                             add     eax,ebx
 10c4  c1 e0 02                          shl     eax,02H
 10c7  01 d8                             add     eax,ebx
 10c9  8b 1d 00 00 00 00                 mov     ebx,int near void near move_sprite_to_buffer( int )::.0::dis_x
 10cf  03 1d 00 00 00 00                 add     ebx,int unsigned near void near move_sprite_to_buffer( int )::.0::vi_w
 10d5  8b a8 01 00 00 00                 mov     ebp,__22ij7SO near so_list[]+1H[eax]
 10db  39 eb                             cmp     ebx,ebp
 10dd  72 0f                             jb      L93
 10df  89 e8                             mov     eax,ebp
 10e1  8b 1d 00 00 00 00                 mov     ebx,int near void near move_sprite_to_buffer( int )::.0::dis_x
 10e7  29 d8                             sub     eax,ebx
 10e9  a3 00 00 00 00                    mov     int unsigned near void near move_sprite_to_buffer( int )::.0::vi_w,eax
 10ee  31 db             L93             xor     ebx,ebx
 10f0  8a 1d 00 00 00 00                 mov     bl,char unsigned near buffer_so
 10f6  89 d8                             mov     eax,ebx
 10f8  c1 e0 03                          shl     eax,03H
 10fb  01 d8                             add     eax,ebx
 10fd  c1 e0 02                          shl     eax,02H
 1100  01 d8                             add     eax,ebx
 1102  8b 1d 00 00 00 00                 mov     ebx,int near void near move_sprite_to_buffer( int )::.0::dis_y
 1108  03 1d 00 00 00 00                 add     ebx,int unsigned near void near move_sprite_to_buffer( int )::.0::vi_h
 110e  8b b0 05 00 00 00                 mov     esi,__22ij7SO near so_list[]+5H[eax]
 1114  39 f3                             cmp     ebx,esi
 1116  72 0f                             jb      L94
 1118  89 f0                             mov     eax,esi
 111a  8b 3d 00 00 00 00                 mov     edi,int near void near move_sprite_to_buffer( int )::.0::dis_y
 1120  29 f8                             sub     eax,edi
 1122  a3 00 00 00 00                    mov     int unsigned near void near move_sprite_to_buffer( int )::.0::vi_h,eax
 1127  83 3d 00 00 00 00 
       00                L94             cmp     dword ptr int unsigned near void near move_sprite_to_buffer( int )::.0::vi_w,00000000H
 112e  0f 86 78 f9 ff ff                 jbe     L66
 1134  83 3d 00 00 00 00 
       00                                cmp     dword ptr int unsigned near void near move_sprite_to_buffer( int )::.0::vi_h,00000000H
 113b  0f 86 6b f9 ff ff                 jbe     L66
 1141  89 d3                             mov     ebx,edx
 1143  c1 e3 03                          shl     ebx,03H
 1146  01 d3                             add     ebx,edx
 1148  c1 e3 02                          shl     ebx,02H
 114b  01 d3                             add     ebx,edx
 114d  a1 00 00 00 00                    mov     eax,int near void near move_sprite_to_buffer( int )::.0::vwy
 1152  0f af 83 01 00 00 
       00                                imul    eax,__22ij7SO near so_list[]+1H[ebx]
 1159  8b 15 00 00 00 00                 mov     edx,int near void near move_sprite_to_buffer( int )::.0::vwx
 115f  01 c2                             add     edx,eax
 1161  8b 83 21 00 00 00                 mov     eax,__22ij7SO near so_list[]+21H[ebx]
 1167  01 c2                             add     edx,eax
 1169  89 15 00 00 00 00                 mov     char unsigned near * near void near move_sprite_to_buffer( int )::.0::address,edx
 116f  31 d2                             xor     edx,edx
 1171  8a 15 00 00 00 00                 mov     dl,char unsigned near buffer_so
 1177  89 d0                             mov     eax,edx
 1179  c1 e0 03                          shl     eax,03H
 117c  01 d0                             add     eax,edx
 117e  c1 e0 02                          shl     eax,02H
 1181  01 c2                             add     edx,eax
 1183  a1 00 00 00 00                    mov     eax,int near void near move_sprite_to_buffer( int )::.0::dis_y
 1188  0f af 82 01 00 00 
       00                                imul    eax,__22ij7SO near so_list[]+1H[edx]
 118f  8b 15 00 00 00 00                 mov     edx,int near void near move_sprite_to_buffer( int )::.0::dis_x
 1195  01 c2                             add     edx,eax
 1197  a1 00 00 00 00                    mov     eax,char unsigned near * near buffer_address
 119c  01 c2                             add     edx,eax
 119e  89 15 00 00 00 00                 mov     char unsigned near * near void near move_sprite_to_buffer( int )::.0::address_buff,edx
 11a4  31 f6                             xor     esi,esi
 11a6  89 35 00 00 00 00                 mov     int near void near move_sprite_to_buffer( int )::.0::i,esi
 11ac  eb 28                             jmp     L96
 11ae  31 c0             L95             xor     eax,eax
 11b0  a0 00 00 00 00                    mov     al,char unsigned near buffer_so
 11b5  6b c0 25                          imul    eax,25H
 11b8  8b 80 01 00 00 00                 mov     eax,__22ij7SO near so_list[]+1H[eax]
 11be  01 05 00 00 00 00                 add     char unsigned near * near void near move_sprite_to_buffer( int )::.0::address_buff,eax
 11c4  8b 83 01 00 00 00                 mov     eax,__22ij7SO near so_list[]+1H[ebx]
 11ca  01 05 00 00 00 00                 add     char unsigned near * near void near move_sprite_to_buffer( int )::.0::address,eax
 11d0  ff 05 00 00 00 00                 inc     dword ptr int near void near move_sprite_to_buffer( int )::.0::i
 11d6  a1 00 00 00 00    L96             mov     eax,int near void near move_sprite_to_buffer( int )::.0::i
 11db  3b 05 00 00 00 00                 cmp     eax,int unsigned near void near move_sprite_to_buffer( int )::.0::vi_h
 11e1  0f 83 c5 f8 ff ff                 jae     L66
 11e7  a1 00 00 00 00                    mov     eax,char unsigned near * near void near move_sprite_to_buffer( int )::.0::address
 11ec  a3 00 00 00 00                    mov     char unsigned near * near void near move_sprite_to_buffer( int )::.0::temp,eax
 11f1  a1 00 00 00 00                    mov     eax,char unsigned near * near void near move_sprite_to_buffer( int )::.0::address_buff
 11f6  a3 00 00 00 00                    mov     char unsigned near * near void near move_sprite_to_buffer( int )::.0::temp_buff,eax
 11fb  31 ed                             xor     ebp,ebp
 11fd  89 2d 00 00 00 00                 mov     int near void near move_sprite_to_buffer( int )::.0::j,ebp
 1203  eb 12                             jmp     L98
 1205  ff 05 00 00 00 00 L97             inc     dword ptr char unsigned near * near void near move_sprite_to_buffer( int )::.0::temp_buff
 120b  ff 05 00 00 00 00                 inc     dword ptr char unsigned near * near void near move_sprite_to_buffer( int )::.0::temp
 1211  ff 05 00 00 00 00                 inc     dword ptr int near void near move_sprite_to_buffer( int )::.0::j
 1217  a1 00 00 00 00    L98             mov     eax,int near void near move_sprite_to_buffer( int )::.0::j
 121c  3b 05 00 00 00 00                 cmp     eax,int unsigned near void near move_sprite_to_buffer( int )::.0::vi_w
 1222  73 8a                             jae     L95
 1224  a1 00 00 00 00                    mov     eax,char unsigned near * near void near move_sprite_to_buffer( int )::.0::temp
 1229  8a 10                             mov     dl,[eax]
 122b  3a 15 00 00 00 00                 cmp     dl,char unsigned near trans_color
 1231  74 d2                             je      L97
 1233  8b 15 00 00 00 00                 mov     edx,char unsigned near * near void near move_sprite_to_buffer( int )::.0::temp_buff
 1239  8a 00                             mov     al,[eax]
 123b  88 02                             mov     [edx],al
 123d  eb c6                             jmp     L97
 123f  90                                nop     
 1240  b4 12 00 00       L99             DD      L102
 1244  bd 12 00 00                       DD      L103
 1248  f1 12 00 00                       DD      L107
 124c  c6 12 00 00                       DD      L104
 1250  f1 12 00 00                       DD      L107
 1254  cf 12 00 00                       DD      L105
 1258                    int near set_vesamode( short ):
 1258  68 2c 00 00 00                    push    0000002cH
 125d  e8 00 00 00 00                    call    __CHK
 1262  53                                push    ebx
 1263  51                                push    ecx
 1264  52                                push    edx
 1265  83 ec 1c                          sub     esp,0000001cH
 1268  89 c1                             mov     ecx,eax
 126a  66 c7 04 24 02 4f                 mov     word ptr [esp],4f02H
 1270  66 89 44 24 04                    mov     +4H[esp],ax
 1275  89 e3                             mov     ebx,esp
 1277  89 e2                             mov     edx,esp
 1279  b8 10 00 00 00                    mov     eax,00000010H
 127e  e8 00 00 00 00                    call    int386_
 1283  31 c0                             xor     eax,eax
 1285  8a 04 24                          mov     al,[esp]
 1288  83 f8 4f                          cmp     eax,0000004fH
 128b  75 0a                             jne     L100
 128d  31 c0                             xor     eax,eax
 128f  8a 44 24 01                       mov     al,+1H[esp]
 1293  85 c0                             test    eax,eax
 1295  74 07                             je      L101
 1297  b8 ff ff ff ff    L100            mov     eax,0ffffffffH
 129c  eb 55                             jmp     L108
 129e  31 d2             L101            xor     edx,edx
 12a0  66 89 ca                          mov     dx,cx
 12a3  b8 00 00 00 00                    mov     eax,offset __3a58ujVESAINFO near _vi
 12a8  e8 00 00 00 00                    call    int near get_vesainfo( __3a58ujVESAINFO near *, short unsigned )
 12ad  83 f8 ff                          cmp     eax,0ffffffffH
 12b0  75 26                             jne     L106
 12b2  eb 3f                             jmp     L108
 12b4  c6 05 1a 00 00 00 
       04                L102            mov     byte ptr __3a58ujVESAINFO near _vi+1aH,04H
 12bb  eb 34                             jmp     L107
 12bd  c6 05 1a 00 00 00 
       05                L103            mov     byte ptr __3a58ujVESAINFO near _vi+1aH,05H
 12c4  eb 2b                             jmp     L107
 12c6  c6 05 1a 00 00 00 
       07                L104            mov     byte ptr __3a58ujVESAINFO near _vi+1aH,07H
 12cd  eb 22                             jmp     L107
 12cf  c6 05 1a 00 00 00 
       0c                L105            mov     byte ptr __3a58ujVESAINFO near _vi+1aH,0cH
 12d6  eb 19                             jmp     L107
 12d8  81 e9 00 01 00 00 L106            sub     ecx,00000100H
 12de  66 83 f9 05                       cmp     cx,0005H
 12e2  77 0d                             ja      L107
 12e4  31 c0                             xor     eax,eax
 12e6  66 89 c8                          mov     ax,cx
 12e9  2e ff 24 85 40 12 
       00 00                             jmp     dword ptr cs:L99[eax*4]
 12f1  31 c0             L107            xor     eax,eax
 12f3  83 c4 1c          L108            add     esp,0000001cH
 12f6  5a                                pop     edx
 12f7  59                                pop     ecx
 12f8  5b                                pop     ebx
 12f9  c3                                ret     
 12fa                    void near * near real_malloc( int unsigned near *, short unsigned ):
 12fa  68 28 00 00 00                    push    00000028H
 12ff  e8 00 00 00 00                    call    __CHK
 1304  53                                push    ebx
 1305  51                                push    ecx
 1306  83 ec 1c                          sub     esp,0000001cH
 1309  89 c1                             mov     ecx,eax
 130b  66 c7 04 24 00 01                 mov     word ptr [esp],0100H
 1311  31 c0                             xor     eax,eax
 1313  66 89 d0                          mov     ax,dx
 1316  83 c0 0f                          add     eax,0000000fH
 1319  c1 f8 04                          sar     eax,04H
 131c  66 89 44 24 04                    mov     +4H[esp],ax
 1321  89 e3                             mov     ebx,esp
 1323  89 e2                             mov     edx,esp
 1325  b8 31 00 00 00                    mov     eax,00000031H
 132a  e8 00 00 00 00                    call    int386_
 132f  83 7c 24 18 00                    cmp     dword ptr +18H[esp],00000000H
 1334  74 04                             je      L109
 1336  31 c0                             xor     eax,eax
 1338  eb 11                             jmp     L110
 133a  8b 44 24 0c       L109            mov     eax,+0cH[esp]
 133e  89 01                             mov     [ecx],eax
 1340  8b 04 24                          mov     eax,[esp]
 1343  25 ff ff 00 00                    and     eax,0000ffffH
 1348  c1 e0 04                          shl     eax,04H
 134b  83 c4 1c          L110            add     esp,0000001cH
 134e  59                                pop     ecx
 134f  5b                                pop     ebx
 1350  c3                                ret     
 1351                    void near real_free( short unsigned ):
 1351  68 28 00 00 00                    push    00000028H
 1356  e8 00 00 00 00                    call    __CHK
 135b  53                                push    ebx
 135c  52                                push    edx
 135d  83 ec 1c                          sub     esp,0000001cH
 1360  c7 04 24 01 01 00 
       00                                mov     dword ptr [esp],00000101H
 1367  25 ff ff 00 00                    and     eax,0000ffffH
 136c  89 44 24 0c                       mov     +0cH[esp],eax
 1370  89 e3                             mov     ebx,esp
 1372  89 e2                             mov     edx,esp
 1374  b8 31 00 00 00                    mov     eax,00000031H
 1379  e8 00 00 00 00                    call    int386_
 137e  83 c4 1c                          add     esp,0000001cH
 1381  5a                                pop     edx
 1382  5b                                pop     ebx
 1383  c3                                ret     
 1384                    void near int_real( char unsigned, __1tfsc7RMI near * ):
 1384  68 34 00 00 00                    push    00000034H
 1389  e8 00 00 00 00                    call    __CHK
 138e  53                                push    ebx
 138f  51                                push    ecx
 1390  83 ec 28                          sub     esp,00000028H
 1393  89 d3                             mov     ebx,edx
 1395  c7 04 24 00 03 00 
       00                                mov     dword ptr [esp],00000300H
 139c  25 ff 00 00 00                    and     eax,000000ffH
 13a1  89 44 24 04                       mov     +4H[esp],eax
 13a5  31 d2                             xor     edx,edx
 13a7  66 89 54 24 08                    mov     +8H[esp],dx
 13ac  8c da                             mov     dx,ds
 13ae  89 d8                             mov     eax,ebx
 13b0  66 89 54 24 1c                    mov     +1cH[esp],dx
 13b5  89 5c 24 14                       mov     +14H[esp],ebx
 13b9  8d 4c 24 1c                       lea     ecx,+1cH[esp]
 13bd  89 e3                             mov     ebx,esp
 13bf  89 e2                             mov     edx,esp
 13c1  b8 31 00 00 00                    mov     eax,00000031H
 13c6  e8 00 00 00 00                    call    int386x_
 13cb  83 c4 28                          add     esp,00000028H
 13ce  59                                pop     ecx
 13cf  5b                                pop     ebx
 13d0  c3                                ret     
 13d1                    int near get_vesainfo( __3a58ujVESAINFO near *, short unsigned ):
 13d1  68 50 00 00 00                    push    00000050H
 13d6  e8 00 00 00 00                    call    __CHK
 13db  53                                push    ebx
 13dc  51                                push    ecx
 13dd  56                                push    esi
 13de  57                                push    edi
 13df  55                                push    ebp
 13e0  83 ec 38                          sub     esp,00000038H
 13e3  89 c5                             mov     ebp,eax
 13e5  89 d1                             mov     ecx,edx
 13e7  ba 00 04 00 00                    mov     edx,00000400H
 13ec  8d 44 24 34                       lea     eax,+34H[esp]
 13f0  e8 00 00 00 00                    call    void near * near real_malloc( int unsigned near *, short unsigned )
 13f5  89 c6                             mov     esi,eax
 13f7  85 c0                             test    eax,eax
 13f9  75 07                             jne     L111
 13fb  b8 ff ff ff ff                    mov     eax,0ffffffffH
 1400  eb 76                             jmp     L112
 1402  bb 32 00 00 00    L111            mov     ebx,00000032H
 1407  31 d2                             xor     edx,edx
 1409  89 e0                             mov     eax,esp
 140b  e8 00 00 00 00                    call    memset_
 1410  c7 44 24 1c 01 4f 
       00 00                             mov     dword ptr +1cH[esp],00004f01H
 1418  31 c0                             xor     eax,eax
 141a  66 89 c8                          mov     ax,cx
 141d  89 44 24 18                       mov     +18H[esp],eax
 1421  31 db                             xor     ebx,ebx
 1423  89 1c 24                          mov     [esp],ebx
 1426  89 f0                             mov     eax,esi
 1428  c1 e8 04                          shr     eax,04H
 142b  25 ff ff 00 00                    and     eax,0000ffffH
 1430  66 89 44 24 22                    mov     +22H[esp],ax
 1435  89 e2                             mov     edx,esp
 1437  b8 10 00 00 00                    mov     eax,00000010H
 143c  e8 00 00 00 00                    call    void near int_real( char unsigned, __1tfsc7RMI near * )
 1441  b9 1d 00 00 00                    mov     ecx,0000001dH
 1446  89 ef                             mov     edi,ebp
 1448  57                                push    edi
 1449  89 c8                             mov     eax,ecx
 144b  c1 e9 02                          shr     ecx,02H
 144e  f2 a5                             repne   movsd    
 1450  8a c8                             mov     cl,al
 1452  80 e1 03                          and     cl,03H
 1455  f2 a4                             repne   movsb    
 1457  5f                                pop     edi
 1458  31 c0                             xor     eax,eax
 145a  66 8b 44 24 34                    mov     ax,+34H[esp]
 145f  e8 00 00 00 00                    call    void near real_free( short unsigned )
 1464  66 8b 45 04                       mov     ax,+4H[ebp]
 1468  66 a3 00 00 00 00                 mov     short near win_granularity,ax
 146e  8a 45 02                          mov     al,+2H[ebp]
 1471  a2 00 00 00 00                    mov     char unsigned near win_A_attr,al
 1476  31 c0                             xor     eax,eax
 1478  83 c4 38          L112            add     esp,00000038H
 147b  e9 78 ec ff ff                    jmp     L7
 1480                    void near print_vesainfo( __3a58ujVESAINFO near * ):
 1480  68 1c 00 00 00                    push    0000001cH
 1485  e8 00 00 00 00                    call    __CHK
 148a  53                                push    ebx
 148b  52                                push    edx
 148c  89 c2                             mov     edx,eax
 148e  31 c0                             xor     eax,eax
 1490  8a 42 19                          mov     al,+19H[edx]
 1493  50                                push    eax
 1494  31 c0                             xor     eax,eax
 1496  66 8b 42 14                       mov     ax,+14H[edx]
 149a  50                                push    eax
 149b  31 c0                             xor     eax,eax
 149d  66 8b 42 12                       mov     ax,+12H[edx]
 14a1  50                                push    eax
 14a2  68 03 00 00 00                    push    offset L144
 14a7  e8 00 00 00 00                    call    printf_
 14ac  83 c4 10                          add     esp,00000010H
 14af  31 c0                             xor     eax,eax
 14b1  66 8b 42 06                       mov     ax,+6H[edx]
 14b5  50                                push    eax
 14b6  68 26 00 00 00                    push    offset L145
 14bb  e8 00 00 00 00                    call    printf_
 14c0  83 c4 08                          add     esp,00000008H
 14c3  31 c0                             xor     eax,eax
 14c5  66 8b 42 0a                       mov     ax,+0aH[edx]
 14c9  50                                push    eax
 14ca  31 c0                             xor     eax,eax
 14cc  66 8b 42 08                       mov     ax,+8H[edx]
 14d0  50                                push    eax
 14d1  68 3f 00 00 00                    push    offset L146
 14d6  e8 00 00 00 00                    call    printf_
 14db  83 c4 0c                          add     esp,0000000cH
 14de  31 c0                             xor     eax,eax
 14e0  66 8b 42 04                       mov     ax,+4H[edx]
 14e4  50                                push    eax
 14e5  68 61 00 00 00                    push    offset L147
 14ea  e8 00 00 00 00                    call    printf_
 14ef  83 c4 08                          add     esp,00000008H
 14f2  31 c0                             xor     eax,eax
 14f4  8a 42 03                          mov     al,+3H[edx]
 14f7  50                                push    eax
 14f8  31 c0                             xor     eax,eax
 14fa  8a 42 02                          mov     al,+2H[edx]
 14fd  50                                push    eax
 14fe  68 82 00 00 00                    push    offset L148
 1503  e8 00 00 00 00                    call    printf_
 1508  83 c4 0c                          add     esp,0000000cH
 150b  8b 5a 0c                          mov     ebx,+0cH[edx]
 150e  53                                push    ebx
 150f  68 a6 00 00 00                    push    offset L149
 1514  e8 00 00 00 00                    call    printf_
 1519  83 c4 08                          add     esp,00000008H
 151c  5a                                pop     edx
 151d  5b                                pop     ebx
 151e  c3                                ret     
 151f                    int near creat_so( int, int unsigned, int unsigned, char unsigned ):
 151f  68 0c 00 00 00                    push    0000000cH
 1524  e8 00 00 00 00                    call    __CHK
 1529  56                                push    esi
 152a  83 ec 04                          sub     esp,00000004H
 152d  89 c6                             mov     esi,eax
 152f  89 d0                             mov     eax,edx
 1531  88 0c 24                          mov     [esp],cl
 1534  83 fe 28                          cmp     esi,00000028H
 1537  7d 1e                             jge     L113
 1539  89 f1                             mov     ecx,esi
 153b  89 ca                             mov     edx,ecx
 153d  c1 e2 03                          shl     edx,03H
 1540  01 ca                             add     edx,ecx
 1542  c1 e2 02                          shl     edx,02H
 1545  01 ca                             add     edx,ecx
 1547  31 c9                             xor     ecx,ecx
 1549  8a 8a 00 00 00 00                 mov     cl,__22ij7SO near so_list[][edx]
 154f  81 f9 ff 00 00 00                 cmp     ecx,000000ffH
 1555  74 0a                             je      L114
 1557  b8 ff ff ff ff    L113            mov     eax,0ffffffffH
 155c  83 c4 04                          add     esp,00000004H
 155f  5e                                pop     esi
 1560  c3                                ret     
 1561  8a 0c 24          L114            mov     cl,[esp]
 1564  88 8a 00 00 00 00                 mov     __22ij7SO near so_list[][edx],cl
 156a  89 82 01 00 00 00                 mov     __22ij7SO near so_list[]+1H[edx],eax
 1570  89 9a 05 00 00 00                 mov     __22ij7SO near so_list[]+5H[edx],ebx
 1576  31 c9                             xor     ecx,ecx
 1578  89 8a 09 00 00 00                 mov     __22ij7SO near so_list[]+9H[edx],ecx
 157e  89 8a 0d 00 00 00                 mov     __22ij7SO near so_list[]+0dH[edx],ecx
 1584  89 82 11 00 00 00                 mov     __22ij7SO near so_list[]+11H[edx],eax
 158a  89 9a 15 00 00 00                 mov     __22ij7SO near so_list[]+15H[edx],ebx
 1590  89 8a 19 00 00 00                 mov     __22ij7SO near so_list[]+19H[edx],ecx
 1596  89 8a 1d 00 00 00                 mov     __22ij7SO near so_list[]+1dH[edx],ecx
 159c  0f af d8                          imul    ebx,eax
 159f  89 d8                             mov     eax,ebx
 15a1  e8 00 00 00 00                    call    malloc_
 15a6  89 82 21 00 00 00                 mov     __22ij7SO near so_list[]+21H[edx],eax
 15ac  85 c0                             test    eax,eax
 15ae  74 a7                             je      L113
 15b0  31 d2                             xor     edx,edx
 15b2  e8 00 00 00 00                    call    memset_
 15b7  31 c0                             xor     eax,eax
 15b9  83 c4 04                          add     esp,00000004H
 15bc  5e                                pop     esi
 15bd  c3                                ret     
 15be                    int near delete_so( int ):
 15be  68 0c 00 00 00                    push    0000000cH
 15c3  e8 00 00 00 00                    call    __CHK
 15c8  53                                push    ebx
 15c9  52                                push    edx
 15ca  83 f8 28                          cmp     eax,00000028H
 15cd  7c 08                             jl      L115
 15cf  b8 ff ff ff ff                    mov     eax,0ffffffffH
 15d4  5a                                pop     edx
 15d5  5b                                pop     ebx
 15d6  c3                                ret     
 15d7  89 c2             L115            mov     edx,eax
 15d9  c1 e2 03                          shl     edx,03H
 15dc  01 c2                             add     edx,eax
 15de  c1 e2 02                          shl     edx,02H
 15e1  01 c2                             add     edx,eax
 15e3  30 e4                             xor     ah,ah
 15e5  88 a2 00 00 00 00                 mov     __22ij7SO near so_list[][edx],ah
 15eb  31 db                             xor     ebx,ebx
 15ed  89 9a 01 00 00 00                 mov     __22ij7SO near so_list[]+1H[edx],ebx
 15f3  89 9a 05 00 00 00                 mov     __22ij7SO near so_list[]+5H[edx],ebx
 15f9  89 9a 09 00 00 00                 mov     __22ij7SO near so_list[]+9H[edx],ebx
 15ff  89 9a 0d 00 00 00                 mov     __22ij7SO near so_list[]+0dH[edx],ebx
 1605  89 9a 11 00 00 00                 mov     __22ij7SO near so_list[]+11H[edx],ebx
 160b  89 9a 15 00 00 00                 mov     __22ij7SO near so_list[]+15H[edx],ebx
 1611  89 9a 19 00 00 00                 mov     __22ij7SO near so_list[]+19H[edx],ebx
 1617  89 9a 1d 00 00 00                 mov     __22ij7SO near so_list[]+1dH[edx],ebx
 161d  8b 82 21 00 00 00                 mov     eax,__22ij7SO near so_list[]+21H[edx]
 1623  e8 00 00 00 00                    call    free_
 1628  89 9a 21 00 00 00                 mov     __22ij7SO near so_list[]+21H[edx],ebx
 162e  c6 82 00 00 00 00 
       ff                                mov     byte ptr __22ij7SO near so_list[][edx],0ffH
 1635  31 c0                             xor     eax,eax
 1637  5a                                pop     edx
 1638  5b                                pop     ebx
 1639  c3                                ret     
 163a                    int near set_page( short ):
 163a  68 2c 00 00 00                    push    0000002cH
 163f  e8 00 00 00 00                    call    __CHK
 1644  53                                push    ebx
 1645  51                                push    ecx
 1646  52                                push    edx
 1647  83 ec 1c                          sub     esp,0000001cH
 164a  89 c1                             mov     ecx,eax
 164c  31 d2                             xor     edx,edx
 164e  66 8b 15 00 00 00 
       00                                mov     dx,short unsigned near int near set_page( short )::.0::cbn
 1655  98                                cwde    
 1656  39 c2                             cmp     edx,eax
 1658  75 0a                             jne     L116
 165a  b8 01 00 00 00                    mov     eax,00000001H
 165f  e9 8f fc ff ff                    jmp     L108
 1664  66 c7 04 24 05 4f L116            mov     word ptr [esp],4f05H
 166a  31 db                             xor     ebx,ebx
 166c  66 89 5c 24 04                    mov     +4H[esp],bx
 1671  66 89 4c 24 0c                    mov     +0cH[esp],cx
 1676  89 e3                             mov     ebx,esp
 1678  89 e2                             mov     edx,esp
 167a  b8 10 00 00 00                    mov     eax,00000010H
 167f  e8 00 00 00 00                    call    int386_
 1684  31 c0                             xor     eax,eax
 1686  8a 04 24                          mov     al,[esp]
 1689  83 f8 4f                          cmp     eax,0000004fH
 168c  0f 85 05 fc ff ff                 jne     L100
 1692  31 c0                             xor     eax,eax
 1694  8a 44 24 01                       mov     al,+1H[esp]
 1698  85 c0                             test    eax,eax
 169a  0f 85 f7 fb ff ff                 jne     L100
 16a0  66 89 0d 00 00 00 
       00                                mov     short unsigned near int near set_page( short )::.0::cbn,cx
 16a7  e9 47 fc ff ff                    jmp     L108
 16ac                    void near init( int ):
 16ac  68 0c 00 00 00                    push    0000000cH
 16b1  e8 00 00 00 00                    call    __CHK
 16b6  53                                push    ebx
 16b7  52                                push    edx
 16b8  83 f8 13                          cmp     eax,00000013H
 16bb  75 08                             jne     L117
 16bd  98                                cwde    
 16be  e8 00 00 00 00                    call    void near set_videomode( short )
 16c3  eb 06                             jmp     L118
 16c5  98                L117            cwde    
 16c6  e8 00 00 00 00                    call    int near set_vesamode( short )
 16cb  31 c0             L118            xor     eax,eax
 16cd  b2 ff                             mov     dl,0ffH
 16cf  88 90 00 00 00 00 L119            mov     __22ij7SO near so_list[][eax],dl
 16d5  83 c0 25                          add     eax,00000025H
 16d8  3d c8 05 00 00                    cmp     eax,000005c8H
 16dd  75 f0                             jne     L119
 16df  31 db                             xor     ebx,ebx
 16e1  66 8b 1d 14 00 00 
       00                                mov     bx,__3a58ujVESAINFO near _vi+14H
 16e8  31 d2                             xor     edx,edx
 16ea  66 8b 15 12 00 00 
       00                                mov     dx,__3a58ujVESAINFO near _vi+12H
 16f1  31 c0                             xor     eax,eax
 16f3  e8 00 00 00 00                    call    void near set_buffer( int, int, int )
 16f8  30 f6                             xor     dh,dh
 16fa  88 35 00 00 00 00                 mov     char unsigned near trans_color,dh
 1700  88 35 00 00 00 00                 mov     char unsigned near active_so,dh
 1706  88 35 00 00 00 00                 mov     char unsigned near logic_flag,dh
 170c  5a                                pop     edx
 170d  5b                                pop     ebx
 170e  c3                                ret     
 170f                    void near ending():
 170f  68 04 00 00 00                    push    00000004H
 1714  e8 00 00 00 00                    call    __CHK
 1719  31 c0                             xor     eax,eax
 171b  a0 00 00 00 00                    mov     al,char unsigned near buffer_so
 1720  e8 00 00 00 00                    call    int near delete_so( int )
 1725  b8 03 00 00 00                    mov     eax,00000003H
 172a                    void near set_videomode( short ):
 172a  68 30 00 00 00                    push    00000030H
 172f  e8 00 00 00 00                    call    __CHK
 1734  53                                push    ebx
 1735  51                                push    ecx
 1736  52                                push    edx
 1737  57                                push    edi
 1738  83 ec 1c                          sub     esp,0000001cH
 173b  66 89 04 24                       mov     [esp],ax
 173f  89 e3                             mov     ebx,esp
 1741  89 e2                             mov     edx,esp
 1743  b8 10 00 00 00                    mov     eax,00000010H
 1748  e8 00 00 00 00                    call    int386_
 174d  66 c7 05 12 00 00 
       00 40 01                          mov     word ptr __3a58ujVESAINFO near _vi+12H,0140H
 1756  66 c7 05 14 00 00 
       00 c8 00                          mov     word ptr __3a58ujVESAINFO near _vi+14H,00c8H
 175f  b9 40 00 00 00                    mov     ecx,00000040H
 1764  66 89 0d 06 00 00 
       00                                mov     __3a58ujVESAINFO near _vi+6H,cx
 176b  66 89 0d 04 00 00 
       00                                mov     __3a58ujVESAINFO near _vi+4H,cx
 1772  bf 00 a0 00 00                    mov     edi,0000a000H
 1777  66 89 3d 08 00 00 
       00                                mov     __3a58ujVESAINFO near _vi+8H,di
 177e  66 89 3d 0a 00 00 
       00                                mov     __3a58ujVESAINFO near _vi+0aH,di
 1785  c6 05 1a 00 00 00 
       01                                mov     byte ptr __3a58ujVESAINFO near _vi+1aH,01H
 178c  c6 05 1c 00 00 00 
       40                                mov     byte ptr __3a58ujVESAINFO near _vi+1cH,40H
 1793  83 c4 1c                          add     esp,0000001cH
 1796  5f                                pop     edi
 1797  5a                                pop     edx
 1798  59                                pop     ecx
 1799  5b                                pop     ebx
 179a  c3                                ret     
 179b  68 70 03 00 00    main_           push    00000370H
 17a0  e8 00 00 00 00                    call    __CHK
 17a5  53                                push    ebx
 17a6  51                                push    ecx
 17a7  52                                push    edx
 17a8  56                                push    esi
 17a9  57                                push    edi
 17aa  55                                push    ebp
 17ab  81 ec 50 03 00 00                 sub     esp,00000350H
 17b1  31 f6                             xor     esi,esi
 17b3  c7 84 24 0c 03 00 
       00 cd cc cc 3d                    mov     dword ptr +30cH[esp],3dcccccdH
 17be  89 b4 24 38 03 00 
       00                                mov     +338H[esp],esi
 17c5  31 c9                             xor     ecx,ecx
 17c7  89 b4 24 34 03 00 
       00                                mov     +334H[esp],esi
 17ce  89 b4 24 14 03 00 
       00                                mov     +314H[esp],esi
 17d5  30 e4                             xor     ah,ah
 17d7  88 a4 24 44 03 00 
       00                                mov     +344H[esp],ah
 17de  68 ce 00 00 00                    push    offset L150
 17e3  e8 00 00 00 00                    call    printf_
 17e8  83 c4 04                          add     esp,00000004H
 17eb  89 fa                             mov     edx,edi
 17ed  b8 00 00 00 00                    mov     eax,offset istream near cin
 17f2  e8 00 00 00 00                    call    istream near & near istream::operator >>( char near * )
 17f7  68 e2 00 00 00                    push    offset L151
 17fc  e8 00 00 00 00                    call    printf_
 1801  83 c4 04                          add     esp,00000004H
 1804  8d 94 24 10 03 00 
       00                                lea     edx,+310H[esp]
 180b  b8 00 00 00 00                    mov     eax,offset istream near cin
 1810  e8 00 00 00 00                    call    istream near & near istream::operator >>( int near & )
 1815  68 fa 00 00 00                    push    offset L152
 181a  e8 00 00 00 00                    call    printf_
 181f  83 c4 04                          add     esp,00000004H
 1822  8d 94 24 00 03 00 
       00                                lea     edx,+300H[esp]
 1829  b8 00 00 00 00                    mov     eax,offset istream near cin
 182e  e8 00 00 00 00                    call    istream near & near istream::operator >>( int near & )
 1833  68 13 01 00 00                    push    offset L153
 1838  e8 00 00 00 00                    call    printf_
 183d  83 c4 04                          add     esp,00000004H
 1840  8b 94 24 28 03 00 
       00                                mov     edx,+328H[esp]
 1847  b8 00 00 00 00                    mov     eax,offset istream near cin
 184c  e8 00 00 00 00                    call    istream near & near istream::operator >>( char near * )
 1851  68 2f 01 00 00                    push    offset L154
 1856  e8 00 00 00 00                    call    printf_
 185b  83 c4 04                          add     esp,00000004H
 185e  68 71 01 00 00                    push    offset L155
 1863  e8 00 00 00 00                    call    printf_
 1868  83 c4 04                          add     esp,00000004H
 186b  8d 94 24 14 03 00 
       00                                lea     edx,+314H[esp]
 1872  b8 00 00 00 00                    mov     eax,offset istream near cin
 1877  e8 00 00 00 00                    call    istream near & near istream::operator >>( int near & )
 187c  e8 00 00 00 00                    call    void near init_key()
 1881  b8 13 00 00 00                    mov     eax,00000013H
 1886  e8 00 00 00 00                    call    void near init( int )
 188b  bb c8 00 00 00                    mov     ebx,000000c8H
 1890  ba 40 01 00 00                    mov     edx,00000140H
 1895  b8 01 00 00 00                    mov     eax,00000001H
 189a  e8 00 00 00 00                    call    int near creat_so( int, int unsigned, int unsigned, char unsigned )
 189f  30 d2                             xor     dl,dl
 18a1  88 15 00 00 00 00                 mov     char unsigned near active_so,dl
 18a7  31 db                             xor     ebx,ebx
 18a9  31 d2                             xor     edx,edx
 18ab  31 c0                             xor     eax,eax
 18ad  e8 00 00 00 00                    call    void near set_display( int, int, int )
 18b2  c6 05 00 00 00 00 
       01                                mov     byte ptr char unsigned near logic_flag,01H
 18b9  89 fa                             mov     edx,edi
 18bb  b8 01 00 00 00                    mov     eax,00000001H
 18c0  e8 00 00 00 00                    call    void near pcx_read( int, char near * )
 18c5  b8 01 00 00 00                    mov     eax,00000001H
 18ca  e8 00 00 00 00                    call    int near view_so( int )
 18cf  e8 00 00 00 00                    call    void near view()
 18d4  31 c0                             xor     eax,eax
 18d6  e8 00 00 00 00                    call    int near view_so( int )
 18db  30 db                             xor     bl,bl
 18dd  88 1d 00 00 00 00                 mov     char unsigned near active_so,bl
 18e3  bd 00 00 47 43                    mov     ebp,43470000H
 18e8  bf 00 80 9f 43                    mov     edi,439f8000H
 18ed  80 3d 1d 00 00 00 
       00                L120            cmp     byte ptr char unsigned near scan[]+1dH,00H
 18f4  74 0b                             je      L121
 18f6  c7 84 24 0c 03 00 
       00 00 00 80 3f                    mov     dword ptr +30cH[esp],3f800000H
 1901  80 3d 1d 00 00 00 
       00                L121            cmp     byte ptr char unsigned near scan[]+1dH,00H
 1908  75 0b                             jne     L122
 190a  c7 84 24 0c 03 00 
       00 cd cc cc 3d                    mov     dword ptr +30cH[esp],3dcccccdH
 1915  80 3d 4b 00 00 00 
       00                L122            cmp     byte ptr char unsigned near scan[]+4bH,00H
 191c  74 15                             je      L123
 191e  d9 84 24 38 03 00 
       00                                fld     dword ptr +338H[esp]
 1925  d8 a4 24 0c 03 00 
       00                                fsub    dword ptr +30cH[esp]
 192c  d9 9c 24 38 03 00 
       00                                fstp    dword ptr +338H[esp]
 1933  80 3d 4d 00 00 00 
       00                L123            cmp     byte ptr char unsigned near scan[]+4dH,00H
 193a  74 15                             je      L124
 193c  d9 84 24 38 03 00 
       00                                fld     dword ptr +338H[esp]
 1943  d8 84 24 0c 03 00 
       00                                fadd    dword ptr +30cH[esp]
 194a  d9 9c 24 38 03 00 
       00                                fstp    dword ptr +338H[esp]
 1951  80 3d 48 00 00 00 
       00                L124            cmp     byte ptr char unsigned near scan[]+48H,00H
 1958  74 15                             je      L125
 195a  d9 84 24 34 03 00 
       00                                fld     dword ptr +334H[esp]
 1961  d8 a4 24 0c 03 00 
       00                                fsub    dword ptr +30cH[esp]
 1968  d9 9c 24 34 03 00 
       00                                fstp    dword ptr +334H[esp]
 196f  80 3d 50 00 00 00 
       00                L125            cmp     byte ptr char unsigned near scan[]+50H,00H
 1976  74 15                             je      L126
 1978  d9 84 24 34 03 00 
       00                                fld     dword ptr +334H[esp]
 197f  d8 84 24 0c 03 00 
       00                                fadd    dword ptr +30cH[esp]
 1986  d9 9c 24 34 03 00 
       00                                fstp    dword ptr +334H[esp]
 198d  80 3d 01 00 00 00 
       00                L126            cmp     byte ptr char unsigned near scan[]+1H,00H
 1994  74 0a                             je      L127
 1996  b8 01 00 00 00                    mov     eax,00000001H
 199b  e9 18 01 00 00                    jmp     L133
 19a0  80 3d 39 00 00 00 
       00                L127            cmp     byte ptr char unsigned near scan[]+39H,00H
 19a7  74 07                             je      L128
 19a9  31 c0                             xor     eax,eax
 19ab  e9 08 01 00 00                    jmp     L133
 19b0  d9 84 24 38 03 00 
       00                L128            fld     dword ptr +338H[esp]
 19b7  d9 ee                             fldz    
 19b9  de d9                             fcompp  st(1)
 19bb  df e0                             fstsw   ax
 19bd  9e                                sahf    
 19be  76 09                             jbe     L129
 19c0  31 db                             xor     ebx,ebx
 19c2  89 9c 24 38 03 00 
       00                                mov     +338H[esp],ebx
 19c9  d9 84 24 34 03 00 
       00                L129            fld     dword ptr +334H[esp]
 19d0  d9 ee                             fldz    
 19d2  de d9                             fcompp  st(1)
 19d4  df e0                             fstsw   ax
 19d6  9e                                sahf    
 19d7  76 09                             jbe     L130
 19d9  31 c9                             xor     ecx,ecx
 19db  89 8c 24 34 03 00 
       00                                mov     +334H[esp],ecx
 19e2  d9 84 24 38 03 00 
       00                L130            fld     dword ptr +338H[esp]
 19e9  dc 1d 90 01 00 00                 fcomp   qword ptr L158
 19ef  df e0                             fstsw   ax
 19f1  9e                                sahf    
 19f2  76 07                             jbe     L131
 19f4  89 bc 24 38 03 00 
       00                                mov     +338H[esp],edi
 19fb  d9 84 24 34 03 00 
       00                L131            fld     dword ptr +334H[esp]
 1a02  dc 1d 98 01 00 00                 fcomp   qword ptr L159
 1a08  df e0                             fstsw   ax
 1a0a  9e                                sahf    
 1a0b  76 07                             jbe     L132
 1a0d  89 ac 24 34 03 00 
       00                                mov     +334H[esp],ebp
 1a14  b8 01 00 00 00    L132            mov     eax,00000001H
 1a19  e8 00 00 00 00                    call    int near view_so( int )
 1a1e  6a 0f                             push    0000000fH
 1a20  db 84 24 04 03 00 
       00                                fild    dword ptr +304H[esp]
 1a27  d8 84 24 38 03 00 
       00                                fadd    dword ptr +338H[esp]
 1a2e  dc 05 a0 01 00 00                 fadd    qword ptr L160
 1a34  e8 00 00 00 00                    call    __CHP
 1a39  db 9c 24 1c 03 00 
       00                                fistp   dword ptr +31cH[esp]
 1a40  db 84 24 14 03 00 
       00                                fild    dword ptr +314H[esp]
 1a47  d8 84 24 3c 03 00 
       00                                fadd    dword ptr +33cH[esp]
 1a4e  dc 05 a0 01 00 00                 fadd    qword ptr L160
 1a54  e8 00 00 00 00                    call    __CHP
 1a59  db 9c 24 20 03 00 
       00                                fistp   dword ptr +320H[esp]
 1a60  d9 84 24 38 03 00 
       00                                fld     dword ptr +338H[esp]
 1a67  e8 00 00 00 00                    call    __CHP
 1a6c  db 9c 24 28 03 00 
       00                                fistp   dword ptr +328H[esp]
 1a73  d9 84 24 3c 03 00 
       00                                fld     dword ptr +33cH[esp]
 1a7a  e8 00 00 00 00                    call    __CHP
 1a7f  db 9c 24 24 03 00 
       00                                fistp   dword ptr +324H[esp]
 1a86  8b 8c 24 1c 03 00 
       00                                mov     ecx,+31cH[esp]
 1a8d  8b 9c 24 20 03 00 
       00                                mov     ebx,+320H[esp]
 1a94  8b 94 24 28 03 00 
       00                                mov     edx,+328H[esp]
 1a9b  8b 84 24 24 03 00 
       00                                mov     eax,+324H[esp]
 1aa2  e8 00 00 00 00                    call    void near box( int, int, int, int, char unsigned )
 1aa7  31 c0                             xor     eax,eax
 1aa9  e8 00 00 00 00                    call    int near view_so( int )
 1aae  e8 00 00 00 00                    call    void near view()
 1ab3  e9 35 fe ff ff                    jmp     L120
 1ab8  85 c0             L133            test    eax,eax
 1aba  0f 85 86 02 00 00                 jne     L142
 1ac0  bb 00 03 00 00                    mov     ebx,00000300H
 1ac5  ba ff 00 00 00                    mov     edx,000000ffH
 1aca  89 e0                             mov     eax,esp
 1acc  e8 00 00 00 00                    call    memset_
 1ad1  8b 84 24 10 03 00 
       00                                mov     eax,+310H[esp]
 1ad8  0f af 84 24 00 03 
       00 00                             imul    eax,+300H[esp]
 1ae0  e8 00 00 00 00                    call    malloc_
 1ae5  89 c7                             mov     edi,eax
 1ae7  89 84 24 2c 03 00 
       00                                mov     +32cH[esp],eax
 1aee  d9 84 24 34 03 00 
       00                                fld     dword ptr +334H[esp]
 1af5  e8 00 00 00 00                    call    __CHP
 1afa  db 9c 24 20 03 00 
       00                                fistp   dword ptr +320H[esp]
 1b01  8b 94 24 20 03 00 
       00                                mov     edx,+320H[esp]
 1b08  89 d0                             mov     eax,edx
 1b0a  c1 e0 02                          shl     eax,02H
 1b0d  01 d0                             add     eax,edx
 1b0f  c1 e0 06                          shl     eax,06H
 1b12  d9 84 24 38 03 00 
       00                                fld     dword ptr +338H[esp]
 1b19  e8 00 00 00 00                    call    __CHP
 1b1e  db 9c 24 24 03 00 
       00                                fistp   dword ptr +324H[esp]
 1b25  03 84 24 24 03 00 
       00                                add     eax,+324H[esp]
 1b2c  8b 15 46 00 00 00                 mov     edx,__22ij7SO near so_list[]+46H
 1b32  01 c2                             add     edx,eax
 1b34  89 94 24 30 03 00 
       00                                mov     +330H[esp],edx
 1b3b  89 d5                             mov     ebp,edx
 1b3d  8b 84 24 20 03 00 
       00                                mov     eax,+320H[esp]
 1b44  89 84 24 04 03 00 
       00                                mov     +304H[esp],eax
 1b4b  89 c2                             mov     edx,eax
 1b4d  c1 e0 02                          shl     eax,02H
 1b50  01 d0                             add     eax,edx
 1b52  c1 e0 06                          shl     eax,06H
 1b55  89 84 24 08 03 00 
       00                                mov     +308H[esp],eax
 1b5c  eb 20                             jmp     L135
 1b5e  8b ac 24 08 03 00 
       00                L134            mov     ebp,+308H[esp]
 1b65  03 ac 24 30 03 00 
       00                                add     ebp,+330H[esp]
 1b6c  81 84 24 08 03 00 
       00 40 01 00 00                    add     dword ptr +308H[esp],00000140H
 1b77  ff 84 24 04 03 00 
       00                                inc     dword ptr +304H[esp]
 1b7e  d9 84 24 34 03 00 
       00                L135            fld     dword ptr +334H[esp]
 1b85  e8 00 00 00 00                    call    __CHP
 1b8a  db 9c 24 24 03 00 
       00                                fistp   dword ptr +324H[esp]
 1b91  8b 84 24 24 03 00 
       00                                mov     eax,+324H[esp]
 1b98  03 84 24 00 03 00 
       00                                add     eax,+300H[esp]
 1b9f  3b 84 24 04 03 00 
       00                                cmp     eax,+304H[esp]
 1ba6  0f 8e f8 00 00 00                 jle     L141
 1bac  d9 84 24 38 03 00 
       00                                fld     dword ptr +338H[esp]
 1bb3  e8 00 00 00 00                    call    __CHP
 1bb8  db 9c 24 3c 03 00 
       00                                fistp   dword ptr +33cH[esp]
 1bbf  e9 75 00 00 00                    jmp     L140
 1bc4  31 f6             L136            xor     esi,esi
 1bc6  83 c2 03                          add     edx,00000003H
 1bc9  43                                inc     ebx
 1bca  81 fa 00 03 00 00 L137            cmp     edx,00000300H
 1bd0  7d 1a                             jge     L138
 1bd2  3a 0c 14                          cmp     cl,[esp+edx]
 1bd5  75 ed                             jne     L136
 1bd7  3a 6c 14 01                       cmp     ch,+1H[esp+edx]
 1bdb  75 e7                             jne     L136
 1bdd  3a 64 14 02                       cmp     ah,+2H[esp+edx]
 1be1  75 e1                             jne     L136
 1be3  88 1f                             mov     [edi],bl
 1be5  be 01 00 00 00                    mov     esi,00000001H
 1bea  01 f7                             add     edi,esi
 1bec  85 f6             L138            test    esi,esi
 1bee  75 41                             jne     L139
 1bf0  31 d2                             xor     edx,edx
 1bf2  8a 94 24 44 03 00 
       00                                mov     dl,+344H[esp]
 1bf9  8d 14 52                          lea     edx,[edx+edx*2]
 1bfc  8a 84 24 48 03 00 
       00                                mov     al,+348H[esp]
 1c03  88 04 14                          mov     [esp+edx],al
 1c06  8a 84 24 4c 03 00 
       00                                mov     al,+34cH[esp]
 1c0d  88 44 14 01                       mov     +1H[esp+edx],al
 1c11  8a 84 24 40 03 00 
       00                                mov     al,+340H[esp]
 1c18  88 44 14 02                       mov     +2H[esp+edx],al
 1c1c  8a 84 24 44 03 00 
       00                                mov     al,+344H[esp]
 1c23  88 07                             mov     [edi],al
 1c25  47                                inc     edi
 1c26  88 c2                             mov     dl,al
 1c28  fe c2                             inc     dl
 1c2a  88 94 24 44 03 00 
       00                                mov     +344H[esp],dl
 1c31  45                L139            inc     ebp
 1c32  ff 84 24 3c 03 00 
       00                                inc     dword ptr +33cH[esp]
 1c39  d9 84 24 38 03 00 
       00                L140            fld     dword ptr +338H[esp]
 1c40  e8 00 00 00 00                    call    __CHP
 1c45  db 9c 24 24 03 00 
       00                                fistp   dword ptr +324H[esp]
 1c4c  8b 84 24 24 03 00 
       00                                mov     eax,+324H[esp]
 1c53  03 84 24 10 03 00 
       00                                add     eax,+310H[esp]
 1c5a  3b 84 24 3c 03 00 
       00                                cmp     eax,+33cH[esp]
 1c61  0f 8e f7 fe ff ff                 jle     L134
 1c67  31 c0                             xor     eax,eax
 1c69  8a 45 00                          mov     al,+0H[ebp]
 1c6c  8d 8c 24 40 03 00 
       00                                lea     ecx,+340H[esp]
 1c73  8d 9c 24 4c 03 00 
       00                                lea     ebx,+34cH[esp]
 1c7a  8d 94 24 48 03 00 
       00                                lea     edx,+348H[esp]
 1c81  e8 00 00 00 00                    call    void near get_pal( char unsigned, char unsigned near *, char unsigned near *, char unsigned near * )
 1c86  31 db                             xor     ebx,ebx
 1c88  31 d2                             xor     edx,edx
 1c8a  8a a4 24 40 03 00 
       00                                mov     ah,+340H[esp]
 1c91  8a ac 24 4c 03 00 
       00                                mov     ch,+34cH[esp]
 1c98  8a 8c 24 48 03 00 
       00                                mov     cl,+348H[esp]
 1c9f  e9 26 ff ff ff                    jmp     L137
 1ca4  ba 80 01 00 00    L141            mov     edx,offset L156
 1ca9  8b 84 24 28 03 00 
       00                                mov     eax,+328H[esp]
 1cb0  e8 00 00 00 00                    call    fopen_
 1cb5  89 c6                             mov     esi,eax
 1cb7  31 db                             xor     ebx,ebx
 1cb9  31 d2                             xor     edx,edx
 1cbb  e8 00 00 00 00                    call    fseek_
 1cc0  89 f2                             mov     edx,esi
 1cc2  8b 84 24 14 03 00 
       00                                mov     eax,+314H[esp]
 1cc9  e8 00 00 00 00                    call    fputc_
 1cce  89 f1                             mov     ecx,esi
 1cd0  bb 01 00 00 00                    mov     ebx,00000001H
 1cd5  ba 04 00 00 00                    mov     edx,00000004H
 1cda  8d 84 24 10 03 00 
       00                                lea     eax,+310H[esp]
 1ce1  e8 00 00 00 00                    call    fwrite_
 1ce6  89 f1                             mov     ecx,esi
 1ce8  bb 01 00 00 00                    mov     ebx,00000001H
 1ced  ba 04 00 00 00                    mov     edx,00000004H
 1cf2  8d 84 24 00 03 00 
       00                                lea     eax,+300H[esp]
 1cf9  e8 00 00 00 00                    call    fwrite_
 1cfe  8b 94 24 10 03 00 
       00                                mov     edx,+310H[esp]
 1d05  0f af 94 24 00 03 
       00 00                             imul    edx,+300H[esp]
 1d0d  89 f1                             mov     ecx,esi
 1d0f  bb 01 00 00 00                    mov     ebx,00000001H
 1d14  8b 84 24 2c 03 00 
       00                                mov     eax,+32cH[esp]
 1d1b  e8 00 00 00 00                    call    fwrite_
 1d20  89 f1                             mov     ecx,esi
 1d22  bb 01 00 00 00                    mov     ebx,00000001H
 1d27  ba 00 03 00 00                    mov     edx,00000300H
 1d2c  89 e0                             mov     eax,esp
 1d2e  e8 00 00 00 00                    call    fwrite_
 1d33  89 f0                             mov     eax,esi
 1d35  e8 00 00 00 00                    call    fclose_
 1d3a  8b 84 24 2c 03 00 
       00                                mov     eax,+32cH[esp]
 1d41  e8 00 00 00 00                    call    free_
 1d46  e8 00 00 00 00    L142            call    void near del_key()
 1d4b  b8 01 00 00 00                    mov     eax,00000001H
 1d50  e8 00 00 00 00                    call    int near delete_so( int )
 1d55  e8 00 00 00 00                    call    void near ending()
 1d5a  b8 00 00 00 00                    mov     eax,offset __3a58ujVESAINFO near _vi
 1d5f  e8 00 00 00 00                    call    void near print_vesainfo( __3a58ujVESAINFO near * )
 1d64  68 83 01 00 00                    push    offset L157
 1d69  e8 00 00 00 00                    call    printf_
 1d6e  83 c4 04                          add     esp,00000004H
 1d71  81 c4 50 03 00 00                 add     esp,00000350H
 1d77  e9 30 ed ff ff                    jmp     L66

No disassembly errors

------------------------------------------------------------

Segment: CONST  DWORD USE32  000001a8 bytes  
 0000  72 62 00                L143            - rb.
 0003  44 69 73 70 6c 61 79 20 L144            - Display 
 000b  53 69 7a 65 20 3a 20 25                 - Size : %
 0013  34 64 20 78 20 25 34 64                 - 4d x %4d
 001b  20 2c 20 25 64 42 69 74                 -  , %dBit
 0023  73 0a 00                                - s..
 0026  57 69 6e 64 6f 77 20 53 L145            - Window S
 002e  69 7a 65 20 3a 20 25 34                 - ize : %4
 0036  64 20 4b 62 79 74 65 0a                 - d Kbyte.
 003e  00                                      - .
 003f  57 69 6e 64 6f 77 20 41 L146            - Window A
 0047  2c 42 20 53 65 67 6d 65                 - ,B Segme
 004f  6e 74 20 3a 20 25 30 34                 - nt : %04
 0057  78 20 20 20 25 30 34 78                 - x   %04x
 005f  0a 00                                   - ..
 0061  57 69 6e 64 6f 77 20 47 L147            - Window G
 0069  72 61 6e 75 6c 61 72 69                 - ranulari
 0071  74 79 20 3a 20 25 34 64                 - ty : %4d
 0079  20 4b 62 79 74 65 20 0a                 -  Kbyte .
 0081  00                                      - .
 0082  57 69 6e 64 6f 77 20 41 L148            - Window A
 008a  2c 42 20 41 74 74 72 69                 - ,B Attri
 0092  62 75 74 65 20 3a 20 25                 - bute : %
 009a  30 34 78 20 20 20 25 30                 - 04x   %0
 00a2  34 78 0a 00                             - 4x..
 00a6  57 69 6e 64 6f 77 20 43 L149            - Window C
 00ae  6f 6e 74 72 6f 6c 20 46                 - ontrol F
 00b6  75 6e 63 74 69 6f 6e 20                 - unction 
 00be  50 6f 69 6e 74 65 72 20                 - Pointer 
 00c6  3a 20 25 30 38 78 0a 00                 - : %08x..
 00ce  0a 20 49 6e 70 75 74 20 L150            - . Input 
 00d6  46 69 6c 65 20 4e 61 6d                 - File Nam
 00de  65 20 3a 00                             - e :.
 00e2  0a 20 49 6e 70 75 74 20 L151            - . Input 
 00ea  54 69 6c 65 27 73 20 57                 - Tile's W
 00f2  69 64 74 68 20 3a 20 00                 - idth : .
 00fa  0a 20 49 6e 70 75 74 20 L152            - . Input 
 0102  54 69 6c 65 27 73 20 48                 - Tile's H
 010a  65 69 67 68 74 20 3a 20                 - eight : 
 0112  00                                      - .
 0113  0a 49 6e 70 75 74 20 66 L153            - .Input f
 011b  69 6c 65 20 6e 61 6d 65                 - ile name
 0123  20 28 2a 2e 64 61 74 29                 -  (*.dat)
 012b  20 3a 20 00                             -  : .
 012f  0a 49 6e 70 75 74 20 41 L154            - .Input A
 0137  74 74 72 69 62 75 74 65                 - ttribute
 013f  2e 2e 2e 28 30 2e 54 49                 - ...(0.TI
 0147  4c 45 20 31 2e 53 50 52                 - LE 1.SPR
 014f  49 54 45 20 32 2e 50 61                 - ITE 2.Pa
 0157  6c 2e 20 53 43 52 4f 4c                 - l. SCROL
 015f  4c 20 33 2e 50 41 4c 2e                 - L 3.PAL.
 0167  20 34 2e 55 4e 55 53 45                 -  4.UNUSE
 016f  44 00                                   - D.
 0171  0a 20 43 68 6f 6f 73 65 L155            - . Choose
 0179  2e 2e 2e 20 3a 20 00                    - ... : .
 0180  77 62 00                L156            - wb.
 0183  47 6f 6f 64 20 62 79 65 L157            - Good bye
 018b  2e 2e 2e 2e 00                          - .....
 0190  00 00 00 00 00 f0 73 40 L158            - ......s@
 0198  00 00 00 00 00 e0 68 40 L159            - ......h@
 01a0  00 00 00 00 00 00 f0 bf L160            - ........

No disassembly errors

------------------------------------------------------------

Segment: _BSS  DWORD USE32  00000834 bytes  

No disassembly errors

------------------------------------------------------------

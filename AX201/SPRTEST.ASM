
Module: C:\LANGUAGE\WC\BINB\SPRTEST.CPP
Group: 'DGROUP' CONST,CONST2,_DATA,_BSS

Segment: _TEXT  DWORD USE32  000001ba bytes  
 0000                    void near set_block_pal( char unsigned near *, char unsigned, int ):
 0000  68 10 00 00 00                    push    00000010H
 0005  e8 00 00 00 00                    call    __CHK
 000a  51                                push    ecx
 000b  56                                push    esi
 000c  57                                push    edi
 000d  89 c7                             mov     edi,eax
 000f  88 d0                             mov     al,dl
 0011  ba c8 03 00 00                    mov     edx,000003c8H
 0016  ee                                out     dx,al
 0017  31 c9                             xor     ecx,ecx
 0019  89 de                             mov     esi,ebx
 001b  c1 e6 02                          shl     esi,02H
 001e  29 de                             sub     esi,ebx
 0020  89 fb                             mov     ebx,edi
 0022  ba c9 03 00 00                    mov     edx,000003c9H
 0027  eb 05                             jmp     L2
 0029  8a 03             L1              mov     al,[ebx]
 002b  ee                                out     dx,al
 002c  43                                inc     ebx
 002d  41                                inc     ecx
 002e  39 f1             L2              cmp     ecx,esi
 0030  7c f7                             jl      L1
 0032  5f                                pop     edi
 0033  5e                                pop     esi
 0034  59                                pop     ecx
 0035  c3                                ret     
 0036                    void near set_videomode( short ):
 0036  68 28 00 00 00                    push    00000028H
 003b  e8 00 00 00 00                    call    __CHK
 0040  53                                push    ebx
 0041  52                                push    edx
 0042  83 ec 1c                          sub     esp,0000001cH
 0045  66 89 04 24                       mov     [esp],ax
 0049  89 e3                             mov     ebx,esp
 004b  89 e2                             mov     edx,esp
 004d  b8 10 00 00 00                    mov     eax,00000010H
 0052  e8 00 00 00 00                    call    int386_
 0057  83 c4 1c                          add     esp,0000001cH
 005a  5a                                pop     edx
 005b  5b                                pop     ebx
 005c  c3                                ret     
 005d  68 20 03 00 00    main_           push    00000320H
 0062  e8 00 00 00 00                    call    __CHK
 0067  53                                push    ebx
 0068  51                                push    ecx
 0069  52                                push    edx
 006a  56                                push    esi
 006b  57                                push    edi
 006c  81 ec 04 03 00 00                 sub     esp,00000304H
 0072  68 00 00 00 00                    push    offset L3
 0077  e8 00 00 00 00                    call    printf_
 007c  83 c4 04                          add     esp,00000004H
 007f  89 f2                             mov     edx,esi
 0081  b8 00 00 00 00                    mov     eax,offset istream near cin
 0086  e8 00 00 00 00                    call    istream near & near istream::operator >>( char near * )
 008b  68 1c 00 00 00                    push    offset L4
 0090  e8 00 00 00 00                    call    printf_
 0095  83 c4 04                          add     esp,00000004H
 0098  89 fa                             mov     edx,edi
 009a  b8 00 00 00 00                    mov     eax,offset istream near cin
 009f  e8 00 00 00 00                    call    istream near & near istream::operator >>( char near * )
 00a4  ba 3f 00 00 00                    mov     edx,offset L5
 00a9  89 f0                             mov     eax,esi
 00ab  e8 00 00 00 00                    call    fopen_
 00b0  89 c6                             mov     esi,eax
 00b2  31 db                             xor     ebx,ebx
 00b4  31 d2                             xor     edx,edx
 00b6  e8 00 00 00 00                    call    fseek_
 00bb  89 f1                             mov     ecx,esi
 00bd  bb 01 00 00 00                    mov     ebx,00000001H
 00c2  ba 00 03 00 00                    mov     edx,00000300H
 00c7  89 e0                             mov     eax,esp
 00c9  e8 00 00 00 00                    call    fread_
 00ce  89 f0                             mov     eax,esi
 00d0  e8 00 00 00 00                    call    fclose_
 00d5  ba 42 00 00 00                    mov     edx,offset L6
 00da  89 f8                             mov     eax,edi
 00dc  e8 00 00 00 00                    call    fopen_
 00e1  89 c6                             mov     esi,eax
 00e3  bb 02 00 00 00                    mov     ebx,00000002H
 00e8  ba fc ff ff ff                    mov     edx,0fffffffcH
 00ed  e8 00 00 00 00                    call    fseek_
 00f2  89 f1                             mov     ecx,esi
 00f4  bb 01 00 00 00                    mov     ebx,00000001H
 00f9  ba 04 00 00 00                    mov     edx,00000004H
 00fe  8d 84 24 00 03 00 
       00                                lea     eax,+300H[esp]
 0105  e8 00 00 00 00                    call    fread_
 010a  31 db                             xor     ebx,ebx
 010c  31 d2                             xor     edx,edx
 010e  89 f0                             mov     eax,esi
 0110  e8 00 00 00 00                    call    fseek_
 0115  8b 84 24 00 03 00 
       00                                mov     eax,+300H[esp]
 011c  e8 00 00 00 00                    call    malloc_
 0121  89 c7                             mov     edi,eax
 0123  89 f1                             mov     ecx,esi
 0125  bb 01 00 00 00                    mov     ebx,00000001H
 012a  8b 94 24 00 03 00 
       00                                mov     edx,+300H[esp]
 0131  e8 00 00 00 00                    call    fread_
 0136  89 f0                             mov     eax,esi
 0138  e8 00 00 00 00                    call    fclose_
 013d  89 3d 00 00 00 00                 mov     void (near * near sprite)(),edi
 0143  b8 13 00 00 00                    mov     eax,00000013H
 0148  e8 00 00 00 00                    call    void near set_videomode( short )
 014d  bb 00 01 00 00                    mov     ebx,00000100H
 0152  31 d2                             xor     edx,edx
 0154  89 e0                             mov     eax,esp
 0156  e8 00 00 00 00                    call    void near set_block_pal( char unsigned near *, char unsigned, int )
 015b  c7 05 00 00 00 00 
       64 7d 0a 00                       mov     dword ptr int unsigned near off,000a7d64H
 0165  53                                push    ebx
 0166  8b 1d 00 00 00 00                 mov     ebx,int unsigned near off
 016c  ff 15 00 00 00 00                 call    dword ptr void (near * near sprite)()
 0172  5b                                pop     ebx
 0173  c7 05 00 00 00 00 
       b2 3e 0a 00                       mov     dword ptr int unsigned near off,000a3eb2H
 017d  53                                push    ebx
 017e  8b 1d 00 00 00 00                 mov     ebx,int unsigned near off
 0184  ff 15 00 00 00 00                 call    dword ptr void (near * near sprite)()
 018a  5b                                pop     ebx
 018b  e8 00 00 00 00                    call    getch_
 0190  b8 03 00 00 00                    mov     eax,00000003H
 0195  e8 00 00 00 00                    call    void near set_videomode( short )
 019a  89 f8                             mov     eax,edi
 019c  e8 00 00 00 00                    call    free_
 01a1  68 45 00 00 00                    push    offset L7
 01a6  e8 00 00 00 00                    call    printf_
 01ab  83 c4 04                          add     esp,00000004H
 01ae  81 c4 04 03 00 00                 add     esp,00000304H
 01b4  5f                                pop     edi
 01b5  5e                                pop     esi
 01b6  5a                                pop     edx
 01b7  59                                pop     ecx
 01b8  5b                                pop     ebx
 01b9  c3                                ret     

No disassembly errors

------------------------------------------------------------

Segment: CONST  DWORD USE32  00000052 bytes  
 0000  0a 49 6e 70 75 74 20 50 L3              - .Input P
 0008  61 6c 65 74 74 65 20 66                 - alette f
 0010  69 6c 65 20 6e 61 6d 65                 - ile name
 0018  20 3a 20 00                             -  : .
 001c  0a 49 6e 70 75 74 20 53 L4              - .Input S
 0024  70 72 69 74 65 20 63 6f                 - prite co
 002c  64 65 20 6e 61 6d 65 20                 - de name 
 0034  28 2a 2e 63 6f 64 29 20                 - (*.cod) 
 003c  3a 20 00                                - : .
 003f  72 62 00                L5              - rb.
 0042  72 62 00                L6              - rb.
 0045  47 6f 6f 64 20 62 79 65 L7              - Good bye
 004d  2e 2e 2e 2e 00                          - .....

No disassembly errors

------------------------------------------------------------

Segment: _BSS  DWORD USE32  00000008 bytes  

No disassembly errors

------------------------------------------------------------

//  .. RunE ..  Graphic Library
//   VESA 2.0  Linear mode Initialize Routine...
//   1996. 8. 1.   by  Reizes    (Nam Gi Hoon)          .. RunE ..

#include <dos.h>
#include <i86.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;

/* SuperVGA mode information block */
typedef struct {
    WORD modeattr;
    BYTE winAattr,winBattr;
    WORD win_granularity;
    WORD win_size;
    WORD win_aseg,win_bseg;
    void (*win_func)();
    WORD bytePerScanLine;
    WORD h_resol,v_resol;
    BYTE char_width,char_height;
    BYTE num_of_planes;
    BYTE bitPerPixel;
    BYTE num_of_banks;
    BYTE memory_model;
    BYTE banksize;
    char    NumberOfImagePages;     /* Number of images pages           */
    char    res1;                   /* Reserved                         */
    char    RedMaskSize;            /* Size of direct color red mask    */
    char    RedFieldPosition;       /* Bit posn of lsb of red mask      */
    char    GreenMaskSize;          /* Size of direct color green mask  */
    char    GreenFieldPosition;     /* Bit posn of lsb of green mask    */
    char    BlueMaskSize;           /* Size of direct color blue mask   */
    char    BlueFieldPosition;      /* Bit posn of lsb of blue mask     */
    char    RsvdMaskSize;           /* Size of direct color res mask    */
    char    RsvdFieldPosition;      /* Bit posn of lsb of res mask      */
    char    DirectColorModeInfo;    /* Direct color mode attributes     */

    /* VBE 2.0 extensions */
    long    PhysBasePtr;            /* Physical address for linear buf  */
    long    OffScreenMemOffset;     /* Pointer to start of offscreen mem*/
    short   OffScreenMemSize;       /* Amount of offscreen mem in 1K's  */
    char    res2[206];              /* Pad to 256 byte block size       */
    } VESAINFO;

typedef struct {
 DWORD EDI,ESI,EBP,reserved;
 DWORD EBX,EDX,ECX,EAX;
 WORD flags;
 WORD ES,DS,FS,GS,IP,CS,SP,SS;
 } RMI;

static VESAINFO _vi;

int get_vesainfo(VESAINFO *vi,WORD mode);
void set_videomode(short mode);
int set_vesamode(short mode);
void *real_malloc(DWORD *selector,WORD size);
void real_free(WORD selector);
void int_real(BYTE int_no,RMI *in_reg);
void print_vesainfo(VESAINFO *vi);
int set_page(short page);
int set_logical_scanline(short line);
int set_display_line(short start_x,short start_line);

static char far * Linear_pointer;                /* Pointer to linear framebuffer    */

int DPMI_allocSelector(void)
/****************************************************************************
* Function:     DPMI_allocSelector
* Returns:      Newly allocated protected mode selector
* Description:  Allocates a new protected mode selector using DPMI
*               services. This selector has a base address and limit of 0.
****************************************************************************/
{
    int         sel;
    union REGS  r;

    r.w.ax = 0;                     /* DPMI allocate selector           */
    r.w.cx = 1;                     /* Allocate a single selector       */
    int386(0x31, &r, &r);
    if (r.x.cflag)
        {printf("\nDPMI_allocSelector() failed!\n"); exit(1); }
    sel = r.w.ax;

    r.w.ax = 9;                     /* DPMI set access rights           */
    r.w.bx = sel;
    r.w.cx = 0x8092;                /* 32 bit page granular             */
    int386(0x31, &r, &r);
    return sel;
}
long DPMI_mapPhysicalToLinear(long physAddr,long limit)
/****************************************************************************
* Function:     DPMI_mapPhysicalToLinear
* Parameters:   physAddr    - Physical memory address to map
*               limit       - Length-1 of physical memory region to map
* Returns:      Starting linear address for mapped memory
* Description:  Maps a section of physical memory into the linear address
*               space of a process using DPMI calls. Note that this linear
*               address cannot be used directly, but must be used as the
*               base address for a selector.
****************************************************************************/
{
    union REGS  r;

    r.w.ax = 0x800;                 /* DPMI map physical to linear      */
    r.w.bx = physAddr >> 16;
    r.w.cx = physAddr & 0xFFFF;
    r.w.si = limit >> 16;
    r.w.di = limit & 0xFFFF;
    int386(0x31, &r, &r);
    if (r.x.cflag)
        {printf("\nDPMI_mapPhysicalToLinear() failed!\n"); exit(1); }
    return ((long)r.w.bx << 16) + r.w.cx;
}
void DPMI_setSelectorBase(int sel,long linAddr)
/****************************************************************************
* Function:     DPMI_setSelectorBase
* Parameters:   sel     - Selector to change base address for
*               linAddr - Linear address used for new base address
* Description:  Sets the base address for the specified selector.
****************************************************************************/
{
    union REGS  r;

    r.w.ax = 7;                     /* DPMI set selector base address   */
    r.w.bx = sel;
    r.w.cx = linAddr >> 16;
    r.w.dx = linAddr & 0xFFFF;
    int386(0x31, &r, &r);
    if (r.x.cflag)
        {printf("\nDPMI_setSelectorBase() failed!\n"); exit(1); }
}
void DPMI_setSelectorLimit(int sel,long limit)
/****************************************************************************
* Function:     DPMI_setSelectorLimit
* Parameters:   sel     - Selector to change limit for
*               limit   - Limit-1 for the selector
* Description:  Sets the memory limit for the specified selector.
****************************************************************************/
{
    union REGS  r;

    r.w.ax = 8;                     /* DPMI set selector limit          */
    r.w.bx = sel;
    r.w.cx = limit >> 16;
    r.w.dx = limit & 0xFFFF;
    int386(0x31, &r, &r);
    if (r.x.cflag)
        {printf("\nDPMI_setSelectorLimit() failed!\n"); exit(1); }
}

void far *GetPtrToLFB(long physAddr)
{
    int     sel;
    long    linAddr,limit = (4096 * 1024) - 1;

    sel = DPMI_allocSelector();
    linAddr = DPMI_mapPhysicalToLinear(physAddr,limit);
    DPMI_setSelectorBase(sel,linAddr);
    DPMI_setSelectorLimit(sel,limit);
    return MK_FP(sel,0);
}

void set_videomode(short mode)
 {
  union REGS r;
  r.w.ax=mode;
  int386(0x10,&r,&r);
  if (mode=0x13)
   {
    _vi.h_resol=320; _vi.v_resol=200;
    _vi.win_size=64; _vi.win_granularity=64;
    _vi.win_aseg=0xa000; _vi.win_bseg=0xa000;
    _vi.num_of_banks=1; _vi.banksize=64;
   }
 }
int set_vesamode(short mode,int flag=0) // flag : 1 Linear mode
 {
  union REGS r; int ret;
  ret=get_vesainfo(&_vi,mode);
  r.w.ax=0x4f02;
  if (flag==0) r.w.bx=mode;
   else { if ((_vi.modeattr & 0x0080)==0) { printf("\n This mode can not supprot linear mode...\n");
                                            printf("Please install VESA2.0 emulation (Univbe...)\n");exit(1);}
           else r.w.bx=0x4000 | mode;
        }
  int386 (0x10,&r,&r);
  if (r.h.al!=0x4f || r.h.ah!=0) return -1;
  if (ret==-1) return -1;
  Linear_pointer = (char __far *)GetPtrToLFB(_vi.PhysBasePtr);
  return 0;
 }
void *real_malloc(DWORD *selector,WORD size)
 {
  union REGS regs;

  regs.w.ax=0x0100;
  regs.w.bx=((size+15)>>4);
  int386(0x31,&regs,&regs);
  if (regs.x.cflag) return NULL;
  *selector=regs.x.edx;
  return (void *)((regs.x.eax&0xffff)<<4);
 }
void real_free(WORD selector)
 {
  union REGS regs;
  regs.x.eax=0x0101;
  regs.x.edx=selector;
  int386(0x31,&regs,&regs);
 }
void int_real(BYTE int_no,RMI *in_reg)
 {
  union REGS regs;
  struct SREGS sregs;

  regs.x.eax=0x0300;
  regs.x.ebx=int_no;
  regs.w.cx=0;
  sregs.es=FP_SEG(in_reg);
  regs.x.edi=FP_OFF(in_reg);
  int386x(0x31,&regs,&regs,&sregs);
 }
int get_vesainfo(VESAINFO *vi,WORD mode)
 {
  BYTE *buff;
  RMI rmi_call;
  DWORD selector;
  buff=(BYTE *)real_malloc(&selector,1024);
  if (buff==NULL) return -1;
  memset(&rmi_call,0,sizeof(RMI));
  rmi_call.EAX=0x4f01;
  rmi_call.ECX=mode;
  rmi_call.EDI=0;
  rmi_call.ES=((DWORD)buff>>4) & 0xffff;
  int_real(0x10,&rmi_call);
  memcpy(vi,buff,sizeof(VESAINFO));
  real_free(selector);
  return 0;
 }
void print_vesainfo(VESAINFO *vi)
 {
  printf("Display Size : %4d x %4d , %dBits\n",vi->h_resol,vi->v_resol,vi->bitPerPixel);
  printf("Window Size : %4d Kbyte\n",vi->win_size);
  printf("Window A,B Segment : %04x   %04x\n",vi->win_aseg,vi->win_bseg);
  printf("Window Granularity : %4d Kbyte \n",vi->win_granularity);
  printf("Window A,B Attribute : %04x   %04x\n",vi->winAattr,vi->winBattr);
  printf("Window Control Function Pointer : %08x\n",vi->win_func);
  printf("Linear mode pointer : %08x\n",Linear_pointer);
  printf("Red Mask Size : %d, Position : %d \n",vi->RedMaskSize,vi->RedFieldPosition);
  printf("Green Mask Size : %d, Position : %d \n",vi->GreenMaskSize,vi->GreenFieldPosition);
  printf("Blue Mask Size : %d, Position : %d \n",vi->BlueMaskSize,vi->BlueFieldPosition);
 }

int set_page(short page)
 {
  union REGS r;
  static WORD cbn=0;

  if (cbn==page) return 1;

  r.w.ax=0x4f05;
  r.w.bx=0;
  r.w.dx=page;
  int386(0x10,&r,&r);
  if (r.h.al==0x4f && r.h.ah==0) {cbn=page;return 0 ;}
  return -1;
 }
int set_logical_scanline(short line)
 {
  union REGS r;

  r.w.ax=0x4f06;
  r.h.bl=0;
  r.w.cx=line;
  int386(0x10,&r,&r);
  if (r.h.ah==0) return 0;
  return -1;
 }
int set_display_line(short start_x,short start_line)
 {
  union REGS r;

  r.w.ax=0x4f07;
  r.w.bx=0x0;
  r.w.cx=start_x;
  r.w.dx=start_line;
  int386(0x10,&r,&r);
  if (r.h.ah==0) return 0;
  return -1;
 }


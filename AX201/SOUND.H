/*  modplay.h - Tiny MOD Player V2.11 for Watcom C/C++ and DOS/4GW

    Module player for Sound Blaster and compatibles header file.

    Copyright 1993,94 Carlos Hasan
*/


#define PM_TIMER    0
#define PM_MANUAL   1

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long dword;
typedef byte *pointer;

typedef struct {
    word    NumTracks;
    word    OrderLength;
    byte    Orders[128];
    pointer Patterns[128];
    pointer SampPtr[32];
    pointer SampEnd[32];
    pointer SampLoop[32];
    byte    SampVolume[32];
} Module;

typedef struct {
    word    Period;
    word    Volume;
    dword   Length;
    pointer Data;
} Sample;


extern "C" {
int  _cdecl MODDetectCard(word *Port, byte *IRQ, byte *DRQ);
int  _cdecl MODPlayModule(Module *Modulefile,word Chans,word Rate,word Port,byte IRQ,byte DRQ,byte Mode);
void _cdecl MODStopModule(void);
void _cdecl MODPlaySample(byte Voice,Sample *Instr);
void _cdecl MODStopSample(byte Voice);
void _cdecl MODSetPeriod(byte Voice,word Period);
void _cdecl MODSetVolume(byte Voice,byte Volume);
void _cdecl MODSetMusicVolume(byte Volume);
void _cdecl MODSetSampleVolume(byte Volume);
void _cdecl MODPoll(void);

Module *MODLoadModule(char *Path);
void MODFreeModule(Module *Song);
Sample *MODLoadSample(char *Path);
void MODFreeSample(Sample *Instr);
}

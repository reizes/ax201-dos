#define NO_VOICE      0 /* ·q¬÷ Â‰b·i Ða»¡ ´g“e”a. */
#define SOUNDBLASTER  2 /* ¬a¶…—a §iœ¯aÈá */
#define PC_SPEAKER    1 /* Ï¡¯¡ ¯aÏ¡Äá */
#define COVOX         3 /* Å¡¥¢¯a */

#define VOICE_IDLE 0    /* ·q¬÷ Â‰bº—·¡ ´a“¡”a. */
#define VOICE_BUSY 1    /* ·q¬÷ Â‰bº—·¡”a. */

#define DIRECT_8BIT_DAC 0x10  /* ¬a§i »¢¸ó 8 §¡Ëa DAC */
#define DMA_8BIT_DAC    0x14  /* DMAŸi ·¡¶wÐe 8 §¡Ëa DAC */
#define HALT_DMA        0xd0  /* DMA ¸å­· º—»¡ */
#define FREQ_DIVISER    0x40  /* ¬‘ÏiŸ· ºÌa® ¬é¸÷ */
#define SBL_SPEAKER_ON  0xD1  /* ¬a§i ¯aÏ¡ÄáŸi Åe”a. */
#define SBL_SPEAKER_OFF 0xD3  /* ¬a§i ¯aÏ¡ÄáŸi e”a. */
#define SBL_RESET       0x6   /* ¬a§i Ÿ¡­[ */
#define SBL_RESET_CMD   0x1
#define SBL_DATA_AVAIL  0x0e  /* ¬a§i •A·¡Èa ¦…¬âº— */
#define SBL_READ_DATA   0xa   /* ¬a§i •A·¡Èa ·ª‹¡ */
#define SBL_READ_STATUS 0xc   /* ¬a§i ¬wÈ ·ª‹¡ */
#define SBL_WRITE_DATA  0xc   /* ¬a§i •A·¡Èa ³a‹¡ */

#define SBLPRO_MIXER_A  0x4   /* ¬a§i Ïa¡ £¢¬á ´á—aA¯a */
#define SBLPRO_MIXER_D  0x5   /* ¬a§i Ïa¡ £¢¬á •A·¡Èa ´á—aA¯a */
#define SBLPRO_VOICE_VOLUME   0x04 /* ¬a§i Ïa¡ ¥¡·¡¯a ¥©ŸQ */
#define SBLPRO_MASTER_VOLUME  0x22
#define SBLPRO_LINE_VOLUME    0x2e
#define SBLPRO_FM_VOLUME      0x26
#define SBLPRO_CD_VOLUME      0x28

#define setSBLProMixer(A,R,L) \
  { outp(SBLBaseIO+SBLPRO_MIXER_A,(A)) ; \
	outp(SBLBaseIO+SBLPRO_MIXER_D,((R)<<4)|(L)) ; }

short int SBLBaseIO=0x220;   /* default sound blaster Base IO Address */
short int SBLIRQ=7;        /* default sound blaster hardware interrupt */
short int SBLDMAChannel=0x1; /* default sound blaster DMA channel */
short unsigned int SampleRate=8000;
short int VoiceFlag=VOICE_IDLE; /* ·q¬÷ Â‰b ¬wÉA ¥e® */
short int VoiceHardWare=NO_VOICE;  /* ·q¬÷ Â‰b Ða—a¶Á´á */

unsigned short int VOC_GetDMACount(void);
int VOC_Play(char *filename);
int VOC_Init(void);
void VOC_Close(void);

int SBL_Command(unsigned char);
int SBL_Reset(short int);
void VOC_SetSampleRate(unsigned short int);
int SBL_AutoDetect(void);
void SBL_Speaker(unsigned char);
int SBL_sendcommand(unsigned char);
#pragma aux SBL_sendcommand= \
 " mov dx,SBLBaseIO "\
 " add dx,0xc "\
 " mov cx,0x2000 "\
 " waitLoop: "\
 " in  al,dx "\
 " test al,0x80 "\
 " jz  writeCommand "\
 " loop waitLoop "\
 " mov eax,-1 "\
 " jmp end "\
 " writeCommand: "\
 " mov al,bl "\
 " out dx,al "\
 " mov eax,1 "\
 " end: "\
 parm [bl] \
 value [eax] \
 modify [eax ebx ecx edx] ;

void waitmSec(unsigned short int);
void VOC_SetVolume(unsigned short int vol);
unsigned int VOC_GetVolume(void);

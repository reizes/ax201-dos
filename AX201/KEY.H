// #ifndef __HKEY_H__
//#define __HKEY_H__

#define  _ESC		1
#define  _1		2
#define	 _2		3
#define	 _3		4
#define	 _4		5
#define	 _5		6
#define	 _6		7
#define	 _7		8
#define	 _8		9
#define	 _9		10
#define	 _0		11
#define	 _SUB		12
#define	 _PLUS		13
#define	 _BKSP		14     // BACK SPACEBAR
#define  _TAB		15
#define	 _Q		16
#define	 _ENTER		28
#define	 _CTRL		29
#define	 _LSHT		42
#define	 _RSHT		54
#define	 _ALT		56
#define	 _SPACE		57
#define	 _F1		59
#define	 _F2		60
#define	 _F3		61
#define	 _F4		62
#define	 _F5		63
#define	 _F6		64
#define	 _F7		65
#define	 _F8		66
#define	 _F9		67
#define	 _F10		68
#define	 _F11		69
#define	 _F12		70
#define	 _HOME		71
#define	 _UP		72
#define	 _PGUP		73
#define	 _LEFT		75
#define	 _CENTER	76
#define	 _RIGHT		77
#define	 _END		79
#define	 _DOWN		80
#define	 _PGDN		81
#define	 _INS		82
#define	 _DEL		83

unsigned char Scan[128];

    void initkey();
    void delkey();
//#endif

/*
    ”aº—·q¬÷Â‰b µ¹A Ïa¡‹aœ‘
*/

#include <stdio.h>
#include <bios.h>
#include "voice.h"

/*

        Space Bar    :  Play Voice
        Left Arrow   :  Volume down
        Right Arrow  :  Volume up
        ESC          :  Exit program

*/

void main(int argc,char *argv[])
{
    int keyin;
    if( argc != 2 ) {
        printf(" Usage : test VOCfile\n");
        return;
    }
	if( VOC_Init() == -1 ) {
		printf("\n Voice Initiation error.");
		return;
	}
	while( 1 ) {
		if( bioskey( 1 ) ) {
			keyin = bioskey( 0 );
			if( keyin == 0x3920 ) VOC_Play( argv[1] );
			if( keyin == 0x4B00 ) VOC_SetVolume( VOC_GetVolume() - 1 );
			if( keyin == 0x4D00 ) VOC_SetVolume( VOC_GetVolume() + 1 );
			else if( keyin == 0x011B ) break;
		}
	}
	VOC_Close();
		/* ·q¬÷ Â‰b·i ¶áÐ ¬é¸÷–E ·¥ÈáœóËaŸi Ð¹AÐe”a. */
}

/*

		SetVoiceVolume()  :  Set Volume   --==>  Volume range is 0 - 15.

*/
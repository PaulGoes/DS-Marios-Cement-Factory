#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <unistd.h>
#include <maxmod9.h>

#include <nds.h>

#include "intro.h"
#include "select.h"
#include "controls.h"
#include "history.h"
#include "original.h"
#include "background.h"

#include "gameover.h"

#include "marioleft.h"
#include "marioright.h"
#include "rsmario.h"

#include "mariosiloleftclosed.h"
#include "mariosiloleftopen.h"
#include "mariosilorightclosed.h"
#include "mariosilorightopen.h"
#include "rsmariosilo.h"

#include "marioelevatorleft.h"
#include "marioelevatorright.h"
#include "rsmarioelevator.h"

#include "mariohang.h"
#include "rsmariohang.h"

#include "mariocrashtop.h"
#include "mariocrashbottom.h"
#include "rsmariocrash.h"

#include "driverleft.h"
#include "driverright.h"
#include "rsdriver.h"

#include "driverhitleft.h"
#include "driverhitright.h"
#include "rsdriverhit.h"

#include "cartempty.h"
#include "cartfull.h"
#include "cart4left.h"
#include "cart4right.h"
#include "rscart.h"
#include "rscart4.h"

#include "valveclosed.h"
#include "valveopenleft.h"
#include "valveopenright.h"
#include "rsvalveclosed.h"
#include "rsvalveopen.h"

#include "valvecart.h"
#include "rsvalvecart.h"

#include "handleleftup.h"
#include "handlerightup.h"
#include "rshandleup.h"

#include "handleleftdown.h"
#include "handlerightdown.h"
#include "rshandledown.h"

#include "elevator.h"
#include "rselevator.h"

#include "cement1.h"
#include "cement2left.h"
#include "cement2right.h"
#include "rscement1.h"
#include "rscement2left.h"
#include "rscement2right.h"

#include "dump1.h"
#include "dump2.h"
#include "rsdump1.h"
#include "rsdump2.h"

#include "overflowleft.h"
#include "overflowright.h"
#include "rsoverflow.h"

#include "overflowdriverleft.h"
#include "overflowdriverright.h"
#include "rsoverflowdriver.h"

#include "score0.h"
#include "score1.h"
#include "score2.h"
#include "score3.h"
#include "score4.h"
#include "score5.h"
#include "score6.h"
#include "score7.h"
#include "score8.h"
#include "score9.h"

#include "miss1.h"
#include "miss2.h"

#include "soundbank.h"
#include "soundbank_bin.h"


struct pngimg { unsigned int *imageptr; int width; int height; }; 
struct cart_status { int status; int position; };

#define SILOLEFTTOP 	0
#define SILOLEFTBOTTOM 	1
#define SILORIGHTTOP 	2
#define SILORIGHTBOTTOM 3

#define CARTEMPTY 1
#define CARTFULL  2

#define VALVECLOSED 1
#define VALVEOPEN 	2

#define SETMARIO   1
#define RESETMARIO 0

#define LEFT        1
#define RIGHT       2
#define DRIVERTRUCK 1
#define DRIVERHIT   2


int foul_pos_map[4][2] = {
		{ 172, 13 },		/* miss text */			/* [ ][1] : x-coordinate */
		{ 203, 10 },		/* position 1 */		/* [ ][2] : y-coordinate */
		{ 220, 10 },		/* position 2 */
		{ 237, 10 }			/* position 3 */
	};
	

int driver_pos_map[4][2] = {
		{ 33, 148 },		/* left truck */		/* [ ][0] : x-coordinate */
		{ 200, 148 },		/* right truck */		/* [ ][1] : y-coordinate */
		{ 39, 170 },		/* left hit */	
		{ 170, 170 }		/* right hit */	
	};

int cart_pos_map[4][4] = {		
		{ 64, 35, 174, 35 },		/* position 0 */		/* [ ][0] : x-coordinate Left */
		{ 41, 35, 197, 35 },		/* position 1 */		/* [ ][1] : y-coordinate Left */
		{ 18, 35, 220, 35 },		/* position 2 */		/* [ ][2] : x-coordinate Right */
		{ 2, 35, 243, 35 }			/* position 3 */		/* [ ][3] : y-coordinate Right */
	};

int valvecart_pos_map[4][2] = {		
		{ 32, 56},			/* position 1 */		/* [ ][0] : x-coordinate */
		{ 220, 56}			/* position 2 */		/* [ ][1] : x-coordinate */
	};

int valve_pos_map[4][4] = {		
		{ 16, 94, 5, 97},			/* Silo Left Up */			/* [ ][0] : x-coordinate closed */
		{ 16, 132, 5, 135},		/* Silo Left Down */		/* [ ][1] : Y-coordinate closed */
		{ 230, 94, 242, 97},		/* Silo Right Up */			/* [ ][2] : x-coordinate open */
		{ 230, 132, 242, 135}		/* Silo Right Down */		/* [ ][3] : x-coordinate open */
	};
	
int handle_pos_map[4][4] = {		
		{ 36, 80, 38, 90 },		/* Silo Left Up */			/* [ ][0] : x-coordinate up */
		{ 36, 118, 38, 128 },		/* Silo Left Down */		/* [ ][1] : Y-coordinate up */
		{ 211, 80, 209, 90 },		/* Silo Right Up */			/* [ ][2] : x-coordinate down */
		{ 211, 118, 209, 128 }		/* Silo Right Down */		/* [ ][3] : x-coordinate down */
	};

int elevator_pos_map[5][4] = {
		{ 101, 22, 129, 162 },		/* position 0 */		/* [ ][0] : x-coordinate Left */
		{ 101, 57, 129, 127 },		/* position 1 */		/* [ ][1] : y-coordinate Left */
		{ 101, 92, 129, 92 },		/* position 2 */		/* [ ][2] : x-coordinate Right */
		{ 101, 127, 129, 57 },		/* position 3 */		/* [ ][3] : y-coordinate Right */
		{ 101, 162, 129, 22 } 		/* position 4 */
	};

int cement_pos_map[4][4][2] = {
		{ {15, 59}, {12, 70}, {12, 78}, {14, 85} },			/* silo Up Left    */	/* [ ][0] : pre layer    */ 	/* [ ][ ][0] x-coordinate */
		{ {12, 99}, {12, 108}, {12, 116}, {14, 123} },		/* silo Down Left  */	/* [ ][1] : top layer 	 */ 	/* [ ][ ][1] y-coordinate */
		{ {223, 59}, {226, 70}, {226, 78}, {227, 85} },		/* silo Up Right   */	/* [ ][2] : middle layer */
		{ {226, 99}, {226, 108}, {226, 116}, {227, 123} }		/* silo Down Right */	/* [ ][3] : lower layer  */
	};

int dump_pos_map[6][2] = {
		{ 15, 59 },		/* left upper */		/* [ ][0] : x-coordinate */
		{ 12, 99 },		/* left middle */		/* [ ][1] : y-coordinate */
		{ 12, 136 },	/* left bottom */
		{ 223, 59 },	/* right upper */
		{ 226, 99 },	/* right middle */
		{ 226, 136 }	/* right bottom */
	};
	
int overflow_pos_map[6][2] = {
		{ 34, 67 },		/* left upper */		/* [ ][0] : x-coordinate */
		{ 34, 105 },	/* left middle */		/* [ ][1] : y-coordinate */
		{ 37, 140 },	/* left bottom */
		{ 213, 67 },	/* right upper */
		{ 213, 105 },	/* right middle */
		{ 200, 140  }	/* right bottom */
	};


int mario_pos_map[20][4] = {
		{ 0, 0, 0, 0 },		/* not exists  */		/* [ ][0] : move left    */
		{ 1, 9, 100, 32 },		/* position  1 */		/* [ ][1] : move right   */
		{ 11, 8, 100, 67 },	/* position  2 */       /* [ ][2] : x-coordinate */
		{ 13, 7, 100, 102 },	/* position  3 */		/* [ ][3] : y-coordinate */
		{ 19, 6, 100, 137 },	/* position  4 */
		{ 5, 5, 101, 168 },	/* position  5 */
		{ 4, 6, 129, 137 },	/* position  6 */
		{ 3, 17, 129, 102 },	/* position  7 */
		{ 2, 15, 129, 67 },	/* position  8 */
		{ 1, 9, 129, 32 }, 	/* position  9 */
		{ 10, 10, 100, 8 },	/* position 10 */
		{ 12, 2, 73, 68 },		/* position 11 */
		{ 12, 11, 45, 68},		/* position 12 */
		{ 14, 3, 73, 102}, 	/* position 13 */
		{ 14, 13, 45, 102 },	/* position 14 */
		{ 8, 16, 156, 68},		/* position 15 */
		{ 15, 16, 178, 68},	/* position 16 */
		{ 7, 18, 156, 102},	/* position 17 */
		{ 17, 18, 178, 102},	/* position 18 */
		{ 19, 4, 74, 134}		/* position 19 */
		
	};


int jump_pos_map[5][2] = {
		{ 80, 43 },			/* position 1 */		/* [ ][1] : x-coordinate */
		{ 58, 26 },			/* position 2 */		/* [ ][2] : y-coordinate */
		{ 58, 56 },			/* position 3 */
		{ 15, 110 },		/* position 4 */
		{ 4, 149 }			/* position 5 */
	};


	
pngimg img_gameover = { (unsigned int *)gameoverBitmap, 100, 45 };

pngimg img_marioleft = { (unsigned int *)marioleftBitmap, 26, 24 }; pngimg img_marioright = { (unsigned int *)mariorightBitmap, 26, 24 };
pngimg img_rsmario = { (unsigned int *)rsmarioBitmap, 26, 24 };

pngimg img_mariosiloleftclosed = { (unsigned int *)mariosiloleftclosedBitmap, 32, 24 }; pngimg img_mariosiloleftopen = { (unsigned int *)mariosiloleftopenBitmap, 32, 24 };
pngimg img_mariosilorightclosed = { (unsigned int *)mariosilorightclosedBitmap, 32, 24 }; pngimg img_mariosilorightopen = { (unsigned int *)mariosilorightopenBitmap, 32, 24 };
pngimg img_rsmariosilo = { (unsigned int *)rsmariosiloBitmap, 32, 24 };

pngimg img_marioelevatorleft = { (unsigned int *)marioelevatorleftBitmap, 26, 24 }; pngimg img_marioelevatorright = { (unsigned int *)marioelevatorrightBitmap, 26, 24 };
pngimg img_rsmarioelevator = { (unsigned int *)rsmarioelevatorBitmap, 26, 24 };

pngimg img_mariohang = { (unsigned int *)mariohangBitmap, 24, 22 }; pngimg img_rsmariohang = { (unsigned int *)rsmariohangBitmap, 24, 22 };

pngimg img_mariocrashtop = { (unsigned int *)mariocrashtopBitmap, 54, 14 }; pngimg img_mariocrashbottom = { (unsigned int *)mariocrashbottomBitmap, 54, 14 };
pngimg img_rsmariocrash = { (unsigned int *)rsmariocrashBitmap, 54, 14 };

pngimg img_driverleft = { (unsigned int *)driverleftBitmap, 22, 20 }; pngimg img_driverright = { (unsigned int *)driverrightBitmap, 22, 20 };
pngimg img_rsdriver = { (unsigned int *)rsdriverBitmap, 22, 20 };
	
pngimg img_driverhitleft = { (unsigned int *)driverhitleftBitmap, 46, 20 }; pngimg img_driverhitright = { (unsigned int *)driverhitrightBitmap, 46, 20 };
pngimg img_rsdriverhit = { (unsigned int *)rsdriverhitBitmap, 46, 20 };
	
pngimg img_cartempty = { (unsigned int *)cartemptyBitmap, 18, 16 }; pngimg img_cartfull = { (unsigned int *)cartfullBitmap, 18, 16 };	
pngimg img_cart3left = { (unsigned int *)cart4leftBitmap, 12, 16 }; pngimg img_cart3right = { (unsigned int *)cart4rightBitmap, 12, 16 };	
pngimg img_rscart = { (unsigned int *)rscartBitmap, 18, 16 }; pngimg img_rscart3 = { (unsigned int *)rscart4Bitmap, 12, 16 };

pngimg img_valvecart = { (unsigned int *)valvecartBitmap, 2, 8 }; pngimg img_rsvalvecart = { (unsigned int *)rsvalvecartBitmap, 2, 8 };
pngimg img_valveclosed = { (unsigned int *)valveclosedBitmap, 10, 2 }; pngimg img_rsvalveclosed = { (unsigned int *)rsvalveclosedBitmap, 10, 2 };
pngimg img_valveopenleft = { (unsigned int *)valveopenleftBitmap, 8, 6 }; pngimg img_valveopenright = { (unsigned int *)valveopenrightBitmap, 8, 6 };
pngimg img_rsvalveopen = { (unsigned int *)rsvalveopenBitmap, 8, 6 };

pngimg img_handleleftup = { (unsigned int *)handleleftupBitmap, 8, 10 }; pngimg img_handlerightup = { (unsigned int *)handlerightupBitmap, 8, 10 };
pngimg img_handleleftdown = { (unsigned int *)handleleftdownBitmap, 8, 4 }; pngimg img_handlerightdown = { (unsigned int *)handlerightdownBitmap, 8, 4 };
pngimg img_rshandleup = { (unsigned int *)rshandleupBitmap, 8, 10 }; pngimg img_rshandledown = { (unsigned int *)rshandledownBitmap, 8, 4 };

pngimg img_elevator = { (unsigned int *)elevatorBitmap, 26, 2 }; pngimg img_rselevator = { (unsigned int *)rselevatorBitmap, 26, 2 };	

pngimg img_cement1 = { (unsigned int *)cement1Bitmap, 18, 6 }; pngimg img_rscement1 = { (unsigned int *)rscement1Bitmap, 18, 6 };
pngimg img_cement2left = { (unsigned int *)cement2leftBitmap, 14, 8 }; pngimg img_rscement2left = { (unsigned int *)rscement2leftBitmap, 14, 8 };	
pngimg img_cement2right = { (unsigned int *)cement2rightBitmap, 14, 8 }; pngimg img_rscement2right = { (unsigned int *)rscement2rightBitmap, 14, 8 };				

pngimg img_dump1 = { (unsigned int *)dump1Bitmap, 16, 8 }; pngimg img_rsdump1 = { (unsigned int *)rsdump1Bitmap, 16, 8 };
pngimg img_dump2 = { (unsigned int *)dump2Bitmap, 16, 6 }; pngimg img_rsdump2 = { (unsigned int *)rsdump2Bitmap, 16, 6 };

pngimg img_overflowleft = { (unsigned int *)overflowleftBitmap, 8, 12 }; pngimg img_overflowright = { (unsigned int *)overflowrightBitmap, 8, 12 };
pngimg img_rsoverflow = { (unsigned int *)rsoverflowBitmap, 8, 12 };

pngimg img_overflowdriverleft = { (unsigned int *)overflowdriverleftBitmap, 18, 8 }; pngimg img_overflowdriverright = { (unsigned int *)overflowdriverrightBitmap, 18, 8 };
pngimg img_rsoverflowdriver = { (unsigned int *)rsoverflowdriverBitmap, 18, 8 };

pngimg img_score0 = { (unsigned int *)scoreBitmap, 16, 20 }; pngimg img_score1 = { (unsigned int *)score1Bitmap, 16, 20 };
pngimg img_score2 = { (unsigned int *)score2Bitmap, 16, 20 }; pngimg img_score3 = { (unsigned int *)score3Bitmap, 16, 20 };
pngimg img_score4 = { (unsigned int *)score4Bitmap, 16, 20 }; pngimg img_score5 = { (unsigned int *)score5Bitmap, 16, 20 };
pngimg img_score6 = { (unsigned int *)score6Bitmap, 16, 20 }; pngimg img_score7 = { (unsigned int *)score7Bitmap, 16, 20 };
pngimg img_score8 = { (unsigned int *)score8Bitmap, 16, 20 }; pngimg img_score9 = { (unsigned int *)score9Bitmap, 16, 20 };

pngimg img_miss1 = { (unsigned int *)miss1Bitmap, 30, 8 }; pngimg img_miss2 = { (unsigned int *)miss2Bitmap, 14, 14 };


int mario_position;
int mario_position_old;

int game_score;
int game_score_old;
int game_level;

bool elevator_left[5];
bool elevator_right[5];
int elevator_rythm;
int elevator_switch;

cart_status cart_left;
cart_status cart_right;
int cart_rythm;
int cart_switch;

int cement_rythm;
bool cement_status[4][4];

int dump_slt_counter;
int dump_slb_counter;
int dump_srt_counter;
int dump_srb_counter;

int fouls;
bool game_over;

int speed = 80000;
int resolution = 3;


void sleepwait(int timer) {

	int frames;
	int counter;
	
	frames = ( timer * 58 ) / 1000000;
	
	for(counter=0; counter<frames; counter++) swiWaitForVBlank();

}


/* Select a low priority DMA channel to perform our background copying. */
static const int DMA_CHANNEL = 3;


void initVideo() {
    
    /*  Map VRAM to display a background on the main and sub screens. */
    vramSetPrimaryBanks(VRAM_A_MAIN_BG_0x06000000,
                        VRAM_B_MAIN_BG_0x06020000,
                        VRAM_C_SUB_BG_0x06200000,
                        VRAM_D_LCD);

    /*  Set the video mode on the main screen. */
    videoSetMode(MODE_5_2D | DISPLAY_BG2_ACTIVE | DISPLAY_BG3_ACTIVE);

    /*  Set the video mode on the sub screen. */
    videoSetModeSub(MODE_5_2D | DISPLAY_BG3_ACTIVE); 
}


void initBackgrounds() {

    REG_BG3CNT = BG_BMP16_256x256 | BG_BMP_BASE(0) | BG_PRIORITY(3); 
    REG_BG3PA = 1 << 8;
    REG_BG3PB = 0;
    REG_BG3PC = 0;
    REG_BG3PD = 1 << 8;
    REG_BG3X = 0;
    REG_BG3Y = 0;

    REG_BG2CNT = BG_BMP16_128x128 | BG_BMP_BASE(8) | BG_PRIORITY(2);
    REG_BG2PA = 1 << 8;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 1 << 8;
    REG_BG2X = -(SCREEN_WIDTH / 2 - 32) << 8;
    REG_BG2Y = -32 << 8;

    REG_BG3CNT_SUB = BG_BMP16_256x256 | BG_BMP_BASE(0) | BG_PRIORITY(3);
    REG_BG3PA_SUB = 1 << 8;
    REG_BG3PB_SUB = 0;
    REG_BG3PC_SUB = 0;
    REG_BG3PD_SUB = 1 << 8;
    REG_BG3X_SUB = 0;
    REG_BG3Y_SUB = 0;
}


void displayselect_bg() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     selectBitmap, 
                     (uint16 *)BG_BMP_RAM(0), 
                     selectBitmapLen); 
}


void displayintro_bg() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     introBitmap, 
                     (uint16 *)BG_BMP_RAM_SUB(0), 
                     introBitmapLen); 
}


void displaycontrols_bg() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     controlsBitmap, 
                     (uint16 *)BG_BMP_RAM_SUB(0), 
                     controlsBitmapLen); 
}


void displayhistory_bg() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     historyBitmap, 
                     (uint16 *)BG_BMP_RAM_SUB(0), 
                     historyBitmapLen); 
}


void displayoriginal_bg() {
	dmaCopyHalfWords(DMA_CHANNEL,
                     originalBitmap, 
                     (uint16 *)BG_BMP_RAM_SUB(0), 
                     originalBitmapLen); 
}


void displaygame_bg() {
    dmaCopyHalfWords(DMA_CHANNEL,
                     backgroundBitmap, 
                     (uint16 *)BG_BMP_RAM(0), 
                     backgroundBitmapLen); 
}


void display_jpeg(pngimg png, int x_pos, int y_pos) {
	
	uint16 			*pointer_scr;
	unsigned int 	*pointer_png; int width; int height;
	
	pointer_scr = (uint16 *)BG_BMP_RAM(0);
	
	pointer_png = png.imageptr;
	width 		= png.width;
	height 		= png.height;
	
	int i;

		for(i=0;i<=height/2-1;i++) {
		
			/* draw the even line */
			dmaCopyHalfWords(DMA_CHANNEL,
                     pointer_png+i*width, 
                     (uint16 *)pointer_scr+(y_pos+i*2)*256+x_pos, 
                     width*2);
		
			/* draw the uneven line */
			dmaCopyHalfWords(DMA_CHANNEL,
                     pointer_png+i*width+width/2, 
                     (uint16 *)pointer_scr+(y_pos+i*2+1)*256+x_pos, 
                     width*2);
		
		}
			
}


void display_score(int score) {

	int score_1, score_10, score_100, score_1000;

	/* play sound */
	mmEffect( SFX_SCORE );
	
	/* display units */
	score_1 = score % 10;
	switch ( score_1 )
		{
			case 0: display_jpeg(img_score0, 62, 7 ); break;
			case 1: display_jpeg(img_score1, 62, 7 ); break;
			case 2: display_jpeg(img_score2, 62, 7 ); break;
			case 3: display_jpeg(img_score3, 62, 7 ); break;
			case 4: display_jpeg(img_score4, 62, 7 ); break;
			case 5: display_jpeg(img_score5, 62, 7 ); break;
			case 6: display_jpeg(img_score6, 62, 7 ); break;
			case 7: display_jpeg(img_score7, 62, 7 ); break;
			case 8: display_jpeg(img_score8, 62, 7 ); break;
			case 9: display_jpeg(img_score9, 62, 7 ); break;	
		}
	
	/* display tens */
	if( score >= 10){
		score_10 = ( score / 10 ) % 10;
		switch ( score_10 )
		{
			case 0: display_jpeg(img_score0, 45, 7 ); break;
			case 1: display_jpeg(img_score1, 45, 7 ); break;
			case 2: display_jpeg(img_score2, 45, 7 ); break;
			case 3: display_jpeg(img_score3, 45, 7 ); break;
			case 4: display_jpeg(img_score4, 45, 7 ); break;
			case 5: display_jpeg(img_score5, 45, 7 ); break;
			case 6: display_jpeg(img_score6, 45, 7 ); break;
			case 7: display_jpeg(img_score7, 45, 7 ); break;
			case 8: display_jpeg(img_score8, 45, 7 ); break;
			case 9: display_jpeg(img_score9, 45, 7 ); break;	
		}
	}
	
	/* display hundreds */
	if( score >= 100){
		score_100 = ( score / 100 ) % 10;
		switch ( score_100 )
		{
			case 0: display_jpeg(img_score0, 28, 7 ); break;
			case 1: display_jpeg(img_score1, 28, 7 ); break;
			case 2: display_jpeg(img_score2, 28, 7 ); break;
			case 3: display_jpeg(img_score3, 28, 7 ); break;
			case 4: display_jpeg(img_score4, 28, 7 ); break;
			case 5: display_jpeg(img_score5, 28, 7 ); break;
			case 6: display_jpeg(img_score6, 28, 7 ); break;
			case 7: display_jpeg(img_score7, 28, 7 ); break;
			case 8: display_jpeg(img_score8, 28, 7 ); break;
			case 9: display_jpeg(img_score9, 28, 7 ); break;	
		}
	}
	
	/* display thousands */
	if( score >= 1000){
		score_1000 = ( score / 1000 ) % 10;
		switch ( score_1000 )
		{
			case 0: display_jpeg(img_score0, 11, 7 ); break;
			case 1: display_jpeg(img_score1, 11, 7 ); break;
			case 2: display_jpeg(img_score2, 11, 7 ); break;
			case 3: display_jpeg(img_score3, 11, 7 ); break;
			case 4: display_jpeg(img_score4, 11, 7 ); break;
			case 5: display_jpeg(img_score5, 11, 7 ); break;
			case 6: display_jpeg(img_score6, 11, 7 ); break;
			case 7: display_jpeg(img_score7, 11, 7 ); break;
			case 8: display_jpeg(img_score8, 11, 7 ); break;
			case 9: display_jpeg(img_score9, 11, 7 ); break;	
		}
	}
}


void update_score( int old_score, int new_score ) {
	
	int score;
	
	/* increment score until new score and display intermediate scores */
	for( score = old_score; score <= new_score; score++) {
		display_score( score );
		sleepwait(100000);
	}
}


bool elevator_randomizer() {

	int random_value;
	int difficulty;      /* 2 = difficult, 5 = easy */
	
	switch( game_level )
	{
		case 1: 
		case 2: difficulty = 5; break; /* 1 on 5 - 20% change elevator step missing */
		case 3:
		case 4: difficulty = 4; break; /* 1 on 4 - 25% change elevator step missing */
		case 5:
		case 6: difficulty = 3; break; /* 1 on 3 - 33% change elevator step missing */
		default: difficulty = 2;       /* 1 on 2 - 50% change elevator step missing */
	}
	
	random_value = rand() % difficulty;
	
	if( random_value == 0) return FALSE; else return TRUE;
}


int cart_randomizer() {

	int random_value;

	int numerator;
	int denominator;
	
	int counter;
	int cart_status = CARTEMPTY;
	
	switch( game_level )
	{
		case 1: 
			numerator = 1; denominator = 4;	break; /* 1 on 4 - 25% chance cart full */
		case 2:
		case 3:
			numerator = 1; denominator = 3;	break; /* 1 on 3 - 33% chance cart full */
		case 4: 
			numerator = 2; denominator = 5;	break; /* 2 on 5 - 40% chance cart full */
		case 5:
		case 6:
			numerator = 1; denominator = 2;	break; /* 1 on 2 - 50% chance cart full */	
		case 7:	
			numerator = 3; denominator = 5;	break; /* 3 on 5 - 60% chance cart full */	
		default:
			numerator = 3; denominator = 4;	break; /* 3 on 4 - 75% chance cart full */			
	}
	
	random_value = rand() % denominator;

	for(counter = 0; counter<numerator; counter++) {
	
		if( random_value == counter ) cart_status = CARTFULL;
	
	}

	return cart_status;
}


void display_mario(bool set_reset, int position ) {
	
	/* reset junior image at given position */
	if( set_reset == FALSE ) {
		
		switch ( position )
		{
			case 1: display_jpeg(img_rsmarioelevator, mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 2: display_jpeg(img_rsmarioelevator, mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 3: display_jpeg(img_rsmarioelevator, mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 4: display_jpeg(img_rsmarioelevator, mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 5: display_jpeg(img_rsmariocrash,    mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 6: display_jpeg(img_rsmarioelevator, mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 7: display_jpeg(img_rsmarioelevator, mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 8: display_jpeg(img_rsmarioelevator, mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 9: display_jpeg(img_rsmarioelevator, mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 10: display_jpeg(img_rsmariocrash,   mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 11: display_jpeg(img_rsmario,        mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 12: display_jpeg(img_rsmariosilo,    mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 13: display_jpeg(img_rsmario,        mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 14: display_jpeg(img_rsmariosilo,    mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 15: display_jpeg(img_rsmario,        mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 16: display_jpeg(img_rsmariosilo,    mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 17: display_jpeg(img_rsmario,        mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 18: display_jpeg(img_rsmariosilo,    mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 19: display_jpeg(img_rsmariohang,    mario_pos_map[position][2], mario_pos_map[position][3] ); break;
		}
	}
	
	/* set junior image at given position */
	if( set_reset == TRUE ) {
		
		switch ( position )
		{
			case 1: display_jpeg(img_marioelevatorleft,     mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 2: display_jpeg(img_marioelevatorleft,     mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 3: display_jpeg(img_marioelevatorleft,     mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 4: display_jpeg(img_marioelevatorleft,     mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 5: display_jpeg(img_mariocrashbottom,      mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 6: display_jpeg(img_marioelevatorright,    mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 7: display_jpeg(img_marioelevatorright,    mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 8: display_jpeg(img_marioelevatorright,    mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 9: display_jpeg(img_marioelevatorright,    mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 10: display_jpeg(img_mariocrashtop,        mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 11: display_jpeg(img_marioleft,            mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 12: display_jpeg(img_mariosiloleftclosed,  mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 13: display_jpeg(img_marioleft,            mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 14: display_jpeg(img_mariosiloleftclosed,  mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 15: display_jpeg(img_marioright,           mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 16: display_jpeg(img_mariosilorightclosed, mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 17: display_jpeg(img_marioright,           mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 18: display_jpeg(img_mariosilorightclosed, mario_pos_map[position][2], mario_pos_map[position][3] ); break;
			case 19: display_jpeg(img_mariohang,            mario_pos_map[position][2], mario_pos_map[position][3] ); break;
		}
	}


}


void display_driver( int side, int driverstatus ) {

	/* display driver left */
	if( side == LEFT ) {

		switch ( driverstatus )
		{
			/* driver in truck */
			case DRIVERTRUCK: 
				display_jpeg(img_rsdriverhit, driver_pos_map[2][0], driver_pos_map[2][1]);
				display_jpeg(img_driverleft, driver_pos_map[0][0], driver_pos_map[0][1]);
				break;
			/* driver hit */
			case DRIVERHIT:
				display_jpeg(img_rsdriver, driver_pos_map[0][0], driver_pos_map[0][1]);
				display_jpeg(img_driverhitleft, driver_pos_map[2][0], driver_pos_map[2][1]);
				break;
		}
	}

	/* display driver right */
	if( side == RIGHT ) {

		switch ( driverstatus )
		{
			/* driver in truck */
			case DRIVERTRUCK: 
				display_jpeg(img_rsdriverhit, driver_pos_map[3][0], driver_pos_map[3][1]);
				display_jpeg(img_driverright, driver_pos_map[1][0], driver_pos_map[1][1]);
				break;
			/* driver hit */
			case DRIVERHIT:
				display_jpeg(img_rsdriver, driver_pos_map[1][0], driver_pos_map[1][1]);
				display_jpeg(img_driverhitright, driver_pos_map[3][0], driver_pos_map[3][1]);
				break;
		}
	}

}


void display_cement( int silonr ) {
 
	/* display cement in top layer */
	if( cement_status[silonr][1] ) {
		display_jpeg(img_cement1, cement_pos_map[silonr][1][0], cement_pos_map[silonr][1][1]);
	}
	else {
		display_jpeg(img_rscement1, cement_pos_map[silonr][1][0], cement_pos_map[silonr][1][1]);
	}
	
	/* display cement in middle layer */
	if( cement_status[silonr][2] ) {
		display_jpeg(img_cement1, cement_pos_map[silonr][2][0], cement_pos_map[silonr][2][1]);
	}
	else {
		display_jpeg(img_rscement1, cement_pos_map[silonr][2][0], cement_pos_map[silonr][2][1]);
	}
	
	/* display cement in bottom layer */
	if( cement_status[silonr][3] ) {
		switch( silonr )
		{
			case SILOLEFTTOP:
			case SILOLEFTBOTTOM:
				display_jpeg(img_cement2left, cement_pos_map[silonr][3][0], cement_pos_map[silonr][3][1]);
				break;
			case SILORIGHTTOP:
			case SILORIGHTBOTTOM:
				display_jpeg(img_cement2right, cement_pos_map[silonr][3][0], cement_pos_map[silonr][3][1]);
				break;
		}		
	}
	else {
		switch( silonr )
		{
			case SILOLEFTTOP:
			case SILOLEFTBOTTOM:
				display_jpeg(img_rscement2left, cement_pos_map[silonr][3][0], cement_pos_map[silonr][3][1]);
				break;
			case SILORIGHTTOP:
			case SILORIGHTBOTTOM:
				display_jpeg(img_rscement2right, cement_pos_map[silonr][3][0], cement_pos_map[silonr][3][1]);
				break;
		}
	}	
}


void display_overflow( int silonr ) {

	int blink_counter;

	/* overflow silo left top */
	if( silonr == SILOLEFTTOP ) {
	
		mmEffect( SFX_COLLISION );
		display_jpeg(img_rsdump1, dump_pos_map[0][0], dump_pos_map[0][1]);
		display_jpeg(img_overflowleft, overflow_pos_map[0][0], overflow_pos_map[0][1]); sleepwait(550000);
		display_jpeg(img_rsoverflow, overflow_pos_map[0][0],overflow_pos_map[0][1]);
	}

	/* overflow silo left bottom */
	if( silonr == SILOLEFTBOTTOM ) {
	
		mmEffect( SFX_COLLISION );
		display_jpeg(img_rsdump1, dump_pos_map[1][0], dump_pos_map[1][1]);
	}
	
	/* continue overflow left and hit driver */
	if( (silonr == SILOLEFTTOP) || (silonr == SILOLEFTBOTTOM) ) {
	
		mmEffect( SFX_COLLISION );
		display_jpeg(img_overflowleft, overflow_pos_map[1][0], overflow_pos_map[1][1]); sleepwait(550000);
		display_jpeg(img_rsoverflow, overflow_pos_map[1][0], overflow_pos_map[1][1]); 
		mmEffect( SFX_COLLISION );
		display_jpeg(img_overflowdriverleft, overflow_pos_map[2][0], overflow_pos_map[2][1]); sleepwait(550000);
		display_jpeg(img_rsoverflowdriver, overflow_pos_map[2][0], overflow_pos_map[2][1]);
		
		for(blink_counter=0; blink_counter<4; blink_counter++) {
			mmEffect( SFX_COLLISION );
			display_driver( LEFT, DRIVERHIT); sleepwait(200000);
			display_jpeg(img_rsdriverhit, driver_pos_map[2][0], driver_pos_map[2][1]); sleepwait(500000);	
		}
		
		display_driver( LEFT, DRIVERTRUCK);
	}
	
	/* overflow silo right top */
	if( silonr == SILORIGHTTOP ) {
	
		mmEffect( SFX_COLLISION );
		display_jpeg(img_rsdump1, dump_pos_map[3][0], dump_pos_map[3][1]);
		display_jpeg(img_overflowright, overflow_pos_map[3][0], overflow_pos_map[3][1]); sleepwait(550000);
		display_jpeg(img_rsoverflow, overflow_pos_map[3][0],overflow_pos_map[3][1]);
	}

	/* overflow silo right bottom */
	if( silonr == SILORIGHTBOTTOM ) {
	
		mmEffect( SFX_COLLISION );
		display_jpeg(img_rsdump1, dump_pos_map[4][0], dump_pos_map[4][1]);
	}
	
	/* continue overflow right and hit driver */
	if( (silonr == SILORIGHTTOP) || (silonr == SILORIGHTBOTTOM) ) {
	
		mmEffect( SFX_COLLISION );
		display_jpeg(img_overflowright, overflow_pos_map[4][0], overflow_pos_map[4][1]); sleepwait(550000);
		display_jpeg(img_rsoverflow, overflow_pos_map[4][0], overflow_pos_map[4][1]); 
		mmEffect( SFX_COLLISION );
		display_jpeg(img_overflowdriverleft, overflow_pos_map[5][0], overflow_pos_map[5][1]); sleepwait(550000);
		display_jpeg(img_rsoverflowdriver, overflow_pos_map[5][0], overflow_pos_map[5][1]);
		
		for(blink_counter=0; blink_counter<4; blink_counter++) {
			mmEffect( SFX_COLLISION );
			display_driver( RIGHT, DRIVERHIT); sleepwait(200000);
			display_jpeg(img_rsdriverhit, driver_pos_map[3][0], driver_pos_map[3][1]); sleepwait(500000);	
		}
		
		display_driver( RIGHT, DRIVERTRUCK);
	}
	
}


void display_valve( int silonr, int valvestatus ) {

	/* close valve at given position */
	if( valvestatus == VALVECLOSED ) {

		switch ( silonr )
		{
			/* left top */
			case SILOLEFTTOP: 		
				display_jpeg(img_rsvalveopen, valve_pos_map[0][2], valve_pos_map[0][3]); display_jpeg(img_valveclosed, valve_pos_map[0][0], valve_pos_map[0][1]);
				display_jpeg(img_rshandledown, handle_pos_map[0][2], handle_pos_map[0][3]); display_jpeg(img_handleleftup, handle_pos_map[0][0], handle_pos_map[0][1]);
				break;
			/* left bottom */
			case SILOLEFTBOTTOM: 	
				display_jpeg(img_rsvalveopen, valve_pos_map[1][2], valve_pos_map[1][3]); display_jpeg(img_valveclosed, valve_pos_map[1][0], valve_pos_map[1][1]);
				display_jpeg(img_rshandledown, handle_pos_map[1][2], handle_pos_map[1][3]); display_jpeg(img_handleleftup, handle_pos_map[1][0], handle_pos_map[1][1]);
				break;
			/* right top */
			case SILORIGHTTOP: 		
				display_jpeg(img_rsvalveopen, valve_pos_map[2][2], valve_pos_map[2][3]); display_jpeg(img_valveclosed, valve_pos_map[2][0], valve_pos_map[2][1]);
				display_jpeg(img_rshandledown, handle_pos_map[2][2], handle_pos_map[2][3]); display_jpeg(img_handlerightup, handle_pos_map[2][0], handle_pos_map[2][1]);
				break;
			/* right bottom */
			case SILORIGHTBOTTOM: 	
				display_jpeg(img_rsvalveopen, valve_pos_map[3][2], valve_pos_map[3][3]); display_jpeg(img_valveclosed, valve_pos_map[3][0], valve_pos_map[3][1]);
				display_jpeg(img_rshandledown, handle_pos_map[3][2], handle_pos_map[3][3]); display_jpeg(img_handlerightup, handle_pos_map[3][0], handle_pos_map[3][1]);
				break;
		}
	}
	
	/* open valve at given position */
	if( valvestatus == VALVEOPEN ) {

		switch ( silonr )
		{
			/* left top */
			case SILOLEFTTOP: 		
				display_jpeg(img_rsvalveclosed, valve_pos_map[0][0], valve_pos_map[0][1]); display_jpeg(img_valveopenleft, valve_pos_map[0][2], valve_pos_map[0][3]);
				display_jpeg(img_rshandleup, handle_pos_map[0][0], handle_pos_map[0][1]); display_jpeg(img_handleleftdown, handle_pos_map[0][2], handle_pos_map[0][3]);
				break;
			/* left bottom */
			case SILOLEFTBOTTOM: 	
				display_jpeg(img_rsvalveclosed, valve_pos_map[1][0], valve_pos_map[1][1]); display_jpeg(img_valveopenleft, valve_pos_map[1][2], valve_pos_map[1][3]);
				display_jpeg(img_rshandleup, handle_pos_map[1][0], handle_pos_map[1][1]); display_jpeg(img_handleleftdown, handle_pos_map[1][2], handle_pos_map[1][3]);
				break;
			/* right top */
			case SILORIGHTTOP: 		
				display_jpeg(img_rsvalveclosed, valve_pos_map[2][0], valve_pos_map[2][1]); display_jpeg(img_valveopenright, valve_pos_map[2][2], valve_pos_map[2][3]);
				display_jpeg(img_rshandleup, handle_pos_map[2][0], handle_pos_map[2][1]); display_jpeg(img_handlerightdown, handle_pos_map[2][2], handle_pos_map[2][3]);
				break;
			/* right bottom */
			case SILORIGHTBOTTOM: 	
				display_jpeg(img_rsvalveclosed, valve_pos_map[3][0], valve_pos_map[3][1]); display_jpeg(img_valveopenright, valve_pos_map[3][2], valve_pos_map[3][3]);
				display_jpeg(img_rshandleup, handle_pos_map[3][0], handle_pos_map[3][1]); display_jpeg(img_handlerightdown, handle_pos_map[3][2], handle_pos_map[3][3]);
				break;
		}
	}
}


void increase_fouls() {

	fouls++;

	switch( fouls )
	{
		/* first foul */
		case 1: 
			display_jpeg(img_miss1, foul_pos_map[0][0], foul_pos_map[0][1]); 
			display_jpeg(img_miss2, foul_pos_map[1][0], foul_pos_map[1][1]);
			mario_position = 11;
			display_mario(SETMARIO,mario_position);
			break;
		/* second foul */
		case 2:
			display_jpeg(img_miss2, foul_pos_map[2][0], foul_pos_map[2][1]);
			mario_position = 11;
			display_mario(SETMARIO,mario_position);
			break;
		/* third foul and game over */
		case 3: 
			display_jpeg(img_miss2, foul_pos_map[3][0], foul_pos_map[3][1]);
			game_over = TRUE;
	}
}


void display_elevator( int side ) {

	int counter;

	/* play sound */
	mmEffect( SFX_MOVEELEVATOR );

	/* display left elevator*/
	if( side == LEFT ) {

		for( counter = 0; counter <= 4; counter ++) {

			/* display elevator floor */
			if( elevator_left[counter] == TRUE ) {
				display_jpeg(img_elevator, elevator_pos_map[counter][0], elevator_pos_map[counter][1]);
			}
			/* display empty space */
			else {
				display_jpeg(img_rselevator, elevator_pos_map[counter][0], elevator_pos_map[counter][1]);
			}
		}
	}

	/* display right elevator */
	if( side == RIGHT ) {

		for( counter = 0; counter <= 4; counter ++) {

			/* display elevator floor */
			if( elevator_right[counter] == TRUE ) {
				display_jpeg(img_elevator, elevator_pos_map[counter][2], elevator_pos_map[counter][3]);
			}
			/* display empty space */
			else {
				display_jpeg(img_rselevator, elevator_pos_map[counter][2], elevator_pos_map[counter][3]);
			}
		}
	}


}


void display_cart( int side ) {

	/* display carts left */
	if( side == LEFT ) {

		switch( cart_left.position )
		{
			/* display carts in position 0 and position 3 (empty) */
			case 0:
				display_jpeg(img_rscart, cart_pos_map[2][0], cart_pos_map[2][1]);
				display_jpeg(img_cart3left, cart_pos_map[3][0], cart_pos_map[3][1]);
				/* empty cart */
				if( cart_left.status == CARTEMPTY ) {
					display_jpeg(img_cartempty, cart_pos_map[0][0], cart_pos_map[0][1]);
				}
				/* full cart */
				else
				{
					display_jpeg(img_cartfull, cart_pos_map[0][0], cart_pos_map[0][1]);
				}
				break;
		
			/* display cart in position 1 */
			case 1:
				display_jpeg(img_rscart, cart_pos_map[0][0], cart_pos_map[0][1]);
				display_jpeg(img_rscart3, cart_pos_map[3][0], cart_pos_map[3][1]);
				/* empty cart */
				if( cart_left.status == CARTEMPTY ) {
					display_jpeg(img_cartempty, cart_pos_map[1][0], cart_pos_map[1][1]);
				}
				/* full cart */
				else
				{
					display_jpeg(img_cartfull, cart_pos_map[1][0], cart_pos_map[1][1]);
				}
				break;
			
			/* display cart in position 2 */
			case 2:
				display_jpeg(img_rscart, cart_pos_map[1][0], cart_pos_map[1][1]);
				/* empty cart */
				if( cart_left.status == CARTEMPTY ) {
					display_jpeg(img_cartempty, cart_pos_map[2][0], cart_pos_map[2][1]);
				}
				/* full cart */
				else
				{
					display_jpeg(img_cartfull, cart_pos_map[2][0], cart_pos_map[2][1]);
				}
				break;
		}
	}

	/* display carts right */
	if( side == RIGHT ) {

		switch( cart_right.position )
		{
			/* display carts in position 0 and position 3 (empty) */
			case 0:
				display_jpeg(img_rscart, cart_pos_map[2][2], cart_pos_map[2][3]);
				display_jpeg(img_cart3right, cart_pos_map[3][2], cart_pos_map[3][3]);
				/* empty cart */
				if( cart_right.status == CARTEMPTY ) {
					display_jpeg(img_cartempty, cart_pos_map[0][2], cart_pos_map[0][3]);
				}
				/* full cart */
				else
				{
					display_jpeg(img_cartfull, cart_pos_map[0][2], cart_pos_map[0][3]);
				}
				break;
		
			/* display cart in position 1 */
			case 1:
				display_jpeg(img_rscart, cart_pos_map[0][2], cart_pos_map[0][3]);
				display_jpeg(img_rscart3, cart_pos_map[3][2], cart_pos_map[3][3]);
				/* empty cart */
				if( cart_right.status == CARTEMPTY ) {
					display_jpeg(img_cartempty, cart_pos_map[1][2], cart_pos_map[1][3]);
				}
				/* full cart */
				else
				{
					display_jpeg(img_cartfull, cart_pos_map[1][2], cart_pos_map[1][3]);
				}
				break;
			
			/* display cart in position 2*/
			case 2:
				display_jpeg(img_rscart, cart_pos_map[1][2], cart_pos_map[1][3]);
				/* empty cart */
				if( cart_right.status == CARTEMPTY ) {
					display_jpeg(img_cartempty, cart_pos_map[2][2], cart_pos_map[2][3]);
				}
				/* full cart */
				else
				{
					display_jpeg(img_cartfull, cart_pos_map[2][2], cart_pos_map[2][3]);
				}
				break;
		}
	}
}


void move_elevator( int side ) {

	int counter;
	int blink_counter;
	bool mario_crash = FALSE;
	
	mario_position_old = mario_position;

	/* move elevator left */
	if( side == LEFT ) {
	
		/* check if mario in elevator */
		switch( mario_position )
		{
			case 1: mario_position = 2; break;
			case 2: mario_position = 3; break;
			case 3: mario_position = 4; break;
			case 4: mario_position = 5; mario_crash = TRUE; break;
		}
	
		/* move elevator */
		for( counter = 4; counter>0; counter--) elevator_left[counter] = elevator_left[counter-1];
		
		/* create new step */
		if( elevator_left[0] == TRUE ) {
			elevator_left[0] = FALSE;
		}
		else {
			elevator_left[0] = elevator_randomizer();
		}
	
		/* display elevator */
		display_elevator( LEFT );	
	}

	/* move elevator right */
	if( side == RIGHT ) {
	
		/* check if mario in elevator */
		switch( mario_position )
		{
			case 6: mario_position = 7; break;
			case 7: mario_position = 8; break;
			case 8: mario_position = 9; break;
			case 9: mario_position = 10; mario_crash = TRUE; break;
		}
	
		/* move elevator */
		for( counter = 4; counter>0; counter--) elevator_right[counter] = elevator_right[counter-1];
		
		/* create new step */
		if( elevator_right[0] == TRUE ) {
			elevator_right[0] = FALSE;
		}
		else {
			elevator_right[0] = elevator_randomizer();
		}
	
		/* display elevator */
		display_elevator( RIGHT );
	
	}

	/* display mario when moved */
	if( mario_position != mario_position_old ) {
		
		display_mario(RESETMARIO, mario_position_old);
		display_mario(SETMARIO, mario_position);
	}
	
	/* mario crashes */
		if( mario_crash ) {
		
			/* blink mario */
			for( blink_counter=0; blink_counter<3; blink_counter++ ) {
			
				mmEffect( SFX_COLLISION );
				sleepwait(200000);
				display_mario(RESETMARIO, mario_position);
				
				sleepwait(500000);
				mmEffect( SFX_COLLISION );
				display_mario(SETMARIO, mario_position);
			}
			
			sleepwait(500000);
				display_mario(RESETMARIO, mario_position);
			
			/* increase fouls */
			increase_fouls();
		}	
}


void move_cart( int side ) {

	/* move cart left */
	if( side == LEFT ) {
	
		/* move cart one position*/
		cart_left.position++;
		
		/* full cart in dump position */
		if( (cart_left.position == 2 ) && (cart_left.status == CARTFULL) )  {
		;
			display_jpeg(img_dump1, dump_pos_map[0][0], dump_pos_map[0][1]); 
			display_jpeg(img_valvecart, valvecart_pos_map[0][0], valvecart_pos_map[0][1]);
			
		}
		
		/* full cart in last position */
		if( (cart_left.position == 3 ) && (cart_left.status == CARTFULL) )  {
		
			display_jpeg(img_rsvalvecart, valvecart_pos_map[0][0], valvecart_pos_map[0][1]);
			
			cement_status[SILOLEFTTOP][0] = TRUE;
		}
		
		/* cart in last position */
		if( cart_left.position == 3 ) {
		
			/* introduce new cart at first position */
			cart_left.position = 0;
			cart_left.status = cart_randomizer();
			
		}
		
		display_cart( LEFT );
	}

	
	/* move cart right */
	if( side == RIGHT ) {
	
		/* move cart one position */
		cart_right.position++;
		
		/* full cart in dump position */
		if( (cart_right.position == 2 ) && (cart_right.status == CARTFULL) )  {
		
			display_jpeg(img_dump1, dump_pos_map[3][0], dump_pos_map[3][1]); 
			display_jpeg(img_valvecart, valvecart_pos_map[1][0], valvecart_pos_map[1][1]);
		}
		
		/* full cart in last position */
		if( (cart_right.position == 3 ) && (cart_right.status == CARTFULL) )  {
		
			display_jpeg(img_rsvalvecart, valvecart_pos_map[1][0], valvecart_pos_map[1][1]);
			
			cement_status[SILORIGHTTOP][0] = TRUE;	
		}
		
		/* cart in last position */
		if( cart_right.position == 3 ) {
		
			/* introduce new cart at first position */
			cart_right.position = 0;
			cart_right.status = cart_randomizer();
			
		}
		
		display_cart( RIGHT );
	}
}


void move_cement( int silonr ) {

	/* check cement from middle to bottom layer */
	if( (cement_status[silonr][3] == FALSE) && (cement_status[silonr][2] == TRUE) ) {
		
		cement_status[silonr][3] = TRUE;
		cement_status[silonr][2] = FALSE;
	}
	
	/* check cement from top to middle layer */
	if( (cement_status[silonr][2] == FALSE) && (cement_status[silonr][1] == TRUE) ) {
		
		cement_status[silonr][2] = TRUE;
		cement_status[silonr][1] = FALSE;
	}
	
	/* check cement from pre to top layer */
	if( (cement_status[silonr][1] == FALSE) && (cement_status[silonr][0] == TRUE) ) {
		
		cement_status[silonr][1] = TRUE;
		cement_status[silonr][0] = FALSE;
		
		if( silonr == SILOLEFTTOP ) display_jpeg(img_rsdump1, dump_pos_map[0][0], dump_pos_map[0][1]);
		if( silonr == SILOLEFTBOTTOM ) display_jpeg(img_rsdump1, dump_pos_map[1][0], dump_pos_map[1][1]); 
		if( silonr == SILORIGHTTOP ) display_jpeg(img_rsdump1, dump_pos_map[3][0], dump_pos_map[3][1]);
		if( silonr == SILORIGHTBOTTOM ) display_jpeg(img_rsdump1, dump_pos_map[4][0], dump_pos_map[4][1]); 
	}
	
	/* check cement overflow */
	if( (cement_status[silonr][1] == TRUE) && (cement_status[silonr][0] == TRUE) ) {
	
		/* display the overflow */
		display_overflow(silonr);
		
		/* empty the silo */
		cement_status[silonr][0] = FALSE;
		cement_status[silonr][1] = FALSE; 
		cement_status[silonr][2] = FALSE; 
		cement_status[silonr][3] = FALSE;
		
		/* remove mario */
		display_mario(RESETMARIO, mario_position);
		
		/* increase fouls */
		increase_fouls();
	}
	
	display_cement( silonr );
}


void signal_silofull() {

	bool signal = FALSE;

	/* sound if silo is almost full */
	if( (cement_status[0][1] == TRUE) && (cement_status[0][2] == TRUE) && (cement_status[0][3] == TRUE) ) signal = TRUE;
	if( (cement_status[1][1] == TRUE) && (cement_status[1][2] == TRUE) && (cement_status[1][3] == TRUE) ) signal = TRUE;
	if( (cement_status[2][1] == TRUE) && (cement_status[2][2] == TRUE) && (cement_status[2][3] == TRUE) ) signal = TRUE;
	if( (cement_status[3][1] == TRUE) && (cement_status[3][2] == TRUE) && (cement_status[3][3] == TRUE) ) signal = TRUE;
	
	if( signal == TRUE ) mmEffect( SFX_SCORE );

}


void check_action() {

	bool move_mario = TRUE;

	bool mario_falls = FALSE;
	int fall_side;
	
	int blink_counter;
	
	mario_position_old = mario_position;
	scanKeys();
	
	/* do not move mario when a button pressed in previous call */
	if( (dump_slt_counter>0) && (dump_slt_counter<=12) ) move_mario = FALSE;
	if( (dump_slb_counter>0) && (dump_slb_counter<=12) ) move_mario = FALSE;
	if( (dump_srt_counter>0) && (dump_srt_counter<=12) ) move_mario = FALSE;
	if( (dump_srb_counter>0) && (dump_srb_counter<=12) ) move_mario = FALSE;
	
	if( move_mario ) {

		/* d-pad left pressed */
		if( keysDown() & KEY_LEFT ) mario_position = mario_pos_map[mario_position_old][0];	

		/* d-pad right pressed */
		if( keysDown() & KEY_RIGHT) mario_position = mario_pos_map[mario_position_old][1];	
	}

	/* mario moved position */
	if( mario_position != mario_position_old ) {
		
		/* play sound */
		mmEffect( SFX_MOVEMARIO );
		
		/* add additional randomness */
		rand();
		
		/* display mario in new position */
		display_mario(RESETMARIO, mario_position_old);
		display_mario(SETMARIO, mario_position);
		
		/* check elevator position */
		switch( mario_position )
		{
			case 1: if( !elevator_left[1] ) mario_falls = TRUE; fall_side = LEFT; break;
			case 2: if( !elevator_left[2] ) mario_falls = TRUE; fall_side = LEFT; break;
			case 3: if( !elevator_left[3] ) mario_falls = TRUE; fall_side = LEFT; break;
			case 4: if( !elevator_left[4] ) mario_falls = TRUE; fall_side = LEFT; break;
			case 6: if( !elevator_right[0] ) mario_falls = TRUE; fall_side = RIGHT; break;
			case 7: if( !elevator_right[1] ) mario_falls = TRUE; fall_side = RIGHT; break;
			case 8: if( !elevator_right[2] ) mario_falls = TRUE; fall_side = RIGHT; break;
			case 9: if( !elevator_right[3] ) mario_falls = TRUE; fall_side = RIGHT; break;
		}
		
		/* mario falls */
		if( mario_falls ) {
		
			/* display mario falling down */
			while( mario_position != 5)
			{
				sleepwait(550000);
				
				mario_position_old = mario_position;
				
				if( fall_side == LEFT ) mario_position++;
				if( fall_side == RIGHT ) mario_position--;
			
				display_mario(RESETMARIO, mario_position_old);
				mmEffect( SFX_COLLISION );
				display_mario(SETMARIO, mario_position);
			}
		
			/* blink when mario down */
			for( blink_counter=0; blink_counter<3; blink_counter++ ) {
			
				sleepwait(200000);
				display_mario(RESETMARIO, mario_position);
				
				sleepwait(500000);
				mmEffect( SFX_COLLISION );
				display_mario(SETMARIO, mario_position);
			}
			
			sleepwait(500000);
				display_mario(RESETMARIO, mario_position);
			
			/* increase fouls */
			increase_fouls();
		}	
	}
	
	/* button a pressed */
	if( keysDown() & KEY_A ) {
	
		switch( mario_position ) 
		{
		
			/* handle silo left top */
			case 12:
				
				/* open the valve */
				display_valve( SILOLEFTTOP, VALVEOPEN);
				display_jpeg(img_mariosiloleftopen, mario_pos_map[12][2], mario_pos_map[12][3]);
				dump_slt_counter = 1;
				
				/* if cement in lower layer, dump it */
				if( cement_status[SILOLEFTTOP][3] == TRUE ) {
				
					display_jpeg(img_dump1, dump_pos_map[1][0], dump_pos_map[1][1]);
					cement_status[SILOLEFTTOP][3] = FALSE; display_cement( SILOLEFTTOP );
					
					/* update score */
					game_score_old = game_score;
					game_score = game_score + 1;
					update_score( game_score_old, game_score );
					
					cement_status[SILOLEFTBOTTOM][0] = TRUE;
				}
		
				break;
				
			/* handle silo right top */
			case 16:
				
				/* open the valve */
				display_valve( SILORIGHTTOP, VALVEOPEN);
				display_jpeg(img_mariosilorightopen, mario_pos_map[16][2], mario_pos_map[16][3]);
				dump_srt_counter = 1;
				
				/* if cement in lower layer, dump it */
				if( cement_status[SILORIGHTTOP][3] == TRUE ) {
				
					display_jpeg(img_dump1, dump_pos_map[4][0], dump_pos_map[4][1]);
					cement_status[SILORIGHTTOP][3] = FALSE; display_cement( SILORIGHTTOP );
					
					/* update score */
					game_score_old = game_score;
					game_score = game_score + 1;
					update_score( game_score_old, game_score );
					
					cement_status[SILORIGHTBOTTOM][0] = TRUE;
				}
		
				break;		
				
			/* handle silo left bottom */
			case 14:
				
				/* open the valve */
				display_valve( SILOLEFTBOTTOM, VALVEOPEN);
				display_jpeg(img_mariosiloleftopen, mario_pos_map[14][2], mario_pos_map[14][3]);
				dump_slb_counter = 1;
				
				/* if cement in lower layer, dump it */
				if( cement_status[SILOLEFTBOTTOM][3] == TRUE ) {
				
					display_jpeg(img_dump2, dump_pos_map[2][0], dump_pos_map[2][1]);
					cement_status[SILOLEFTBOTTOM][3] = FALSE; display_cement( SILOLEFTBOTTOM );
					
					/* update score */
					game_score_old = game_score;
					game_score = game_score + 3;
					update_score( game_score_old, game_score );
				}
		
				break;

			/* handle silo left bottom */
			case 18:
				
				/* open the valve */
				display_valve( SILORIGHTBOTTOM, VALVEOPEN);
				display_jpeg(img_mariosilorightopen, mario_pos_map[18][2], mario_pos_map[18][3]);
				dump_srb_counter = 1;
				
				/* if cement in lower layer, dump it */
				if( cement_status[SILORIGHTBOTTOM][3] == TRUE ) {
				
					display_jpeg(img_dump2, dump_pos_map[5][0], dump_pos_map[5][1]);
					cement_status[SILORIGHTBOTTOM][3] = FALSE; display_cement( SILORIGHTBOTTOM );
					
					/* update score */
					game_score_old = game_score;
					game_score = game_score + 3;
					update_score( game_score_old, game_score );
				}
		
				break;	
				
		}	
	}
	
	/* close valve left top after a certain time */
	if( dump_slt_counter > 0){
	
		dump_slt_counter++;
		if( dump_slt_counter == 12) {
		
			display_valve(SILOLEFTTOP, VALVECLOSED);
			display_mario(SETMARIO, 12);

			dump_slt_counter = 0;
		}
	}
	
	/* close valve right top after a certain time */
	if( dump_srt_counter > 0){
	
		dump_srt_counter++;
		if( dump_srt_counter == 12) {
		
			display_valve(SILORIGHTTOP, VALVECLOSED);
			display_mario(SETMARIO, 16);

			dump_srt_counter = 0;
		}
	}
	
	/* close valve left bottom after a certain time */
	if( dump_slb_counter > 0){
	
		dump_slb_counter++;
		if( dump_slb_counter == 12) {
		
			display_valve(SILOLEFTBOTTOM, VALVECLOSED);
			display_mario(SETMARIO, 14);	
		}
		
		if( dump_slb_counter == 24 ) {
		
			display_jpeg(img_rsdump2, dump_pos_map[2][0], dump_pos_map[2][1]);
			dump_slb_counter = 0;
		}
	}
	
	/* close valve right bottom after a certain time */
	if( dump_srb_counter > 0){
	
		dump_srb_counter++;
		if( dump_srb_counter == 12) {
		
			display_valve(SILORIGHTBOTTOM, VALVECLOSED);
			display_mario(SETMARIO, 18);	
		}
		
		if( dump_srb_counter == 24 ) {
		
			display_jpeg(img_rsdump2, dump_pos_map[5][0], dump_pos_map[5][1]);
			dump_srb_counter = 0;
		}
		
	}	
}


void init_game() {

	/* mario */
	mario_position = 11;
	mario_position_old = 11;
	
	/* score and level */
	game_score = 0;
	game_level = 1;
	
	/* elevators */
	elevator_left[0]  = TRUE; elevator_left[1]  = FALSE; elevator_left[2]  = FALSE; elevator_left[3]  = FALSE; elevator_left[4]  = FALSE; 
	elevator_right[0] = TRUE; elevator_right[1] = FALSE; elevator_right[2] = FALSE; elevator_right[3] = FALSE; elevator_right[4] = FALSE;
	
	elevator_rythm = 6;
	elevator_switch = RIGHT;
	
	/* carts */
	cart_left.status  = CARTEMPTY; cart_left.position  = 1;
	cart_right.status = CARTFULL; cart_right.position = 0;

	cart_rythm = 23;
	cart_switch = RIGHT;
	
	/* silos */
	cement_status[SILOLEFTTOP][0]     = FALSE; cement_status[SILOLEFTTOP][1]     = FALSE; cement_status[SILOLEFTTOP][2]     = FALSE; cement_status[SILOLEFTTOP][3]     = FALSE;
	cement_status[SILOLEFTBOTTOM][0]  = FALSE; cement_status[SILOLEFTBOTTOM][1]  = FALSE; cement_status[SILOLEFTBOTTOM][2]  = FALSE; cement_status[SILOLEFTBOTTOM][3]  = FALSE; 
	cement_status[SILORIGHTTOP][0]    = FALSE; cement_status[SILORIGHTTOP][1]    = FALSE; cement_status[SILORIGHTTOP][2]    = FALSE; cement_status[SILORIGHTTOP][3]    = FALSE; 
	cement_status[SILORIGHTBOTTOM][0] = FALSE; cement_status[SILORIGHTBOTTOM][1] = FALSE; cement_status[SILORIGHTBOTTOM][2] = FALSE; cement_status[SILORIGHTBOTTOM][3] = FALSE; 
	
	cement_rythm = 6;
	
	dump_slt_counter = 0;
	dump_slb_counter = 0;
	dump_srt_counter = 0;
	dump_srb_counter = 0;
	
	/* gameover and fouls */
	game_over = FALSE;
	fouls = 0;
}


int main() {
	
	touchPosition touch;
	
    /* Turn on the 2D graphics core. */
    powerOn(POWER_ALL_2D);

    /* Configure the VRAM and background control registers. */
    lcdMainOnBottom(); 
    initVideo();
    initBackgrounds();
	
    /* Display the backgrounds. */
    displayselect_bg();
    displayintro_bg();
	
	/* initialize sound */
	mmInitDefaultMem((mm_addr)soundbank_bin);
	
	/* load sound effects */
	mmLoadEffect( SFX_COLLISION );
	mmLoadEffect( SFX_MOVEMARIO );
	mmLoadEffect( SFX_MOVEELEVATOR );
	mmLoadEffect( SFX_SCORE );
	
    for (;;) {

		touchRead(&touch);
		
		/* display control screen */
		if ( ( (touch.px>29) & (touch.px<112) ) & ( (touch.py>22) & (touch.py<85) ) ) displaycontrols_bg();
		
		/* display original screen */
		if ( ( (touch.px>29) & (touch.px<112) ) & ( (touch.py>109) & (touch.py<171) ) ) displayoriginal_bg();
		
		/* display history screen */
		if ( ( (touch.px>141) & (touch.px<225) ) & ( (touch.py>109) & (touch.py<171) ) ) displayhistory_bg();
		
		/* play game */
		if ( ( (touch.px>141) & (touch.px<225) ) & ( (touch.py>22) & (touch.py<85) ) ) {
	
			/* display backgrounds */
			displayintro_bg(); displaygame_bg(); 
			
			/* initialize game */
			init_game();
			
			/* display initial elements */
			display_score( game_score );
			
			display_valve( SILOLEFTTOP, VALVECLOSED ); display_valve( SILOLEFTBOTTOM, VALVECLOSED ); 
			display_valve( SILORIGHTTOP, VALVECLOSED ); display_valve( SILORIGHTBOTTOM, VALVECLOSED );
			
			display_mario( SETMARIO, mario_position );
			
			display_driver( LEFT, DRIVERTRUCK ); display_driver( RIGHT, DRIVERTRUCK );
			
			display_elevator( LEFT ); display_elevator( RIGHT );
			
			display_cart( LEFT ); display_cart( RIGHT );
			
			while( !game_over ) {
			
				/* check for action */
				for(int action_counter=0; action_counter<resolution; action_counter++) {
			
					check_action();
					sleepwait( speed / resolution);
				}
			
				/* do rythmic movement of carts */
				cart_rythm++;
				
				if( cart_rythm == 24 ) {
				
					cart_rythm = 0;
					if( cart_switch == RIGHT ) cart_switch = LEFT; else cart_switch = RIGHT;
					
					move_cart( cart_switch );				
				}
				
				/* do rythmic movement of elevators */
				elevator_rythm++;
				
				if( elevator_rythm == 15 ) {
				
					elevator_rythm = 0;
					if( elevator_switch == RIGHT ) elevator_switch = LEFT; else elevator_switch = RIGHT;
					
					move_elevator( elevator_switch );
				}
			
				/* do rythmic flowing of cement */
				cement_rythm++;
				
				if( (cement_rythm == 5) || (cement_rythm == 15) || (cement_rythm == 20) || (cement_rythm == 30) ) signal_silofull();
				
				if( cement_rythm == 30 ) {
				
					cement_rythm = 0;
				
					move_cement( SILOLEFTTOP );
					move_cement( SILOLEFTBOTTOM );
					move_cement( SILORIGHTTOP );
					move_cement( SILORIGHTBOTTOM );
				}
			
				/* determine level */
				if( (game_level == 1) && (game_score >= 16) ) game_level = 2;
				if( (game_level == 2) && (game_score >= 32) ) game_level = 3;
				if( (game_level == 3) && (game_score >= 64) ) game_level = 4;
				if( (game_level == 4) && (game_score >= 128) ) game_level = 5;
				if( (game_level == 5) && (game_score >= 192) ) game_level = 6;
				if( (game_level == 6) && (game_score >= 256) ) game_level = 7;
			}
			
			/* end game */
			display_jpeg(img_gameover, 80, 71); 
			
			do { 
				sleepwait(100000);
									
				touchRead(&touch);
		
				if ( ( (touch.px>80) & (touch.px<180) ) & ( (touch.py>71) & (touch.py<116) ) ) break;
								
			} while ( 1 );	
			
			
			displayselect_bg();
		
		}
	
	}

    return 0;
}


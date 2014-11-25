/******************************************************************
*
*
*		-----------------------
*		    TirMarioFireball.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 13 Decembre 2000
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_mario_fireball.h"


TirMarioFireball::TirMarioFireball(int vx): speed_etape(0)
{

	dy = 0;
	dx = vx;
}


void TirMarioFireball::update()
{

	if (x < offset - 100 || x > offset + 700 || y > 520 || y < -50)
		a_detruire = true;

	speed_etape++;
	speed_etape %= DELAY_ACCELERATION;
	if (speed_etape == 0) {
		if (dir == SENS_DROITE) {
			dx++;
		} else {
			dx--;
		}
	}

	x += dx;


	ss_etape++;
	ss_etape %= 4;
	if (ss_etape == 0) {
		etape++;
		etape %= 3;
	}

	if (dx > 12) {
		pic = pbk_ennemis[27 + etape];
	} else if (dx > 6) {
		pic = pbk_ennemis[24 + etape];
	} else if (dx > 0) {
		pic = pbk_ennemis[21 + etape];
	}

	if (dx < -12) {
		pic = pbk_ennemis[18 + etape];
	} else if (dx < -6) {
		pic = pbk_ennemis[15 + etape];
	} else if (dx < 0) {
		pic = pbk_ennemis[12 + etape];
	}

	colFromPic();
}

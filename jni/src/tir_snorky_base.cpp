/******************************************************************
*
*
*		---------------------------------
*		    TirSnorkyBase.cpp
*		---------------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 12 Decembre 2000
*
*
*
******************************************************************/


//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_snorkybase.h"

const int tir_snorky_oscilation[] = {0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 2, 2, 2, 1, 1, 1, 0, 0, 0};



TirSnorkybase::TirSnorkybase(int vx): speed_etape(0), oscilation_etape(0)
{
	dy = 0;
	dx = vx;
}


void TirSnorkybase::update()
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


	oscilation_etape++;
	oscilation_etape %= 43;
	if (oscilation_etape >= 22) {
		y -= tir_snorky_oscilation[oscilation_etape - 22];
	} else {
		y += tir_snorky_oscilation[oscilation_etape];
	}
	ss_etape++;
	ss_etape %= 4;
	if (ss_etape == 0) {
		etape++;
		etape %= 3;
	}

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[32 + etape];
	} else {
		pic = pbk_ennemis[35 + etape];
	}

	if (mur_opaque(x, y) != 0)
		a_detruire = true;

	colFromPic();
}

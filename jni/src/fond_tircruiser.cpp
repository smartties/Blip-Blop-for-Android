/******************************************************************
*
*
*		-----------------------
*		    TirCruiser.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.3 - 15 Decembre 2000
*
*
*
******************************************************************/

#include "fond_tir_cruiser.h"

TirCruiser::TirCruiser(int vx, int vy, int nb_pic): dx(vx)
{
	pic = pbk_niveau[nb_pic];
	dy = vy;
	etape = 0;
	ss_etape = 0;
}

void TirCruiser::update()
{

	if ((dy >= 0) && (y + dy > 43)) {
		y = 43;
		ss_etape++;
		ss_etape %= 4;
		if (ss_etape == 0) {
			etape++;
			if (etape == 3) {
				a_detruire = true;
			} else {
				pic = pbk_niveau[21 + etape];
			}
		}
	}

	else if ((dy <= 0) && (y - dy < 20)) {
		y = 18;
		ss_etape++;
		ss_etape %= 4;
		if (ss_etape == 0) {
			etape++;
			if (etape == 3) {
				a_detruire = true;
			} else {
				pic = pbk_niveau[18 + etape];
			}
		}
	} else {
		x += dx;
		y += dy;
	}
	updateADetruire();
}
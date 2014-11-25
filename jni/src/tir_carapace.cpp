
//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_carapace.h"
#include "ben_debug.h"

TirCarapace::TirCarapace()
{
	pic = pbk_ennemis[58];
	rebond = false;
}


void TirCarapace::update()
{
	tombe();

	ss_etape++;
	ss_etape %= 3;


	if (ss_etape == 0) {
		etape += 1;
		etape %= 4;
	}
	pic = pbk_ennemis[58 + etape];


	if (/*x - CARAPACE_SPEED < xmin ||*/ mur_opaque(x - CARAPACE_SPEED, y)) {
		if (rebond) {
			a_detruire = true;
		} else {
			dir = SENS_DROITE;
			rebond = true;
		}
	} else if (/* x + CARAPACE_SPEED > offset + 640 ||*/ mur_opaque(x + CARAPACE_SPEED, y)) {
		if (rebond) {
			a_detruire = true;
		} else {
			dir = SENS_GAUCHE;
			rebond = true;
		}
	}

	if (dir == SENS_GAUCHE) {
		x -= CARAPACE_SPEED;
	} else {
		x += CARAPACE_SPEED;
	}
	if (x < offset - 100 || x > offset + 700 || y > 520 || y < -50)
		a_detruire = true;

	colFromPic();
}

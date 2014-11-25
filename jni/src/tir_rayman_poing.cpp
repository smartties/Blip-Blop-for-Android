
//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <cmath>
#include "tir_rayman_poing.h"
#include "ben_debug.h"

//implementation de la classe TirRaymanPoing

TirRaymanpoing::TirRaymanpoing(int dx0, int xc): dx(dx0), x_cible(xc)
{
	ss_etape = 1;
}


void TirRaymanpoing::update()
{

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[230];
	} else {
		pic = pbk_ennemis[231];
	}

	if ((dx != 0) && (((dir == SENS_DROITE) && (x > x_cible)) || ((dir == SENS_GAUCHE) && (x < x_cible)))) {
		ss_etape++;
		ss_etape %= abs(dx);
	}
	if (ss_etape == 0) {
		if (dir == SENS_DROITE) {
			dx -= 2;
		} else {
			dx += 2;
		}
	}

	x += dx;


	colFromPic();
}



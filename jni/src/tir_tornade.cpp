/******************************************************************
*
*
*		---------------------------------
*		   TirTornade.cpp
*		---------------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 22 Decembre 2000
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <cmath>
#include "tir_tornade.h"



TirTornade::TirTornade(int vx): dx(vx), etape_speed(0), nb_tour(0)
{
	dy = 0;
}


void TirTornade::update()
{
	ss_etape++;
	ss_etape %= 6;

	if (ss_etape == 0) {
		etape++;
		if ((etape > 5) && (nb_tour < TOUR_MAX)) {
			etape = 0;
			nb_tour ++;
		}
	}

	lat_grav += 1;
	if (dy > -7) {
		lat_grav %= LATENCE_TORNADE + 5 * dy;
	} else {
		lat_grav = 0;
	}

	if (lat_grav == 0) {
		dy -= 1;
	}

	y += dy;


	if (etape == 10) {
		a_detruire = true;
		return;
	}

	if (x < offset - 100 || x > offset + 700 || y > 520 || y < -50)
		a_detruire = true;


	etape_speed++;
	etape_speed %= TORNADE_ACCELERATION;
	if ((etape_speed == 0) && (abs(dx) < SPEED_MAX)) {
		if (dir == SENS_DROITE) {
			dx ++;
		} else {
			dx --;
		}
	}

	x += dx;

	if (dx <= 0) {
		pic = pbk_ennemis[80 + etape];
	} else {
		pic = pbk_ennemis[63 + etape];
	}
	if (etape <= 8) {
		colFromPic();
	}
}

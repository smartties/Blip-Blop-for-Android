/******************************************************************
*
*
*		----------------------------------
*		    TirMarioFireballVertical.cpp
*		----------------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 14 Decembre 2000
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_mario_fireball_vertical.h"

TirMarioFireballVertical::TirMarioFireballVertical(int vx, int xc): x_cible(xc), dx(vx)
{
	dy = -12;
}


void TirMarioFireballVertical::update()
{

	if (x < offset - 100 || x > offset + 700 || y > 520 || y < -250)
		a_detruire = true;
	if (dy > 0) {
		fireball_tombe();
	} else {
		y += dy;
	}

	if (y < -50) {
		x = x_cible;
		dy = 1;
	}

	if (dy < 0)
		x += dx;


	ss_etape++;
	ss_etape %= 4;
	if (ss_etape == 0) {
		etape++;
		etape %= 3;
	}

	if (dy > 12) {
		pic = pbk_ennemis[45 + etape];
	} else if (dy > 6) {
		pic = pbk_ennemis[42 + etape];
	} else if (dy > 0) {
		pic = pbk_ennemis[39 + etape];
	}

	if (dy < -12) {
		pic = pbk_ennemis[36 + etape];
	} else if (dy < -6) {
		pic = pbk_ennemis[33 + etape];
	} else if (dy < 0) {
		pic = pbk_ennemis[30 + etape];
	}

	colFromPic();

	if ((y_plat[0][0] < y + dy) && (y_plat[0][0] > y)) {
		tremblement(7);
	}
}


void TirMarioFireballVertical::fireball_tombe()
{
	lat_grav += 1;
	lat_grav %= LATENCE_FIREBALL;

	if (lat_grav == 0 && dy < GRAVITE_FIREBALL)
		dy += 1;

	if (dy < 0 && mur_opaque(x, y + dy))
		dy = GRAVITE_FIREBALL;

	//int ny = plat( x, y + dy);

	//if ( ny != 0 && dy > 0 && plat( x, y) == 0)
	//y = ny;
	//else
	y += dy;
}

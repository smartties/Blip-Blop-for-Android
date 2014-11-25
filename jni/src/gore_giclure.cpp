
/******************************************************************
*
*
*		-----------------------
*		   GoreGiclure.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 01 Mars 2001
*
*
*
******************************************************************/

#include "gore_giclure.h"

//implementation de la classe GoreGiclure

GoreGiclure::GoreGiclure(int vx, int vy): dx(vx)
{
	dy  = vy;

	if ((dx > -2) && (dx < 0)) {
		dx = -2;
	} else if ((dx < 2) && (dx >= 0)) {
		dx = 2;
	}

	int decalage;
	if (dx < 0) {
		decalage = 0;
	} else {
		decalage = 7;
	}
	if (dy >= 6) {
		pic = pbk_misc[92 + decalage];
	} else if (dy >= 4) {
		pic = pbk_misc[91 + decalage];
	} else if (dy >= 1) {
		pic = pbk_misc[90 + decalage];
	} else if (dy >= 0) {
		pic = pbk_misc[89 + decalage];
	} else if (dy >= -2) {
		pic = pbk_misc[88 + decalage];
	} else if (dy >= -4) {
		pic = pbk_misc[87 + decalage];
	} else {
		pic = pbk_misc[86 + decalage];
	}
}

void GoreGiclure::update()
{
	int decalage;
	if (dx < 0) {
		decalage = 0;
	} else {
		decalage = 7;
	}


	if (dy >= 6) {
		pic = pbk_misc[92 + decalage];
	} else if (dy >= 4) {
		pic = pbk_misc[91 + decalage];
	} else if (dy >= 1) {
		pic = pbk_misc[90 + decalage];
	} else if (dy >= 0) {
		pic = pbk_misc[89 + decalage];
	} else if (dy >= -2) {
		pic = pbk_misc[88 + decalage];
	} else if (dy >= -4) {
		pic = pbk_misc[87 + decalage];
	} else {
		pic = pbk_misc[86 + decalage];
	}
	x += dx;
	tombe();

	if ((dy > 0) && plat(x, y) != 0) {
		a_detruire = true;
	}
	updateADetruire();
}

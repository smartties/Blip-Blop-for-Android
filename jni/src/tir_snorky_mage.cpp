/******************************************************************
*
*
*		---------------------------------
*		   TirSnorkyMage.cpp
*		---------------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 16 Decembre 2000
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_snorky_mage.h"



TirSnorkyMage::TirSnorkyMage()
{
	dy = 6;
}


void TirSnorkyMage::update()
{
	ss_etape ++;
	ss_etape %= 4;


	if ((ss_etape == 0) && (etape < 3))
		etape ++;


	if (etape == 3)
		etape = 1;


	if ((etape == 0) && (ss_etape == 1)) {
		if (dir == SENS_DROITE)
			dx = 6;

		else
			dx = -6;
	}

	if (x < offset - 100 || x > offset + 700 || y > 520 || y < -50)
		a_detruire = true;


	if (mur_opaque(x + dx, y + dy))
		a_detruire = true;


	if (mur_opaque(x + 3 * dx, y + 3 * dy))
		etape = 3;



	x += dx;
	y += dy;

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[252 + etape];
	} else {
		pic = pbk_ennemis[261 + etape];
	}


	colFromPic();
}

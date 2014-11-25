/******************************************************************
*
*
*		-----------------------
*		    MorceauTeteRayman.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 23 Fevrier 2001
*
*
*
******************************************************************/

#include "morceau_tete_rayman.h"


MorceauTeteRayman::MorceauTeteRayman(int vx, int vy): dx(vx)
{
	pic = pbk_ennemis[496];
	dy = vy;
}

void MorceauTeteRayman::update()
{
	x += dx;
	tombe();

	ss_etape ++;
	ss_etape %= 4;
	if (ss_etape == 0) {
		etape ++;
		etape %= 8;
		pic = pbk_ennemis[496 + etape];
	}


	// Et si la tete touche le sol? ?
	//
	if (dy > 0 && (plat(x, y + dy)) != 0) {
		grave(x, y, pic);
		a_detruire = true;
	}
}


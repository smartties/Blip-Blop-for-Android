/******************************************************************
*
*
*		---------------------------
*		    FondEcrancamera.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/

#include "globals.h"
#include "fond_ecrancamera.h"

void FondEcrancamera::update()
{
	ss_etape += 1;
	ss_etape %= 87;
	if (ss_etape == 0) {
		etape += 1;
		etape %= 3;
	}
	pic = pbk_niveau[50 + etape];
}

void FondEcrancamera::affiche()
{
	Sprite::affiche();
	draw(x, y + ss_etape, pbk_niveau[49]);
}

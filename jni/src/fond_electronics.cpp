/******************************************************************
*
*
*		---------------------------
*		    FondElectronics.cpp
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
#include "fond_electronics.h"

void FondElectronic1::update()
{
	ss_etape += 1;
	ss_etape %= 2;
	if (ss_etape == 0) {
		etape += 1;
		etape %= 15;
	}
	pic = pbk_niveau[27 + etape];
}

void FondElectronic1::affiche()
{
	Sprite::affiche();
	draw(x, y, pbk_niveau[42]);
}


void FondElectronic2::update()
{
	ss_etape += 1;
	ss_etape %= 2;
	if (ss_etape == 0) {
		etape += 1;
		etape %= 15;
	}
	pic = pbk_niveau[27 + etape];
}

void FondElectronic2::affiche()
{
	Sprite::affiche();
	draw(x, y, pbk_niveau[44]);
}



void FondElectronic3::update()
{
	ss_etape += 1;
	ss_etape %= 2;
	if (ss_etape == 0) {
		etape += 1;
		etape %= 15;
	}
	pic = pbk_niveau[27 + etape];
}

void FondElectronic3::affiche()
{
	Sprite::affiche();
	draw(x, y, pbk_niveau[43]);
}



void FondElectronic4::update()
{
	ss_etape += 1;
	ss_etape %= 2;
	if (ss_etape == 0) {
		etape += 1;
		etape %= 15;
	}
	pic = pbk_niveau[27 + etape];
}



/******************************************************************
*
*
*		-----------------------
*		    EnnemiTeteRayman.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 22 Fevrier 2001
*
*
*
******************************************************************/

#include "ennemi_tete___rayman.h"


EnnemiTeteRayman::EnnemiTeteRayman(): dx(3)
{
	pv = 1;
	pic = pbk_ennemis[171];
}

void EnnemiTeteRayman::update()
{
	if (blood > 0)
		blood -= 1;

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
		case ETAT_SAUTE:
		case ETAT_TOMBE:
			onAvance();
			break;

		case ETAT_CARBONISE:
		case ETAT_MEURE:
			onMeure();
			break;
	}
}

void EnnemiTeteRayman::onAvance()
{
	x += dx;
	tombe();
	colFromPic();

	ss_etape ++;
	ss_etape %= 4;
	if (ss_etape == 0) {
		etape ++;
		etape %= 8;
		pic = pbk_ennemis[171 + etape];
	}


	// Et si la tete touche le sol? ?
	//
	if (dy > 0 && (plat(x, y + dy)) != 0) {
		grave(x, y, pic);
		game_flag[0] = 2;
		a_detruire = true;
	}
}



void EnnemiTeteRayman::onMeure()
{
	ss_etape ++;
	ss_etape %= 6;
	if (ss_etape == 0) {
		etape ++;
		if (etape >= 6) {
			game_flag[0] = 2;
			a_detruire = true;
		} else {
			pic = pbk_ennemis[179 + etape];
		}
	}
}


int EnnemiTeteRayman::degats()
{
	return 0;
};

void EnnemiTeteRayman::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	tir->aTouche(9999);
	gicle(tir, dx_giclure, dy_giclure);
}
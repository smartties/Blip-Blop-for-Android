
#include "ennemi_flameche.h"

EnnemiFlameche::EnnemiFlameche()
{
	pv = 100;
}


void EnnemiFlameche::update()
{

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_MEURE:
		case ETAT_CARBONISE:
			onMeure();
			break;
	}

	updateADetruire();
}


void EnnemiFlameche::onAvance()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 8;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 2;
	}

	// Marche
	//
	if (x - 1 < xmin || mur_opaque(x - 1, y))
		dir = SENS_DROITE;
	else if (x + 1 > offset + 640 || mur_opaque(x + 1, y))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(2);
		pic = pbk_ennemis[44 + etape];
	} else {
		marche(-2);
		pic = pbk_ennemis[46 + etape];
	}


	colFromPic();
}


void EnnemiFlameche::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0 && etape < 14)
		etape += 1;

	if (etape >= 14) {
		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[62 + etape];
		else
			pic = pbk_ennemis[48 + etape];
	}
}


void EnnemiFlameche::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 10, 10, 0, -10, -10, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);
}

#include "ennemi_bulbizarre.h"

EnnemiBulbizarre::EnnemiBulbizarre()
{
	pv = 100;
}


void EnnemiBulbizarre::update()
{
	if (blood > 0)
		blood -= 1;

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_MEURE:
			onMeure();
			break;

		case ETAT_CARBONISE:
			onCarbonise();
			break;
	}

	updateADetruire();
}


void EnnemiBulbizarre::onAvance()
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
		marche(1);
		pic = pbk_ennemis[24 + etape];
	} else {
		marche(-1);
		pic = pbk_ennemis[26 + etape];
	}


	colFromPic();
}


void EnnemiBulbizarre::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0 && etape < 8)
		etape += 1;

	if (etape >= 8) {
		int		yy = plat(x, y);

		if (yy != 0 && yy != y_plat[4][x])
			grave(x, y, pic);

		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[36 + etape];
		else
			pic = pbk_ennemis[28 + etape];
	}
}

void EnnemiBulbizarre::onCarbonise()
{
	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	if (etape >= 14)
		a_detruire = true;
	else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[128 + etape];
		else
			pic = pbk_ennemis[143 + etape];
	}
}

void EnnemiBulbizarre::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (etat == ETAT_MEURE) {
		sbk_misc.play(8 + rand() % 2);
	}
}
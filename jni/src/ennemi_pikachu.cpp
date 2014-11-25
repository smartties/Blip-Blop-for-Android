
#include "ennemi_pikachu.h"


EnnemiPikachu::EnnemiPikachu()
{
	pv = 100;
}

void EnnemiPikachu::update()
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

void EnnemiPikachu::onAvance()
{
	static const int SPEED = 3;

	tombe();

	ss_etape += 1;
	ss_etape %= 8;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 2;
	}

	// Marche
	//
	if (x - SPEED < xmin || mur_opaque(x - SPEED, y))
		dir = SENS_DROITE;
	else if (x + SPEED > offset + 640 || mur_opaque(x + SPEED, y))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(SPEED);
		pic = pbk_ennemis[etape];
	} else {
		marche(-SPEED);
		pic = pbk_ennemis[2 + etape];
	}


	colFromPic();
}

void EnnemiPikachu::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0 && etape < 10)
		etape += 1;

	if (etape >= 10) {
		int		yy = plat(x, y);

		if (yy != 0 && yy != y_plat[4][x])
			grave(x, y, pic);

		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[14 + etape];
		else
			pic = pbk_ennemis[4 + etape];
	}
}

void EnnemiPikachu::onCarbonise()
{
	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	if (etape >= 14)
		a_detruire = true;
	else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[100 + etape];
		else
			pic = pbk_ennemis[114 + etape];
	}
}

void EnnemiPikachu::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (etat == ETAT_MEURE) {
//		sbk_niveau.play( 7/*+rand()%3*/);
		sbk_misc.play(8 + rand() % 2);
	}
}
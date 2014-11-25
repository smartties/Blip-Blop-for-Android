
#include "ennemi_bisou_coeur.h"
#include "gore_tete_bisou_coeur.h"
#include "tir_coeur_bisou.h"

EnnemiBisouCoeur::EnnemiBisouCoeur()
{
	pv = 300;
}


void EnnemiBisouCoeur::update()
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

		case ETAT_MEURE_2:
			onPart();
			break;

		case ETAT_CARBONISE:
			break;
	}

	updateADetruire();
}


void EnnemiBisouCoeur::onAvance()
{
	static const int SPEED = 2;

	static const int anim_gauche [] = { 431, 432, 433, 434, 433, 432 };
	static const int anim_droite [] = { 427, 428, 429, 430, 429, 428 };

	if (dir == SENS_GAUCHE) {
		x -= SPEED;

		if (mur_opaque(x, y) || x < xmin)
			dir = SENS_DROITE;

		pic = pbk_ennemis[anime(anim_gauche, 6, 7)];
	} else {
		x += SPEED;

		if (mur_opaque(x, y) || x > offset + 600)
			dir = SENS_GAUCHE;

		pic = pbk_ennemis[anime(anim_droite, 6, 7)];
	}

	if (etape == 3 && ss_etape == 0) {
		TirCoeurBisou * tir = new TirCoeurBisou();

		if (dir == SENS_DROITE)
			tir->xbase = x + 10;
		else
			tir->xbase = x - 10;

		tir->y = y;

		list_tirs_ennemis.ajoute((void*) tir);
	}

	colFromPic();
}

void EnnemiBisouCoeur::onMeure()
{
	static const int SPEED = 2;

	ss_etape += 1;
	ss_etape %= 3;

	if (ss_etape == 0) {
		etape += 1;

		if (etape > 5) {
			etat = ETAT_MEURE_2;
			return;
		}

		if (etape == 4) {
			GoreTeteBisouCoeur * tete = new GoreTeteBisouCoeur();

			tete->y = y - 20;
			tete->dir = dir;

			if (dir == SENS_DROITE)
				tete->x = x + 11;
			else
				tete->x = x - 11;

			list_gore.ajoute((void*) tete);
		}
	}

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[435 + etape];
		x += SPEED;
	} else {
		pic = pbk_ennemis[441 + etape];
		x -= SPEED;
	}
}



void EnnemiBisouCoeur::onPart()
{
	static const int SPEED = 10;

	if (dir == SENS_DROITE)
		x += SPEED;
	else
		x -= SPEED;
}


void EnnemiBisouCoeur::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 7, 10, 7, 0, -7, -10, -7 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (etat == ETAT_MEURE)
		sbk_niveau.play((rand() % 9));
}

#include "ennemi_bisou_boom.h"
#include "gore_bisou_boom.h"

EnnemiBisouBoom::EnnemiBisouBoom()
{
	pv = 200;
}


void EnnemiBisouBoom::update()
{
	if (blood > 0)
		blood -= 1;


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

void EnnemiBisouBoom::onAvance()
{
	static const int SPEED = 3;

	tombe();

	ss_etape += 1;
	ss_etape %= 3;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 8;
	}

	// Marche
	//
	if (x - SPEED < xmin || mur_opaque(x - SPEED, y))
		dir = SENS_DROITE;
	else if (x + SPEED > offset + 640 || mur_opaque(x + SPEED, y))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(SPEED);
		pic = pbk_ennemis[154 + etape];
	} else {
		marche(-SPEED);
		pic = pbk_ennemis[162 + etape];
	}

	// Si assez prêt du joueur -> kamikaze!
	//
	if (tete_turc != NULL) {
		int ddx = x - tete_turc->x;
		int ddy = y - tete_turc->y;

		if (ddx > -60 && ddx < 60 && ddy > -40 && ddy < 20) {
			ss_etape = etape = 0;
			etat = ETAT_MEURE;
			sbk_misc.play(11);
			onMeure();
		}
	}

	colFromPic();
}

void EnnemiBisouBoom::onMeure()
{
	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 7 && ss_etape == 0) {
		Sprite * s = new GorePiedBisouBoom();

		if (dir == SENS_DROITE) {
			s->x = x - 60;
			s->y = y - 22;
			s->dir = dir;
			s->dy = -(rand() % 4);
		} else {
			s->x = x + 60;
			s->y = y - 26;
			s->dir = dir;
			s->dy = -(rand() % 4);
		}

		list_gore.ajoute((void*) s);

		s = new GoreTeteBisouBoom();

		if (dir == SENS_DROITE) {
			s->x = x + 46;
			s->y = y - 70;
			s->dir = dir;
			s->dy = -1;
		} else {
			s->x = x - 45;
			s->y = y - 62;
			s->dir = dir;
			s->dy = -1;
		}

		list_gore.ajoute((void*) s);
	} else if (etape == 8 && ss_etape == 0) {
		Sprite * s = new GoreBideBisouBoom();

		if (dir == SENS_DROITE) {
			s->x = x + 59;
			s->y = y - 3;
			s->dir = dir;
			s->dy = 0;
		} else {
			s->x = x - 58;
			s->y = y - 7;
			s->dir = dir;
			s->dy = 0;
		}

		list_gore.ajoute((void*) s);
	} else if (etape >= 10) {
		a_detruire = true;
	} else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[170 + etape];
		else
			pic = pbk_ennemis[180 + etape];

		colFromPic();
	}
}


void EnnemiBisouBoom::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 7, 10, 7, 0, -7, -10, -7 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	if (etat == ETAT_MEURE || etat == ETAT_CARBONISE)
		return;

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (etat == ETAT_MEURE || etat == ETAT_CARBONISE)
		sbk_misc.play(11);
}
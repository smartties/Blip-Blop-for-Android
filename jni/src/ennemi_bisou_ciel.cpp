
#include "ennemi_bisou_ciel.h"
#include "gore_pieds_bisou_ciel.h"
#include "tir_arc_ciel.h"


EnnemiBisouCiel::EnnemiBisouCiel() : wait_for_pisser(0)
{
	pv = 175;
}


void EnnemiBisouCiel::update()
{
	if (blood > 0)
		blood -= 1;

	if (wait_for_pisser > 0)
		wait_for_pisser -= 1;

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_MEURE:
			onMeureEntier();
			break;

		case ETAT_MEURE_2:
			onMeureHaut();
			break;

		case ETAT_MEURE_3:
			onMeureHautFin();
			break;

		case ETAT_TIRE:
			onTire();
			break;

		case ETAT_CARBONISE:
			onCarbonise();
			break;
	}

	updateADetruire();
}

void EnnemiBisouCiel::onMeureEntier()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 4) {
		GorePiedsBisouCiel * pieds = new GorePiedsBisouCiel();

		pieds->x = x;
		pieds->dir = dir;
		pieds->y = y;

		list_gore.ajoute((void*) pieds);

		y -= 19;
		dy = 0;
		etape = 0;
		ss_etape = 0;
		etat = ETAT_MEURE_2;
		onMeureHaut();
	} else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[32 + etape];
		else
			pic = pbk_ennemis[36 + etape];
	}
}

void EnnemiBisouCiel::onTire()
{
	ss_etape += 1;

	if (ss_etape >= 60) {
		ss_etape = 0;
		etat = ETAT_AVANCE;
		wait_for_pisser = 150;
	}
}

void EnnemiBisouCiel::onMeureHaut()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0 && etape < 3)
		etape += 1;

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[40 + etape];
		x += 1;
	} else {
		pic = pbk_ennemis[44 + etape];
		x -= 1;
	}

	tombe();

	if (plat(x, y) != 0 && etape >= 3) {
		etape = ss_etape = 0;
		etat = ETAT_MEURE_3;
		onMeureHautFin();
	}
}

void EnnemiBisouCiel::onMeureHautFin()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0 && etape < 3)
		etape += 1;

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[24 + etape];
	else
		pic = pbk_ennemis[28 + etape];


	if (etape >= 3) {
		grave(x, y, pic);
		a_detruire = true;
	}
}

void EnnemiBisouCiel::onAvance()
{
	static const int SPEED = 1;

	tombe();

	ss_etape += 1;
	ss_etape %= 4;

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
		pic = pbk_ennemis[8 + etape];
	} else {
		marche(-SPEED);
		pic = pbk_ennemis[16 + etape];
	}

	// Regarde s'il peut tirer
	//
	if (wait_for_pisser == 0 && etape == 4) { // L'etape 4 est plus jolie
		if (tete_turc != NULL && plat(x, y) != 0) { // ne tire pas en tombant
			int ddx = x - tete_turc->x;
			int ddy = y - tete_turc->y;

			if (ddy > -10 && ddy < 20) {
				if (dir == SENS_GAUCHE) {
					if (ddx > 0 && ddx < 90) {
						sbk_niveau.play(9);
						Sprite * s = new TirArcCiel();
						s->x = x - 15;
						s->y = y - 25;
						s->dir = SENS_GAUCHE;

						list_tirs_ennemis.ajoute((void*) s);

						ss_etape = 0;
						etat = ETAT_TIRE;
					}
				} else {
					if (ddx < 0 && ddx > -90) {
						sbk_niveau.play(9);
						Sprite * s = new TirArcCiel();
						s->x = x + 15;
						s->y = y - 25;
						s->dir = SENS_DROITE;

						list_tirs_ennemis.ajoute((void*) s);

						ss_etape = 0;
						etat = ETAT_TIRE;
					}
				}
			}
		}
	}

	colFromPic();
}


void EnnemiBisouCiel::onCarbonise()
{
	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape += 1;

		if (etape > 6) {
			a_detruire = true;
			return;
		}
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[559 + etape];
	else
		pic = pbk_ennemis[566 + etape];
}


void EnnemiBisouCiel::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 7, 10, 7, 0, -7, -10, -7 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (etat == ETAT_MEURE)
		sbk_niveau.play((rand() % 9));
}
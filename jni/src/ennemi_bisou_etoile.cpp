
#include "ennemi_bisou_etoile.h"
#include "gore_pieds_bisou_etoile.h"
#include "tir_etoile.h"


EnnemiBisouEtoile::EnnemiBisouEtoile() : etape_shoot(0)
{
	pv = 200;
	wait_shoot = 200 + rand() % 250;
}


void EnnemiBisouEtoile::update()
{
	if (blood > 0)
		blood -= 1;

	etape_shoot += 1;

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

void EnnemiBisouEtoile::onMeureEntier()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 4) {
		GorePiedsBisouEtoile * pieds = new GorePiedsBisouEtoile();

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
			pic = pbk_ennemis[114 + etape];
		else
			pic = pbk_ennemis[118 + etape];
	}
}

void EnnemiBisouEtoile::onTire()
{
	ss_etape += 1;

	if (ss_etape >= 60) {
		ss_etape = 0;
		etat = ETAT_AVANCE;
		wait_shoot = 200 + rand() % 500;;
		etape_shoot = 0;
	}
}



void EnnemiBisouEtoile::onMeureHaut()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0 && etape < 3)
		etape += 1;

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[122 + etape];
		x += 1;
	} else {
		pic = pbk_ennemis[126 + etape];
		x -= 1;
	}

	tombe();

	if (plat(x, y) != 0 && etape >= 3) {
		etape = ss_etape = 0;
		etat = ETAT_MEURE_3;
		onMeureHautFin();
	}
}

void EnnemiBisouEtoile::onMeureHautFin()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0 && etape < 3)
		etape += 1;

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[106 + etape];
	else
		pic = pbk_ennemis[110 + etape];


	if (etape >= 3) {
		grave(x, y, pic);
		a_detruire = true;
	}
}

void EnnemiBisouEtoile::onAvance()
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
	if (x - SPEED < xmin || mur_opaque(x - SPEED, y) || (plat(x - SPEED, y) == 0 && plat(x - SPEED, y + 5) == 0))
		dir = SENS_DROITE;
	else if (x + SPEED > offset + 680 || mur_opaque(x + SPEED, y)  || (plat(x + SPEED, y) == 0 && plat(x + SPEED, y + 5) == 0))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(SPEED);
		pic = pbk_ennemis[78 + etape];
	} else {
		marche(-SPEED);
		pic = pbk_ennemis[86 + etape];
	}

	etape_shoot += 1;

	if (etape == 4 && etape_shoot >= wait_shoot && x > offset) {
		Sprite * s = new TirEtoile();

		s->x = x;
		s->y = y - 30;
		s->dir = dir;

		list_tirs_ennemis.ajoute((void*) s);

		ss_etape = 0;
		etat = ETAT_TIRE;
	}

	colFromPic();
}

void EnnemiBisouEtoile::onCarbonise()
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

void EnnemiBisouEtoile::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 7, 10, 7, 0, -7, -10, -7 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (etat == ETAT_MEURE)
		sbk_niveau.play((rand() % 9));
}

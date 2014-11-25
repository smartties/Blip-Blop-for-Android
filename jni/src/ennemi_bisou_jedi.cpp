
#include "ennemi_bisou_jedi.h"
#include "tir_epee_laser.h"

EnnemiBisouJedi::EnnemiBisouJedi() : etape_shoot(0), a_epee(true)
{
	pv = 250;
	wait_shoot = 200 + rand() % 250;
}

void EnnemiBisouJedi::update()
{
	if (blood > 0)
		blood -= 1;

	if (a_epee)
		etape_shoot += 1;

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_MEURE:
			onMeure();
			break;

		/*
			case ETAT_TIRE:
				onTire();
				break;
		*/
		case ETAT_CARBONISE:
			onCarbonise();
			break;
	}

	updateADetruire();
}

void EnnemiBisouJedi::onAvance()
{
	static const int SPEED = 1;

	tombe();

	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 8;
	}

	// Marche
	//
	if (x - SPEED < offset + 20 || mur_opaque(x - SPEED, y))
		dir = SENS_DROITE;
	else if (x + SPEED > offset + 600 || mur_opaque(x + SPEED, y))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(SPEED);
		pic = pbk_ennemis[467 + etape];
	} else {
		marche(-SPEED);
		pic = pbk_ennemis[475 + etape];
	}

	if (etape_shoot > wait_shoot && tete_turc != NULL) {
		TirEpeeLaser * t = new TirEpeeLaser;

		t->x = x;
		t->y = y - 40;
		t->dy = 0;
		t->dx = -20;
		t->lanceur = this;
		t->cible = tete_turc;

		list_tirs_ennemis.ajoute((void*) t);

		etape_shoot = 0;
		wait_shoot = 200 + rand() % 250;
		a_epee = false;
	}

	colFromPic();
}

void EnnemiBisouJedi::onMeure()
{
	if (a_epee) {
		TirEpeeLaser * t = new TirEpeeLaser;

		t->x = x;
		t->y = y - 40;
		t->dy = 0;
		t->dx = -20;
		t->lanceur = this;

		if (tete_turc == NULL)
			t->isdead = true;
		else
			t->cible = tete_turc;

		list_tirs_ennemis.ajoute((void*) t);

		etape_shoot = 0;
		wait_shoot = 200 + rand() % 250;
		a_epee = false;
	}

	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape += 1;

		if (etape > 20) {
			if (plat(x, y) != 0)
				grave(x, y, pic);

			a_detruire = true;
			return;
		}
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[483 + etape];
	else
		pic = pbk_ennemis[504 + etape];
}


void EnnemiBisouJedi::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 7, 10, 7, 0, -7, -10, -7 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);
}

void EnnemiBisouJedi::onCarbonise()
{
	if (a_epee) {
		TirEpeeLaser * t = new TirEpeeLaser;

		t->x = x;
		t->y = y - 40;
		t->dy = 0;
		t->dx = -20;
		t->lanceur = this;

		if (tete_turc == NULL)
			t->isdead = true;
		else
			t->cible = tete_turc;

		list_tirs_ennemis.ajoute((void*) t);

		etape_shoot = 0;
		wait_shoot = 200 + rand() % 250;
		a_epee = false;
	}

	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape += 1;

		if (etape > 7) {
			a_detruire = true;
			return;
		}
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[589 + etape];
	else
		pic = pbk_ennemis[597 + etape];
}

void EnnemiBisouJedi::affiche()
{
	static const int dx_epee [] = { 8, 4, -1, -6, -6, -6, -1, 3};
	static const int dy_epee [] = { -19, -19, -19, -19, -18, -18, -19, -19 };
	static const int etape_epee [] = { 0, 1, 2, 3, 4, 3, 2, 1};

	Sprite::affiche();

	if (a_epee) {
		if (dir == SENS_DROITE)
			draw(x + dx_epee[etape], y + dy_epee[etape], pbk_ennemis[549 + etape_epee[etape]]);
		else
			draw(x - dx_epee[etape], y + dy_epee[etape], pbk_ennemis[554 + etape_epee[etape]]);
	}
}

#include "ennemi_smurf_costaud.h"
#include "tir_hadoken.h"

#define ETAT_TIRE_HADOKEN	1000
#define ETAT_TIRE_DPUNCH	1001
#define ETAT_TIRE_HKICK		1002


EnnemiSmurfCostaud::EnnemiSmurfCostaud() : etape_shoot(0), dx(0)
{
	wait_shoot = 50 + rand() % 50;
	pv = 2000;
}

void EnnemiSmurfCostaud::update()
{
	if (blood > 0)
		blood -= 1;

	if (game_flag[0] != 0) {
		etape_shoot += 1;

		if (game_flag[2] == 0) {
			mbk_niveau.play(2);
			game_flag[2] = 1;
			game_flag[FLAG_TIMER] = 40;
		}
	}

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_MEURE:
			onMeure();
			break;

		case ETAT_TIRE_HADOKEN:
			onTireHadoken();
			break;

		case ETAT_TIRE_DPUNCH:
			onTireDragonPunch();
			break;

		case ETAT_TIRE_HKICK:
			onTireHurricanKick();
			break;

		case ETAT_CARBONISE:
			onCarbonise();
			break;
	}

	updateADetruire();
}

void EnnemiSmurfCostaud::onAvance()
{
	static const int marche_droite[] = { 265, 266, 267, 268, 267, 266 };
	static const int marche_gauche[] = { 269, 270, 271, 272, 271, 270 };
	static const int SPEED = 1;

	tombe();

	dx = 0;

	// Marche
	//
	if (x - SPEED < xmin || mur_opaque(x - SPEED, y))
		dir = SENS_DROITE;
	else if (x + SPEED > offset + 640 || mur_opaque(x + SPEED, y))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(SPEED);
		pic = pbk_ennemis[anime(marche_droite, 6, 6)];
	} else {
		marche(-SPEED);
		pic = pbk_ennemis[anime(marche_gauche, 6, 6)];
	}

	if (etape_shoot >= wait_shoot && plat(x, y) != 0) {
		onTire();
		return;
	}

	colFromPic();
}

void EnnemiSmurfCostaud::estTouche(Tir * tir)
{
	static const int dx_giclure_smurf [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_smurf [] = { -15, -15, -15, -15, -15, -15, -15, -15 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_smurf, dy_giclure_smurf);

	if (pv <= 0) {
		game_flag[1]++;
	}
}

void EnnemiSmurfCostaud::onCarbonise()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape += 1;

	if (etape >= 6) {
		a_detruire = true;
	} else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[253 + etape];
		else
			pic = pbk_ennemis[259 + etape];
	}
}

void EnnemiSmurfCostaud::onMeure()
{
	tombe();

	int x2;

	if (plat(x, y) == 0)
		x2 = x + dx;
	else
		x2 = x;

	if (!mur_opaque(x2, y))
		x = x2;

	if (etape < 13) {
		ss_etape += 1;
		ss_etape %= 3;

		if (ss_etape == 0)
			etape += 1;
	}

	if (etape >= 14 && plat(x, y) != 0) {
		a_detruire = true;
		grave(x, y, pic);
	} else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[273 + etape];
		else
			pic = pbk_ennemis[287 + etape];
	}
}

void EnnemiSmurfCostaud::onTireHadoken()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0) {
		etape += 1;

		if (etape == 4) {
			TirHadoken * t = new TirHadoken();

			t->x = x;
			t->y = y - 30;
			t->setDir(dir);

			list_tirs_ennemis.ajoute((void*) t);
		}

		if (etape > 7) {
			etape = ss_etape = 0;
			etat = ETAT_AVANCE;
			wait_shoot = 100 + rand() % 50;
			etape_shoot = 0;
			onAvance();
			return;
		}
	}

	if (etape <= 4) {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[237 + etape];
		else
			pic = pbk_ennemis[242 + etape];
	}
}

void EnnemiSmurfCostaud::onTireDragonPunch()
{
	tombe();

	if (etape <= 2) { // Le départ
		ss_etape += 1;
		ss_etape %= 4;

		if (ss_etape == 0) {
			etape += 1;

			if (etape > 2)
				dy = dypunch;
		}
	} else if (dy < 0) {
		if (dir == SENS_DROITE && x < offset + 640 && !mur_opaque(x + 1, y))
			x += 1;
		else if (dir == SENS_GAUCHE && x > xmin && !mur_opaque(x - 1, y))
			x -= 1;
	} else {
		if (etape < 6) {
			ss_etape += 1;
			ss_etape %= 12;

			if (ss_etape == 0)
				etape += 1;
		}

		if (plat(x, y) != 0) {
			ss_etape = etape = 0;
			wait_shoot = 100 + rand() % 50;
			etape_shoot = 0;
			etat = ETAT_NORMAL;
			onAvance();
			return;
		}
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[223 + etape];
	else
		pic = pbk_ennemis[230 + etape];

	colFromPic();
}


void EnnemiSmurfCostaud::onTireHurricanKick()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 6;
	}

	int x2 = x + dx;

	if (!mur_opaque(x2, y) && x2 > xmin && x2 < offset + 740)
		x = x2;

	if (dy > 0 && plat(x, y) != 0) {
		ss_etape = etape = 0;
		wait_shoot = 100 + rand() % 50;
		etape_shoot = 0;
		etat = ETAT_NORMAL;
		onAvance();
		return;
	}

	pic = pbk_ennemis[247 + etape];

	colFromPic();
}

void EnnemiSmurfCostaud::onTire()
{
	if (tete_turc == NULL)
		return;

	etape = ss_etape = 0;

	int xc = tete_turc->x;
	int yc = tete_turc->y;

	int ddx = xc - x;
	int ddy = yc - y;

	if (ddx > 0)
		dir = SENS_DROITE;
	else
		dir = SENS_GAUCHE;

	if (ddy > -50 && ddy < 50 && x > offset && x < offset + 640) {
		etat = ETAT_TIRE_HADOKEN;
		sbk_niveau.play(19);
		onTireHadoken();
	} else if (ddx < 150 && ddx > -150 && ddy < 0) {
		etat = ETAT_TIRE_DPUNCH;
		dypunch = ddy / 10;

		if (dypunch < -10)
			dypunch = -10;

		sbk_niveau.play(20);
		onTireDragonPunch();
	} else {
		tirEnCloche(x, y - 5, xc, yc, dx, dy);
		etat = ETAT_TIRE_HKICK;
		onTireHurricanKick();
	}
}

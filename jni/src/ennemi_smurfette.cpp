
#include "ennemi_smurfette.h"
#include "tir_bisou_mortel.h"

EnnemiSmurfette::EnnemiSmurfette() : etape_shoot(0)
{
	wait_shoot = 100 + rand() % 100;
	pv = 200;
}

void EnnemiSmurfette::update()
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
			onMeure();
			break;

		case ETAT_TIRE:
			onTire();
			break;

		case ETAT_CARBONISE:
			onCarbonise();
			break;
	}

	if (x < offset - 20)
		a_detruire = true;

	updateADetruire();
}

void EnnemiSmurfette::onAvance()
{
	static const int marche_droite[] = { 315, 316, 317, 318, 319, 318, 317, 316 };
	static const int marche_gauche[] = { 320, 321, 322, 323, 324, 323, 322, 321 };
	static const int SPEED = 1;

	tombe();

	// Marche
	//
	if (x - SPEED < xmin || mur_opaque(x - SPEED, y) || (plat(x - SPEED, y) == 0 && plat(x - SPEED, y + 5) == 0))
		dir = SENS_DROITE;
	else if (x + SPEED > offset + 640 || mur_opaque(x + SPEED, y)  || (plat(x + SPEED, y) == 0 && plat(x + SPEED, y + 5) == 0))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(SPEED);
		pic = pbk_ennemis[anime(marche_droite, 8, 6)];
	} else {
		marche(-SPEED);
		pic = pbk_ennemis[anime(marche_gauche, 8, 6)];
	}

	if (etape_shoot >= wait_shoot && x > offset + 10 && x < offset + 630) {
		etape = ss_etape = 0;
		etat = ETAT_TIRE;
		onTire();
		return;
	}

	colFromPic();
}

void EnnemiSmurfette::onMeure()
{
	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0) {
		etape += 1;

		if (etape >= 11) {
			a_detruire = true;
			grave(x, y, pic);
			return;
		}
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[325 + etape];
	else
		pic = pbk_ennemis[337 + etape];
}

void EnnemiSmurfette::onTire()
{
	static const int tire_droite [] = { 301, 302, 303, 304, 305, 304, 303, 302, 301 };
	static const int tire_gauche [] = { 306, 307, 308, 309, 310, 309, 308, 307, 306 };

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0) {
		etape += 1;

		if (etape == 4 && ss_etape == 0 && tete_turc != NULL) {
			TirBisouMortel * t = new TirBisouMortel();

			t->x = x;
			t->y = y - 25;
			t->setDir(dir);
			t->cible = tete_turc;

			list_tirs_ennemis.ajoute((void*) t);
		} else if (etape >= 9) {
			etat = ETAT_AVANCE;
			etape = ss_etape = etape_shoot = 0;
			wait_shoot = 200 + rand() % 100;
			onAvance();
			return;
		}
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[tire_droite[etape]];
	else
		pic = pbk_ennemis[tire_gauche[etape]];

	colFromPic();
}

void EnnemiSmurfette::estTouche(Tir * tir)
{
	static const int dx_giclure_smurf [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_smurf [] = { -15, -15, -15, -15, -15, -15, -15, -15 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_smurf, dy_giclure_smurf);

	if (etat == ETAT_MEURE) {
		sbk_niveau.play(21);
	}
}

void EnnemiSmurfette::onCarbonise()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 6) {
		a_detruire = true;
	} else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[34 + etape];
		else
			pic = pbk_ennemis[40 + etape];
	}
}

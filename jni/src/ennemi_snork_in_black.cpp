/******************************************************************
*
*
*		------------------------
*		  EnnemiSnorkInBlack.cpp
*		------------------------
*
*
*		Mephisto / LOADED -   V 0.2 - 28 Decembre 2000
*
*
*
******************************************************************/

#include "ennemi_snork_in_black.h"
#include "tir_epine.h"

const int anim_snork_in_black_marche_droite[] = { 344, 345, 346, 345};
const int anim_snork_in_black_marche_gauche[] = { 347, 348, 349, 348};

EnnemiSnorkInBlack::EnnemiSnorkInBlack(): wait_for_shoot(0), shoot_delay(50 + rand() % 100), nb_tir(0)
{
	pv = 250;
	dy = 0;
}


void EnnemiSnorkInBlack::update()
{
	switch (etat) {
		case ETAT_AVANCE:
		case ETAT_NORMAL:
			onAvance();
			break;

		case ETAT_TOMBE:
		case ETAT_SAUTE:
			onTombe();
			break;

		case ETAT_MEURE:
			onMeure();
			break;

		case ETAT_CARBONISE:
			onCarbonise();
			break;

		case ETAT_TIRE:
			onTire();
			break;
	}

	updateADetruire();

}

void EnnemiSnorkInBlack::onAvance()
{

	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		onTombe();
		return;
	}

	wait_for_shoot++;
	if ((tete_turc != NULL) && (wait_for_shoot > shoot_delay) && ((dir == SENS_DROITE && x > offset + 80) || (dir == SENS_GAUCHE && x < offset + 560)))

	{
		x_cible = tete_turc->x;
		y_cible = tete_turc->y;

		if (x_cible != x) {

			int vy = ((y_cible - y + 14) * 6) / (x_cible - x);

			if ((dir == SENS_DROITE) && (x < x_cible) && (vy < 2) && (vy > -2)) {
				wait_for_shoot = 0;
				shoot_delay = 50 + rand() % 100;
				etape = 0;
				ss_etape = 0;
				nb_tir = rand() % 3;
				etat = ETAT_TIRE;
				onTire();
				return;
			} else if ((dir == SENS_GAUCHE) && (x > x_cible) && (vy < 2) && (vy > -2)) {
				wait_for_shoot = 0;
				shoot_delay = 50 + rand() % 100;
				etape = 0;
				ss_etape = 0;
				nb_tir = rand() % 3;
				etat = ETAT_TIRE;
				onTire();
				return;
			}
		}

	}

	if (dir == SENS_GAUCHE) {
		marche(-SNORK_IN_BLACK_SPEED);

		pic = pbk_ennemis[anime(anim_snork_in_black_marche_gauche, 4, 4)];

		if (mur_opaque(x - SNORK_IN_BLACK_SPEED, y) || (x - SNORK_IN_BLACK_SPEED < xmin))
			dir = SENS_DROITE;
	} else {
		marche(SNORK_IN_BLACK_SPEED);

		pic = pbk_ennemis[anime(anim_snork_in_black_marche_droite, 4, 4)];

		if (mur_opaque(x + SNORK_IN_BLACK_SPEED, y) || (x + SNORK_IN_BLACK_SPEED > offset + 640))
			dir = SENS_GAUCHE;
	}

	colFromPic();
}

void EnnemiSnorkInBlack::onTombe()
{
	tombe();

	if (plat(x, y) != 0)
		etat = ETAT_AVANCE;

	colFromPic();
}

void EnnemiSnorkInBlack::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 8;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 5) {
		if (plat(x, y) != 0)
			grave(x, y, pic);

		a_detruire = true;
	} else {
		if (dir == SENS_DROITE) {
			pic = pbk_ennemis[354 + etape];
		} else {
			pic = pbk_ennemis[359 + etape];
		}
	}
}

void EnnemiSnorkInBlack::onTire()
{
	ss_etape ++;
	if (etape == 0) {
		ss_etape %= 20;
	} else {
		ss_etape %= 4;
	}

	if (ss_etape == 0) {
		etape ++;
	}

	if ((etape == 1) && (ss_etape == 0)) {
		if (dir == SENS_DROITE) {
			int vx = 5 + rand() % 2;
			int vy = rand() % 5 - 2;

			TirEpine * tir = new TirEpine(364, vx , vy);

			tir->setDir(dir);
			tir->x = x + 49;
			tir->y = y - 15;

			list_tirs_ennemis.ajoute((void*) tir);
		} else {
			int vx = -5 - rand() % 2;
			int vy = rand() % 5 - 2;

			TirEpine * tir = new TirEpine(365, vx , vy);

			tir->setDir(dir);
			tir->x = x - 49;
			tir->y = y - 15;

			list_tirs_ennemis.ajoute((void*) tir);
		}

		sbk_niveau.play(24);
	}

	if (etape == 3) {
		nb_tir ++;
		etape = 0;
		if (nb_tir >= SNORK_IN_BLACK_MAX_TIR) {
			ss_etape = 0;
			etape = 0;
			etat = ETAT_AVANCE;
			onAvance();
			return;
		}
	}

	if (dir == SENS_DROITE) {
		if (etape == 0) {
			pic = pbk_ennemis[344];
		} else {
			pic = pbk_ennemis[350 + etape - 1];
		}
	} else {
		if (etape == 0) {
			pic = pbk_ennemis[347 ];
		} else {
			pic = pbk_ennemis[352 + etape - 1];
		}
	}
	colFromPic();
}

void EnnemiSnorkInBlack::onCarbonise()
{
	ss_etape ++;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape ++;

	if (etape == 7) {
		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[373 + etape];
		else
			pic = pbk_ennemis[366 + etape];
	}
}

void EnnemiSnorkInBlack::estTouche(Tir * tir)
{
	static const int dx_giclure_snorkbase1 [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_snorkbase1 [] = { -15, -15, -15, -15, -25, -15, -15, -15 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_snorkbase1, dy_giclure_snorkbase1);

	if (etat == ETAT_MEURE) {
		sbk_niveau.play(21 + rand() % 3);
	}
}

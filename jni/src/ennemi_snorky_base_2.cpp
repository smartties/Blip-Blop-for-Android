/******************************************************************
*
*
*		-------------------------
*		  EnnemiSnorkyBase2.cpp
*		------------------------
*
*		(giclures faites...)
*
*		Mephisto / LOADED -   V 0.2 - 28 Decembre 2000
*
*
*
******************************************************************/

#include "ennemi_snorky_base_2.h"
#include "tir_snorky_base_2.h"

const int anim_snorky_base_marche_droite[] = { 114, 115, 116, 117, 118, 117, 116, 115 };
const int anim_snorky_base_marche_gauche[] = { 119, 120, 121, 122, 123, 122, 121, 120 };

EnnemiSnorkyBase2::EnnemiSnorkyBase2(): wait_for_shoot(0), shoot_delay(50 + rand() % 200)
{
	pv = 150;
	pic = pbk_ennemis[0];
	dy = 0;
}


void EnnemiSnorkyBase2::update()
{
	if (blood > 0)
		blood -= 1;

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

void EnnemiSnorkyBase2::onAvance()
{

	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		onTombe();
		return;
	}

	wait_for_shoot++;
	if ((tete_turc != NULL) && (wait_for_shoot > shoot_delay) && ((dir == SENS_DROITE && x > offset + 80) || (dir == SENS_GAUCHE && x < offset + 560))) {
		wait_for_shoot = 0;
		shoot_delay = 50 + rand() % 200;
		etape = 0;
		ss_etape = 0;
		etat = ETAT_TIRE;
		x_cible = tete_turc->x;
		y_cible = tete_turc->y;
		onTire();
		return;
	}

	if (dir == SENS_GAUCHE) {
		marche(-SNORKY_BASE_SPEED);

		pic = pbk_ennemis[anime(anim_snorky_base_marche_gauche, 8, 4)];

		if (mur_opaque(x - SNORKY_BASE_SPEED, y) || (x - SNORKY_BASE_SPEED < xmin))
			dir = SENS_DROITE;
	} else {
		marche(SNORKY_BASE_SPEED);

		pic = pbk_ennemis[anime(anim_snorky_base_marche_droite, 8, 4)];

		if (mur_opaque(x + SNORKY_BASE_SPEED, y) || (x + SNORKY_BASE_SPEED > offset + 640))
			dir = SENS_GAUCHE;
	}

	colFromPic();
}

void EnnemiSnorkyBase2::onTombe()
{
	tombe();

	if (plat(x, y) != 0)
		etat = ETAT_AVANCE;

	colFromPic();
}

void EnnemiSnorkyBase2::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	if ((etape == 5) && (ss_etape == 0)) {
		dy = 0;
		y -= 17;

		if (dir == SENS_DROITE)
			x += 10;

		else
			x -= 10;

	}
	if (etape >= 5) {
		tombe();

		if (dir == SENS_DROITE)
			x += 1;

		else
			x -= 1;

	}

	if (etape == 10) {
		if (plat(x, y) != 0)
			grave(x, y, pic);

		a_detruire = true;
	}

	if (dir == SENS_GAUCHE) {
		pic = pbk_ennemis[154 + etape];
	} else {
		pic = pbk_ennemis[144 + etape];
	}
}

void EnnemiSnorkyBase2::onTire()
{
	ss_etape ++;
	ss_etape %= 6;
	if (ss_etape == 0) {
		etape ++;
	}

	if (etape == 12) {
		etape = 0;
		ss_etape = 0;
		etat = ETAT_AVANCE;
		onAvance();
		return;
	}

	if (etape == 10 && ss_etape == 0) {
		if (dir == SENS_DROITE) {
			if ((x_cible > x) && (x_cible - x != 0)) {
				int vy = ((y_cible - y + 50) * 6) / (x_cible - x);
				if (vy > 3)
					vy = 3;

				if (vy < -3)
					vy = -3;

				TirSnorkyBase2 *	tir = new TirSnorkyBase2(6, vy);
				tir->setDir(dir);
				tir->x = x + 35;
				tir->y = y - 42;

				list_tirs_ennemis.ajoute((void*) tir);

			} else {
				TirSnorkyBase2 *	tir = new TirSnorkyBase2(6, 1);
				tir->setDir(dir);
				tir->x = x + 35;
				tir->y = y - 42;

				list_tirs_ennemis.ajoute((void*) tir);
			}
			pic = pbk_ennemis[124];
		} else {
			if ((x_cible < x) && (x_cible - x != 0)) {
				int vy = ((y_cible - y + 50) * 6) / (x_cible - x);
				if (vy > 3)
					vy = 3;

				if (vy < -3)
					vy = -3;

				TirSnorkyBase2 *	tir = new TirSnorkyBase2(-6, -vy);
				tir->setDir(dir);
				tir->x = x - 35;
				tir->y = y - 42;

				list_tirs_ennemis.ajoute((void*) tir);

			} else {
				TirSnorkyBase2 *	tir = new TirSnorkyBase2(-6, 1);
				tir->setDir(dir);
				tir->x = x - 35;
				tir->y = y - 42;

				list_tirs_ennemis.ajoute((void*) tir);
			}
			pic = pbk_ennemis[134];
		}
	}

	if (etape < 10) {
		if (dir == SENS_DROITE) {
			pic = pbk_ennemis[124 + etape];
		} else {
			pic = pbk_ennemis[134 + etape];
		}
	}
	colFromPic();
}

void EnnemiSnorkyBase2::onCarbonise()
{
	ss_etape ++;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape ++;

	if (etape == 9) {
		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[173 + etape];
		else
			pic = pbk_ennemis[164 + etape];
	}
}

void EnnemiSnorkyBase2::estTouche(Tir * tir)
{
	static const int dx_giclure_snorkbase2 [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_snorkbase2 [] = { -15, -15, -15, -15, -35, -15, -15, -15 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_snorkbase2, dy_giclure_snorkbase2);

	if (etat == ETAT_MEURE) {
		sbk_niveau.play(18/*+rand()%3*/);
	}
}

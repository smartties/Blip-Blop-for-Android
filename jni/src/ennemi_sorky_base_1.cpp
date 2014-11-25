/******************************************************************
*
*
*		------------------------
*		  EnnemiSnorkyBase1.cpp
*		------------------------
*
*		(giclures faites...)
*
*		Mephisto / LOADED -   V 0.2 - 28 Decembre 2000
*
*
*
******************************************************************/

#include "ennemi_snorky_base_1.h"
#include "morceaux_tete_snorky.h"
#include "tir_snorkybase.h"

const int anim_snorky_base_marche_droite[] = { 0, 1, 2, 3, 4, 3, 2, 1 };
const int anim_snorky_base_marche_gauche[] = { 5, 6, 7, 8, 9, 8, 7, 6 };

EnnemiSnorkyBase1::EnnemiSnorkyBase1(): wait_for_shoot(0), shoot_delay(50 + rand() % 200)
{
	pv = 200;
	pic = pbk_ennemis[0];
	dy = 0;
}


void EnnemiSnorkyBase1::update()
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

void EnnemiSnorkyBase1::onAvance()
{

	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		onTombe();
		return;
	}

	wait_for_shoot++;
	if	((wait_for_shoot > shoot_delay) && ((dir == SENS_DROITE && x > offset + 40) || (dir == SENS_GAUCHE && x < offset + 600))) {
		wait_for_shoot = 0;
		shoot_delay = 50 + rand() % 200;
		etape = 0;
		ss_etape = 0;
		etat = ETAT_TIRE;
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

void EnnemiSnorkyBase1::onTombe()
{
	tombe();

	if (plat(x, y) != 0)
		etat = ETAT_AVANCE;

	colFromPic();
}

void EnnemiSnorkyBase1::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 4 && ss_etape == 1) {
		Sprite * s = new MorceauSnorkyBaseTeteEntiere();

		s->dir = dir;
		s->y = y - 22;
		s->x = x;

		list_giclures.ajoute((void*) s);

		dy = 0;
	}
	if (etape == 14) {
		if (plat(x, y) != 0) {
			grave(x, y, pic);
		}

		a_detruire = true;

	} else {
		if (dir == SENS_GAUCHE) {
			marche(-SNORKY_BASE_SPEED);
			pic = pbk_ennemis[71 + etape];
		} else {
			marche(SNORKY_BASE_SPEED);
			pic = pbk_ennemis[38 + etape];
		}
	}
}

void EnnemiSnorkyBase1::onTire()
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

			TirSnorkybase *	tir = new TirSnorkybase(1);

			tir->setDir(dir);
			tir->x = x + 35;
			tir->y = y - 42;

			list_tirs_ennemis.ajoute((void*) tir);

		} else {
			TirSnorkybase *	tir = new TirSnorkybase(-1);

			tir->setDir(dir);
			tir->x = x - 35;
			tir->y = y - 42;

			list_tirs_ennemis.ajoute((void*) tir);
		}

		sbk_niveau.play(17);
	}

	if (etape < 11) {
		if (dir == SENS_DROITE) {
			pic = pbk_ennemis[10 + etape];
		} else {
			pic = pbk_ennemis[21 + etape];
		}
	}
}

void EnnemiSnorkyBase1::onCarbonise()
{
	ss_etape ++;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape ++;

	if (etape == 9) {
		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[105 + etape];
		else
			pic = pbk_ennemis[96 + etape];
	}
}

void EnnemiSnorkyBase1::estTouche(Tir * tir)
{
	static const int dx_giclure_snorkbase1 [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_snorkbase1 [] = { -15, -15, -15, -15, -25, -15, -15, -15 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_snorkbase1, dy_giclure_snorkbase1);

	if (etat == ETAT_MEURE) {
		sbk_niveau.play(14 + rand() % 3);
	}
}

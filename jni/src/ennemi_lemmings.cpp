/******************************************************************
*
*
*		----------------------
*		  EnnemiLemmings.cpp
*		----------------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 3 Aout 2000
*
*
*
******************************************************************/

#include "ennemi_lemmings.h"
#include "bonus_vache.h"

static int wait_no = 0;

EnnemiLemmings::EnnemiLemmings() : suicide(false)
{
	pv = 100;
}


void EnnemiLemmings::update()
{
	if (blood != 0)
		blood -= 1;

	// Si 200+ lemmings tués, ils se suicident et arrêtent les générateurs
	//
	if (game_flag[FLAG_NB_KILL] >= 200 && etat != ETAT_MEURE && etat != ETAT_CARBONISE) {
		suicide = true;
		col_on = false;
		ss_etape = 0;
		etape = 0;
		etat = ETAT_MEURE;
		game_flag[FLAG_GEN_OFF] = 1;
	}

	if (game_flag[3] == 1) {
		sbk_niveau.play(5);
		game_flag[3] = 0;
	}

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
	}

	updateADetruire();

}

void EnnemiLemmings::onAvance()
{

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 14;
	}

	if (dir == SENS_GAUCHE) {
		x -= LEM_SPEED;

		tombe();

		pic = pbk_ennemis[14 + etape];

		if (mur_opaque(x, y) || x < 5)
			dir = SENS_DROITE;
	} else {
		x += LEM_SPEED;

		tombe();

		pic = pbk_ennemis[etape];

		if (mur_opaque(x, y))
			dir = SENS_GAUCHE;
	}

	colFromPic();
}

void EnnemiLemmings::onTombe()
{
	tombe();

	if (plat(x, y) != 0)
		etat = ETAT_AVANCE;

	colFromPic();
}

void EnnemiLemmings::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	// Explosion abrégée si plus de plateforme
	//
	if (etape >= 6 && (plat(x - 80, y) == 0 || plat(x + 80, y) == 0))
		a_detruire = true;

	if (etape == 10) {
		if (plat(x, y) != 0 && plat(x - 80, y) != 0 && plat(x + 80, y) != 0)
			grave(x, y, pic);

		a_detruire = true;

		if (suicide && game_flag[0] == 0) {
			Bonus * bonus = new BonusVache();
			bonus->x = 1500;
			bonus->y = -50;

			list_bonus.ajoute((void*) bonus);
			game_flag[0] = 1;
		}
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[38 + etape];
		else
			pic = pbk_ennemis[28 + etape];
	}
}

void EnnemiLemmings::onCarbonise()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 14) {
		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[62 + etape];
		else
			pic = pbk_ennemis[48 + etape];
	}
}

void EnnemiLemmings::estTouche(Tir * tir)
{
	static const int dx_giclure_lem [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_lem [] = { -15, -15, -15, -15, -15, -15, -15, -15 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_lem, dy_giclure_lem);

	if (etat == ETAT_MEURE) {
		wait_no += 1;
		wait_no %= 20;

		if (wait_no == 0) {
			sbk_niveau.play(1);
		} else {
			sbk_misc.play(7 + rand() % 3);
		}
	}
}

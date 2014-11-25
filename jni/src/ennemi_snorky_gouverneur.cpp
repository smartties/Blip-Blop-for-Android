/******************************************************************
*
*
*		-----------------------------
*		  EnnemiSnorkyGouverneur.cpp
*		-----------------------------
*
*		(giclures faites...)
*
*		Mephisto / LOADED -   V 0.2 - 28 Decembre 2000
*
*
*
******************************************************************/

#include "ennemi_snorky_gouverneur.h"
#include "tir_snorky_gouverneur.h"


const int anim_gouverneur_marche_droite[] = { 183, 184, 185, 186, 185, 184};
const int anim_gouverneur_marche_gauche[] = { 187, 188, 189, 190, 189, 188};

EnnemiSnorkyGouverneur::EnnemiSnorkyGouverneur(): wait_for_shoot(0), shoot_delay(50 + rand() % 200)
{
	pv = 150;
	pic = pbk_ennemis[0];
	dy = 0;
}


void EnnemiSnorkyGouverneur::update()
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

void EnnemiSnorkyGouverneur::onAvance()
{

	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		onTombe();
		return;
	}

	wait_for_shoot++;
	if ((wait_for_shoot > shoot_delay) && ((dir == SENS_DROITE && x > offset + 40) || (dir == SENS_GAUCHE && x < offset + 600))) {
		wait_for_shoot = 0;
		shoot_delay = 50 + rand() % 200;
		etape = 0;
		ss_etape = 0;
		nb_tir = 0;
		etat = ETAT_TIRE;
		onTire();
		return;
	}

	if (dir == SENS_GAUCHE) {
		marche(-GOUVERNEUR_SPEED);

		pic = pbk_ennemis[anime(anim_gouverneur_marche_gauche, 6, 4)];

		if (mur_opaque(x - GOUVERNEUR_SPEED, y) || (x - GOUVERNEUR_SPEED < xmin))
			dir = SENS_DROITE;
	} else {
		marche(GOUVERNEUR_SPEED);

		pic = pbk_ennemis[anime(anim_gouverneur_marche_droite, 6, 4)];

		if (mur_opaque(x + GOUVERNEUR_SPEED, y) || (x + GOUVERNEUR_SPEED > offset + 640))
			dir = SENS_GAUCHE;
	}

	colFromPic();
}

void EnnemiSnorkyGouverneur::onTombe()
{
	tombe();

	if (plat(x, y) != 0)
		etat = ETAT_AVANCE;

	colFromPic();
}

void EnnemiSnorkyGouverneur::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;


	if (etape == 5) {
		if (plat(x, y) != 0)
			grave(x, y, pic);

		a_detruire = true;
	}

	if (dir == SENS_GAUCHE) {
		pic = pbk_ennemis[210 + etape];
	} else {
		pic = pbk_ennemis[205 + etape];
	}
}

void EnnemiSnorkyGouverneur::onTire()
{
	ss_etape ++;
	ss_etape %= 6;
	if (ss_etape == 0) {
		etape ++;
	}

	if (etape == 10) {
		etape = 0;
		ss_etape = 0;
		etat = ETAT_AVANCE;
		onAvance();
		return;
	}

	if (etape == 6 && ss_etape == 0) {
		//if (dir == SENS_DROITE)
		//{

		if (tete_turc != NULL) {
			TirSnorkyGouverneur *	tir = new TirSnorkyGouverneur(tete_turc, rand() % 6 - 2 , -5 - rand() % 5);

			tir->setDir(dir);
			tir->x = x;
			tir->y = y - 71;

			list_tirs_ennemis.ajoute((void*) tir);
			nb_tir++;
		}

		if (nb_tir == 0) {
			sbk_niveau.play(6);
		}

		//}
	}
	if ((etape == 7) && (nb_tir < 5) && (ss_etape == 0)) {
		etape -= 4;
	}

	if (etape < 7) {
		if (dir == SENS_DROITE) {
			pic = pbk_ennemis[191 + etape];
		} else {
			pic = pbk_ennemis[198 + etape];
		}
	}
}

void EnnemiSnorkyGouverneur::onCarbonise()
{
	ss_etape ++;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape ++;

	if (etape == 8)
		a_detruire = true;

	else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[224 + etape];

		else
			pic = pbk_ennemis[215 + etape];
	}
}

void EnnemiSnorkyGouverneur::estTouche(Tir * tir)
{
	static const int dx_giclure_gouverneur [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_gouverneur [] = { -15, -15, -15, -15, -35, -15, -15, -15 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_gouverneur, dy_giclure_gouverneur);

	if (etat == ETAT_MEURE) {
		sbk_niveau.play(4 + rand() % 2);
	}
}

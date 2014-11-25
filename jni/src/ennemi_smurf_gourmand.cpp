/******************************************************************
*
*
*		--------------------
*		    EnnemiSmurf.h
*		--------------------
*
*		Le schtroumpf de base!
*
*
*		Prosper / LOADED -   V 0.1 - 3 Aout 2000
*
*
*
******************************************************************/

#include "ennemi_smurf_gourmand.h"
#include "tir_gateau.h"

#define	ETAT_HOLD		15

EnnemiSmurfGourmand::EnnemiSmurfGourmand() : wait_for_shoot(0)
{
	pv = 150;
	shoot_delay = 50 + rand() % 100;
}

void EnnemiSmurfGourmand::update()
{
	if (blood != 0)
		blood -= 1;

	switch (etat) {
		case ETAT_NORMAL:
			onNormal();
			break;

		case ETAT_TIRE:
			onTire();
			break;

		case ETAT_HOLD:
			onHold();
			break;

		case ETAT_MEURE:
			onMeure();
			break;

		case ETAT_CARBONISE:
			onCarbonise();
			break;
	}

	if (x < offset - 20)
		a_detruire = true;

	updateADetruire();
}


void EnnemiSmurfGourmand::onNormal()
{
	tombe();

	// Tire de temps en temps
	//
	wait_for_shoot += 1;

	if (wait_for_shoot > shoot_delay && x > offset && x < offset + 640 && tete_turc != NULL) {
		sbk_niveau.play(14 + rand() % 2);
		etat = ETAT_TIRE;
		wait_for_shoot = 0;
		shoot_delay = 100 + rand() % 250;
		etape = 0;
		ss_etape = 0;
		xcible = tete_turc->x;
		ycible = tete_turc->y;

		if (xcible > x)
			dir = SENS_DROITE;
		else
			dir = SENS_GAUCHE;

		onTire();
	}

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[182];
	} else {
		pic = pbk_ennemis[188];
	}

	colFromPic();
}


void EnnemiSmurfGourmand::onTire()
{

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	if (etape >= 5) {
		TirGateau *	tir = new TirGateau();

		tir->setDir(dir);

		if (dir == SENS_GAUCHE)
			tir->x = x - 13;
		else
			tir->x = x + 13;

		tir->y = y - 28;

		tirEnCloche(tir->x, tir->y, xcible, ycible, tir->dx, tir->dy);

		list_tirs_ennemis.ajoute((void*) tir);

		etape = 0;
		etat = ETAT_HOLD;
		return;
	}


	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[182 + etape];
	} else {
		pic = pbk_ennemis[188 + etape];
	}

	colFromPic();

}


void EnnemiSmurfGourmand::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0 && etape < 11)
		etape += 1;

	if (dir == SENS_DROITE) {
		if (!mur_opaque(x - 2, y))
			x -= 2;

		pic = pbk_ennemis[195 + etape];
	} else {
		if (!mur_opaque(x + 2, y))
			x += 2;

		pic = pbk_ennemis[207 + etape];
	}

	if (etape >= 11 && plat(x, y) != 0) {
		a_detruire = true;
		grave(x, y, pic);
	}

}

void EnnemiSmurfGourmand::estTouche(Tir * tir)
{
	static const int dx_giclure_smurf [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_smurf [] = { -15, -15, -15, -15, -15, -15, -15, -15 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_smurf, dy_giclure_smurf);

	if (tir->getGiclureDir() < 4)
		dir = SENS_GAUCHE;
	else
		dir = SENS_DROITE;

	if (etat == ETAT_MEURE)
		sbk_niveau.play(rand() % 4);
}

void EnnemiSmurfGourmand::onHold()
{
	etape += 1;

	if (etape >= 50) {
		etape = 0;
		etat = ETAT_NORMAL;
		return;
	}

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[187];
	} else {
		pic = pbk_ennemis[193];
	}

	colFromPic();
}


void EnnemiSmurfGourmand::onCarbonise()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 6) {
		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[34 + etape];
		else
			pic = pbk_ennemis[40 + etape];
	}
}

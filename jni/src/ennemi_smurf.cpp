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

#include "ennemi_smurf.h"

const int anim_smurf_marche_droite[] = { 0, 1, 2, 3, 4, 3, 2, 1 };
const int anim_smurf_marche_gauche[] = { 5, 6, 7, 8, 9, 8, 7, 6 };

EnnemiSmurf::EnnemiSmurf() : wait_for_jump(0)
{
	pv = 100;
	jump_delay = 50 + rand() % 250;
	dy_saut = -5 ;
	speed = 1 ;
}

void EnnemiSmurf::update()
{
	if (blood != 0)
		blood -= 1;

	switch (etat) {
		case ETAT_AVANCE:
		case ETAT_NORMAL:
			onAvance();
			break;

		case ETAT_TOMBE:
		case ETAT_SAUTE:
			onSaute();
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


void EnnemiSmurf::onAvance()
{
	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		onSaute();
	}

	// Saute de temps en temps
	//
	wait_for_jump += 1;

	if (wait_for_jump > jump_delay) {
		etat = ETAT_SAUTE;
		dy = dy_saut ;
		lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur
		wait_for_jump = 0;
		jump_delay = 50 + rand() % 250;
		/*
				if ( rand() % 10 == 0)
				{
					sbk_niveau.play( 14 + rand() % 1);
				}
		*/
		onSaute();
	}

	// Marche
	//
	if (x - speed < xmin || mur_opaque(x - speed, y))
		dir = SENS_DROITE;
	else if (x + speed > offset + 640 || mur_opaque(x + speed, y))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(speed);
		pic = pbk_ennemis[anime(anim_smurf_marche_droite, 8, 5)];
	} else {
		marche(-speed);
		pic = pbk_ennemis[anime(anim_smurf_marche_gauche, 8, 5)];
	}

	colFromPic();
}


void EnnemiSmurf::onSaute()
{
	int		yp;

	tombe();

	// Et si on arrêtait de tomber ?
	//
	if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
		etat = ETAT_NORMAL;
		dy = 0;
		y = yp;
		onAvance();
		return;
	}


	if (dir == SENS_DROITE) {
		x += speed ;
		pic = pbk_ennemis[10];
	} else {
		x -= speed ;
		pic = pbk_ennemis[11];
	}

	colFromPic();

}


void EnnemiSmurf::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0)
		etape += 1;

	if (etape > 10) {
		a_detruire = true;
		return;
	}

	if (dir == SENS_GAUCHE) {
		if (!mur_opaque(x - speed, y) && plat(x, y) == 0)
			x -= speed;

		pic = pbk_ennemis[23 + etape];
	} else {
		if (!mur_opaque(x + speed, y) && plat(x, y) == 0)
			x += speed;

		pic = pbk_ennemis[12 + etape];
	}
}

void EnnemiSmurf::estTouche(Tir * tir)
{
	static const int dx_giclure_smurf [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_smurf [] = { -15, -15, -15, -15, -15, -15, -15, -15 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_smurf, dy_giclure_smurf);

	if (etat == ETAT_MEURE)
		sbk_niveau.play(4 + rand() % 10);
}


void EnnemiSmurf::onCarbonise()
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




















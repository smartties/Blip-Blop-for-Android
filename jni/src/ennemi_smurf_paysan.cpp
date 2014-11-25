/******************************************************************
*
*
*		--------------------
*		EnnemiSmurfPaysan.h
*		--------------------
*
*		Burn ! Burn ! Burn !
*
*
*		Mortimus / LOADED -   V 0.1 - 22 Octobre 2000
*
*
*
******************************************************************/

#include "ennemi_smurf_paysan.h"

const int smurf_paysan_charge_droite[] = { 156, 157, 158, 159 };
const int smurf_paysan_charge_gauche[] = { 160, 161, 162, 163 };

const int smurf_paysan_decapite_droite[] = { 174, 175, 176, 177 };
const int smurf_paysan_decapite_gauche[] = { 178, 179, 180, 180 };

EnnemiSmurfPaysan::EnnemiSmurfPaysan()
{
	pv = 200 ;
	etat = ETAT_AVANCE ;
	tete_etape = 0 ;
	tete_ss_etape = 0 ;
}

void EnnemiSmurfPaysan::update()
{
	if (blood != 0)
		blood -= 1;

	switch (etat) {
		case ETAT_MEURE:
			onMeure() ;
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance() ;
			break ;
		case ETAT_CARBONISE:
			onCarbonise() ;
			break ;
	}

	updateADetruire();
}

void EnnemiSmurfPaysan::onMeure()
{
	if (tete_etape == 0) {
		x_mort = x ;
		y_mort = y - 25 ;
	}

	if (tete_etape < 5) {
		tete_ss_etape += 1 ;
		tete_ss_etape %= 4 ;

		if (tete_ss_etape == 0)
			tete_etape += 1 ;
	}
}


void EnnemiSmurfPaysan::onAvance()
{
	tombe() ;

	// Marche
	//
	if (mur_opaque(x - SMURF_PAYSAN_SPEED, y))
		dir = SENS_DROITE;
	else if (mur_opaque(x + SMURF_PAYSAN_SPEED, y))
		dir = SENS_GAUCHE;

	if (etat == ETAT_MEURE) {
		if (dir == SENS_DROITE) {
			marche(SMURF_PAYSAN_SPEED);
			pic	= pbk_ennemis[anime(smurf_paysan_decapite_droite, 4, 3)];
		} else {
			marche(-SMURF_PAYSAN_SPEED);
			pic = pbk_ennemis[anime(smurf_paysan_decapite_gauche, 4, 3)];
		}
	} else {
		if (dir == SENS_DROITE) {
			marche(SMURF_PAYSAN_SPEED);
			pic	= pbk_ennemis[anime(smurf_paysan_charge_droite, 4, 3)];
		} else {
			marche(-SMURF_PAYSAN_SPEED);
			pic = pbk_ennemis[anime(smurf_paysan_charge_gauche, 4, 3)];
		}
		colFromPic();
	}
}

void EnnemiSmurfPaysan::onCarbonise()
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

void EnnemiSmurfPaysan::estTouche(Tir * tir)
{
	static const int dx_giclure_smurf_paysan [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_smurf_paysan [] = { -15, -15, -15, -15, -15, -15, -15, -15 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_smurf_paysan, dy_giclure_smurf_paysan);

	if (etat == ETAT_MEURE)
		sbk_misc.play(8 + rand() % 3);
}















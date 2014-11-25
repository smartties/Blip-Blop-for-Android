/******************************************************************
*
*
*		----------------------
*		EnnemiSmurfFarceur.cpp
*		----------------------
*
*		Le poseur de bombes
*
*
*		Mortimus / LOADED -   V 0.1 - 18 Octobre 2000
*
*
*
******************************************************************/

#include "ennemi_smurf_farceur.h"
#include "tir_cadeau.h"

const int anim_smurf_farceur_marche_droite[] = { 46, 47, 48, 49, 50, 49, 48, 47 };
const int anim_smurf_farceur_marche_gauche[] = { 51, 52, 53, 54, 55, 54, 53, 52 };

EnnemiSmurfFarceur::EnnemiSmurfFarceur()
{
	pv = 150 ;
	bomb_delay = 100 + rand() % 400;
	wait_for_bomb = 0 ;
	porte_bomb = true ;
	wait_for_new_bomb = 0 ;
	new_bomb_delay = 50 + rand() % 200 ;
	decalage_y_cadeau = 5 ;
}

void EnnemiSmurfFarceur::update()
{
	if (blood != 0)
		blood -= 1;

	switch (etat) {
		case ETAT_NORMAL :
		case ETAT_AVANCE :
			onAvance() ;
			break ;
		case ETAT_MEURE :
			onMeure() ;
			break ;
		case ETAT_ATTEND :
			onPoseCadeau() ;
			break ;
		case ETAT_DEGAINE :
			onDegaine() ;
			break ;
		case ETAT_CARBONISE :
			onCarbonise() ;
			break ;
	}
	updateADetruire() ;
}

void EnnemiSmurfFarceur::onDegaine()
{
	ss_etape += 1 ;
	ss_etape %= 8 ;

	if (ss_etape == 0)
		etape += 1 ;

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[57 + etape] ;
	else
		pic = pbk_ennemis[62 + etape] ;

	if (etape > 4) {
		etat = ETAT_NORMAL ;
		porte_bomb = true ;
		etape = 0 ;
		ss_etape = 0 ;
		onAvance();
	}
}

void EnnemiSmurfFarceur::onPoseCadeau()
{
	ss_etape += 1 ;
	ss_etape %= 5 ;

	// Le cadeau atterit delicatement sur le sol ...
	if (ss_etape == 0)
		decalage_y_cadeau -= 1 ;

	// Une fois le cadeau posé :
	if (decalage_y_cadeau < 0) {
		// On actualise l'état de l'ennemi
		etat = ETAT_NORMAL ;
		porte_bomb = false ;
		decalage_y_cadeau = 5 ;
		wait_for_new_bomb = 0 ;
		new_bomb_delay = 50 + rand() % 200 ;

		// On crée un objet TirCadeau
		TirCadeau * tir = new TirCadeau() ;
		if (dir == SENS_DROITE)
			tir->x = x + 26 ;
		else
			tir->x = x - 26 ;
		tir->y = y ;
		list_tirs_ennemis.ajoute((void*) tir);

		// et on réinitialise etape et ss_etape
		etape = 0 ;
		ss_etape = 0 ;
	}
}


void EnnemiSmurfFarceur::onAvance()
{
	// Si pas de sol en dessous, on tombe
	tombe() ;

	// Si on porte un cadeau, on le pose au bout d'un moment
	if (porte_bomb) {
		wait_for_bomb += 1;

		if (wait_for_bomb > bomb_delay && plat(x, y) != 0) {
			etat = ETAT_ATTEND ;
			wait_for_bomb = 0 ;
			bomb_delay = 50 + rand() % 250 ;
			etape = 0 ;
			ss_etape = 0 ;
		}
	}
	// Sinon, on sort un cadeau au bout d'un moment
	else if (plat(x, y) != 0) {
		wait_for_new_bomb += 1 ;
		if (wait_for_new_bomb > new_bomb_delay) {
			wait_for_new_bomb = 0 ;
			new_bomb_delay = 50 + rand() % 200 ;
			etat = ETAT_DEGAINE ;
			etape = 0 ;
			ss_etape = 0 ;
		}
	}

	// On marche
	// Si obstacle, on fait demi-tour
	if (x - SMURF_FARCEUR_SPEED < xmin || mur_opaque(x - SMURF_FARCEUR_SPEED, y))
		dir = SENS_DROITE;
	else if (x + SMURF_FARCEUR_SPEED > offset + 640 || mur_opaque(x + SMURF_FARCEUR_SPEED, y))
		dir = SENS_GAUCHE;


	// On avance dans le sens ou on regarde
	if (dir == SENS_DROITE) {
		marche(SMURF_FARCEUR_SPEED);
		if (porte_bomb)
			pic = pbk_ennemis[anime(anim_smurf_farceur_marche_droite, 8, 4)];
		else
			pic = pbk_ennemis[anime(anim_smurf_marche_droite, 8, 4)];
	} else {
		marche(-SMURF_FARCEUR_SPEED);
		if (porte_bomb)
			pic = pbk_ennemis[anime(anim_smurf_farceur_marche_gauche, 8, 4)];
		else
			pic = pbk_ennemis[anime(anim_smurf_marche_gauche, 8, 4)];
	}
	colFromPic() ;
}

void EnnemiSmurfFarceur::onMeure()
{
	tombe();

	// Si on porte un cadeau, alors on meure carbonisé
	if (porte_bomb) {
		etat = ETAT_CARBONISE ;
		porte_bomb = false ;
		TirCadeau * tir = new TirCadeau() ;
		tir->etape = 20 ;
		tir->y = y - 5 ;
		if (dir == SENS_DROITE) {
			tir->x = x + 26 ;
		} else {
			tir->x = x - 26 ;
		}
		list_tirs_ennemis.ajoute((void*) tir);
		onCarbonise() ;
	} else {
		ss_etape += 1;
		ss_etape %= 4;

		if (ss_etape == 0)
			etape += 1;

		if (etape > 10) {
			a_detruire = true;
			return;
		}

		if (dir == SENS_GAUCHE) {
			if (!mur_opaque(x - SMURF_FARCEUR_SPEED, y) && plat(x, y) == 0)
				x -= SMURF_FARCEUR_SPEED;

			pic = pbk_ennemis[23 + etape];
		} else {
			if (!mur_opaque(x + SMURF_FARCEUR_SPEED, y) && plat(x, y) == 0)
				x += SMURF_FARCEUR_SPEED;

			pic = pbk_ennemis[12 + etape];
		}
	}
}

void EnnemiSmurfFarceur::onCarbonise()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 11) {
		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[78 + etape];
		else
			pic = pbk_ennemis[67 + etape];
	}
}

void EnnemiSmurfFarceur::estTouche(Tir * tir)
{
	static const int dx_giclure_smurf_farceur [] = { 0, 0, 6, 0, 0, 0, -6, 0 };
	static const int dy_giclure_smurf_farceur [] = { -15, -15, -15, -15, -15, -15, -15, -15 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_smurf_farceur, dy_giclure_smurf_farceur);

	if (etat == ETAT_MEURE) {
		if (porte_bomb)
			sbk_misc.play(11);
		else
			sbk_niveau.play(4 + rand() % 10);
	}
}
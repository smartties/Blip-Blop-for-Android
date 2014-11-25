
#include "ennemi_grand_smurf.h"

#define ATT_ATATA	0
#define ATT_BOOM	1

EnnemiGrandSmurf::EnnemiGrandSmurf() : wait_change_cible(0), dx(0), cible(NULL), attak_wanted(ATT_BOOM)
{
	pv = 5000;
}

void EnnemiGrandSmurf::updateCible()
{
	if (wait_change_cible > 0 && cible != NULL && !cible->a_detruire) {
		wait_change_cible -= 1;
	} else {
		if (tete_turc != NULL && !tete_turc->a_detruire) {
			cible = tete_turc;
			wait_change_cible = 200 + rand() % 100;
		} else {
			cible = NULL;
		}
	}
}


void EnnemiGrandSmurf::updateChoice()
{
	if (cible == NULL)
		return;

	int ddx = cible->x - x;

	if (ddx < 0)
		dir = SENS_GAUCHE;
	else
		dir = SENS_DROITE;

	if (attak_wanted == ATT_ATATA) {
		if (ddx > -100 && ddx < 100) {
			etape = ss_etape = 0;
			etat = ETAT_TIRE;
		} else if (ddx < 0)
			dx = -3;
		else
			dx = 3;
	} else {
		if (ddx < -400 || ddx > 400 || x <= offset + 60 || x >= offset + 580)
			attak_wanted = ATT_ATATA;
		else if (ddx < 0)
			dx = 3;
		else
			dx = -3;
	}
}

void EnnemiGrandSmurf::update()
{
	if (blood != 0)
		blood -= 1;

	updateCible();

	switch (etat) {
		case ETAT_NORMAL :
		case ETAT_AVANCE :
			updateChoice();
			onAvance() ;
			break ;

		case ETAT_TIRE:
			switch (attak_wanted) {
				case ATT_ATATA:
					onAtata();
					break;
			}
			break;

		case ETAT_CARBONISE :
		case ETAT_MEURE :
//			onMeure() ;
			break ;
	}
}

void EnnemiGrandSmurf::onAtata()
{
	ss_etape += 1;
	ss_etape %= 3;

	if (ss_etape == 0)
		etape += 1;

	if (etape > 50) {
		etape = ss_etape = 0;
		etat = ETAT_NORMAL;
		attak_wanted = rand() % 2;
	} else {
		if (dir == SENS_GAUCHE) {
			pic = pbk_ennemis[3 + (etape % 3)];
			dx = -1;
		} else {
			pic = pbk_ennemis[(etape % 3)];
			dx = 1;
		}

		int x2 = x + dx;

		if (!mur_opaque(x2, y) && x2 > offset + 50 && x2 < offset + 600)
			x = x2;
	}
}

void EnnemiGrandSmurf::onAvance()
{
	int x2 = x + dx;

	if (!mur_opaque(x2, y) && x2 > offset + 50 && x2 < offset + 600)
		x = x2;

	if (dx <= 0) {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[9];
		else
			pic = pbk_ennemis[37];
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[40];
		else
			pic = pbk_ennemis[6];
	}
}

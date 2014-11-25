
#include "tir_colonne_chaman.h"

TirColonneChaman::TirColonneChaman() : etat(0)
{
	duree_vie = 250 + rand() % 100;
}


void TirColonneChaman::update()
{
	deplace();

	ss_etape += 1;
	ss_etape %= 6;


	switch (etat) {
		case 0:

			if (ss_etape == 0) {
				etape += 1;

				if (etape > 4) {
					etat = 1;
					return;
				}
			}

			pic = pbk_ennemis[398 - etape];

			break;

		case 1:

			if (ss_etape == 0) {
				etape += 1;
				etape %= 6;
			}

			duree_vie -= 1;

			if (duree_vie <= 0) {
				etat = 2;
				etape = ss_etape = 0;
				return;
			}

			pic = pbk_ennemis[399 + etape];

			break;

		case 2:

			if (ss_etape == 0) {
				etape += 1;

				if (etape > 4) {
					a_detruire = true;
					return;
				}
			}

			pic = pbk_ennemis[394 + etape];

			break;
	}

	colFromPic();
	updateADetruire();
}


void TirColonneChaman::deplace()
{
	static const int SPEED = 4;

	tombe();

	// Marche
	//
	if (mur_opaque(x - SPEED, y) || x + SPEED < offset/*|| (plat( x-SPEED, y) == 0 && plat( x-SPEED, y+5) == 0)*/)
		dir = SENS_DROITE;
	else if (x + SPEED > offset + 640 /*|| mur_opaque( x+SPEED, y)  || (plat( x+SPEED, y) == 0 && plat( x+SPEED, y+5) == 0)*/)
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(SPEED);
	} else {
		marche(-SPEED);
	}
}

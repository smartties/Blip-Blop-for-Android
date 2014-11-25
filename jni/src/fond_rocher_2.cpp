/******************************************************************
*
*
*		---------------------------
*		    FondRocher2.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/


#include "fond_rocher_2.h"

const int rocher2_levitation[] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0};
const int rocher2_animation[] = {57, 58, 58, 59, 59, 59, 60, 60, 60, 60, 60, 59, 59, 59, 58, 58, 57, 61, 61, 62, 62, 62, 63, 63, 63, 63, 63, 62, 62, 62, 61, 61};


FondRocher2::FondRocher2(): etape_levitation(0), ss_etape_levitation(0)
{
	pic = pbk_niveau[38];
	dy = 0;
}

void FondRocher2::update()
{
	pic = pbk_niveau[anime(rocher2_animation, 32, 4)];


	ss_etape_levitation++;
	ss_etape_levitation %= 6;
	if (ss_etape_levitation == 0) {
		etape_levitation++;
		if (etape_levitation == 18) {
			etape_levitation = 0;
		}
	}

	int		xtmp;

	// Fait des allers/retour
	//

	/*if ( y <= 96)
		dy = 1;
	else if ( y >= 387)
		dy = -1;*/

	// Si un joueur est sur la plateforme, on le déplace
	//
	Sprite * joueur;

	list_joueurs.start();

	while (!list_joueurs.fin()) {
		joueur = (Sprite*) list_joueurs.info();

		xtmp = joueur->x;

		if (xtmp >= x - 45 && xtmp < x + pic->xSize() - 45 && plat(xtmp, joueur->y) == y - 25) {
			if (etape_levitation <= 9) {
				joueur->y += rocher2_levitation[etape_levitation];
			} else {
				joueur->y -= rocher2_levitation[etape_levitation - 9];
			}
		}
		//	joueur->y += dy;

		list_joueurs.suivant();
	}

	// Déplace la plateforme
	//
	//y += dy;

	if (etape_levitation <= 9) {
		y += rocher2_levitation[etape_levitation];
	} else {
		y -= rocher2_levitation[etape_levitation - 9];
	}

	for (int i = x - 45; i < x + pic->xSize() - 45; i++)
		y_plat[4][i] = y - 25;

	colFromPic();

	/*if ( x < offset-400)
		a_detruire = true;*/
}
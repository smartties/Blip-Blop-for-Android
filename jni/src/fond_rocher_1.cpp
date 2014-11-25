/******************************************************************
*
*
*		---------------------------
*		    FondRocher1.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/


#include "fond_rocher_1.h"

const int monolite_levitation[] = {0, 0, 1, 1, 1, 1, 2, 2, 1, 1, 1, 0, 0, 0};
const int monolite_animation[] = {50, 51, 51, 52, 52, 52, 53, 53, 53, 53, 53, 52, 52, 52, 51, 51, 50, 54, 54, 55, 55, 55, 56, 56, 56, 56, 56, 55, 55, 55, 54, 54};


FondRocher1::FondRocher1(): etape_levitation(0), ss_etape_levitation(0)
{
	pic = pbk_niveau[31];
	dy = 0;
}

void FondRocher1::update()
{
	pic = pbk_niveau[anime(monolite_animation, 32, 3)];


	ss_etape_levitation++;
	ss_etape_levitation %= 4;
	if (ss_etape_levitation == 0) {
		etape_levitation++;
		if (etape_levitation == 26) {
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

		if (xtmp >= x - 45 && xtmp < x + pic->xSize() - 45 && plat(xtmp, joueur->y) == y - 30) {
			if (etape_levitation <= 13) {
				joueur->y += monolite_levitation[etape_levitation];
			} else {
				joueur->y -= monolite_levitation[etape_levitation - 13];
			}
		}
		//	joueur->y += dy;

		list_joueurs.suivant();
	}

	// Déplace la plateforme
	//
	//y += dy;
	if (etape_levitation <= 13) {
		y += monolite_levitation[etape_levitation];
	} else {
		y -= monolite_levitation[etape_levitation - 13];
	}

	for (int i = x - 45; i < x + pic->xSize() - 45; i++)
		y_plat[4][i] = y - 30;

	colFromPic();

	/*if ( x < offset-400)
		a_detruire = true;*/
}
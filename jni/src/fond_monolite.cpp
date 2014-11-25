/******************************************************************
*
*
*		---------------------------
*		    FondMonolite.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/


#include "fond_monolite.h"

const int monolite_levitation[] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0};
const int monolite_animation[] = {41, 42, 43, 43, 44, 44, 44, 45, 45, 45, 45, 45, 44, 44, 44, 43, 43, 42, 41, 46, 47, 47, 48, 48, 48, 49, 49, 49, 49, 49, 48, 48, 48, 47, 47, 46};


FondMonolite::FondMonolite(): etape_levitation(0), ss_etape_levitation(0)
{
	pic = pbk_niveau[22];
	dy = 0;
}

void FondMonolite::update()
{
	pic = pbk_niveau[anime(monolite_animation, 36, 3)];
	//anime36
	ss_etape_levitation++;
	ss_etape_levitation %= 4;
	if (ss_etape_levitation == 0) {
		etape_levitation++;
		if (etape_levitation == 44) {
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
	Sprite * ennemis;

	list_joueurs.start();

	while (!list_joueurs.fin()) {
		joueur = (Sprite*) list_joueurs.info();

		xtmp = joueur->x;

		if (xtmp >= x - 138 && xtmp < x + pic->xSize() - 118 && plat(xtmp, joueur->y) == y - 20) {
			if (etape_levitation <= 22) {
				joueur->y += monolite_levitation[etape_levitation];
			} else {
				joueur->y -= monolite_levitation[etape_levitation - 22];
			}
		}
		//	joueur->y += dy;

		list_joueurs.suivant();
	}


	list_ennemis.start();

	while (!list_ennemis.fin()) {
		ennemis = (Sprite*) list_ennemis.info();

		xtmp = ennemis->x;

		if (xtmp >= x - 138 && xtmp < x + pic->xSize() - 118 && plat(xtmp, ennemis->y) == y - 20) {
			if (etape_levitation <= 22) {
				ennemis->y += monolite_levitation[etape_levitation];
			} else {
				ennemis->y -= monolite_levitation[etape_levitation - 22];
			}
		}
		//	joueur->y += dy;

		list_ennemis.suivant();
	}

	// Déplace la plateforme
	//
	//y += dy;
	if (etape_levitation <= 22) {
		y += monolite_levitation[etape_levitation];
	} else {
		y -= monolite_levitation[etape_levitation - 22];
	}

	for (int i = x - 118; i < x + pic->xSize() - 138; i++)
		y_plat[4][i] = y - 20;

	colFromPic();

	/*if ( x < offset-400)
		a_detruire = true;*/
}
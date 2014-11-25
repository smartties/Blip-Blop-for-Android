
#include "fond_poke_ascenseur_2.h"


FondPokeAscenceur2::FondPokeAscenceur2()
{
	pic = pbk_niveau[51];
	dy = 1;
}

void FondPokeAscenceur2::update()
{
	if (game_flag[2] > 1) {
		int		xtmp;

		// Fait des allers/retour
		//
		if (y <= 96)
			dy = 1;
		else if (y >= 387)
			dy = -1;

		// Si un joueur est sur la plateforme, on le déplace
		//
		Sprite * joueur;

		list_joueurs.start();

		while (!list_joueurs.fin()) {
			joueur = (Sprite*) list_joueurs.info();

			xtmp = joueur->x;

			if (xtmp > x && xtmp < x + pic->xSize() && plat(xtmp, joueur->y) == y + 20)
				joueur->y += dy;

			list_joueurs.suivant();
		}

		// Déplace la plateforme
		//
		y += dy;

		for (int i = x; i < x + pic->xSize(); i++)
			y_plat[4][i] = y + 20;

		colFromPic();

		if (x < offset - 400)
			a_detruire = true;
	} else {
		y = -60;
	}
}
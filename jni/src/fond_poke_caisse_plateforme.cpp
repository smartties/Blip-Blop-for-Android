/******************************************************************
*
*
*		---------------------------
*		    FondPokeCaissePlateforme.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 21 Janvier 2001
*
*
*
******************************************************************/


#include "fond_poke_caisse_plateforme.h"

FondPokeCaissePlateforme::FondPokeCaissePlateforme(int niveau_y): y_cible(niveau_y)
{
	pic = pbk_niveau[87];
}

void FondPokeCaissePlateforme::update()
{

	if (y  < y_cible - 50) {
		y += 5;
	} else if (y  < y_cible - 40) {
		y += 4;
	} else if (y  < y_cible - 30) {
		y += 3;
	} else if (y  < y_cible - 20) {
		y += 2;
	} else if (y  < y_cible - 10) {
		y += 1;
	}
	/*else
	{
		grave(x ,y ,pic);
		a_detruire = true;
	}*/



	int i;

	if (y + 28 != 0) {
		for (i = x - 90 ; i < x + 140 ; i++) {
			y_plat[4][i] = y + 28;
		}
	} else {
		for (i = x - 90 ; i < x + 140 ; i++) {
			y_plat[4][i] = y + 29;
		}
	}

};
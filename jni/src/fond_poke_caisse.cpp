/******************************************************************
*
*
*		---------------------------
*		    FondPokeCaisse.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 21 Janvier 2001
*
*
*
******************************************************************/

#include "sprite.h"
#include "fond_poke_caisse.h"

FondPokeCaisse::FondPokeCaisse()
{
	pic = pbk_niveau[117];
}

void FondPokeCaisse::update()
{

	int		yp;

	tombe();

	// Et si la caisse touche le sol ?
	//
	if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
		y = yp;
		grave(x, y - 10, pic);

		int i;

		for (i = x - 90 ; i < x + 140 ; i++) {
			y_plat[4][i] = y - 125;
		}

		colFromPic();

		a_detruire = true;
	}
};
/******************************************************************
*
*
*		---------------------------
*		    FondPokeCaissePlateforme2.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 21 Janvier 2001
*
*
*
******************************************************************/


#include "fond_poke_caisse_plateforme_2.h"
#include "ben_maths.h"

FondPokeCaissePlateforme2::FondPokeCaissePlateforme2()
{
	pic = pbk_niveau[87];
}

void FondPokeCaissePlateforme2::update()
{
	if (y < 20) { //-200
		y += 3;
	} else {
		etape += 2;
		etape %= 360;

		y = 80 - ((60 * (bCos[etape])) >> COSINUS);
		/*
				if (etape < 80)
				{
					y += 3;
				}
				else if (etape < 100)
				{
					y += 2 ;
				}
				else if (etape < 120)
				{
					y += 1;
				}
				else if (etape < 130)
				{
					//x += 2;
				}
				else if (etape < 150)
				{
					y -= 1;
				}
				else if (etape < 170)
				{
					y -= 2;
				}
				else if (etape < 250)
				{
					y -= 2;
				}

				else
				{
					etape = 0;
				}

		*/

		/*int i;
		for (i = 1920; i < x - 90 ; i++)
		{
			y_plat[3][i] = 0;
		}*/

		if (y + 28 != 0) {
			for (int i = x - 90 ; i < x + 140 ; i++) {
				y_plat[3][i] = y + 28;
			}
		} else {
			for (int i = x - 90 ; i < x + 140 ; i++) {
				y_plat[3][i] = y + 29;
			}
		}

		/*for (i = x + 140; i < 2560 ; i++)
		{
			y_plat[3][i] = 0;
		}*/
	}
};
/******************************************************************
*
*
*		---------------------------
*		    FondPokeLevel2.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 16 Fevrier 2001
*
*
*
******************************************************************/

#include "fond_poke_level_3.h"
#include "ben_debug.h"

const int anim_clignotement [] = {2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 0, 0};

FondPokeLevel3::FondPokeLevel3(): etape_E1(0), etape_V(0), etape_E2(0), etape_L2(0)
{
	pic = pbk_niveau[142];
}

void FondPokeLevel3::update()
{
	etape ++;
	etape %= 460;

	etape_E1 ++;
	etape_E1 %= 120;

	etape_V ++;
	etape_V %= 180;

	etape_E2 ++;
	etape_E2 %= 290;

	etape_L2 ++;
	etape_L2 %= 190;

	if (etape < 57) {
		pic = pbk_niveau[PBK_3 + anim_clignotement[etape]];
	}
}

void FondPokeLevel3::affiche()
{
	Sprite::affiche();

	if (etape_E1 < 57) {
		draw(x + 12, y - 19, pbk_niveau[PBK_E + anim_clignotement[etape_E1]]);
	}
	if (etape_V < 57) {
		draw(x + 23, y - 19, pbk_niveau[PBK_V + anim_clignotement[etape_V]]);
	}
	if (etape_E2 < 57) {
		draw(x + 36, y - 19, pbk_niveau[PBK_E + anim_clignotement[etape_E2]]);
	}
	if (etape_L2 < 57) {
		draw(x + 47, y - 19, pbk_niveau[PBK_L + anim_clignotement[etape_L2]]);
	}
}
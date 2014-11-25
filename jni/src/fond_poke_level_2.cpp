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

#include "fond_poke_level_2.h"
#include "ben_debug.h"

const int anim_clignotement [] = {2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 0, 0};
//const int anim_clignotement[] = {0 ,2, 2, 2, 1, 2, 2};

FondPokeLevel2::FondPokeLevel2(): etape_L1(0), etape_E1(0), etape_V(0), etape_E2(0), etape_L2(0)
{
	pic = pbk_niveau[130];
}

void FondPokeLevel2::update()
{
	etape ++;
	etape %= 560;

	etape_L1 ++;
	etape_L1 %= 155;

	etape_E1 ++;
	etape_E1 %= 300;

	etape_V ++;
	etape_V %= 210;

	etape_E2 ++;
	etape_E2 %= 190;

	etape_L2 ++;
	etape_L2 %= 380;

	if (etape < 57) {
		pic = pbk_niveau[PBK_2 + anim_clignotement[etape]];
	}
}

void FondPokeLevel2::affiche()
{
	Sprite::affiche();

	if (etape_L1 < 57) {
		//debug <<"etape_L1: "<<etape_L1<<endl;
		draw(x, y - 19, pbk_niveau[PBK_L + anim_clignotement[etape_L1]]);
	}
	if (etape_E1 < 57) {
		//debug <<"etape_E1: "<<etape_E1<<endl;
		draw(x + 12, y - 19, pbk_niveau[PBK_E + anim_clignotement[etape_E1]]);
	}
	if (etape_V < 57) {
		//debug <<"etape_V: "<<etape_V<<endl;
		draw(x + 23, y - 19, pbk_niveau[PBK_V + anim_clignotement[etape_V]]);
	}
	if (etape_E2 < 57) {
		//debug <<"etape_E2: "<<etape_E2<<endl;
		draw(x + 36, y - 19, pbk_niveau[PBK_E + anim_clignotement[etape_E2]]);
	}
	if (etape_L2 < 57) {
		//debug <<"etape_L2: "<<etape_L2<<endl;
		draw(x + 47, y - 19, pbk_niveau[PBK_L + anim_clignotement[etape_L2]]);
	}
}
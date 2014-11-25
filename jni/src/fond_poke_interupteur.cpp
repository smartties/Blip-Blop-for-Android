/******************************************************************
*
*
*		---------------------------
*		    FondPokeInterupteur.cpp
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
#include "fond_poke_interupteur.h"
#include "enemy.h"
#include "texte_cool.h"

const int anim_interupteur_on[] = {84 , 85, 86, 84};
const int anim_interupteur_off[] = {81 , 82, 83, 82};

FondPokeInterupteur::FondPokeInterupteur(): etat(false), wait_msg(false), ascenc_msg(false), bravo(false)
{
}

void FondPokeInterupteur::update()
{
	ss_etape ++;
	ss_etape %= 8;

	if (ss_etape == 0) {
		etape ++;
		etape %= 4;
	}

	if (etat) {
		pic = pbk_niveau[anim_interupteur_on[etape]];
	} else {
		if (tete_turc != NULL) {
			if ((tete_turc->x > x - 10) && (tete_turc->x < x + 33) && (tete_turc->y > y - 10) && (tete_turc->y < y + 51)) {
				game_flag[2] ++;
				etat = true;
				sbk_niveau.play(2);
			}
		}
		pic = pbk_niveau[anim_interupteur_off[etape]];
	}


	if (x < offset - 100)
		a_detruire = true;

	if (game_flag[0] == 0) {
		if (wait_msg || game_flag[2] == 0) {
			game_flag[7] = 1;
		} else {
			game_flag[7] = 0;
		}
	}

	if (!wait_msg && game_flag[2] == 0 && game_flag[6] <= 80) {
		wait_msg = true;
		TexteCool * txt = new TexteCool();
		txt->ntxt = 104;
		list_txt_cool.ajoute((void*) txt);
	}

	if (!ascenc_msg && wait_msg && game_flag[2] == 1) {
		ascenc_msg = true;
		TexteCool * txt = new TexteCool();
		txt->ntxt = 105;
		list_txt_cool.ajoute((void*) txt);
		txt = new TexteCool();
		txt->ntxt = 106;
		list_txt_cool.ajoute((void*) txt);
	}

	if (!bravo && ascenc_msg && game_flag[0] == 1) {
		bravo = true;
		TexteCool * txt = new TexteCool();
		txt->ntxt = 107;
		list_txt_cool.ajoute((void*) txt);
	}
};

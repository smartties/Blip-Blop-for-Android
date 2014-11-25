/******************************************************************
*
*
*		---------------------------
*		    FondBombe.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 17 Janvier 2001
*
*
*
******************************************************************/

#include "globals.h"
#include "fond_bombe.h"
#include "enemy.h"
#include "bonus_fusil.h"
#include "bonus_pm.h"
#include "bonus_vache.h"

int save_time = 0;

const int anim_warning[] = { 118, 118, 118, 118, 118, 119, 119, 120, 119, 119};
const int anim_nuke[] = {53, 53, 53, 54, 54, 54, 55, 55, 56, 57, 58, 59, 59, 60, 60, 60, 61, 61, 61, 61, 60, 60, 60, 59, 59, 58, 57, 56, 55, 55, 54, 54, 54, 53, 53};

FondBombe::FondBombe(): etape_compteur(0), etape_warning(0), ss_etape_warning(0), etape_nuke(0), ss_etape_nuke(0), armed(true)
{
	pic = pbk_niveau[52];
}

void FondBombe::update()
{
	if (armed) {
		if (tete_turc != NULL) {
			if ((tete_turc->x > x - 50) && (tete_turc->x < x + 50) && (tete_turc->y > y - 10) && (tete_turc->y < y + 51)) {
				game_flag[0] ++;
				armed = false;
				Bonus * bonus;
				switch (game_flag[0]) {
					case 1:
						bonus = new BonusFusil();
						break;

					case 2:
						bonus = new BonusPM();
						break;

					case 3:
						bonus = new BonusVache();
						save_time = game_flag[FLAG_TIMER];
						game_flag[FLAG_GEN_OFF] = 1;
						break;
				}
				bonus->x = x;
				bonus->y = 0;
				list_bonus.ajoute((void*) bonus);

				sbk_niveau.play(1);
			}
		}
		ss_etape ++;
		ss_etape %= 4;
		if (ss_etape == 0) {
			etape ++;
			etape %= 9;
		}


		ss_etape_nuke ++;
		ss_etape_nuke %= 3;

		if (ss_etape_nuke == 0) {
			etape_nuke ++;
			etape_nuke %= 35;
		}


		etape_compteur += 2;
		if (etape_compteur >= 100) {
			etape_compteur = 0;
		}


		if (game_flag[FLAG_TIMER] < 40) {
			ss_etape_warning ++;
			if (game_flag[FLAG_TIMER] / 3 > 0) {
				ss_etape_warning %= game_flag[FLAG_TIMER] / 3;
			} else {
				ss_etape_warning = 0;
			}

			if (ss_etape_warning == 0) {
				etape_warning ++;
				etape_warning %= 10;
			}
		}
		/*else if (game_flag[FLAG_TIMER] <40)
		{

			ss_etape_warning ++;
			ss_etape_warning %= 5;


			if ( ss_etape_warning == 0)
			{
				etape_warning ++;
				etape_warning %= 8;
			}
		}*/
		seconde  = game_flag[FLAG_TIMER];
		centieme = etape_compteur;
	} else if (game_flag[0] == 3) {
		game_flag[FLAG_TIMER] = save_time;
	}

}

void FondBombe::affiche()
{
	Sprite::affiche();
	if (armed) {
		draw(x, y, pbk_niveau[121 + etape]);


		draw(x, y, pbk_niveau[anim_nuke[etape_nuke]]);


		if (game_flag[FLAG_TIMER] >= 100) {
			draw(x + 6, y - 27, pbk_niveau[80]);
			draw(x + 11, y - 27, pbk_niveau[80]);
			draw(x + 16, y - 27, pbk_niveau[80]);
			draw(x + 21, y - 27, pbk_niveau[80]);
		} else {
			draw(x + 6, y - 27, pbk_niveau[71 + game_flag[FLAG_TIMER] / 10]);
			draw(x + 11, y - 27, pbk_niveau[71 + game_flag[FLAG_TIMER] % 10]);
			draw(x + 16, y - 27, pbk_niveau[80 - etape_compteur / 10]);
			draw(x + 21, y - 27, pbk_niveau[80 - etape_compteur % 10]);
		}

		if (game_flag[FLAG_TIMER] < 40) {
			draw(x, y - 35, pbk_niveau[anim_warning[etape_warning]]);
		}
		/*else if (game_flag[FLAG_TIMER] < 40)
		{
			draw(x, y -35, pbk_niveau[anim_warning[etape_warning]]);
		}*/
		else if (game_flag[FLAG_TIMER] < 60) {
			draw(x , y - 35, pbk_niveau[118]);
		}
	} else {
		draw(x, y, pbk_niveau[anim_nuke[etape_nuke]]);
		draw(x + 6, y - 27, pbk_niveau[71 + seconde / 10]);
		draw(x + 11, y - 27, pbk_niveau[71 + seconde % 10]);
		draw(x + 16, y - 27, pbk_niveau[80 - centieme / 10]);
		draw(x + 21, y - 27, pbk_niveau[80 - centieme % 10]);
	}
}

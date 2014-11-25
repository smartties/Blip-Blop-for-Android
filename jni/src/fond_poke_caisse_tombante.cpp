/******************************************************************
*
*
*		---------------------------
*		    FondPokeCaisseTombante.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 21 Janvier 2001
*
*
*
******************************************************************/

#include "fond_poke_caisse_tombante.h"
#include "fond_poke_caisse.h"
#include "fond_poke_caisse_plateforme.h"
#include "fond_poke_caisse_plateforme_2.h"

const int anim_lock[] = {88 , 89, 90, 91, 92, 93, 92, 91, 90, 89};

FondPokeCaisseTombante::FondPokeCaisseTombante()
{
	pic = pbk_niveau[87];
}

void FondPokeCaisseTombante::update()
{
	if (game_flag[2] > 2) {
		if ((y < 100) && (etape <= UNLOCK_DELAY)) {
			y += 2;
		} else {
			ss_etape ++;
			ss_etape %= 5;
			if (ss_etape == 0) {
				etape ++;
			}

			if ((etape == 0) && (ss_etape == 1)) {
				//les 2 autres en haut a droite de l'ecran...
				FondPokeCaissePlateforme * s2 = new FondPokeCaissePlateforme(180);
				s2->x = x - 250;
				s2->y = -150;

				list_plateformes_mobiles.ajoute((void*) s2);


				s2 = new FondPokeCaissePlateforme(180);
				s2->x = x - 470;
				s2->y = - 150;

				list_plateformes_mobiles.ajoute((void*) s2);
			}

			if (etape > UNLOCK_DELAY + 4) {
				y -= 3;
				if (y < -160) {
					a_detruire = true;
				}

				if ((etape == UNLOCK_DELAY + 5) && (ss_etape == 0)) {
					pic = pbk_niveau[116];

					FondPokeCaisse * s = new FondPokeCaisse();
					s->x = x;
					s->y = y + 150;

					list_fonds_animes.ajoute((void*) s);

					//plateforme qui bouge...
					FondPokeCaissePlateforme2 * s3 = new FondPokeCaissePlateforme2();
					s3->x = x;
					s3->y = -150;

					list_plateformes_mobiles.ajoute((void*) s3);
				}
			}
		}
	} else {
		y = -160;
	}
}

void FondPokeCaisseTombante::affiche()
{
	Sprite::affiche();
	if (etape > UNLOCK_DELAY + 4) {
		draw(x, y, pbk_niveau[94]);
		draw(x , y + 63, pbk_niveau[115]);
	} else if (etape > UNLOCK_DELAY - 1) {
		draw(x , y + 63, pbk_niveau[111 + etape - UNLOCK_DELAY]);
	} else if (etape > 0) {
		draw(x, y, pbk_niveau[anim_lock[etape % 10]]);
		//draw(x, y, pbk_niveau[88 + etape % 6]);
		draw(x, y + 63, pbk_niveau[95 + etape % 16]);
	}
}
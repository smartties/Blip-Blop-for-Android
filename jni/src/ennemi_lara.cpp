/******************************************************************
*
*
*		-----------------------
*		    EnnemiLara.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.3 - 15 Fevrier 2001
*
*
*
******************************************************************/


#include "ben_debug.h"
#include "ennemi_lara.h"
#include "tir_epine.h"
#include "ennemi_pic.h"
#include "ennemi_poid.h"
#include "ennemi_tete___rayman.h"
#include <math.h>



const int anim_lara_bouton[] = {123, 123, 124, 125, 126, 126, 126, 125, 124, 123};
const int anim_lara_degaine[] = {127, 127, 127, 128, 128, 129, 130, 130, 131, 131, 131};

EnnemiLara::EnnemiLara(): numero_image_buste(127), wait_for_attack(0), pics(0), tete_rayman(0)
{
	pv = 15000;
	pic = pbk_ennemis[162];
}

void EnnemiLara::update()
{
	if (blood > 0)
		blood -= 1;

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
		case ETAT_SAUTE:
		case ETAT_TOMBE:
			onAvance();
			break;

		case ETAT_CARBONISE:
		case ETAT_MEURE:
			onMeure();
			break;


		case ETAT_TIRE:
			onTire();
			break;
	}

	//updateADetruire();
}

void EnnemiLara::onAvance()
{
	if (!pics) {
		Ennemi* pic;
		int i, j;
		for (i = 2; i >= 0; i--) {
			for (j = 0; j < 6; j++) {
				pic = new EnnemiPic();

				if (i != 1) {
					pic->x = 515 + j * 65 - i * 20;
				} else {
					pic->x = 547 + j * 65 - i * 20;
				}

				switch (i) {
					case 0:
						pic->y = 429;
						break;
					case 1:
						pic->y = 449;
						break;

					case 2:
						pic->y = 471;
						break;
				}

				pic->dir = SENS_GAUCHE;
				list_ennemis.ajoute((void*) pic);
//				nb_ennemis_created += 1;
			}
		}

		/*pic = new EnnemiPoid();
		pic->x = 565;
		pic->y = -50;
		pic->dir = SENS_GAUCHE;
		pic->etat = ETAT_AVANCE;
		list_ennemis.ajoute( (void*) pic);

		nb_ennemis_created += 1;*/

		pics = true;
	}
	if (game_flag[0] == 1) {
		//cree la tete de rayman et attendre

		if (!tete_rayman) {
			if (tete_turc != NULL) {
				Ennemi * tete = new EnnemiTeteRayman();
				tete->x = tete_turc->x + 10;
				tete->y = tete_turc->y - 30;
				tete->dy = -8;
				tete->dir = SENS_GAUCHE;
				list_ennemis.ajoute((void*) tete);
				tete_rayman = true;
			}
		}
	} else if (game_flag[0] == 2) {
		ss_etape ++;
		ss_etape %= 6;
		if (ss_etape == 0) {
			etape ++;
			if (etape > 9) {
				game_flag[0] = 3;
				etape = 0;
				/*
								mbk_niveau.stop();
								mbk_niveau.play( 0);
				*/
				game_flag[FLAG_TIMER] = 180;
			} else {
				numero_image_buste = anim_lara_bouton[etape];
			}
		}
	} else if (game_flag[0] == 3) {
		ss_etape ++;
		ss_etape %= 6;
		if (ss_etape == 0) {
			etape ++;
			if (etape > 10) {
				game_flag[0] = 4;
				etape = 0;
			} else {
				numero_image_buste = anim_lara_degaine[etape];
			}
		}
	} else if (game_flag[0] == 4) {

		wait_for_attack++;
		if ((wait_for_attack > ATTACK_DELAY) && (tete_turc != NULL)) {
			int dif_y = y - 102 - tete_turc->y;
			int dif_x = x - tete_turc->x;

			if (dif_y != 0) {
				int pente = (dif_x * 10) / dif_y;
				if (pente > 40) {

					int dx = tete_turc->x + 20 - x + 60;
					int dy = tete_turc->y - y + 144;

					int dist = sqrt((dx * dx) + (dy * dy));

					dx = (dx * LARA_TIR_SPEED) / dist;
					dy = (dy * LARA_TIR_SPEED) / dist;


					TirEpine * tir;
					tir  = new TirEpine(163, dx, dy + rand() % 3 - 1);
					tir->x = x - 60;
					tir->y = y - 144;
					tir->traverse = true;
					list_tirs_ennemis.ajoute((void*) tir);

					numero_image_buste = 150;//127
					ss_etape = 0;
					etape = 1;
					etat = ETAT_TIRE;
					onTire();
					return;
				} else if (pente > 30) {
					numero_image_buste = 132;//156
					int dx = tete_turc->x + 20 - x + 58;
					int dy = tete_turc->y - y + 154;

					int dist = sqrt((dx * dx) + (dy * dy));

					dx = (dx * LARA_TIR_SPEED) / dist;
					dy = (dy * LARA_TIR_SPEED) / dist;


					TirEpine * tir;

					tir  = new TirEpine(163, dx, dy + rand() % 3 - 1);

					tir->x = x - 58;
					tir->y = y - 154;
					tir->traverse = true;
					list_tirs_ennemis.ajoute((void*) tir);
					ss_etape = 0;
					etape = 1;
					etat = ETAT_TIRE;
					onTire();
					return;

				} else if (pente > 20) {
					int dx = tete_turc->x + 20 - x + 57;
					int dy = tete_turc->y - y + 165;

					int dist = sqrt((dx * dx) + (dy * dy));

					dx = (dx * LARA_TIR_SPEED) / dist;
					dy = (dy * LARA_TIR_SPEED) / dist;


					TirEpine * tir;

					tir  = new TirEpine(163, dx, dy + rand() % 3 - 1);

					tir->x = x - 57;
					tir->y = y - 165;
					tir->traverse = true;
					list_tirs_ennemis.ajoute((void*) tir);
					numero_image_buste = 138;//150
					ss_etape = 0;
					etape = 1;
					etat = ETAT_TIRE;
					onTire();
					return;
				} else if (pente > 5) {
					numero_image_buste = 144;//132
					int dx = tete_turc->x + 20 - x + 53;
					int dy = tete_turc->y - y + 175;

					int dist = sqrt((dx * dx) + (dy * dy));

					dx = (dx * LARA_TIR_SPEED) / dist;
					dy = (dy * LARA_TIR_SPEED) / dist;



					TirEpine * tir;

					tir  = new TirEpine(163, dx, dy + rand() % 3 - 1);
					tir->x = x - 53;
					tir->y = y - 175;
					tir->traverse = true;
					list_tirs_ennemis.ajoute((void*) tir);
					ss_etape = 0;
					etape = 1;
					etat = ETAT_TIRE;
					onTire();
					return;
				} else if (pente > -15) {
					//trop pres pour tirer > - 15°

					numero_image_buste = 150;//138
				} else if (pente > -40) {
					int dx = tete_turc->x + 20 - x + 59;
					int dy = tete_turc->y - y + 129;

					int dist = sqrt((dx * dx) + (dy * dy));

					dx = (dx * LARA_TIR_SPEED) / dist;
					dy = (dy * LARA_TIR_SPEED) / dist;


					TirEpine * tir;

					tir  = new TirEpine(163, dx, dy + rand() % 3 - 1);

					tir->x = x - 59;
					tir->y = y - 129;
					tir->traverse = true;
					list_tirs_ennemis.ajoute((void*) tir);
					//angle de tir: -10°
					numero_image_buste = 156;

					ss_etape = 0;
					etape = 1;
					etat = ETAT_TIRE;
					onTire();
					return;
				} else {
					int dx = tete_turc->x - x + 60;
					int dy = tete_turc->y - y + 144;

					int dist = sqrt((dx * dx) + (dy * dy));

					dx = (dx * LARA_TIR_SPEED) / dist;
					dy = (dy * LARA_TIR_SPEED) / dist;


					TirEpine * tir;

					tir  = new TirEpine(163, dx, dy + rand() % 3 - 1);

					tir->x = x - 60;
					tir->y = y - 144;
					tir->traverse = true;
					list_tirs_ennemis.ajoute((void*) tir);
					numero_image_buste = 150;
					ss_etape = 0;
					etape = 1;
					etat = ETAT_TIRE;
					onTire();
					return;
				}
				//debug << pente <<" "<<dif_y<<"   "<<dif_x<< "\n";
			} else {

				/*TirEpine * tir  =new TirEpine(163,-9,0);
				tir->x = x;
				tir->y = y-150;
				list_tirs_ennemis.ajoute( (void*) tir);
				numero_image_buste = 150;*/
			}
		}
//		colFromPic();
	} else if (game_flag[0] == 7) {
		a_detruire = true;
		game_flag[FLAG_NB_KILL]++;
	}
}

void EnnemiLara::onTire()
{
	ss_etape ++;
	ss_etape %= etape;
	if (ss_etape == 0) {
		etape ++;
		if (etape >= 7) {
			etat = ETAT_AVANCE;
			ss_etape = 0;
			etape = 0;
			numero_image_buste -= 5;
			wait_for_attack = 0;
			onAvance();
			return;
		} else {
			numero_image_buste ++;
		}
	}
}

void EnnemiLara::onMeure()
{
	game_flag[0] = 5;
	a_detruire = true;
}


void EnnemiLara::affiche()
{
	if (game_flag[0] < 6) {
		draw(x, y - 102, pbk_ennemis[numero_image_buste]);
	}

	Sprite::affiche();
}



void EnnemiLara::estTouche(Tir * tir)
{
	/*
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };
	*/
	Ennemi::estTouche(tir);
}

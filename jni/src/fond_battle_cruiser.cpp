/******************************************************************
*
*
*		---------------------------
*		    FondBattlecruiser.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/


#include "fond_battle_cruiser.h"
#include "sprite.h"
#include "fond_tir_cruiser.h"
#include "tir_cruiser_laser.h"

const int anim_cruiser_droite [] = {0, 1, 2, 1};
const int anim_cruiser_gauche [] = {3, 4, 5, 4};

FondBattlecruiser::FondBattlecruiser(): x_adversaire(700), y_adversaire(40), attack_etape(-2), feu_etape(0), feu_ss_etape(0)
{
	x = -20;
	y = 80;
}

void FondBattlecruiser::update()
{
	feu_ss_etape += 1;
	feu_ss_etape %= 40;
	if (feu_ss_etape == 0) {
		feu_etape += 1;
		feu_etape %= 6;
	}
	//int nb_tir=0;
	//if (attack_etape==0)
	{
		x += 1;
		x_adversaire -= 1;
		pic = pbk_niveau[anime(anim_cruiser_droite, 4, 12)];


		int dif_y = y_adversaire - y;
		int dif_x = x_adversaire - x;

		if (dif_y != 0 && (dif_x / dif_y < 2)/*&&(dif_x<600)*/ && (dif_x > 0) && (dif_x != 0)) {
			//speed=((dif_x*-9)/dif_y);
			//dy=-9+speed*0.25;

			//if (((x_adversaire-30-x)/-36)<3)||((x_adversaire+30+x)/-36)<3))
			//{
			attack_etape += 1;

			if (attack_etape == 2)
				attack_etape = -2;

			//if (attack_etape==0)
			//{
			//	for (int i=-2;i<3;i++)
			//	{
			pic = pbk_niveau[26 + attack_etape];
			Sprite * s = new TirCruiser((dif_x * TIR_SPEED) / dif_y, TIR_SPEED - (dif_x * TIR_SPEED * 0.25) / dif_y, 8 + attack_etape);
			s->x = x - 8 * attack_etape;
			s->y = y + 6;
			list_fonds_animes.ajoute((void*) s);

			s = new TirCruiser(-(dif_x * TIR_SPEED) / dif_y, -TIR_SPEED + (dif_x * TIR_SPEED * 0.25) / dif_y, 7 - attack_etape);
			s->x = x_adversaire - 8 * attack_etape;
			s->y = y_adversaire - 6;
			list_fonds_animes.ajoute((void*) s);

			if (attack_etape == -2) {
				s = new TirCruiserLaser(1, 13 - (dif_x / dif_y));
				s->x = x  + 16;//+8*rand()%5-16;
				s->y = y;
				list_fonds_animes.ajoute((void*) s);
			}
			if (attack_etape == 0) {
				s = new TirCruiserLaser(-1, 17 - (dif_x / dif_y));
				s->x = x_adversaire - 16;//+8*rand()%5-16;
				s->y = y_adversaire;
				list_fonds_animes.ajoute((void*) s);
			}
			//	}
			//}
			//else if(attack_etape == 1)
			//{
			//	pic=pbk_niveau[13];
			//}
			//else if(attack_etape == 2)
			//{
			//	pic=pbk_niveau[13];
			//}


		} else {
			attack_etape = -3;
		}

	}

	if (x > 720) {
		x = -20;
		attack_etape = 1;
		x_adversaire = 700;
	}
	/*else
	{
		x-=1;
		x_adversaire+=1;
		pic = pbk_niveau[anime(anim_cruiser_gauche, 4, 8)];
	}*/
}

void FondBattlecruiser::affiche()
{
	Sprite::affiche();
	if (attack_etape == -3) {
		draw(x_adversaire, y_adversaire, pbk_niveau[anim_cruiser_gauche[etape]]);
	} else {
		//draw( x_adversaire, y_adversaire, pbk_niveau[anim_cruiser_droite[etape]]);
		draw(x_adversaire, y_adversaire , pbk_niveau[29 - attack_etape]);
	}

	if (((feu_ss_etape >= 0) && (feu_ss_etape <= 2)) || ((feu_ss_etape >= 10) && (feu_ss_etape <= 12))) {
		int tmp = 0;

		if ((feu_ss_etape == 1) || (feu_ss_etape == 11))
			tmp = 1;

		switch (feu_etape) {
			case 0:
				draw(x + 21, y - 2, pbk_niveau[32 + tmp]);
				draw(x_adversaire - 20, y_adversaire - 2, pbk_niveau[34 + tmp]);
				break;

			case 1:
				draw(x - 10, y - 7, pbk_niveau[32 + tmp]);
				draw(x_adversaire + 11, y_adversaire - 7, pbk_niveau[34 + tmp]);
				break;

			case 2:
				draw(x + 8, y - 6, pbk_niveau[32 + tmp]);
				draw(x_adversaire - 7, y_adversaire - 6, pbk_niveau[34 + tmp]);
				break;

			case 3:
				draw(x - 8, y + 6, pbk_niveau[32 + tmp]);
				draw(x_adversaire + 7, y_adversaire + 6, pbk_niveau[34 + tmp]);
				break;

			case 4:
				draw(x - 10, y - 7, pbk_niveau[32 + tmp]);
				draw(x_adversaire + 11, y_adversaire - 7, pbk_niveau[34 + tmp]);
				break;

			case 5:
				draw(x + 21, y + 2, pbk_niveau[32 + tmp]);
				draw(x_adversaire - 20, y_adversaire + 2, pbk_niveau[34 + tmp]);
				break;
		}

	}
}
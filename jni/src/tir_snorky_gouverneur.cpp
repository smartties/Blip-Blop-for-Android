/******************************************************************
*
*
*		---------------------------------
*		   TirSnorkyGouverneur.cpp
*		---------------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 15 Decembre 2000
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_snorky_gouverneur.h"



TirSnorkyGouverneur::TirSnorkyGouverneur(Personnage * cible, int vx , int vy): joueur_cible(cible), dx(vx), etape_dx(0), etape_dy(0), time(0)
{
	dy = vy;
}


void TirSnorkyGouverneur::update()
{
	ss_etape++;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape++;
		etape %= 4;
	}


	if (x < offset - 100 || x > offset + 740 || y > 580 || y < -100)
		a_detruire = true;

	//tombe();

	time++;

	if ((time < TIME_MAX || ((dx < 2 && dx > -2) && (dy < 2 && dy > -2))) && (joueur_cible->a_detruire == false)) {
		if (x < joueur_cible->x && dx < SPEED_MAX) {
			etape_dx += 1;

			if (etape_dx > INERTIE_TIR) {
				dx += 1;
				etape_dx = 0;
			}
		}

		else if (x > joueur_cible->x && dx > (-SPEED_MAX)) {
			etape_dx -= 1;

			if (etape_dx < (-INERTIE_TIR)) {
				dx -= 1;
				etape_dx = 0;
			}
		}

		if (y < joueur_cible->y && dy < SPEED_MAX) {
			etape_dy += 1;

			if (etape_dy > INERTIE_TIR) {
				dy += 1;
				etape_dy = 0;
			}
		}

		else if (y > joueur_cible->y && dy > (-SPEED_MAX)) {
			etape_dy -= 1;

			if (etape_dy < (-INERTIE_TIR)) {
				dy -= 1;
				etape_dy = 0;
			}
		}
	}

	x += dx;
	y += dy;

	if (dx <= 0) {
		pic = pbk_ennemis[233 + etape];
	} else {
		pic = pbk_ennemis[236 - etape];
	}

	if (mur_opaque(x + dx, y + dy) != 0)
		a_detruire = true;

	colFromPic();
}

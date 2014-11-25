/******************************************************************
*
*
*		-------------------
*		   TirBBFusil.cpp
*		-------------------
*
*		Pour les tirs de PM de Blip/Blop
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/


//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "tir_bb_fusil.h"

const int dx_tirbb_fusil [] = { 0, 6, 11, 14, 15, 14, 11, 6, 0, -6, -11, -14, -15, -14, -11, -6 };
const int dy_tirbb_fusil [] = { 15, 14, 11, 6, 0, -6, -11, -14, -15, -14, -11, -6, 0, 6, 11, 14 };

const int lat_grande [] = { 1, 2, 2, 1, 2, 1 };
const int lat_tgrande [] = { 1, 2, 3, 2, 1, 3};
const int d_grand [] = { 3, -2, -1, 0, 1, 2, 3 };
const int d_petit [] = { -2, 0, 2, 0, 1, -1, 2, -1, -2, 1 };
const int d_min [] = { -1, 0, 1 };

int n_lat_grande = 0;
int n_lat_tgrande = 0;
int n_d_grand = 0;
int n_d_petit = 0;
int n_d_min = 0;

void TirBBFusil::setDir(int d)
{
	TirBB::setDir(d);

	n_lat_grande += 1;
	n_lat_grande %= 6;

	n_d_grand += 1;
	n_d_grand %= 7;

	n_d_petit += 1;
	n_d_petit %= 10;

	switch (dir / 2) {
		case 0:		// Haut et bas
		case 4:
			latence_x = lat_grande[n_lat_grande];
			latence_y = 1;
			dx = 0;
			dy = d_grand[n_d_grand];
			ddx = d_petit[n_d_petit];
			ddy = 0;
			break;

		case 2:		// Gauche et droite
		case 6:
			latence_y = lat_grande[n_lat_grande];
			latence_x = 1;
			dx = d_grand[n_d_grand];
			dy = 0;
			ddx = 0;
			ddy = d_petit[n_d_petit];
			break;

		case 1:		// Diagonale haut gauche / bas droite
		case 5:
			n_lat_tgrande += 1;
			n_lat_tgrande %= 6;

			latence_y = lat_tgrande[n_lat_tgrande];

			n_lat_tgrande += 1;
			n_lat_tgrande %= 6;

			latence_x = lat_tgrande[n_lat_tgrande];

			dx = d_petit[n_d_petit];
			dy = d_petit[n_d_petit];

			n_d_grand += 1;
			n_d_grand %= 7;

			ddx = d_grand[n_d_grand];

			n_d_grand += 1;
			n_d_grand %= 7;

			ddy = d_grand[n_d_grand];
			break;

		case 3:		// Diagonale bas gauche / haut droite
		case 7:
			n_lat_tgrande += 1;
			n_lat_tgrande %= 3;

			latence_y = lat_tgrande[n_lat_tgrande];

			n_lat_tgrande += 1;
			n_lat_tgrande %= 3;

			latence_x = lat_tgrande[n_lat_tgrande];

			dx = d_petit[n_d_petit];
			dy = -d_petit[n_d_petit];

			n_d_grand += 1;
			n_d_grand %= 7;

			ddx = d_grand[n_d_grand];

			n_d_grand += 1;
			n_d_grand %= 7;

			ddy = d_grand[n_d_grand];
			break;

	}

	dx += dx_tirbb_fusil[dir];
	dy += dy_tirbb_fusil[dir];

	duree_vie = 10 + rand() % 7;
	vie = 0;
}


void TirBBFusil::update()
{
    y += dy;
	x += dx;

	etape_dy += 1;
	etape_dy %= latence_y;

	if (etape_dy == 0)
	y += ddy;


	etape_dx += 1;
	etape_dx %= latence_x;

	if (etape_dx == 0)
	x += ddx;


	vie += 1;

	x += dxReferentiel;


	if (mur_opaque(x, y) || x < offset - 20 || x > offset + 660 || y < -20 || y > 500) {
		pic = NULL;
		noCol();
		a_detruire = true;
	} else {
		if (vie < duree_vie)
			pic = pbk_bb[88 + dir];
		else
			pic = pbk_bb[72 + dir];

		colFromPic();
	}
}

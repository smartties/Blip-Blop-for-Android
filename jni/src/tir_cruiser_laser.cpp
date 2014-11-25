/******************************************************************
*
*
*		-----------------------
*		    TirCruiserlaser.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 17 Decembre 2000
*
*
*
******************************************************************/


#include "tir_cruiser_laser.h"

TirCruiserLaser::TirCruiserLaser(int vx, int nb_pic): dx(vx)
{
	pic = pbk_niveau[nb_pic];
	etape = 0;
	ss_etape = 2;
}

void TirCruiserLaser::update()
{
	ss_etape ++;
	ss_etape %= 4;
	if (ss_etape == 0)
		etape ++;
	if (etape == 4) {
		a_detruire = true;
	} else {
		switch (npic) {
			case 10:
				if ((etape == 1) && (ss_etape == 0)) {
					x += 36;
					y += 19;
				}
				break;

			case 11:
				if ((etape == 1) && (ss_etape == 0)) {
					x += 19;
					y += 19;
				}
				break;

			case 12:
				if ((etape == 1) && (ss_etape == 0)) {
					x += 10;
					y += 19;
				}
				break;

			case 13:

				if ((etape == 1) && (ss_etape == 0))
					y += 19;

				break;

			case 14:
				if ((etape == 1) && (ss_etape == 0)) {
					x -= 36;
					y -= 19;
				}
				break;

			case 15:
				if ((etape == 1) && (ss_etape == 0)) {
					x -= 19;
					y -= 19;
				}
				break;

			case 16:
				if ((etape == 1) && (ss_etape == 0)) {
					x -= 10;
					y -= 19;
				}
				break;

			case 17:

				if ((etape == 1) && (ss_etape == 0))
					y -= 19;

				break;
		}

		if (etape > 0) {
			if (dx > 0) {
				pic = pbk_niveau[20 + etape];
			} else {
				pic = pbk_niveau[17 + etape];
			}
		}
	}
}
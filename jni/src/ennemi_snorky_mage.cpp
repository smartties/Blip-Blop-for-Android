/******************************************************************
*
*
*		----------------------
*		  EnnemiSnorkyMage.cpp
*		----------------------
*
*		(giclures faites...)
*
*		Mephisto / LOADED -   V 0.3 - 28 Decembre 2000
*
*
*
******************************************************************/

#include "ennemi_snorky_mage.h"
#include "tir_snorky_mage.h"


const int snorky_mage_oscilation[] = {0, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 2, 2, 2, 1, 1, 1, 0, 0, 0};


EnnemiSnorkyMage::EnnemiSnorkyMage(): wait_for_shoot(0), shoot_delay(50 + rand() % 200), oscilation_etape(0)
{
	pv = 200;
	pic = pbk_ennemis[0];
	dy = 0;
}


void EnnemiSnorkyMage::update()
{
	switch (etat) {
		case ETAT_AVANCE:
		case ETAT_NORMAL:
			onAvance();
			break;

		case ETAT_TOMBE:
		case ETAT_SAUTE:
			onTombe();
			break;

		case ETAT_MEURE:
			onMeure();
			break;

		case ETAT_CARBONISE:
			onCarbonise();
			break;

		case ETAT_TIRE:
			onTire();
			break;
	}

	updateADetruire();

}

void EnnemiSnorkyMage::onAvance()
{

	oscilation_etape++;
	oscilation_etape %= 43;
	if (oscilation_etape >= 22) {
		y -= snorky_mage_oscilation[oscilation_etape - 22];
	} else {
		y += snorky_mage_oscilation[oscilation_etape];
	}


	wait_for_shoot++;
	if	((tete_turc != NULL) && (wait_for_shoot > shoot_delay) && ((dir == SENS_DROITE && x > offset + 30) || (dir == SENS_GAUCHE && x < offset + 610)))

	{
		int dif_y = tete_turc->y - y;
		int dif_x = tete_turc->x - x;


		if ((dir == SENS_DROITE) && (dif_y > 0) && (dif_x > 0) && (dif_y - dif_x >= -30) && (dif_y - dif_x <= 30)) {
			etape = 0;
			wait_for_shoot = 0;
			shoot_delay = 50 + rand() % 200;
			etape = 0;
			ss_etape = 0;
			etat = ETAT_TIRE;
			concentration = 0;
			onTire();
			return;
		} else if ((dir == SENS_GAUCHE) && (dif_y > 0) && (dif_x < 0) && (dif_y + dif_x >= -30) && (dif_y + dif_x <= 30)) {
			etape = 0;
			wait_for_shoot = 0;
			shoot_delay = 50 + rand() % 200;
			etape = 0;
			ss_etape = 0;
			etat = ETAT_TIRE;
			concentration = 0;
			onTire();
			return;
		}
	}

	ss_etape ++;
	ss_etape %= 5;
	if (ss_etape == 0) {
		etape ++;
		etape %= 6;
	}

	pic = pbk_ennemis[237 + etape];

	if (dir == SENS_GAUCHE) {
		x -= SNORKY_MAGE_SPEED;

		if (mur_opaque(x - SNORKY_MAGE_SPEED, y) || (x - SNORKY_MAGE_SPEED < xmin))
			dir = SENS_DROITE;
	} else {
		x += SNORKY_MAGE_SPEED;

		if (mur_opaque(x + SNORKY_MAGE_SPEED, y) || (x + SNORKY_MAGE_SPEED > offset + 640))
			dir = SENS_GAUCHE;
	}

	colFromPic();
}

void EnnemiSnorkyMage::onTombe()
{
	tombe();

	if (plat(x, y) != 0)
		etat = ETAT_AVANCE;

	colFromPic();
}

void EnnemiSnorkyMage::onMeure()
{
	if (etape > 2) {
		tombe();
	}

	ss_etape ++;
	if (etape < 2) {
		ss_etape %= 17;
	} else {
		ss_etape %= 5;
	}

	if (ss_etape == 0)
		etape += 1;

	if (ss_etape == 0 && etape == 3) {
		sbk_niveau.play(13);
	}

	if ((plat(x, y) != 0) && (etape < 7)) {
		etape = 8;
	}
	if (etape == 7) {
		etape = 4;
	}

	if (etape == 11) {
		if (plat(x, y) != 0)
			grave(x, y, pic);

		a_detruire = true;
//		sbk_niveau.play( 11);
	} else {
		pic = pbk_ennemis[266 + etape];
	}
}

void EnnemiSnorkyMage::onTire()
{
	if (concentration < 3) {
		ss_etape ++;
		ss_etape %= 4;
		if (ss_etape == 0) {
			etape ++;
		}

		if (etape == 6) {
			concentration ++;
			etape = 0;
			if (concentration == 3) {
				etape = 0;
				ss_etape = 0;
			}
		}

		pic = pbk_ennemis[243 + etape];
	} else {
		ss_etape++;
		ss_etape %= 4;
		if (ss_etape == 0) {
			etape ++;
		}
		if ((etape == 2) && (ss_etape == 0)) {
			if (dir == SENS_DROITE) {
				TirSnorkyMage *	tir = new TirSnorkyMage();

				tir->setDir(dir);
				tir->x = x + 35;
				tir->y = y - 42;

				list_tirs_ennemis.ajoute((void*) tir);
			} else {
				TirSnorkyMage *	tir = new TirSnorkyMage();

				tir->setDir(dir);
				tir->x = x - 35;
				tir->y = y - 42;

				list_tirs_ennemis.ajoute((void*) tir);
			}

			sbk_niveau.play(12);
		}

		if (etape == 5) {
			etape = 0;
			ss_etape = 0;
			etat = ETAT_AVANCE;
			onAvance();
			return;
		}


		if (etape < 3) {
			if (dir == SENS_DROITE) {
				pic = pbk_ennemis[249 + etape];
			} else {
				pic = pbk_ennemis[257 + etape];
			}
		}
	}
}

void EnnemiSnorkyMage::onCarbonise()
{
	ss_etape ++;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape ++;

	if (etape == 7) {
		a_detruire = true;
	} else {
		pic = pbk_ennemis[278 + etape];
	}
}

void EnnemiSnorkyMage::estTouche(Tir * tir)
{
	static const int dx_giclure_mage [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_mage [] = { -35, -45, -45, -45, -55, -45, -45, -45 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_mage, dy_giclure_mage);

	if (etat == ETAT_MEURE) {
		sbk_niveau.play(10);
	}
}

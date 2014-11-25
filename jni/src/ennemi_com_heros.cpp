/******************************************************************
*
*
*		----------------------
*		  EnnemiComHeros.cpp
*		----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 14 Janvier 2001
*
*
*
******************************************************************/



#include "ennemi_com_heros.h"


EnnemiComHeros::EnnemiComHeros(): dorkeball(2)
{
	pv = 1000;
	dy = -8;
	dx = -2;
}

void EnnemiComHeros::update()
{
	if (dorkeball == 2) {
		x += dx;
		tombe();
		int yp;
		if ((dy > 0) && (yp = plat(x, y + dy)) != 0) {
			etat = ETAT_NORMAL;
			dy = 0;
			y = yp;
			etape = 0;
			ss_etape = 0;
			dorkeball = 1;
			return;
		} else {
			ss_etape ++;
			ss_etape %= 5;
			if (ss_etape == 0) {
				etape ++;
				etape %= 4;
			}
			pic = pbk_ennemis[272 + etape];
		}
	} else if (dorkeball == 1) {
		ss_etape ++;
		ss_etape %= 8;
		if (ss_etape == 0) {
			etape ++;
			if (etape > 3) {
				dorkeball = 0;
				etape = 0;
				ss_etape = 0;
			} else {
				pic = pbk_ennemis[388 + etape];
			}
		}

	} else {
		if (blood > 0)
			blood -= 1;

		switch (etat) {
			case ETAT_NORMAL:
			case ETAT_AVANCE:
				onAvance();
				break;


			case ETAT_MEURE:
			case ETAT_CARBONISE:
				onMeure();
				break;
		}

		updateADetruire();
	}
}

void EnnemiComHeros::onAvance()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 8;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 2;
	}

	// Marche
	//
	if (x - 1 < xmin || mur_opaque(x - 1, y))
		dir = SENS_DROITE;
	else if (x + 1 > offset + 640 || mur_opaque(x + 1, y))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE) {
		marche(2);
	} else {
		marche(-2);
	}

	pic = pbk_ennemis[304 + etape];

	colFromPic();
}

void EnnemiComHeros::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0 && etape < 22)
		etape += 1;

	if (etape >= 22) {
		game_flag[1] --;
		a_detruire = true;
	} else {
		pic = pbk_ennemis[358 + etape];
	}
}


void EnnemiComHeros::estTouche(Tir * tir)
{
	Ennemi::estTouche(tir);
}
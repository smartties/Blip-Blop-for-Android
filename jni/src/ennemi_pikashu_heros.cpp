/******************************************************************
*
*
*		---------------------------
*		  EnnemiPikachuHeros.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 10 Janvier 2001
*
*
*
******************************************************************/


#include "ennemi_pikashu_heros.h"


EnnemiPikachuHeros::EnnemiPikachuHeros(): dorkeball(2)
{
	pv = 1500;
	dy = -8;
	dx = -2;
	tresor = 100;
}

void EnnemiPikachuHeros::update()
{
	if (dorkeball == 2) {
		x += dx;
		tombe();
		int yp;
		if ((dy > 0) && (yp = plat(x, y + dy)) != 0) {
			sbk_niveau.play(15);
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
				pic = pbk_ennemis[300 + etape];
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

void EnnemiPikachuHeros::onAvance()
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
		marche(3);
		pic = pbk_ennemis[276 + etape];
	} else {
		marche(-3);
		pic = pbk_ennemis[278 + etape];
	}
	colFromPic();
}

void EnnemiPikachuHeros::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0 && etape < 10)
		etape += 1;

	if (etape >= 10) {
		int		yy = plat(x, y);

		if (yy != 0 && yy != y_plat[4][x])
			grave(x, y, pic);

		a_detruire = true;
		game_flag[1] --;
	} else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[280 + etape];
		else
			pic = pbk_ennemis[290 + etape];
	}
}


void EnnemiPikachuHeros::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	if (dorkeball == 0) {
		Ennemi::estTouche(tir);
		gicle(tir, dx_giclure, dy_giclure);
	}
}
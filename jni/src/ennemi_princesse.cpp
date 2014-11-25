/******************************************************************
*
*
*		-----------------------
*		    EnnemiPrincesse.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.9 - 31 Janvier 2001
*
*
*
******************************************************************/

#include "ennemi_princesse.h"
#include "ennemi_princesseguard.h"
#include "texte_cool.h"
#include "bonus_vache.h"



EnnemiPrincesse::EnnemiPrincesse(): avance(false), aide(false)
{
	pv = 3700;
	tresor = 0;
	pic = pbk_ennemis[128];

}

void EnnemiPrincesse::update()
{
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

	if (game_flag[1]) {
		updateADetruire();
	}
}

void EnnemiPrincesse::onAvance()
{
	//if (game_flag[0])
	//{
	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	/*if ( plat( x, y) == 0)
	{
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		onSaute();
	}*/

	//pour marcher

	/*if (x + PRINCESSE_SPEED >offset+640)
	{
		x -=50;
	}*/
	/*
	if ( x - speed < xmin || mur_opaque( x-speed, y))
	{
		dir = SENS_DROITE;
		speed=1;
	}
	else if ( x + speed > offset + 640 || mur_opaque( x+speed, y))
	{
		dir = SENS_GAUCHE;
		speed=1;
	}*/

	if (game_flag[1]) {
		if (x  > offset + 820) {
			TexteCool * txt = new TexteCool();
			txt->ntxt = 517;
			list_txt_cool.ajoute((void*) txt);

			a_detruire  = true;
		}
		if (!aide) {
			/*
							TexteCool * txt = new TexteCool();
							txt->ntxt = 518;
							list_txt_cool.ajoute( (void*) txt);
			*/
			aide = true;
			Ennemi* guard;
			int i;
			for (i = 1; i < 4; i++) {
				guard = new EnnemiPrincesseguard(this, 40 + i * 40);

				guard->x = offset + 720 - i * 20;
				guard->y = y - 20;
				guard->dir = SENS_GAUCHE;
				list_ennemis.ajoute((void*) guard);

			}
			nb_ennemis_created += 3;
		}
		/*if (x < offset + 580)
		{
			avance=true;
		}*/
		if (dir == SENS_DROITE) {
			if (x - offset > 400) {
				ss_etape += 1;
				ss_etape %= 6;
				if (ss_etape == 0) {
					etape += 1;
					etape %= 2;
				}
				marche(PRINCESSE_SPEED);
				pic = pbk_ennemis[126 + etape];
			} else {
				ss_etape += 1;
				ss_etape %= 6;
				if (ss_etape == 0) {
					etape += 1;
					etape %= 2;
				}
				marche(2);
				pic = pbk_ennemis[126 + etape];
			}
		} else if (dir == SENS_GAUCHE) {
			dir = SENS_DROITE;
			//marche( -PRINCESSE_SPEED);
			//pic = pbk_ennemis[128+etape];
		} else {
			avance = false;
		}
	} else {
		if (/*(x < offset + 680)&&*/(x < 5760)) {
			ss_etape += 1;
			ss_etape %= 6;
			if (ss_etape == 0) {
				etape += 1;
				etape %= 2;
			}
			marche(PRINCESSE_SPEED);
			pic = pbk_ennemis[126 + etape];
		} else if (x > 7500) {
			pic = pbk_ennemis[126];
		} else {
			pic = pbk_ennemis[128];
		}
	}
	//}
	colFromPic();
}

void EnnemiPrincesse::onMeure()
{
	/*if (dy<-5)
		dy-=5;
	if (dy<-2)
		dy=0;*/
	tombe();

	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0 && etape < 6)
		etape += 1;

	if (etape >= 5) {
		int		yy = plat(x, y);

		if (yy != 0 && yy != y_plat[4][x]) {
			grave(x, y, pic);
			TexteCool * txt = new TexteCool();
			txt->ntxt = 519;
			list_txt_cool.ajoute((void*) txt);
			a_detruire = true;
			if (game_flag[3] > 0) {
				game_flag[2] = 1;
			}

			Bonus * bonus = new BonusVache();
			bonus->x = x;
			bonus->y = y;
			list_bonus.ajoute((void*) bonus);
		}
	} else {
		//if ( !mur_opaque( x + speed, y) && plat( x, y) == 0)
		//	x += speed;
		pic = pbk_ennemis[130 + etape];

	}
}







void EnnemiPrincesse::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	if (game_flag[1]) {
		Ennemi::estTouche(tir);
	}
	gicle(tir, dx_giclure, dy_giclure);
}
/******************************************************************
*
*
*		------------------------------
*		    EnnemiPrincesseguard.cpp
*		-----------------------------
*
*
*
*		Mephisto / LOADED -   V 0.5 - 28 Decembre 2000
*
*
*
******************************************************************/

#include "ennemi_princesseguard.h"
#include "ennemi_princesse.h"

const int anim_guard_marche_gauche[] = { 135, 136, 137, 136};

EnnemiPrincesseguard::EnnemiPrincesseguard(EnnemiPrincesse * Princesse, int distance): princesse(Princesse), distance_couverture(distance)
{
	pv = 2500;
	tresor = 100;
	dir = SENS_GAUCHE;
}

void EnnemiPrincesseguard::update()
{
	if (blood > 0)
		blood -= 1;

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_CARBONISE:
		case ETAT_MEURE:
			onMeure();
			break;


			//case ETAT_SAUTE:
			/*case ETAT_TOMBE:
				onTombe();
				break;*/

	}

	updateADetruire();
}

void EnnemiPrincesseguard::onAvance()
{
	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	/*if ( plat( x, y) == 0)
	{
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		onTombe();
	}*/

	//pour marcher
	if (princesse->a_detruire == true) {
		a_detruire = true;
	}

	if (game_flag[2]) {
		etat = ETAT_MEURE;
		onMeure();
		return;
	}
	tombe();
	if (princesse != NULL) {
		if ((x + distance_couverture + GUARD_SPEED) < princesse->x) {
			//x=princesse->x-distance_couverture;
			marche(GUARD_SPEED);
			pic = pbk_ennemis[anime(anim_guard_marche_gauche, 4, 6)];
		} else if ((x + distance_couverture - GUARD_SPEED) > princesse->x) {
			//x=princesse->x-distance_couverture;
			marche(-GUARD_SPEED * 3);
			pic = pbk_ennemis[anime(anim_guard_marche_gauche, 4, 6)];
		} else {
			pic = pbk_ennemis[135];
		}
		/*if ( x - GUARD_SPEED < xmin || mur_opaque( x-GUARD_SPEED, y))
		{
			dir = SENS_DROITE;
		}
		else if ( x + GUARD_SPEED > offset + 640 || mur_opaque( x+GUARD_SPEED, y))
		{
			dir = SENS_GAUCHE;
		}

		if ( dir == SENS_DROITE)
		{
			marche(GUARD_SPEED);
			pic = pbk_ennemis[anime( anim_guard_marche_droite, 4, 6)];
		}
		else
		{
			marche( -GUARD_SPEED);
			pic = pbk_ennemis[anime( anim_guard_marche_gauche, 4, 6)];
		}
		*/
	} else {
		a_detruire = true;
	}

	colFromPic();
}

void EnnemiPrincesseguard::onMeure()
{
	/*if (dy<-5)
		dy-=5;
	if (dy<-2)
		dy=0;*/
	tombe();

	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0 && etape < 10)
		etape += 1;

	if (etape >= 10) {
		int		yy = plat(x, y);

		if (yy != 0 && yy != y_plat[4][x]) {
			grave(x, y, pic);
			a_detruire = true;
			game_flag[3] -= 1;
		}
	} else {

		//if ( !mur_opaque( x - GUARD_SPEED, y) && plat( x, y) == 0)
		//	x -= GUARD_SPEED;
		pic = pbk_ennemis[138 + etape];
	}
}



/*void EnnemiPrincesseguard::onTombe()
{
	int		yp;

	tombe();

	// Et si on arrêtait de tomber ?
	//
	if ( dy > 0 && (yp=plat( x, y+dy)) != 0)
	{
		etat = ETAT_NORMAL;
		dy = 0;
		y = yp;
		onAvance();
		return;
	}


	if ( dir == SENS_DROITE)
	{
		x += GUARD_SPEED;
		pic = pbk_ennemis[3];
	}
	else
	{
		x -= GUARD_SPEED;
		pic = pbk_ennemis[7];
	}

	colFromPic();

}*/

/*void EnnemiPrincesseguard::onCarbonise()
{
	a_detruire = true;
	ss_etape += 1;
	ss_etape %= 5;

	if ( ss_etape == 0)
		etape += 1;

	if ( etape >= 14)
		a_detruire = true;
	else
	{
		if ( dir == SENS_DROITE)
			pic = pbk_ennemis[100+etape];
		else
			pic = pbk_ennemis[114+etape];
	}
}*/

void EnnemiPrincesseguard::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);
}
#include "ennemi_tails.h"


EnnemiTails::EnnemiTails(): speed(1), etape_speed(0), fly_delay(100 + rand() % 350), wait_for_fly(0), fly(false)
{
	tresor = 8;
	pv = 150;
}

void EnnemiTails::update()
{
	if (blood > 0)
		blood -= 1;

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_MEURE:
			onMeure();
			break;

		case ETAT_CARBONISE:
			onCarbonise();
			break;

		case ETAT_SAUTE:
		case ETAT_TOMBE:
			onTombe();
			break;

		case ETAT_TIRE:  //Tails Volle(ETAT_TIRE)
			onVolle();
			break;
	}
	/*
		if (y > y_plat[0][x])
		{
			y = y_plat[0][x];
		}
	*/
	updateADetruire();
}

void EnnemiTails::onAvance()
{
	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		fly = true;
		etape = 0;
		ss_etape = 0;
		onTombe();
		return;
	}

	//pour marcher

	if (x - speed < xmin || mur_opaque(x - speed, y)) {
		dir = SENS_DROITE;
		speed = 1;
	} else if (x + speed > offset + 640 || mur_opaque(x + speed, y)) {
		dir = SENS_GAUCHE;
		speed = 1;
	}
	wait_for_fly++;
	if (wait_for_fly >= fly_delay) {
		etat = ETAT_TIRE;
		attack = false;
		speed = 0;
		etape = 0;
		ss_etape = 0;

		fly = true;
		x_cible = tete_turc->x;
		y_cible = tete_turc->y;
		if (x_cible > x) {
			dir = SENS_DROITE;
			direction = 1;
		} else {
			dir = SENS_GAUCHE;
			direction = -1;
		}
		onVolle();
		return;
	}


	ss_etape += 1;
	ss_etape %= 10 - 2 * speed;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 8;
	}

	if (dir == SENS_DROITE) {
		marche(speed);
		pic = pbk_ennemis[etape + 80];
	} else {
		marche(-speed);
		pic = pbk_ennemis[etape + 88];
	}
	if (speed < TAILS_SPEED) {
		etape_speed++;
		if (etape_speed >= 30) {
			etape_speed = 0;
			speed++;
		}
	}
	colFromPic();
}

void EnnemiTails::onMeure()
{
	tombe();

	if (fly) {
		int yp;
		ss_etape += 1;
		ss_etape %= 4;
		if (ss_etape == 0) {
			etape += 1;
			etape %= 2;
		}
		if (dir == SENS_DROITE) {
			if (!mur_opaque(x + speed, y))
				marche(speed);
			pic = pbk_ennemis[122 + etape];
		} else {
			if (!mur_opaque(x - speed, y))
				marche(-speed);
			pic = pbk_ennemis[124 + etape];
		}
		if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
			dy = 0;
			y = yp;
			fly = false;
			etape = 7;
		}
	} else {
		ss_etape += 1;
		ss_etape %= 6;

		if (ss_etape == 0 && etape < 11)
			etape += 1;

		if (etape >= 11) {
			int		yy = plat(x, y);

			if (yy != 0 && yy != y_plat[4][x]) {
				grave(x, y, pic);
				a_detruire = true;
			} else {
				if (dir == SENS_GAUCHE && !mur_opaque(x - speed, y))
					marche(-speed);
				else if (!mur_opaque(x + speed, y))
					marche(speed);
			}
		} else {
			if (dir == SENS_GAUCHE) {
				if (!mur_opaque(x - speed, y))
					marche(-speed);
				pic = pbk_ennemis[111 + etape];
			} else {
				if (!mur_opaque(x + speed, y))
					marche(speed);
				pic = pbk_ennemis[100 + etape];
			}
		}
	}
	/*if ( dir == SENS_GAUCHE)
	{
		if (!mur_opaque( x-speed, y))
			x -= speed;
	}
	else
	{
		if (!mur_opaque( x+speed, y))
			x += speed;
	}*/
}

void EnnemiTails::onVolle()
{
	if (attack && (x - speed < xmin || mur_opaque(x - speed, y))) {
		dir = SENS_DROITE;
		speed = 1;
		etat = ETAT_AVANCE;
		wait_for_fly = 0;
		fly_delay = 100 + rand() % 350;
		fly = false;
		etape = 0;
		ss_etape = 0;
		onAvance();
		return;
	} else if (attack && (x + speed > offset + 640 || mur_opaque(x + speed, y))) {
		dir = SENS_GAUCHE;
		speed = 1;
		etat = ETAT_AVANCE;
		wait_for_fly = 0;
		fly = false;
		fly_delay = 100 + rand() % 350;
		etape = 0;
		ss_etape = 0;
		onAvance();
		return;
	}

	etape += 1;
	etape %= 2;

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[etape + 96];
	} else {
		pic = pbk_ennemis[etape + 98];
	}

	{
	}

	if (attack) {
		if ((y_cible <= y) || (y >= y_plat[0][x])) {
			speed = TAILS_FLY_SPEED;
		} else if ((y_cible - 80 > y) && (y > y_cible - 110)) {
			y += 4;
			speed = 1;
		} else if ((y_cible - 60 > y) && (y >= y_cible - 80)) {
			y += 3;
			speed = 2;
		} else if ((y_cible - 40 > y) && (y >= y_cible - 60)) {
			y += 2;
			speed = 3;
		} else if ((y_cible - 20 > y) && (y >= y_cible - 40)) {
			y += 1;
			speed = 4;
		} else { //if ((y_cible>y)&&(y>=y_cible-20))
			y += 1;
			speed = 5;
		}
		x += speed * direction;
		/*else
		{
			x+=TAILS_FLY_SPEED;
		}*/
	} else {
		if (y < (y_cible - 110)) {
			y += 5;
		} else if (y > (y_cible - 100)) {
			y -= 3;
		} else {
			attack = true;
		}
	}

	colFromPic();
}

void EnnemiTails::onTombe()
{
	int		yp;

	tombe();
	ss_etape += 1;
	ss_etape %= 3;
	if (ss_etape == 0) {
		etape += 1;
		etape %= 2;
	}

	// Et si on arrêtait de tomber ?
	//
	if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
		etat = ETAT_NORMAL;
		dy = 0;
		y = yp;
		fly = false;
		etape = 0;
		ss_etape = 0;
		onAvance();
		return;
	}


	if (dir == SENS_DROITE) {
		x += speed;
		pic = pbk_ennemis[96 + etape];
	} else {
		x -= speed;
		pic = pbk_ennemis[98 + etape];
	}

	colFromPic();

}

void EnnemiTails::onCarbonise()
{
	tombe();
	ss_etape ++;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape ++;

	if (etape >= 11)
		a_detruire = true;
	else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[412 + etape];
		else
			pic = pbk_ennemis[423 + etape];
	}
}

void EnnemiTails::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (etat == ETAT_MEURE) {
		sbk_misc.play(10);
	}
}
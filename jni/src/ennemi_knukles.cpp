#include "ennemi_knukles.h"


EnnemiKnukles::EnnemiKnukles(): speed(1), etape_speed(0), charge_delay(100 + rand() % 150), wait_for_charge(0)
{
	tresor = 7;
	pv = 150;
}

void EnnemiKnukles::update()
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
			onSaute();
			break;

		case ETAT_TOMBE:
			onTombe();
			break;

		case ETAT_TIRE:  //Knukles Charge(ETAT_TIRE)
			onCharge();
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

void EnnemiKnukles::onAvance()
{
	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
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
	wait_for_charge++;
	if (wait_for_charge >= charge_delay && tete_turc != NULL) {
		if ((plat2(tete_turc->x, tete_turc->y) == plat2(x, y))
		        && (((dir == SENS_DROITE) && (x > (tete_turc->x - 200)) && (tete_turc->x > x))
		            || ((dir == SENS_GAUCHE) && (x < (tete_turc->x + 200)) && (tete_turc->x < x)))) {
			etat = ETAT_TIRE;
			sbk_niveau.play(6);
			speed = KNUKLES_CHARGE_SPEED;
			etape = 0;
			ss_etape = 0;
			onCharge();
			return;
		} else if ((tete_turc->y < y) && (tete_turc->x > x - 30) && (tete_turc->x < x + 30)) {
			etat = ETAT_SAUTE;
			speed = 0;
			etape = 0;
			ss_etape = 0;
			lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur
			dy = 0;
			sbk_niveau.play(7);
			onSaute();
			return;
		} else {
			wait_for_charge = 0;
			charge_delay = 10 + rand() % 10;
		}
	}


	ss_etape += 1;
	ss_etape %= 10 - 2 * speed;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 8;
	}

	if (dir == SENS_DROITE) {
		marche(speed);
		pic = pbk_ennemis[etape + 152];
	} else {
		marche(-speed);
		pic = pbk_ennemis[etape + 160];
	}
	if (speed < KNUKLES_SPEED) {
		etape_speed++;
		if (etape_speed >= 20) {
			etape_speed = 0;
			speed++;
		}
	}
	colFromPic();
}

void EnnemiKnukles::onMeure()
{
	tombe();
	/*if (fly)
	{
		int yp;
		ss_etape +=1;
		ss_etape %= 4;
		if (ss_etape==0)
		{
			etape +=1;
			etape %= 2;
		}
		if (dir == SENS_DROITE)
		{
			if (!mur_opaque( x + speed, y) )
				x += speed;
			pic = pbk_ennemis[122+etape];
		}
		else
		{
			if ( !mur_opaque( x - speed, y) )
				x -= speed;
			pic = pbk_ennemis[124+etape];
		}
		if ( dy > 0 && (yp=plat( x, y+dy)) != 0)
		{
			dy = 0;
			y = yp;
			fly=false;
			etape=7;
		}
	}*/
	//else
	{
		ss_etape += 1;
		ss_etape %= 6;

		if (ss_etape == 0 && etape < 10)
			etape += 1;

		if (etape >= 10) {
			int		yy = plat(x, y);

			if (yy != 0 /*&& yy != y_plat[4][x]*/) {
				grave(x, y, pic);
				a_detruire = true;
			} else {
				if (dir == SENS_GAUCHE && !mur_opaque(x - speed, y))
					x -= speed;
				else if (!mur_opaque(x + speed, y))
					x += speed;
			}
		} else {
			if (dir == SENS_GAUCHE) {
				if (!mur_opaque(x - speed, y))
					x -= speed;
				pic = pbk_ennemis[514 + etape];
			} else {
				if (!mur_opaque(x + speed, y))
					x += speed;
				pic = pbk_ennemis[504 + etape];
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

void EnnemiKnukles::onSaute()
{

	ss_etape++;
	ss_etape %= 60;
	if ((ss_etape == 0) && (etape == 0)) {
		etape++;
		dy = - KNUKLES_JUMP_SPEED;
	}

	tombe();


	//if ((dy>=0)&&(etape>0)&&(ss_etape>5))
	//{

	int		yp;
	// Et si on arrêtait de tomber ?
	//
	if ((dy > 0 && (yp = plat(x, y + dy)) != 0) && etape > 0) {
		etat = ETAT_NORMAL;
		dy = 0;
		y = yp;
		speed = 1;
		wait_for_charge = 0;
		etape = 0;
		ss_etape = 0;
		charge_delay = 50 + rand() % 150;
		onAvance();
		return;
	}
	//}
	if (dir == SENS_GAUCHE) {
		pic = pbk_ennemis[170 + etape];
	} else {
		pic = pbk_ennemis[168 + etape];
	}
	colFromPic();
}

void EnnemiKnukles::onCharge()
{
	tombe();
	ss_etape++;
	ss_etape %= 40;
	if (ss_etape % 10 == 0) {
		speed--;
	}
	if (etape == 2) {
		etat = ETAT_AVANCE;
		speed = 1;
		wait_for_charge = 0;
		charge_delay = 50 + rand() % 150;
		etape = 0;
		ss_etape = 0;
		onAvance();
		return;
	}
	if (ss_etape == 0) {
		etape++;
		speed = KNUKLES_CHARGE_SPEED - 1;
	}

	if (dir == SENS_GAUCHE) {
		if (!mur_opaque(x - speed, y)) {
			marche(-speed);//x -= speed;
		} else {
			etat = ETAT_AVANCE;
			//speed=1;
			wait_for_charge = 0;
			charge_delay = 50 + rand() % 150;
			etape = 0;
			ss_etape = 0;
			onAvance();
			return;
		}
		pic = pbk_ennemis[150 + etape];
	} else {
		if (!mur_opaque(x + speed, y)) {
			marche(speed);//x += speed;
		} else {
			etat = ETAT_AVANCE;
			//speed=1;
			wait_for_charge = 0;
			charge_delay = 50 + rand() % 150;
			etape = 0;
			ss_etape = 0;
			onAvance();
			return;
		}
		pic = pbk_ennemis[148 + etape];
	}
	colFromPic();
}

void EnnemiKnukles::onTombe()
{
	int		yp;

	tombe();

	// Et si on arrêtait de tomber ?
	//
	if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
		etat = ETAT_NORMAL;
		dy = 0;
		y = yp;

		onAvance();
		return;
	}


	if (dir == SENS_DROITE) {
		x += speed;
		pic = pbk_ennemis[152];
	} else {
		x -= speed;
		pic = pbk_ennemis[160];
	}

	colFromPic();

}

void EnnemiKnukles::onCarbonise()
{
	tombe();
	ss_etape ++;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape ++;

	if (etape >= 10)
		a_detruire = true;
	else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[392 + etape];
		else
			pic = pbk_ennemis[402 + etape];
	}
}

void EnnemiKnukles::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (etat == ETAT_MEURE) {
		sbk_misc.play(10);
	}
}


void EnnemiKnukles::tombe()
{
	lat_grav += 1;
	lat_grav %= LATENCE_GRAVITE;

	if (lat_grav == 0 && dy < KNUKLES_GRAVITE_MAX)
		dy += 1;

	if (dy < 0 && mur_opaque(x, y + dy))
		dy = KNUKLES_GRAVITE_MAX;

	int ny = plat(x, y + dy);

	if (ny != 0 && dy > 0)
		y = ny;
	else
		y += dy;
}

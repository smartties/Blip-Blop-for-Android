
#include "ennemi_mario_hologramme.h"
#include "tir_mario_fireball.h"
#include "tir_mario_fireball_vertical.h"

const int anim_mario_marche_droite[] = { 0, 1, 2, 1};
const int anim_mario_marche_gauche[] = { 3, 4, 5, 4};
const int recul_mario[] = { 4, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

EnnemiMarioHologramme::EnnemiMarioHologramme(): speed(1), etape_speed(0), attack_delay(50 + rand() % 50), wait_for_attack(0), fireball(0), wait_for_cligno(0), cligno_delay(10 + rand() % 10)
{
	pv = 1;
	pic = pbk_ennemis[0];
}

void EnnemiMarioHologramme::update()
{
	wait_for_cligno++;
	if	(wait_for_cligno > cligno_delay + NB_CLIGNO) {
		decalage_cligno = 54;
		wait_for_cligno = 0;
		cligno_delay = 50 + rand() % 50;
	} else if (wait_for_cligno > cligno_delay) {
		decalage_cligno = 54;
	} else {
		decalage_cligno = 0;
	}

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
			onSaute();
			break;

		case ETAT_TIRE:
			switch (attack_type) {
				case 0:
					onTire();
					break;

				case 1:
					onTireverticale();
					break;
			}
			break;
	}

	//updateADetruire();
}

void EnnemiMarioHologramme::onAvance()
{
	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		onSaute();
	}

	//pour marcher

	if (x - speed < xmin || mur_opaque(x - speed, y)) {
		dir = SENS_DROITE;
		speed = 1;
	} else if (x + speed > offset + 600 || mur_opaque(x + speed, y)) {
		dir = SENS_GAUCHE;
		speed = 1;
	}
	wait_for_attack++;
	if ((wait_for_attack >= attack_delay) && (tete_turc != NULL)) {
		if (((dir == SENS_DROITE) && (tete_turc->x > x)) || ((dir == SENS_GAUCHE) && (tete_turc->x < x))) {
			etape = 0;
			ss_etape = 0;
			speed = 0;
			dy = -6;
			wait_for_attack = 0;
			attack_delay = 50 + rand() % 50;
			etat = ETAT_TIRE;
			y_cible = tete_turc->y;
			x_cible = tete_turc->x;
			attack_etape = 0;
			fireball = 1;
			attack_type = rand() % 2;
			switch (attack_type) {
				case 0:
					onTire();
					break;

				case 1:
					onTireverticale();
					break;
			}
			return;
		}
	}
	if (dir == SENS_DROITE) {
		marche(speed);
		pic = pbk_ennemis[anime(anim_mario_marche_droite, 4, 16 - (3 * speed)) + decalage_cligno];
	} else {
		marche(-speed);
		pic = pbk_ennemis[anime(anim_mario_marche_gauche, 4, 16 - (3 * speed)) + decalage_cligno];
	}
	if (speed < MARIO_SPEED) {
		etape_speed++;
		if (etape_speed >= 20) {
			etape_speed = 0;
			speed++;
		}
	}
	colFromPic();
}

void EnnemiMarioHologramme::onMeure()
{
	a_detruire = true;
}

void EnnemiMarioHologramme::onCharge()
{
	/*speed=MARIO_CHARGE_SPEED;
	if ( x - speed < xmin || mur_opaque( x-speed, y))
	{
		dir = SENS_DROITE;
		speed=1;
		etape=0;
		ss_etape=0;
		etat=ETAT_AVANCE;
		wait_for_attack=0;
		attack_delay=50 + rand() % 250;
		onAvance();
		return;
	}
	else if ( x + speed > offset + 640 || mur_opaque( x+speed, y))
	{
		dir = SENS_GAUCHE;
		speed=1;
		etape=0;
		ss_etape=0;
		etat=ETAT_AVANCE;
		wait_for_attack=0;
		attack_delay=50 + rand() % 250;
		onAvance();
		return;
	}
	attack_etape+=1;
	if (attack_etape<40)
	{
		if ( dir == SENS_DROITE)
		{
			pic = pbk_ennemis[anime( anim_mario_marche_droite, 4, 3)];
		}
		else
		{
			pic = pbk_ennemis[anime( anim_mario_marche_gauche, 4, 3)];
		}
	}
	else
	{
		if ( dir == SENS_DROITE)
		{
			marche(speed);
			pic = pbk_ennemis[anime( anim_mario_marche_droite, 4, 2)];
		}
		else
		{
			marche( -speed);
			pic = pbk_ennemis[anime( anim_mario_marche_gauche, 4, 2)];
		}
	}
	colFromPic();*/
}

void EnnemiMarioHologramme::onSaute()
{
	int		yp;

	if (dy < 0) {
		tombe_mario();
	} else {
		tombe();
	}

	//pour pas que le mario se tire en dehors de l'ecran...
	if ((dir == SENS_GAUCHE) && (x - speed < xmin || mur_opaque(x - speed, y))) {
		dir = SENS_DROITE;
		speed = 1;
	}

	else if ((dir == SENS_DROITE) && (x + speed > offset + 640 || mur_opaque(x + speed, y))) {
		dir = SENS_GAUCHE;
		speed = 1;
	}

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
		if (dy < 0) {
			pic = pbk_ennemis[6 + decalage_cligno];
		} else {
			pic = pbk_ennemis[7 + decalage_cligno];
		}
	} else {
		x -= speed;
		if (dy < 0) {
			pic = pbk_ennemis[8 + decalage_cligno];
		} else {
			pic = pbk_ennemis[9 + decalage_cligno];
		}
	}

	colFromPic();
}

void EnnemiMarioHologramme::onCarbonise()
{
	a_detruire = true;
	/*ss_etape += 1;
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
	}*/
}

void EnnemiMarioHologramme::affiche()
{
	Sprite::affiche();
	if (fireball) {
		if (dir == SENS_DROITE) {
			draw(x + 29, y - 33, pbk_ennemis[48 + etape]);
		} else {
			draw(x - 29, y - 33, pbk_ennemis[51 + etape]);
		}

	}
}

void EnnemiMarioHologramme::onTire()
{
	if (dir == SENS_DROITE)
		pic = pbk_ennemis[10 + decalage_cligno];

	else
		pic = pbk_ennemis[11 + decalage_cligno];


	if ((y - 25 < y_cible) && (y_cible < 400)) {
		if (y > y_cible - 60) {
			dy = 2;
		} else if (y > y_cible - 120) {
			dy = 3;
		} else if (y > y_cible - 180) {
			dy = 4;
		} else if (y > y_cible - 240) {
			dy = 5;
		} else {
			dy = 6;
		}
		y += dy;
	} else if ((y - 30 > y_cible) && (y_cible < 400)) {
		if (y < y_cible + 60) {
			dy = -2;
		} else if (y < y_cible + 120) {
			dy = -3;
		} else if (y < y_cible + 180) {
			dy = -4;
		} else if (y < y_cible + 240) {
			dy = -5;
		} else {
			dy = -6;
		}
		y += dy;
	} else {

		//y+=dy;
		ss_etape++;
		ss_etape %= 4;
		if (ss_etape == 0) {
			etape++;
			etape %= 3;
		}

		attack_etape++;
		if (attack_etape == 60) {
			etat = ETAT_AVANCE;
			etape = 0;
			ss_etape = 0;
			speed = 1;
			onAvance();
			return;
			fireball = 0;
			boule_de_feu();
		} else if (attack_etape >= 40) {
			if (attack_etape == 40) {
				fireball = 0;
				boule_de_feu();
			}
			if ((dir == SENS_DROITE) && (x > 10)) {
				x -= recul_mario[attack_etape - 40];
			} else if ((dir == SENS_GAUCHE) && (x < 630)) {
				x += recul_mario[attack_etape - 40];
			}
		}
	}
	colFromPic();
}

void EnnemiMarioHologramme::onTireverticale()
{
	if (dir == SENS_DROITE)
		pic = pbk_ennemis[10];

	else
		pic = pbk_ennemis[11];


	ss_etape++;
	ss_etape %= 4;
	if (ss_etape == 0) {
		etape++;
		etape %= 3;
	}

	attack_etape++;
	if (attack_etape == 40) {
		fireball = 0;
		TirMarioFireballVertical *	tir = new TirMarioFireballVertical(0, x_cible);

		tir->setDir(dir);
		if (dir == SENS_DROITE) {
			tir->x = x + 38;
		} else {
			tir->x = x - 38;
		}
		tir->y = y - 38;

		list_tirs_ennemis.ajoute((void*) tir);
	} else if (attack_etape == 80) {
		etat = ETAT_AVANCE;
		etape = 0;
		ss_etape = 0;
		speed = 1;
		onAvance();
		return;
	}
	colFromPic();
}

inline void EnnemiMarioHologramme::boule_de_feu()
{
	if (dir == SENS_DROITE) {
		TirMarioFireball *	tir = new TirMarioFireball(1);

		tir->setDir(dir);
		tir->x = x + 38;
		tir->y = y - 31;

		list_tirs_ennemis.ajoute((void*) tir);
	} else {
		TirMarioFireball *	tir = new TirMarioFireball(-1);

		tir->setDir(dir);
		tir->x = x - 38;
		tir->y = y - 31;

		list_tirs_ennemis.ajoute((void*) tir);
	}
}

void EnnemiMarioHologramme::tombe_mario()
{
	lat_grav += 1;
	lat_grav %= LATENCE_MARIO_GRAVITE;

	if (lat_grav == 0 && dy < GRAVITE_MAX)
		dy += 1;

	if (dy < 0 && mur_opaque(x, y + dy))
		dy = GRAVITE_MAX;

	int ny = plat(x, y + dy);

	if (ny != 0 && dy > 0)
		y = ny;
	else
		y += dy;
}

void EnnemiMarioHologramme::estTouche(Tir * tir)
{
	//static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	//static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	//Ennemi::estTouche( tir);
	//gicle( tir, dx_giclure, dy_giclure);
}

#include "ennemi_mariotapette.h"
#include "ennemi_luigi.h"
#include "gore_giclure.h"
#include "event_hold_fire.h"


const int anim_mario_marche_droite[] = { 75, 76, 77, 76};
const int anim_mario_marche_gauche[] = { 78, 79, 80, 79};
const int anim_nabo_droite[] = {164, 165};
const int anim_nabo_gauche[] = {166, 167};
const int anim_transformation_droite[] = {75, 164};
const int anim_transformation_gauche[] = {78, 166};

EnnemiMariotapette::EnnemiMariotapette(): speed(1), etape_speed(0), attack_delay(50 + rand() % 250), wait_for_attack(0), aide_luigi(0), nabo(0), nabo_delay(0), encaissement(0)
{
	pv = 10000;
	//pv = 1;
	xmin = 1280;
	pic = pbk_ennemis[78];
}

void EnnemiMariotapette::update()
{
	if (game_flag[0] < 1) {
		return;
	}

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

		case ETAT_SAUTE:
		case ETAT_TOMBE:
			onSaute();
			break;

		case ETAT_TIRE:
			onCharge();
			break;
	}

	//updateADetruire();
}

void EnnemiMariotapette::onAvance()
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
	} else if (x + speed > offset + 640 || mur_opaque(x + speed, y)) {
		dir = SENS_GAUCHE;
		speed = 1;
	}



	wait_for_attack++;


	if ((wait_for_attack >= attack_delay) && (tete_turc != NULL)) {
		if ((plat2(tete_turc->x, tete_turc->y) == plat2(x, y)) &&
		        (((dir == SENS_DROITE) && (x < tete_turc->x)) ||
		         ((dir == SENS_GAUCHE) && (x > tete_turc->x)))) {
			etape = 0;
			ss_etape = 0;
			attack_etape = 0;
			speed = 0;
			dy = 0;
			etat = ETAT_TIRE;
			onCharge();
			return;
		} else {
			int dif_y = tete_turc->y - y;
			int dif_x = tete_turc->x - x;

			if ((dir == SENS_DROITE) && (dif_y < 0) && (dif_x > 0) && (dif_y + dif_x < 0)) {
				etape = 0;
				ss_etape = 0;
				wait_for_attack = 0;
				attack_delay = 50 + rand() % 250;
				speed = ((dif_x * -9) / dif_y);
				dy = (int)(-9 + speed * 0.25);
				//debug<<"dy: "<<dy<<" speed: "<<speed<<" dif_x: "<<dif_x<<" dif_y: "<<dif_y<<"\n";
				etat = ETAT_SAUTE;
				lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur
				onSaute();
				return;
			} else if ((dir == SENS_GAUCHE) && (dif_y < 0) && (dif_x < 0) && (dif_y - dif_x < 0)) {
				etape = 0;
				ss_etape = 0;
				wait_for_attack = 0;
				attack_delay = 50 + rand() % 250;
				speed = ((dif_x * 9) / dif_y);
				dy = (int)(-9 + speed * 0.25);
				//debug<<"dy: "<<dy<<" speed: "<<speed<<" dif_x: "<<dif_x<<" dif_y: "<<dif_y<<"\n";
				etat = ETAT_SAUTE;
				lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur
				onSaute();
				return;
			}
		}
	}

	if (dir == SENS_DROITE) {
		marche(speed);
		pic = pbk_ennemis[anime(anim_mario_marche_droite, 4, 16 - (3 * speed))];

		if (encaissement < 0) {
			if (speed > - encaissement / MULTIPLACATEUR_VITESSE_AU_SOL) {
				speed += encaissement / MULTIPLACATEUR_VITESSE_AU_SOL;
			} else {
				speed = 0;
			}
		} else {
			if (speed + encaissement / MULTIPLACATEUR_VITESSE_AU_SOL < MARIO_SPEED) {
				speed += encaissement / MULTIPLACATEUR_VITESSE_AU_SOL;
			} else {
				speed = MARIO_SPEED;
			}
		}
	} else {
		marche(-speed);
		pic = pbk_ennemis[anime(anim_mario_marche_gauche, 4, 16 - (3 * speed))];

		if (encaissement > 0) {
			if (speed > encaissement / MULTIPLACATEUR_VITESSE_AU_SOL) {
				speed -= encaissement / MULTIPLACATEUR_VITESSE_AU_SOL;
			} else {
				speed = 0;
			}
		} else {
			if (speed - encaissement / MULTIPLACATEUR_VITESSE_AU_SOL < MARIO_SPEED) {
				speed -= encaissement / MULTIPLACATEUR_VITESSE_AU_SOL;
			} else {
				speed = MARIO_SPEED;
			}
		}
	}

	if (encaissement >= MULTIPLICATEUR_RECUL_SOL) {
		if (x + encaissement / MULTIPLICATEUR_RECUL_SOL < offset + 640) {
			x += encaissement / MULTIPLICATEUR_RECUL_SOL;
		}
		/*else
		{
			encaissement = 0;
		}*/
	} else if (encaissement <= -MULTIPLICATEUR_RECUL_SOL) {
		if (x + encaissement / MULTIPLICATEUR_RECUL_SOL > xmin) {
			x += encaissement / MULTIPLICATEUR_RECUL_SOL;
		}
		/*else
		{
			encaissement = 0;
		}*/
	}
	/*	if (dir == SENS_DROITE)
		{
			if (encaissement/100 <= speed)
			{
				marche(- encaissement/100);
			}
			else
			{
				if (x - encaissement/100 > xmin)
				{
					marche(- encaissement/100);
				}
				else
				{
					encaissement = 0;
				}
			}
		}
		else
		{
			if (encaissement/100 <= speed)
			{
				marche(encaissement/100);
			}
			else
			{
				if (x + encaissement/100 < offset + 640)
				{
					marche(encaissement/100);
				}
				else
				{
					encaissement = 0;
				}
			}
		}
	}*/

	/*if (encaissement > MARIO_ENDURANCE)
	{
		encaissement -= MARIO_ENDURANCE;
	}
	else if (encaissement < -MARIO_ENDURANCE)
	{
		encaissement += MARIO_ENDURANCE;
	}
	else
	{*/
	encaissement = 0;
	//}

	if (speed < MARIO_SPEED) {
		etape_speed++;
		if (etape_speed >= 20) {
			etape_speed = 0;
			speed++;
		}
	}

	colFromPic();
}

void EnnemiMariotapette::onMeure()
{
	if (!nabo) {
		tombe();
		nabo_delay ++;
		if (nabo_delay >= NABO_TRANSFORMATION) {
			speed = 1;
			nabo = true;
		} else {
			if (dir == SENS_DROITE) {
				pic = pbk_ennemis[anime(anim_transformation_droite, 2 , 6)];
			} else {
				pic = pbk_ennemis[anime(anim_transformation_gauche, 2 , 6)];
			}
		}
	} else {
		tombe();

		if (game_flag[0] >= 3) {
			if (!aide_luigi) {
				if (x - speed < xmin || mur_opaque(x - speed, y)) {
					dir = SENS_DROITE;
					speed = 2;
				} else if (x + speed > offset + 640 || mur_opaque(x + speed, y)) {
					dir = SENS_GAUCHE;
					speed = 2;
				}
			}

			if (dir == SENS_DROITE) {
				marche(speed);
				pic = pbk_ennemis[anime(anim_nabo_droite, 2, 16 - (3 * speed))];
			} else {
				marche(-speed);
				pic = pbk_ennemis[anime(anim_nabo_gauche, 2, 16 - (3 * speed))];
			}
		}

		/*if (speed<MARIO_SPEED)
		{
			etape_speed++;
			if (etape_speed>=20)
			{
				etape_speed=0;
				speed++;
			}
		}*/
	}

	if ((!aide_luigi) && (nabo)) {
		game_flag[3] = 1;
		aide_luigi = 1;
		dir = SENS_DROITE;
		Ennemi * luigi = new EnnemiLuigi();

		nb_ennemis_created++;

		luigi->x = 1960;
		luigi->y = y;
		luigi->dir = SENS_GAUCHE;
		list_ennemis.ajoute((void*) luigi);

		EventHoldFire e;

		e.x_activation = 0;
		e.flag = 0;
		e.val = 3;
		e.doEvent();
	}
}

void EnnemiMariotapette::onCharge()
{
	speed = MARIO_CHARGE_SPEED;
	if (x - speed < xmin || mur_opaque(x - speed, y)) {
		dir = SENS_DROITE;
		speed = 1;
		etape = 0;
		ss_etape = 0;
		etat = ETAT_AVANCE;
		wait_for_attack = 0;
		attack_delay = 50 + rand() % 250;
		encaissement = 0;
		onAvance();
		return;
	} else if (x + speed > offset + 640 || mur_opaque(x + speed, y)) {
		dir = SENS_GAUCHE;
		speed = 1;
		etape = 0;
		ss_etape = 0;
		etat = ETAT_AVANCE;
		wait_for_attack = 0;
		attack_delay = 50 + rand() % 250;
		encaissement = 0;
		onAvance();
		return;
	}
	attack_etape += 1;
	if (attack_etape < 40) {
		if (dir == SENS_DROITE) {
			pic = pbk_ennemis[anime(anim_mario_marche_droite, 4, 3)];
		} else {
			pic = pbk_ennemis[anime(anim_mario_marche_gauche, 4, 3)];
		}

		if (encaissement > 1000) {
			speed = 1;
			etape = 0;
			ss_etape = 0;
			etat = ETAT_AVANCE;
			wait_for_attack = 0;
			attack_delay = 50 + rand() % 250;
			encaissement = 0;
			onAvance();
			return;
		}
	} else {
		if (dir == SENS_DROITE) {
			marche(speed);
			pic = pbk_ennemis[anime(anim_mario_marche_droite, 4, 2)];
		} else {
			marche(-speed);
			pic = pbk_ennemis[anime(anim_mario_marche_gauche, 4, 2)];
		}
	}
	colFromPic();
}

void EnnemiMariotapette::onSaute()
{
	int		yp;

	if (dy < 0) {
		tombe_mario();
	} else {
		tombe();
	}

	//pour pas que le mario se tire en dehors de l'ecran...
	if (/*(dir==SENS_GAUCHE)&&*/(x - speed < xmin || mur_opaque(x - speed, y))) {
		dir = SENS_DROITE;
		speed = 1;
	}

	else if (/*(dir==SENS_DROITE)&&*/(x + speed > offset + 640 || mur_opaque(x + speed, y))) {
		dir = SENS_GAUCHE;
		speed = 1;
	}

	// Et si on arrêtait de tomber ?
	//
	if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
		etat = ETAT_NORMAL;
		dy = 0;
		y = yp;
		if (speed > MARIO_SPEED) {
			speed = MARIO_SPEED;
		}
		onAvance();
		return;
	}

	if (!nabo) {
		if (dir == SENS_DROITE) {
			x += speed;
			if (dy < 0) {
				pic = pbk_ennemis[81];
			} else {
				pic = pbk_ennemis[82];
			}

			if (encaissement != 0) {
				x += encaissement /  MULTIPLICATEUR_RECUL_AERIEN;
			}

			if (encaissement < 0) {
				if (speed + encaissement / MULTIPLICATEUR_VITESSE_AERIEN < 0) {
					//speed -= encaissement /MULTIPLICATEUR_VITESSE_AERIEN;
					if (speed + encaissement / MULTIPLICATEUR_VITESSE_AERIEN < -2 * MARIO_SPEED) {
						speed = - 2 * MARIO_SPEED;
					} else {
						speed += encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
					}
				} else {
					speed += encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
				}
				/*if (speed > - encaissement / MULTIPLICATEUR_VITESSE_AERIEN)
				{
					speed += encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
				}
				else
				{
					speed = 0;
				}*/

			} else {
				if (speed + encaissement / MULTIPLICATEUR_VITESSE_AERIEN < 2 * MARIO_SPEED) {
					speed += encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
				} else {
					speed = 2 * MARIO_SPEED;
				}
			}
		} else {
			x -= speed;
			if (dy < 0) {
				pic = pbk_ennemis[83];
			} else {
				pic = pbk_ennemis[84];
			}

			if (encaissement != 0) {
				x += encaissement / MULTIPLICATEUR_RECUL_AERIEN;
			}

			if (encaissement > 0) {

				if (speed - encaissement / MULTIPLICATEUR_VITESSE_AERIEN < 0) {

					if (speed - encaissement / MULTIPLICATEUR_VITESSE_AERIEN < -2 * MARIO_SPEED) {
						speed = - 2 * MARIO_SPEED;
					} else {
						speed -= encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
					}
				} else {
					speed -= encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
				}

			} else {
				if (speed - encaissement / MULTIPLICATEUR_VITESSE_AERIEN < 2 * MARIO_SPEED) {
					speed -= encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
				} else {
					speed = 2 * MARIO_SPEED;
				}
			}
		}
	} else {
		if (dir == SENS_DROITE) {
			x += speed;
			pic = pbk_ennemis[anime(anim_nabo_droite, 2, 16 - (3 * speed))];
		} else {
			x -= speed;
			pic = pbk_ennemis[anime(anim_nabo_gauche, 2, 16 - (3 * speed))];

		}
	}

	encaissement = 0;
	colFromPic();

}

void EnnemiMariotapette::onCarbonise()
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

void EnnemiMariotapette::tombe_mario()
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

void EnnemiMariotapette::estTouche(Tir * tir)
{
	Sprite * s;

	for (int i = 0; i < 4 ; i++) {
		if ((tir->dir >= 2) && (tir->dir <= 6)) {
			s = new GoreGiclure(rand() % 6 , -2 - rand() % 6);
		} else if ((tir->dir >= 10) && (tir->dir <= 14)) {
			s = new GoreGiclure(-rand() % 5 - 1, -2 - rand() % 6);
		} else {
			s = new GoreGiclure(rand() % 11 - 5, -2 - rand() % 6);
		}
		s->x = x + rand() % 11 - 5;
		s->y = y - rand() % 30 - 10;

		list_giclures.ajoute((void*) s);
	}

	if ((tir->dir >= 2) && (tir->dir <= 6)) {
		encaissement += tir->degats();
	} else if ((tir->dir >= 10) && (tir->dir <= 14)) {
		encaissement -= tir->degats();
	}


	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);
}

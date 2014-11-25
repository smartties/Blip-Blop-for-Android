
#include "ennemi_sonic.h"
#include "tir_epine.h"
#include "tir_sonic_eclair.h"
#include "morceau_sonic_ring.h"
#include "ben_debug.h"
#include "globals.h"

const int sonic_anim_boule_droite[] = {	46,	47,	50,	48,	49,	50};
const int sonic_anim_boule_gauche[] = { 51, 52, 55, 53, 54, 55};

const int sonic_anim_super_saien[] = {108, 109, 110, 109, 108, 109, 110, 111, 110, 109, 110, 111, 112, 111, 110, 111, 112, 113, 112, 111, 112, 113, 114, 113, 112, 113, 114, 115, 114, 113, 114, 115, 116, 115, 114, 115, 116, 117, 116, 115, 116, 117, 118};

EnnemiSonic::EnnemiSonic(): speed(1), etape_speed(0), attack_delay(50 + rand() % 250), wait_for_attack(0), vie_sous_critique(3750), vie_critique(2500), vie_sur_critique(1250), ring(90)
{
	pv = 10000;
	//pv = 2;
	xmin = 1280;
	ss_etape_attack = 0;
	etape_attack = 0;
	attack_phase = 0;
	nb_tir = 0;
	wait_sang_tombe = 0;
}

void EnnemiSonic::update()
{
	if (game_flag[0] == 7)
		a_detruire = true;

	if (wait_sang_tombe < 400) {
		wait_sang_tombe++;
		return;
	} else if (game_flag[0] < 4) {
		game_flag[0] = 4;
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

			switch (attack_type) {
				case 0:
					onAttackhorizontal();
					break;

				case 1:
					onAttackvertical();
					break;

				case 2:
					onAttackepine();
					break;

				case 3:
					onAttackeclair();
					break;
			}
			break;
	}

	//updateADetruire();
}

void EnnemiSonic::onAvance()
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
	if ((wait_for_attack >= attack_delay) && (ring == 0)) {
		if (tete_turc != NULL) {
			if ((tete_turc->y > 0) && (((dir == SENS_DROITE) && (((tete_turc->x) - x) > 0)) || ((dir == SENS_GAUCHE) && (((tete_turc->x) - x) < 0)))) {
				int rnd = rand() % 3;
//				debug <<rnd<<"\n";
				switch (rnd) {
					case 0:
						attack_type = 0;
						speed = 12;
						etat = ETAT_TIRE;
						x_cible = tete_turc->x;
						y_cible = tete_turc->y;
						nb_tir = 0;
						attack_phase = -1;
						ss_etape = 0;
						etape = 0;
						onAttackhorizontal();
						return;
						break;

					case 1:
						attack_phase = -1;
						attack_type = 1;
						speed = 12;
						etat = ETAT_TIRE;
						x_cible = tete_turc->x;
						y_cible = tete_turc->y;
						nb_tir = 0;
						ss_etape = 0;
						etape = 0;
						onAttackvertical();
						return;
						break;
					/*
									case 2:
										attack_type=2;
										speed=0;
										etat = ETAT_TIRE;
										nb_tir=0;
										ss_etape=0;
										etape=0;
										onAttackepine();
										return;
										break;
					*/
					case 2:
						attack_type = 3;
						ss_etape = 0;
						etape = 0;
						nb_tir = 0;
						//x_cible = tete_turc->x;
						etat = ETAT_TIRE;
						onAttackeclair();
						return;
						break;

				}
			}

			/*if ((plat2(tete_turc->x,tete_turc->y)==plat2(x,y))&&
				(((dir == SENS_DROITE)&&(x<tete_turc->x))||
				((dir == SENS_GAUCHE)&&(x>tete_turc->x))))
			{
				charge_etape=0;
				speed=0;
				dy=0;
				etat = ETAT_TIRE;
				onCharge();
				return;
			}
			else
			{
				wait_for_charge=0;
				charge_delay = 50 + rand() % 250;
				etat = ETAT_SAUTE;
				dy = -7;
				lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur
				onSaute();
				return;
			}*/
		}
	}

	if ((ring > 0) && (pv < 9000)) {
		if (ring % 30 == 0) {
			onBalancering();
//			game_flag[FLAG_BONUS] = 6;
		}
		ring--;
	}

	ss_etape += 1;
	ss_etape %= (10 - speed);
	if (ss_etape == 0) {
		etape += 1;
		etape %= 8;
	}
	if (dir == SENS_DROITE) {
		marche(speed);
		pic = pbk_ennemis[30 + etape];
	} else {
		marche(-speed);
		pic = pbk_ennemis[38 + etape];
	}
	if (speed < SONIC_SPEED) {
		etape_speed++;
		if (etape_speed >= 15) {
			etape_speed = 0;
			speed++;
		}
	}
	colFromPic();
}

void EnnemiSonic::onMeure()
{
	if (game_flag[2] == 0) {
		tombe();
		if (x - speed < xmin || mur_opaque(x - speed, y)) {
			dir = SENS_DROITE;
			speed = 1;
		} else if (x + speed > offset + 640 || mur_opaque(x + speed, y)) {
			dir = SENS_GAUCHE;
			speed = 1;
		}
		ss_etape += 1;
		ss_etape %= (10 - speed);
		if (ss_etape == 0) {
			etape += 1;
			etape %= 8;
		}
		if (dir == SENS_DROITE) {
			marche(speed);
			pic = pbk_ennemis[30 + etape];
		} else {
			marche(-speed);
			pic = pbk_ennemis[38 + etape];
		}
		if (speed < SONIC_SPEED) {
			etape_speed++;
			if (etape_speed >= 15) {
				etape_speed = 0;
				speed++;
			}
		}

		if ((plat2(x, y) == 0) && (x > 1600) && (x < 1630)) {
			game_flag[2] = 1;
			etape = 0;
			ss_etape = 0;
			dir = SENS_GAUCHE;
		}
	} else if (game_flag[2] == 1) {
		y -= 1;
		ss_etape ++;
		ss_etape %= 5;
		if (ss_etape == 0) {
			tremblement((etape / 5) + 2);
			etape ++;
			if (etape >= 43) {
				game_flag[2] = 2;
				a_detruire = true;
			} else {
				pic = pbk_ennemis[sonic_anim_super_saien[etape]];
			}
		}
	}
}

void EnnemiSonic::onCharge()
{
	/*speed=TOAD_CHARGE_SPEED;
	if ( x - speed < xmin || mur_opaque( x-speed, y))
	{
		dir = SENS_DROITE;
		speed=1;
		etat=ETAT_AVANCE;
		wait_for_charge=0;
		charge_delay=50 + rand() % 250;
		onAvance();
		return;
	}
	else if ( x + speed > offset + 640 || mur_opaque( x+speed, y))
	{
		dir = SENS_GAUCHE;
		speed=1;
		etat=ETAT_AVANCE;
		wait_for_charge=0;
		charge_delay=50 + rand() % 250;
		onAvance();
		return;
	}
	charge_etape+=1;
	if (charge_etape<80)
	{
		if ( dir == SENS_DROITE)
		{
			//marche(speed);
			pic = pbk_ennemis[anime( anim_toad_marche_droite, 4, 3)];
		}
		else
		{
			//marche( -speed);
			pic = pbk_ennemis[anime( anim_toad_marche_gauche, 4, 3)];
		}
	}
	else
	{
		if ( dir == SENS_DROITE)
		{
			marche(speed);
			pic = pbk_ennemis[anime( anim_toad_marche_droite, 4, 2)];
		}
		else
		{
			marche( -speed);
			pic = pbk_ennemis[anime( anim_toad_marche_gauche, 4, 2)];
		}
	}


	colFromPic();*/
}

void EnnemiSonic::onSaute()
{
	int		yp;

	tombe();

	// Et si on arrêtait de tomber ?
	//
	if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
		etat = ETAT_NORMAL;
		dy = 0;
		y = yp;
		ss_etape = 0;
		etape = 0;
		onAvance();
		return;
	}

	//pour pas que sonic se barre en dehors de l'ecran
	if ((dir == SENS_GAUCHE) && (x - speed < xmin || mur_opaque(x - speed, y))) {
		dir = SENS_DROITE;
		speed = 1;
	}

	else if ((dir == SENS_DROITE) && (x + speed > offset + 640 || mur_opaque(x + speed, y))) {
		dir = SENS_GAUCHE;
		speed = 1;
	}


	ss_etape += 1;
	ss_etape %= (10 - speed);
	if (ss_etape == 0) {
		etape += 1;
		etape %= 8;
	}
	if (dir == SENS_DROITE) {
		marche(speed);
		pic = pbk_ennemis[30 + etape];
	} else {
		marche(-speed);
		pic = pbk_ennemis[38 + etape];
	}
	colFromPic();

}

void EnnemiSonic::onAttackhorizontal()
{
	if (attack_phase == -1) {
		if (pv < vie_sous_critique) {
			ss_etape_attack += 1;
			ss_etape_attack %= 2;
			if (ss_etape_attack == 0) {
				etape_attack += 1;
				etape_attack %= 16;
//				balance_epines();
			}
		}
		nb_tir += 1;
		if (nb_tir == 50) {
			attack_phase = 0;
		} else {
			ss_etape += 1;
			ss_etape %= 2;
			if (ss_etape == 0) {
				etape += 1;
				etape %= 5;
			}
			if (dir == SENS_DROITE) {
				pic = pbk_ennemis[85 + etape];
			} else {
				pic = pbk_ennemis[91 + etape];
			}
		}

	} else {
		if (attack_phase == 0) {
			if (pv < vie_critique) {
				ss_etape_attack += 1;
				ss_etape_attack %= 2;
				if (ss_etape_attack == 0) {
					etape_attack += 1;
					etape_attack %= 16;
//					balance_epines();
				}
			}
			tombe();
			if ((dir == SENS_DROITE) && (x + speed > 1900)) {
				speed = 0;
				dy = - 12;
				attack_phase = 1;
			}
			if ((dir == SENS_GAUCHE) && (x - speed < 1300)) {
				speed = 0;
				dy = -12;
				attack_phase = 1;
			}
		} else if (attack_phase == 1) {
			tombe();
			if (pv < vie_sur_critique) {
				ss_etape_attack += 1;
				ss_etape_attack %= 2;
				if (ss_etape_attack == 0) {
					etape_attack += 1;
					etape_attack %= 16;
//					balance_epines();
				}
			}
			if (y + dy < y_cible) {
				if (dir == SENS_DROITE) {
					attack_phase = 2;
					dir = SENS_GAUCHE;
					dy = 0;
					speed = 12;
				} else {
					attack_phase = 2;
					dir = SENS_DROITE;
					dy = 0;
					speed = 12;
				}
			}
		} else if (attack_phase == 2) {

			if (x - speed < xmin || mur_opaque(x - speed, y)) {
				dir = SENS_DROITE;
				speed = 1;
				etat = ETAT_AVANCE;
				wait_for_attack = 0;
				attack_delay = 50 + rand() % 250;
				ss_etape = 0;
				etape = 0;
				onAvance();
				return;
			} else if (x + speed > offset + 640 || mur_opaque(x + speed, y)) {
				dir = SENS_GAUCHE;
				speed = 1;
				etat = ETAT_AVANCE;
				wait_for_attack = 0;
				attack_delay = 50 + rand() % 250;
				ss_etape = 0;
				etape = 0;
				onAvance();
				return;
			}
		}
		if (dir == SENS_DROITE) {
			x += speed;
			pic = pbk_ennemis[anime(sonic_anim_boule_droite, 6, 3)];
		} else {
			x -= speed;
			pic = pbk_ennemis[anime(sonic_anim_boule_gauche, 6, 3)];
		}
	}
	colFromPic();
}

void EnnemiSonic::onAttackvertical()
{
	if (attack_phase == -1) {
		if (pv < vie_sous_critique) {
			ss_etape_attack += 1;
			ss_etape_attack %= 2;
			if (ss_etape_attack == 0) {
				etape_attack += 1;
				etape_attack %= 16;
//				balance_epines();
			}
		}
		nb_tir += 1;
		if (nb_tir == 50) {
			attack_phase = 0;
		} else {
			ss_etape += 1;
			ss_etape %= 2;
			if (ss_etape == 0) {
				etape += 1;
				etape %= 5;
			}
			if (dir == SENS_DROITE) {
				pic = pbk_ennemis[85 + etape];
			} else {
				pic = pbk_ennemis[91 + etape];
			}
		}

	} else {

		if (attack_phase == 0) {
			tombe();
			if (pv < vie_critique) {
				ss_etape_attack += 1;
				ss_etape_attack %= 2;
				if (ss_etape_attack == 0) {
					etape_attack += 1;
					etape_attack %= 16;
//					balance_epines();
				}
			}
			if ((dir == SENS_DROITE) && (x + speed > 1900)) {
				speed = 0;
				dy = - 12;
				attack_phase = 1;
			} else if ((dir == SENS_GAUCHE) && (x - speed < 1300)) {
				speed = 0;
				dy = -12;
				attack_phase = 1;
			}
		} else if (attack_phase == 1) {
			tombe();
			if (pv < vie_sur_critique) {
				ss_etape_attack += 1;
				ss_etape_attack %= 2;
				if (ss_etape_attack == 0) {
					etape_attack += 1;
					etape_attack %= 16;
//					balance_epines();
				}
			}
			if (y + dy < 40) {
				if (dir == SENS_DROITE) {
					attack_phase = 2;
					dir = SENS_GAUCHE;
					speed = -dy;
					dy = 0;
					//speed=12;
				} else {
					attack_phase = 2;
					dir = SENS_DROITE;
					speed = -dy;
					dy = 0;
					//speed=12;
				}
			}
		} else if (attack_phase == 2) {
			//tombe();
			if ((dir == SENS_DROITE) && (x > x_cible)) {
				attack_phase = 3;
				dy = 12;
				speed = 0;
			} else if ((dir == SENS_GAUCHE) && (x < x_cible)) {
				attack_phase = 3;
				dy = 12;
				speed = 0;
			}
		} else if (attack_phase == 3) {



			//y+=dy;
			// Et si on arrêtait de tomber ?
			//
			if (y + dy > y_plat[0][y]) {
				tombe();
				y = y_plat[0][y];
				//if ((dy > 0) && (yp=plat( x, y+dy)) != 0)
				//{
				dy = 0;
				//y = yp;
				ss_etape = 0;
				etape = 0;
				speed = 1;
				etat = ETAT_AVANCE;
				wait_for_attack = 0;
				attack_delay = 50 + rand() % 250;
				onAvance();
				return;
				//}
			} else {
				y += dy;
			}
		}
		if (dir == SENS_DROITE) {
			x += speed;
			pic = pbk_ennemis[anime(sonic_anim_boule_droite, 6, 3)];
		} else {
			x -= speed;
			pic = pbk_ennemis[anime(sonic_anim_boule_gauche, 6, 3)];
		}
	}
	colFromPic();
}

void EnnemiSonic::onAttackepine()
{
	nb_tir += 1;
	if (nb_tir > 200) {
		speed = 1;
		etat = ETAT_AVANCE;
		wait_for_attack = 0;
		attack_delay = 50 + rand() % 250;
		ss_etape = 0;
		etape = 0;
		onAvance();
		return;
	}

	ss_etape += 1;
	if (pv > vie_sous_critique) {
		ss_etape %= 5;
	} else if (pv > vie_critique) {
		ss_etape %= 4;
	} else if (pv > vie_sur_critique) {
		ss_etape %= 3;
	} else {
		ss_etape %= 2;
	}

	if (ss_etape == 0) {
		etape += 1;
		etape %= 5;
	}
	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[85 + etape];
	} else {
		pic = pbk_ennemis[91 + etape];
	}
	ss_etape_attack += 1;
	ss_etape_attack %= 1;
	if (ss_etape_attack == 0) {
		etape_attack += 1;
		etape_attack %= 16;
//		balance_epines();
	}
	colFromPic();
}

void EnnemiSonic::onAttackeclair()
{
	ss_etape++;
	ss_etape %= 5;
	if (ss_etape == 0) {
		etape++;
	}
	if (etape == 23) {
		speed = 1;
		etat = ETAT_AVANCE;
		wait_for_attack = 0;
		attack_delay = 50 + rand() % 250;
		ss_etape = 0;
		etape = 0;
		onAvance();
		return;
	}


	if ((etape == 5) && (ss_etape == 0)) {
		if ((nb_tir <= 1) && (pv < vie_sous_critique)) {
			etape = 0;
			ss_etape = 1;
		} else if ((nb_tir <= 2) && (pv < vie_critique)) {
			etape = 0;
			ss_etape = 1;
		} else if ((nb_tir <= 3) && (pv < vie_sur_critique)) {
			etape = 0;
			ss_etape = 1;
		}

	}

	if ((etape == 0) && (ss_etape == 1) && (tete_turc != NULL)) {
		//tremblement(5);
		TirSoniceclair *	tir;
		tir = new TirSoniceclair();
		tir->setDir(dir);
		tir->x = tete_turc->x;
		tir->y = 0;
		list_tirs_ennemis.ajoute((void*) tir);
		nb_tir += 1;
	}

	if (dir == SENS_DROITE) {
		y -= 1;
		pic = pbk_ennemis[97 + ss_etape];
	} else {
		y -= 1;
		pic = pbk_ennemis[108 + ss_etape];
	}

	colFromPic();
}

void EnnemiSonic::onBalancering()
{
	Sprite * s;
	int i, mx = 1, my = 1;

	for (i = 0; i < 4; i++) {
		switch (i) {
			case 1:
				mx = -1;
				break;

			case 2:
				my = -1;
				break;

			case 3:
				mx = 1;
				break;
		}
		s = new MorceauSonicRing(1 * mx , 10 * my);
		s->x = x;
		s->y = y - 40;
		list_giclures.ajoute((void*) s);

		s = new MorceauSonicRing(3 * mx , 9 * my);
		s->x = x;
		s->y = y - 40;
		list_giclures.ajoute((void*) s);

		s = new MorceauSonicRing(4 * mx , 7 * my);
		s->x = x;
		s->y = y - 40;
		list_giclures.ajoute((void*) s);

		s = new MorceauSonicRing(5 * mx , 6 * my);
		s->x = x;
		s->y = y - 40;
		list_giclures.ajoute((void*) s);

		s = new MorceauSonicRing(6 * mx , 5 * my);
		s->x = x;
		s->y = y - 40;
		list_giclures.ajoute((void*) s);

		s = new MorceauSonicRing(7 * mx, 4 * my);
		s->x = x;
		s->y = y - 40;
		list_giclures.ajoute((void*) s);

		s = new MorceauSonicRing(9 * mx , 3 * my);
		s->x = x;
		s->y = y - 40;
		list_giclures.ajoute((void*) s);

		s = new MorceauSonicRing(10 * mx, 1 * my);
		s->x = x;
		s->y = y - 40;
		list_giclures.ajoute((void*) s);
	}

}

void EnnemiSonic::balance_epines()
{
	TirEpine *	tir;
	switch (etape_attack) {
		case 0:
			tir = new TirEpine(59, 12, 0);
			tir->setDir(dir);
			tir->x = x + 23;
			tir->y = y - 13;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 1:
			tir = new TirEpine(60, 9, -2);
			tir->setDir(dir);
			tir->x = x + 23;
			tir->y = y - 18;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 2:
			tir = new TirEpine(61, 8, -8);
			tir->setDir(dir);
			tir->x = x + 18;
			tir->y = y - 23;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 3:
			tir = new TirEpine(62, 2, -9);
			tir->setDir(dir);
			tir->x = x + 13;
			tir->y = y - 23;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 4:
			tir = new TirEpine(63, 0, -12);
			tir->setDir(dir);
			tir->x = x + 0;
			tir->y = y - 23;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 5:
			tir = new TirEpine(64, -2, -9);
			tir->setDir(dir);
			tir->x = x - 13;
			tir->y = y - 23;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 6:
			tir = new TirEpine(65, -8, -8);
			tir->setDir(dir);
			tir->x = x - 18;
			tir->y = y - 23;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 7:
			tir = new TirEpine(66, -9, -2);
			tir->setDir(dir);
			tir->x = x - 23;
			tir->y = y - 18;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 8:
			tir = new TirEpine(67, -12, 0);
			tir->setDir(dir);
			tir->x = x - 23;
			tir->y = y - 13;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 9:
			tir = new TirEpine(68, -9, 2);
			tir->setDir(dir);
			tir->x = x - 23;
			tir->y = y - 8;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 10:
			tir = new TirEpine(69, -8, 8);
			tir->setDir(dir);
			tir->x = x - 18;
			tir->y = y - 3;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 11:
			tir = new TirEpine(70, -2, 9);
			tir->setDir(dir);
			tir->x = x - 13;
			tir->y = y - 3;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 12:
			tir = new TirEpine(71, 0, 12);
			tir->setDir(dir);
			tir->x = x - 0;
			tir->y = y - 0;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 13:
			tir = new TirEpine(72, 2, 9);
			tir->setDir(dir);
			tir->x = x + 13;
			tir->y = y - 3;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 14:
			tir = new TirEpine(73, 8, 8);
			tir->setDir(dir);
			tir->x = x + 18;
			tir->y = y - 8;
			list_tirs_ennemis.ajoute((void*) tir);
			break;

		case 15:
			tir = new TirEpine(74, 9, 2);
			tir->setDir(dir);
			tir->x = x + 18;
			tir->y = y - 13;
			list_tirs_ennemis.ajoute((void*) tir);
			break;
	}
}

void EnnemiSonic::onCarbonise()
{
	a_detruire = true;
}

void EnnemiSonic::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);
}
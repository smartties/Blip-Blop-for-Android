#include "ennemi_rayman.h"
#include "tir_rayman_poing.h"
#include "morceau_rayman.h"
#include "ennemi_pikashu_heros.h"
#include "ennemi_bulbizarre_heros.h"
#include "ennemi_com_heros.h"
#include "ennemi_flameche_heros.h"
#include "morceau_tete_rayman.h"


EnnemiRayman::EnnemiRayman(): dorkemon(4), attack_delay(100 + rand() % 250), wait_for_attack(0), tir_poing(NULL), poing1(1), poing2(1), pieds(1)
{
	pv = 15000;
	xmin = 10428;
	tresor = 0;
}

void EnnemiRayman::update()
{
	if (blood > 0)
		blood -= 1;

	if (x < 10930 && game_flag[3] == 0) {
		game_flag[3] = 1;
	}

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			if (game_flag[0] > 0) {
				onAvance();
			}
			break;

		case ETAT_CARBONISE:
		case ETAT_MEURE:
			onMeure();
			break;

		case ETAT_SAUTE:
		case ETAT_TOMBE:
			onTombe();
			break;

		case ETAT_TIRE:
			onTire();
			break;
	}

	updateADetruire();
}

void EnnemiRayman::onAvance()
{
	if ((game_flag[1] <= dorkemon) && (game_flag[0] == 2) && (game_flag[1] > 0)) {
		if (game_flag[1] == 4) {
			EnnemiBulbizarreHeros * bulbizarre = new EnnemiBulbizarreHeros();

			bulbizarre->x = x - 10;
			bulbizarre->y = y - 25;
			bulbizarre->dir = SENS_GAUCHE;
			list_ennemis.ajoute((void*) bulbizarre);

			nb_ennemis_created++;

			mbk_niveau.play(1);
			game_flag[FLAG_TIMER] = 70;

			dorkemon --;
		} else if (game_flag[1] == 3) {
			EnnemiFlamecheHeros * flameche = new EnnemiFlamecheHeros();

			flameche->x = x - 10;
			flameche->y = y - 25;
			flameche->dir = SENS_GAUCHE;
			list_ennemis.ajoute((void*) flameche);


			nb_ennemis_created++;

			EnnemiComHeros * Com = new EnnemiComHeros();

			Com->x = x - 10;
			Com->y = y - 25;
			Com->dir = SENS_GAUCHE;
			list_ennemis.ajoute((void*) Com);

			dorkemon -= 2;

		} else if (game_flag[1] == 1) {
			EnnemiPikachuHeros * pika = new EnnemiPikachuHeros();

			nb_ennemis_created++;

			pika->x = x - 10;
			pika->y = y - 25;
			pika->dir = SENS_GAUCHE;
			list_ennemis.ajoute((void*) pika);
			dorkemon --;
		}
	} else if ((game_flag[0] <= 2) && (game_flag[1] == 0) /*&& (game_flag[2]>=0*/) {
		if (game_flag[0] == 2) {
			if ((pv > PV_SOUS_CRITIQUE) || ((pv > PV_CRITIQUE) && (poing1) && ((x - offset < 80) || (x - offset > 600)))) {
				// Si plus de plateformes on passe dans l'etat TOMBE
				//
				if (plat(x, y) == 0) {
					etat = ETAT_TOMBE;
					dy = 0;
					lat_grav = 0;
					onTombe();
				}

				//pour marcher

				if (x - RAYMAN_SPEED < xmin || mur_opaque(x - RAYMAN_SPEED, y)) {
					dir = SENS_DROITE;
				} else if (x + RAYMAN_SPEED > offset + 600 || mur_opaque(x + RAYMAN_SPEED, y)) {
					dir = SENS_GAUCHE;
				}
				wait_for_attack++;
				if ((wait_for_attack >= attack_delay) && (tete_turc != NULL)) {

					if ((plat2(tete_turc->x, tete_turc->y) == plat2(x, y)) &&
					        (((dir == SENS_DROITE) && (x < tete_turc->x)) ||
					         ((dir == SENS_GAUCHE) && (x > tete_turc->x)))) {
						//attack_etape=0;
						x_cible = tete_turc->x;
						dy = 0;
						etat = ETAT_TIRE;
						range_poing = 0;
						etape = 0;
						ss_etape = 0;
						attack_etape = 0;
						onTire();
						return;
					}
				}
				ss_etape++;
				ss_etape %= 3;
				if (ss_etape == 0) {
					etape++;
					etape %= 21;
				}
				if (dir == SENS_DROITE) {
					marche(RAYMAN_SPEED);
					pic = pbk_ennemis[188 + etape];
				} else {
					marche(-RAYMAN_SPEED);
					pic = pbk_ennemis[209 + etape];
				}
			} else if ((pv > PV_CRITIQUE) && (x - offset >= 80) && (x - offset <= 600)) {

				if (poing1) {
					Sprite * s;
					//faire gicler le premier poing
					if (x - offset > 320) {
						s = new MorceauRayman(230, -1 - rand() % 3, -3 - rand() % 3);
					} else {
						s = new MorceauRayman(230, 1 + rand() % 3, -3 - rand() % 3);
					}

					s->dir = dir;
					s->y = y - 22;
					s->x = x;

					list_giclures.ajoute((void*) s);

					game_flag[0] = 1;
					poing1 = 0;
				}
				wait_for_attack++;
				if ((wait_for_attack >= attack_delay) && (tete_turc != NULL)) {

					if (plat2(tete_turc->x, tete_turc->y) == plat2(x, y))

					{
						if (x < tete_turc->x) {
							dir = SENS_DROITE;

						} else {
							dir = SENS_GAUCHE;

						}
						x_cible = tete_turc->x;
						dy = 0;
						etat = ETAT_TIRE;
						range_poing = 0;
						etape = 0;
						ss_etape = 0;
						attack_etape = 0;
						onTire();
						return;
					}
				}
				if (dir == SENS_DROITE) {
					pic = pbk_ennemis[268];
				} else {
					pic = pbk_ennemis[269];
				}
			} else if ((pv > PV_SUR_CRITIQUE)) { //||((pv<PV_SUR_CRITIQUE)&&((x-offset<80)||(x-offset>600))))
				if (poing2) {
					//faire gicler le second poing
					Sprite * s;
					if (x - offset > 320) {
						s = new MorceauRayman(231, -1 - rand() % 3, -3 - rand() % 3);
					} else {
						s = new MorceauRayman(231, 1 + rand() % 3, -3 - rand() % 3);
					}

					s->dir = dir;
					s->y = y - 22;
					s->x = x;

					list_giclures.ajoute((void*) s);
					game_flag[0] = 1;
					poing2 = 0;
				}

				// Si plus de plateformes on passe dans l'etat TOMBE
				//
				if (plat(x, y) == 0) {
					etat = ETAT_TOMBE;
					dy = 0;
					lat_grav = 0;
					onTombe();
				}

				//pour marcher

				if (x - RAYMAN_SPEED < xmin || mur_opaque(x - RAYMAN_SPEED, y)) {
					dir = SENS_DROITE;
				} else if (x + RAYMAN_SPEED > offset + 600 || mur_opaque(x + RAYMAN_SPEED, y)) {
					dir = SENS_GAUCHE;
				}

				ss_etape++;
				ss_etape %= 3;
				if (ss_etape == 0) {
					etape++;
					etape %= 8;
				}
				if (dir == SENS_DROITE) {
					marche(RAYMAN_CRITICAL_SPEED);
					pic = pbk_ennemis[250 + etape];
				} else {
					marche(-RAYMAN_CRITICAL_SPEED);
					pic = pbk_ennemis[258 + etape];
				}

			} else  if ((x - offset >= 80) && (x - offset <= 600)) {
				if (pieds) {
					//faire gicler les pieds
					int vy = -3 - rand() % 3;

					Sprite * s = new MorceauRayman(270, 1 + rand() % 3, vy);

					s->dir = dir;
					s->y = y - 22;
					s->x = x + 10;

					list_giclures.ajoute((void*) s);


					s = new MorceauRayman(271, -1 - rand() % 3, vy);

					s->dir = dir;
					s->y = y - 22;
					s->x = x - 10;

					list_giclures.ajoute((void*) s);

					game_flag[0] = 1;
					pieds = 0;
				}

				if (dir == SENS_DROITE) {
					pic = pbk_ennemis[266];
				} else {
					pic = pbk_ennemis[267];
				}
			}
		}
		colFromPic();
	} else if (x - offset > 445) {
		ss_etape++;
		ss_etape %= 3;
		if (ss_etape == 0) {
			etape++;
			etape %= 21;
		}
		if (dir == SENS_DROITE) {
			marche(RAYMAN_SPEED);
			pic = pbk_ennemis[188 + etape];
		} else {
			marche(-RAYMAN_SPEED);
			pic = pbk_ennemis[209 + etape];
		}

		if (game_flag[3] == 1) { //x-offset<450)
//			game_flag[0]=2;
			col_on = false;
		}
	}

}

void EnnemiRayman::onMeure()
{
	ss_etape ++;
	ss_etape %= 6;

	if ((etape == 0) && (ss_etape == 1)) {
		//fait gicler la tete
		Sprite * tete;
		if (x - offset > 320) {
			tete = new MorceauTeteRayman(-1 - rand() % 3, -3 - rand() % 3);
		} else {
			tete = new MorceauTeteRayman(1 + rand() % 3, -3 - rand() % 3);
		}
		tete->x = x;
		tete->y = y - 60;
		list_giclures.ajoute((void*) tete);
		game_flag[3] = 2;
	}

	if (ss_etape == 0) {
		etape ++;
		if (etape >= 6) {
			a_detruire = true;
		} else {
			if ((etape < 2) && (dir == SENS_DROITE)) {
				pic = pbk_ennemis[494 + etape];
			} else {
				pic = pbk_ennemis[488 + etape];
			}
		}
	}
}

void EnnemiRayman::onTire()
{
	if (pv > PV_SOUS_CRITIQUE) {
		if (attack_etape == 0) {
			ss_etape++;
			ss_etape %= 3;
			if (ss_etape == 0) {
				etape++;
				etape %= 6;
				range_poing += 30;
				if ((dir == SENS_DROITE) && (x_cible - x < range_poing)) {
					tir_poing = new TirRaymanpoing(RAYMAN_POING1_SPEED, x_cible);
					tir_poing->setDir(dir);
					tir_poing->x = x + 13;
					tir_poing->y = y - 13;
					list_tirs_ennemis.ajoute((void*) tir_poing);

					attack_etape = 1;
					ss_etape = 0;
					etape = 6;
				} else if ((dir == SENS_GAUCHE) && (x - x_cible < range_poing)) {
					tir_poing = new TirRaymanpoing(-RAYMAN_POING1_SPEED, x_cible);
					tir_poing->setDir(dir);
					tir_poing->x = x - 13;
					tir_poing->y = y - 13;
					list_tirs_ennemis.ajoute((void*) tir_poing);

					attack_etape = 1;
					ss_etape = 0;
					etape = 6;
				}
			}

		} else if (attack_etape == 1) {
			ss_etape++;
			if (ss_etape == 20) {
				etape = 7;
			}

			if ((dir == SENS_DROITE) && (tir_poing->x < x)) {
				etat = ETAT_AVANCE;
				etape = 0;
				ss_etape = 0;
				wait_for_attack = 0;
				tir_poing->a_detruire = true;
				attack_delay = 50 + rand() % 150;
				onAvance();
				return;
			} else if ((dir == SENS_GAUCHE) && (tir_poing->x > x)) {
				etat = ETAT_AVANCE;
				etape = 0;
				ss_etape = 0;
				wait_for_attack = 0;
				tir_poing->a_detruire = true;
				attack_delay = 50 + rand() % 150;
				onAvance();
				return;
			}

		}

		if (dir == SENS_DROITE) {
			pic = pbk_ennemis[172 + etape];
		} else {
			pic = pbk_ennemis[180 + etape];
		}
	} else {
		if (attack_etape == 0) {
			ss_etape++;
			ss_etape %= 3;
			if (ss_etape == 0) {
				etape++;
				etape %= 7;
				range_poing += 30;
				if ((dir == SENS_DROITE) && (x_cible - x < range_poing)) {
					tir_poing = new TirRaymanpoing(RAYMAN_POING2_SPEED, x_cible);
					tir_poing->setDir(dir);
					tir_poing->x = x + 13;
					tir_poing->y = y - 13;
					list_tirs_ennemis.ajoute((void*) tir_poing);

					attack_etape = 1;
					ss_etape = 0;
					etape = 7;
				} else if ((dir == SENS_GAUCHE) && (x - x_cible < range_poing)) {
					tir_poing = new TirRaymanpoing(-RAYMAN_POING2_SPEED, x_cible);
					tir_poing->setDir(dir);
					tir_poing->x = x - 13;
					tir_poing->y = y - 13;
					list_tirs_ennemis.ajoute((void*) tir_poing);

					attack_etape = 1;
					ss_etape = 0;
					etape = 7;
				}
			}

		} else if (attack_etape == 1) {
			ss_etape++;
			if (ss_etape == 20) {
				etape = 8;
			}

			if ((dir == SENS_DROITE) && (tir_poing->x < x)) {
				etat = ETAT_AVANCE;
				etape = 0;
				ss_etape = 0;
				wait_for_attack = 0;
				tir_poing->a_detruire = true;
				attack_delay = 10 + rand() % 50;
				onAvance();
				return;
			} else if ((dir == SENS_GAUCHE) && (tir_poing->x > x)) {
				etat = ETAT_AVANCE;
				etape = 0;
				ss_etape = 0;
				wait_for_attack = 0;
				tir_poing->a_detruire = true;
				attack_delay = 10 + rand() % 50;
				onAvance();
				return;
			}

		}

		if (dir == SENS_DROITE) {
			pic = pbk_ennemis[232 + etape];
		} else {
			pic = pbk_ennemis[241 + etape];
		}
	}

	colFromPic();
}

void EnnemiRayman::onTombe()
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


	/*if ( dir == SENS_DROITE)
	{
		x += speed;
		pic = pbk_ennemis[3];
	}
	else
	{
		x -= speed;
		pic = pbk_ennemis[7];
	}*/

	colFromPic();

}

void EnnemiRayman::estTouche(Tir * tir)
{
	//static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	//static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };
	static const int dx_giclure [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure [] = { -15, -15, -15, -15, -15, -15, -15, -15 };

	if (game_flag[1] == 0) {
		Ennemi::estTouche(tir);
		gicle(tir, dx_giclure, dy_giclure);
	}
}
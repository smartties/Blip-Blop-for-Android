
#include "ennemi_bisou_chaman.h"
#include "tir_boule_chaman.h"
#include "tir_colonne_chaman.h"
#include <math.h>

static const int xtel [] = { 8144,		// Haut droite
                             8082,		// Droite
                             7653
                           };	// Gauche

static const int ytel [] = { 296, 130, 188 };

#define ETAT_LEVEBATON		30
#define ETAT_BAISSEBATON	31
#define ETAT_TELE			32

EnnemiBisouChaman::EnnemiBisouChaman() : etape_shoot(0), nb_touch(0), n_pos(1)
{
	pv = 11000;
	wait_shoot = 250 + rand() % 50;
	tresor = 0;
}


void EnnemiBisouChaman::update()
{
	game_flag[2] = 1;

	if (game_flag[0] == 1) {
		mbk_niveau.play(1);
		game_flag[0] = 2;
		game_flag[FLAG_TIMER] = 50;
	}

	if (blood > 0)
		blood -= 1;

	etape_shoot += 1;

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_LEVEBATON:
			onLeveBaton();
			break;

		case ETAT_TELE:
			onTele();
			break;

		case ETAT_BAISSEBATON:
			onBaisseBaton();
			break;

		case ETAT_TIRE:
			onTire();
			break;

		case ETAT_MEURE:
		case ETAT_CARBONISE:
			onCarbonise();
			break;
	}

	updateADetruire();
}

void EnnemiBisouChaman::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	if (etape > 12) {
		grave(x, y, pic);
		a_detruire = true;
	} else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[332 + etape];
		else
			pic = pbk_ennemis[345 + etape];
	}
}

void EnnemiBisouChaman::onTele()
{
	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape += 1;

		if (etape == 8) {
			int new_pos;

			if (tete_turc->x > offset + 320) {
				new_pos = 2;
			} else {
				if (tete_turc->y < 280)
					new_pos = 0;
				else
					new_pos = 1;
			}

			if (new_pos != n_pos) {
				n_pos = new_pos;
			} else {
				n_pos += rand() % 2 + 1;
				n_pos %= 3;
			}


			x = xtel[n_pos];
			y = ytel[n_pos];
		} else if (etape == 19) {
			etat = ETAT_NORMAL;
			nb_touch = 0;
			return;
		}
	}

	if (etape <= 7) {
		if (x < offset + 320) {
			pic = pbk_ennemis[316 + etape];
			dir = SENS_DROITE;
		} else {
			pic = pbk_ennemis[324 + etape];
			dir = SENS_GAUCHE;
		}
	} else if (etape <= 10) {
		if (ss_etape % 2 == 0) {
			if (x < offset + 320) {
				pic = pbk_ennemis[323];
				dir = SENS_DROITE;
			} else {
				pic = pbk_ennemis[331];
				dir = SENS_GAUCHE;
			}
		} else {
			pic = NULL;
		}
	} else {
		if (x < offset + 320) {
			pic = pbk_ennemis[323 - (etape - 11)];
			dir = SENS_DROITE;
		} else {
			pic = pbk_ennemis[331 - (etape - 11)];
			dir = SENS_GAUCHE;
		}
	}

	noCol();
}

void EnnemiBisouChaman::onLeveBaton()
{
	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0) {
		etape += 1;

		if (etape > 2) {
			etape = ss_etape = 0;
			etat = ETAT_TIRE;
			nb_lueurs = 0;
			onTire();
			return;
		}
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[358 + etape];
	else
		pic = pbk_ennemis[361 + etape];

	colFromPic();
}


void EnnemiBisouChaman::onBaisseBaton()
{
	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0) {
		etape += 1;

		if (etape > 2) {
			etape = ss_etape = 0;
			etat = ETAT_AVANCE;
			wait_shoot = 100 + rand() % 50;
			etape_shoot = 0;
			return;
		}
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[360 - etape];
	else
		pic = pbk_ennemis[363 - etape];

	colFromPic();
}


void EnnemiBisouChaman::onTire()
{
	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 11;

		if (etape == 0) {
			nb_lueurs += 1;

			if (nb_lueurs >= 3) {
				bool	boule_feu = false;
				int		xc;
				int		yc;
				int		ddx;
				int		ddy;

				// Décide de l'attaque à effectuer
				//
				if (tete_turc != NULL) {
					xc = tete_turc->x;
					yc = tete_turc->y;

					ddx = xc - x;
					ddy = yc - (y - 72);

					int dist = int(sqrt(((ddx * ddx) + (ddy * ddy))));

					ddx = (ddx * 6) / dist;
					ddy = (ddy * 6) / dist;

					int pente;
					if (ddy == 0)
						pente = 10;
					else
						pente = ddx / ddy;

					if (pente < -1 || pente > 1)
						boule_feu = true;
				}

				if (boule_feu) {
					TirBouleChaman * s = new TirBouleChaman();

					s->y = y - 72;

					if (dir == SENS_DROITE)
						s->x = x + 18;
					else
						s->x = x - 18;

					s->dx = (ddx * 4) / 3;
					s->dy = (ddy * 4) / 3;

					list_tirs_ennemis.ajoute((void*) s);
				} else {
					TirColonneChaman * s = new TirColonneChaman();

					s->y = y - 72;

					if (dir == SENS_DROITE)
						s->x = x + 18;
					else
						s->x = x - 18;

					s->setDir(dir);

					list_tirs_ennemis.ajoute((void*) s);
				}


				etape = ss_etape = 0;
				etat = ETAT_BAISSEBATON;
			}
		}
	}

	colFromPic();
}


void EnnemiBisouChaman::affiche()
{
	Sprite::affiche();

	if (etat == ETAT_TIRE) {
		if (dir == SENS_DROITE)
			draw(x + 18, y - 70, pbk_ennemis[405 + etape]);
		else
			draw(x - 18, y - 70, pbk_ennemis[416 + etape]);
	}
}



void EnnemiBisouChaman::onAvance()
{
	static const int SPEED = 1;

	tombe();

	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 8;
	}


	if (x < offset + 320) {
		pic = pbk_ennemis[316];
		dir = SENS_DROITE;
	} else {
		pic = pbk_ennemis[324];
		dir = SENS_GAUCHE;
	}

	if (etape_shoot > wait_shoot && etape == 0) {
		etat = ETAT_LEVEBATON;
		ss_etape = 0;
		onLeveBaton();
	}

	if (nb_touch >= 10) {
		etape = ss_etape = 0;
		etat = ETAT_TELE;
		sbk_niveau.play(16);
	}

	colFromPic();
}


void EnnemiBisouChaman::onCarbonise()
{
	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape += 1;

		if (etape > 7) {
			a_detruire = true;
			return;
		}
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[573 + etape];
	else
		pic = pbk_ennemis[581 + etape];
}


void EnnemiBisouChaman::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 7, 10, 7, 0, -7, -10, -7 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	nb_touch++;

	if (etat == ETAT_MEURE || etat == ETAT_CARBONISE) {
		game_flag[0] = 7;
		game_flag[FLAG_GEN_OFF] = 1;
		sbk_niveau.play(19);
	}
}

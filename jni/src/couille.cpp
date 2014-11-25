/******************************************************************
*
*
*		-----------------
*		    Couille.cpp
*		-----------------
*
*		Pour Blip et Blop
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#include <stdio.h>
#include "config.h"
#include "couille.h"
#include "tir_bbm16.h"
#include "tir_bbpm.h"
#include "tir_bb_fusil.h"
#include "tir_bb_laser.h"
#include "tir_bb_vache.h"

//-----------------------------------------------------------------------------
//		Animes
//-----------------------------------------------------------------------------

//----- Animations de Blip ----------------------------------------------------

const int anim_blip_marche_droite[] = { 0, 1, 2, 1 };
const int anim_blip_marche_gauche[] = { 3, 4, 5, 4 };

const int anim_blip_saute_droite [] = { 8, 8, 8, 7, 7, 6, 6, 0, 0, 0, 0 };
const int anim_blip_saute_gauche [] = { 11, 11, 11, 10, 10, 9, 9, 3, 3, 3, 3 };

const int anime_sautille [] = { 0, 2, 4, 2 };


//----- Animations des détonations -------------------------------------------

const int anim_m16_deto[] = { 0, 1, 2, 1, 0 };
const int anim_pm_deto [] = { 0, 1, 2, 1, 0 };
const int anim_fusil_deto [] = { 0, 1, 2, 1, 0 };


//----- Coordonnées des armes -------------------------------------------------

const int dx_m16 [] = { 3, 6, 0, 2, 7, -7, -2, 0, -6, -3 };
const int dy_m16 [] = { -15, -9, -12, -10, -10, -10, -10, -12, -9, -15 };

const int dx_pm [] = { 2,   6,  0,   0,   7,  -7, 0,  0,   -6, -2 };
const int dy_pm [] = { -12, -6, -10, -15, -9, -9, -15, -10, -6, -12 };

const int dx_lf [] = { -10, -10, -10, -10, -10, 10, 10, 10, 10, 10 };
const int dy_lf [] = { -10, -10, -10, -10, -10, -10, -10, -10, -10, -10 };

const int dx_fusil [] = { 1, -4, -6, -4, -4, 4, 4, 6, 4, -1 };
const int dy_fusil [] = { -14, -12, -11, -10, -9, -9, -10, -11, -12, -14 };

const int dx_main_fusil [] = { 0, 17, 24, 18, -3, 3, -18, -24, -17, 0 };
const int dy_main_fusil [] = { 16, 10, -10, -31, -40, -38, -31, -10, 10, 16 };

const int dx_laser [] = { 1, -4, -6, -4, -4, 4, 4, 6, 4, -1 };
const int dy_laser [] = { -12, -12, -11, -10, -9, -9, -10, -11, -12, -11 };

const int dx_truc_laser [] = { -2, -1, 0, 3, -1, 1, -3, 0, 0, 2 };
const int dy_truc_laser [] = { -6, -5, -8, -13, -15, -15, -13, -8, -5, -5 };


//----- Coordonnées des détonation --------------------------------------------

const int dx_m16_deto [] = { -2, 20, 30, 22, -3, 3, -21, -30, -20, 2 };
const int dy_m16_deto [] = { 24, 20, -9, -31, -49, -49, -31, -9, 20, 24 };

const int dx_m16o_deto [] = { 1, 17, 22, 15, -4, 4, -15, -23, -20, -1 };
const int dy_m16o_deto [] = { 16, 9, -10, -25, -33, -33, -25, -10, 8, 16 };

const int dx_pm_deto [] = { -6, 12, 12, 11, -6,  6, -11,  -12, -13, -1 };
const int dy_pm_deto [] = { 6, 5, -11, -22, -28, -30, -22, -11, 5, 6 };

const int dx_fusil_deto [] = { 2, 29, 41, 29, -5, 5, -29, -41, -30, -2 };
const int dy_fusil_deto [] = { 33, 21, -12, -44, -57, -57, -44, -12, 21, 33 };

const int dx_laser_deto [] = { -3, 24, 37, 29, -1, 0, -29, -37, -24, 2 };
const int dy_laser_deto [] = { 32, 21, -8, -39, -53, -53, -39, -8, 21, 32 };


//----- Coordonnées des tirs -------------------------------------------------

const int dx_tir_m16 [] = { -2, 25, 35, 27, -3, 3, -26, -30, -25, 2 };
const int dy_tir_m16 [] = { 29, 25, -9, -36, -54, -54, -36, -9, 25, 29 };

const int dx_tir_pm [] = { -2, 25, 35, 27, -3, 3, -26, -30, -25, 2 };
const int dy_tir_pm [] = { 29, 25, -9, -36, -54, -54, -36, -9, 25, 29 };

const int dx_tir_fusil [] = { 2, 29, 41, 29, -5, 5, -29, -41, -30, -2 };
const int dy_tir_fusil [] = { 33, 21, -12, -44, -57, -57, -44, -12, 21, 33 };
/*
const int dx_tir_laser [] = { -5, 32, 37, 49, -3, -2, -49, -37, -32, 0 };
const int dy_tir_laser [] = { 32, 23, -10, -64, -53, -53, -64, -10, 23, 32 };
*/
const int dx_tir_laser [] = { -5, 42, 57, 56, -3, -2, -56, -57, -42, 0 };
const int dy_tir_laser [] = { 52, 33, -10, -71, -73, -73, -71, -10, 33, 52 };

const int dx_tir_lf [] = { -2, 32, 44, 31, 0, 1, -31, -44, -32, 2 };
const int dy_tir_lf [] = { 46, 33, -7, -46, -63, -63, -46, -7, 33, 46 };

//----- Recul des armes ------------------------------------------------------

const int x_recul [][5] = {
	{ 0, 0, 0, 0, 0 },		// BBDIR_BAS_B_D
	{ 0, -1, -2, -1, 0},	// BBDIR_BAS_DROITE
	{ 0, -2, -3, -2, 0},	// BBDIR_DROITE
	{ 0, -1, -2, -1, 0},	// BBDIR_HAUT_DROITE
	{ 0, 0, 0, 0, 0},		// BBDIR_HAUT_H_D
	{ 0, 0, 0, 0, 0},		// BBDIR_HAUT_H_G
	{ 0, 1, 2, 1, 0},		// BBDIR_HAUT_GAUCHE
	{ 0, 2, 3, 2, 0},		// BBDIR_GAUCHE
	{ 0, 1, 2, 1, 0},		// BBDIR_BAS_GAUCHE
	{ 0, 0, 0, 0, 0}		// BBDIR_BAS_B_G
};

const int y_recul [][5] = {
	{ 0, -2, -3, -2, 0 },	// BBDIR_BAS_B_D
	{ 0, -1, -2, -1, 0},	// BBDIR_BAS_DROITE
	{ 0, 0, 0, 0, 0},		// BBDIR_DROITE
	{ 0, 1, 2, 1, 0},		// BBDIR_HAUT_DROITE
	{ 0, 2, 3, 2, 0},		// BBDIR_HAUT_H_D
	{ 0, 2, 3, 2, 0},		// BBDIR_HAUT_H_G
	{ 0, 1, 2, 1, 0},		// BBDIR_HAUT_GAUCHE
	{ 0, 0, 0, 0, 0},		// BBDIR_GAUCHE
	{ 0, -1, -2, -1, 0},	// BBDIR_BAS_GAUCHE
	{ 0, -2, -3, -2, 0}		// BBDIR_BAS_B_G
};

const int x_recul_fusil [][5] = {
	{ 0, 0, 0, 0, 0 },		// BBDIR_BAS_B_D
	{ 0, -2, -4, -2, 0},	// BBDIR_BAS_DROITE
	{ 0, -4, -6, -4, 0},	// BBDIR_DROITE
	{ 0, -2, -4, -2, 0},	// BBDIR_HAUT_DROITE
	{ 0, 0, 0, 0, 0},		// BBDIR_HAUT_H_D
	{ 0, 0, 0, 0, 0},		// BBDIR_HAUT_H_G
	{ 0, 2, 4, 2, 0},		// BBDIR_HAUT_GAUCHE
	{ 0, 4, 6, 4, 0},		// BBDIR_GAUCHE
	{ 0, 2, 4, 2, 0},		// BBDIR_BAS_GAUCHE
	{ 0, 0, 0, 0, 0}		// BBDIR_BAS_B_G
};

const int y_recul_fusil [][5] = {
	{ 0, -4, -6, -4, 0 },	// BBDIR_BAS_B_D
	{ 0, -2, -4, -2, 0},	// BBDIR_BAS_DROITE
	{ 0, 0, 0, 0, 0},		// BBDIR_DROITE
	{ 0, 2, 4, 2, 0},		// BBDIR_HAUT_DROITE
	{ 0, 4, 6, 4, 0},		// BBDIR_HAUT_H_D
	{ 0, 4, 6, 4, 0},		// BBDIR_HAUT_H_G
	{ 0, 2, 4, 2, 0},		// BBDIR_HAUT_GAUCHE
	{ 0, 0, 0, 0, 0},		// BBDIR_GAUCHE
	{ 0, -2, -4, -2, 0},	// BBDIR_BAS_GAUCHE
	{ 0, -4, -6, -4, 0}		// BBDIR_BAS_B_G
};



//-----------------------------------------------------------------------------

Couille::Couille() : sauti(0), ctrl(NULL), id_arme(ID_M16), tire(false), etape_recul(0),
	dir_arme(0), poid_arme(1), cadence_arme(10), ammo(0), dx_saut(0),
	latence_arme(3), nb_etape_arme(5), invincible(0), a_mal(0),
	nb_life(5), nb_cow_bomb(0), time_down(0), wait_cow_bomb(0),
	dx_glisse(0), latence_glisse(0), perfect(true), next_m16(0),
	next_pm(0), next_fusil(0), next_laser(0), next_lf(0), locked_fire(false),
	fire_lf(false), locked_dir(false), etape_cli(0), inv_cow(false), mod_life(0)
{
	dir = BBDIR_DROITE;
	col_on = true;
	pv = 5;
}

//-----------------------------------------------------------------------------

void Couille::affiche()
{
	// On n'est pas mort au moins ?
	//
	if (nb_life <= 0)
		return;

	// Si on est invincible, on clignote (2 vitesses)
	//
	if (invincible > 50 && etape_cli == 0 && phase && !inv_cow)
		return;

	// Redirigons le travail...
	//
	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			afficheNormal();
			break;

		case ETAT_SALETO:
		case ETAT_COME_BACK:
			Sprite::affiche();
			break;

		case ETAT_SAUTE:
		case ETAT_TOMBE:
			afficheSaute();
			break;

		case ETAT_MEURE:
			afficheMeure();
			break;

		case ETAT_LOCKEDV:
			afficheVehicule();
			break;
	}
}


//-----------------------------------------------------------------------------

void Couille::afficheNormal()
{
	int yback = y;	// Sauvegarde la valeur de y
	y -= anime_sautille[sauti];

	Sprite::affiche();

	// Affiche les accessoires
	//
	afficheOeil(x, y);
	afficheArme(x, y);

	y = yback;
}


//-----------------------------------------------------------------------------

void Couille::afficheArme(int xtmp, int ytmp)
{
	// Affiche l'arme elle même
	//
	int d_arme = dir_arme / 2;

	if (dir_arme > BBLIM_DROITE)
		d_arme += 1;

	int d_arme2 = d_arme % 5;


	switch (id_arme) {
		case ID_M16:
			if (tire)
				draw(xtmp + dx_m16[d_arme] + x_recul[d_arme][etape_recul],
				     ytmp + dy_m16[d_arme] + y_recul[d_arme][etape_recul],
				     pbk_own[24 + d_arme]);
			else
				draw(xtmp + dx_m16[d_arme], ytmp + dy_m16[d_arme], pbk_own[24 + d_arme]);
			break;

		case ID_PM:
			if (tire)
				draw(xtmp + dx_pm[d_arme] + x_recul[d_arme][etape_recul],
				     ytmp + dy_pm[d_arme] + y_recul[d_arme][etape_recul],
				     pbk_own[64 + d_arme]);
			else
				draw(xtmp + dx_pm[d_arme], ytmp + dy_pm[d_arme], pbk_own[64 + d_arme]);
			break;

		case ID_LF:
			draw(xtmp + dx_lf[d_arme], ytmp + dy_lf[d_arme], pbk_own[54 + d_arme]);
			break;

		case ID_FUSIL:
			if (tire) {
				if (etape_arme < 5) {	// Le recul
					draw(xtmp + dx_fusil[d_arme] + x_recul[d_arme][etape_arme] * 2,
					     ytmp + dy_fusil[d_arme] + y_recul[d_arme][etape_arme] * 2,
					     pbk_own[44 + d_arme]);

					draw(xtmp + dx_main_fusil[d_arme] + x_recul_fusil[d_arme][etape_arme],
					     ytmp + dy_main_fusil[d_arme] + y_recul_fusil[d_arme][etape_arme],
					     pbk_own[104 + d_arme2]);
				} else {	// Recharge
					int ea = (etape_arme - 5) / 2;

					draw(xtmp + dx_fusil[d_arme], ytmp + dy_fusil[d_arme], pbk_own[44 + d_arme]);
					draw(xtmp + dx_main_fusil[d_arme] + x_recul_fusil[d_arme][ea],
					     ytmp + dy_main_fusil[d_arme] + y_recul_fusil[d_arme][ea],
					     pbk_own[104 + d_arme2]);
				}
			} else {
				draw(xtmp + dx_fusil[d_arme], ytmp + dy_fusil[d_arme], pbk_own[44 + d_arme]);
				draw(xtmp + dx_main_fusil[d_arme], ytmp + dy_main_fusil[d_arme], pbk_own[104 + d_arme2]);
			}
			break;

		case ID_LASER:
			if (tire) {
				draw(xtmp + dx_laser[d_arme] + x_recul[d_arme][etape_recul],
				     ytmp + dy_laser[d_arme] + y_recul[d_arme][etape_recul],
				     pbk_own[34 + d_arme]);
				draw(xtmp + dx_truc_laser[d_arme] + x_recul[d_arme][etape_recul],
				     ytmp + dy_truc_laser[d_arme] + y_recul[d_arme][etape_recul],
				     pbk_bb[152 + 4 * d_arme + etape_arme]);
			} else {
				draw(xtmp + dx_laser[d_arme],
				     ytmp + dy_laser[d_arme],
				     pbk_own[34 + d_arme]);
			}
			break;
	}

	// Affiche la détonation
	//
	if (tire) {
		int d_arme2 = d_arme;
		if (d_arme == 9)
			d_arme2 = 0;
		else if (d_arme > 4)
			d_arme2 -= 1;

		switch (id_arme) {
			case ID_M16:
				if (id_couille == ID_BLIP) {
					draw(xtmp + dx_m16_deto[d_arme] + x_recul[d_arme][etape_recul],
					     ytmp + dy_m16_deto[d_arme] + y_recul[d_arme][etape_recul],
					     pbk_bb[12 + d_arme * 3 + anim_m16_deto[etape_arme]]);
				} else {
					draw(xtmp + dx_m16o_deto[d_arme] + x_recul[d_arme][etape_recul],
					     ytmp + dy_m16o_deto[d_arme] + y_recul[d_arme][etape_recul],
					     pbk_bb[12 + d_arme * 3 + anim_m16_deto[etape_arme]]);
				}
				break;

			case ID_PM:
				draw(xtmp + dx_pm_deto[d_arme] + x_recul[d_arme][etape_recul],
				     ytmp + dy_pm_deto[d_arme] + y_recul[d_arme][etape_recul],
				     pbk_own[74 + d_arme * 3 + anim_pm_deto[etape_arme]]);
				break;

			case ID_FUSIL:
				if (etape_arme < 5)
					draw(xtmp + dx_fusil_deto[d_arme] + x_recul_fusil[d_arme][etape_arme],
					     ytmp + dy_fusil_deto[d_arme] + y_recul_fusil[d_arme][etape_arme],
					     pbk_bb[42 + d_arme * 3 + anim_fusil_deto[etape_arme]]);
				break;

			case ID_LASER:
				if (dir_arme == dir)
					draw(xtmp + dx_laser_deto[d_arme] + x_recul[d_arme][etape_recul],
					     ytmp + dy_laser_deto[d_arme] + y_recul[d_arme][etape_recul],
					     pbk_bb[104 + d_arme2 * 4 + etape_arme]);
				break;
		}
	}

}


//-----------------------------------------------------------------------------

void Couille::afficheOeil(int xtmp, int ytmp)
{
	int		base;	// Oeil de base (enervé & co)
	int		delta;	// Selon dir

	// Prend le bon style d'oeil
	//
	if (a_mal) {
		if (dir <= BBLIM_DROITE)
			draw(xtmp + 12, ytmp - 14, pbk_own[22]);
		else
			draw(xtmp - 12, ytmp - 14, pbk_own[23]);
	} else {
		if (tire)
			base = 6;	// Oeil méchant
		else
			base = 0;	// Oeil normal

		// Prend la bonne direction
		//
		if (dir <= BBDIR_BAS_DROITE)
			delta = 0;
		else if (dir <= BBDIR_DROITE)
			delta = 1;
		else if (dir <= BBDIR_HAUT_H_D)
			delta = 2;
		else if (dir <= BBDIR_HAUT_GAUCHE)
			delta = 3;
		else if (dir <= BBDIR_GAUCHE)
			delta = 4;
		else
			delta = 5;

		if (dir <= BBLIM_DROITE)
			draw(xtmp + 12, ytmp - 14, pbk_bb[base + delta]);
		else
			draw(xtmp - 12, ytmp - 14, pbk_bb[base + delta]);
	}

}

//-----------------------------------------------------------------------------

void Couille::afficheSaute()
{
	// Affiche le corps
	//
	Sprite::affiche();

	// Sauter n'est pas tomber
	//
	if (dy < 0) {	// Saute
		afficheOeil(x, y + dy - 2);
		afficheArme(x, y + dy - 2);
	} else {		// Tombe
		afficheOeil(x, y);
		afficheArme(x, y);
	}
}


//-----------------------------------------------------------------------------

void Couille::update()
{
	if (phase) {
		etape_cli += 1;
		etape_cli %= 4;
	}

	if (id_arme == ID_LF) {
		if (tire && !fire_lf) {
			sbk_bb.play(2, SOUND_LOOP);
			fire_lf = true;
		} else if (!tire && fire_lf) {
			sbk_bb.stop(2);
			fire_lf = false;
		}
	} else if (fire_lf) {
		sbk_bb.stop(2);
		fire_lf = false;
	}

	if (id_arme == ID_LASER) {
		if (tire && !fire_laser) {
			sbk_bb.play(4, SOUND_LOOP);
			fire_laser = true;
		} else if (!tire && fire_laser) {
			sbk_bb.stop(4);
			fire_laser = false;
		}
	} else if (fire_laser) {
		sbk_bb.stop(4);
		fire_laser = false;
	}

	// Are we dead ?
	//
	if (nb_life <= 0)
		return;

	// Si on tombe trop bas, on meurt direct
	//
	if (y > 540) {
		nb_life = 0;
		perfect = false;
		a_detruire = true;
	}

	// Si on est morts, pas la peine de faire le reste
	//
	if (etat == ETAT_MEURE) {
		onMeure();
		return;
	}

	if (etat == ETAT_COME_BACK) {
		onComeBack();
		return;
	}

	// Rah! Les cow bombs! =)
	//
	if (wait_cow_bomb < 100)
		wait_cow_bomb += 1;

	if (ctrl->super() && wait_cow_bomb == 100 && nb_cow_bomb >= 1) {
		TirBBVache * ptr;

		for (int i = 0; i < 11; i++) {
			int xVache = offset + i * 64 + rand() % 20;

			if (! mur_opaque(xVache, 0)) {
				ptr = new TirBBVache();

				ptr->x = xVache;
				ptr->y = rand() % 180 - 200;
				ptr->dy = 5 + rand() % 3;
				ptr->etape = rand() % 8;
				ptr->joueur = this;

				list_cow.ajoute((void*) ptr);
			}
		}

		wait_cow_bomb = 0;
		nb_cow_bomb -= 1;
		invincible = 200;
		inv_cow = true;

		sbk_bb.play(5);
	}


	// Poussé par le scroll
	//
	if (x < offset + 20 && !ctrl->droite() && !mur_opaque(x + 2, y)) {
		x += 2;

		if (latence_glisse < 0)
			dx_glisse = latence_glisse = 0;
	}

	int yp = plat(x, y);

	if (yp != 0)
		y = yp;

	// Meure si ecrasé
	//
	if (x < offset - 30) {
		no_scroll1 = true;
		nb_life -= 1;

		if (nb_life == 0) {
			a_detruire = true;
			return;
		}

		etat = ETAT_COME_BACK;

		// Cherche un endroit où atterir
		//
		x = offset + 320;
		int i = 0;

		while (i < NB_MAX_PLAT && y_plat[i][x] == 0xFFFF)
			i++;

		y_to_go = y_plat[i][x];

		y = -50;
		col_on = true;
		pv = 5;
		dir_arme = dir = BBDIR_DROITE;
		invincible = 400;
		id_arme = ID_M16;
		latence_arme = 3;
		nb_etape_arme = 5;
		cadence_arme = 10;
		poid_arme = 1;
		ammo = 0;
		pic = pbk_own[8];
		dy = -5;			// Pour bien afficher l'oeil et l'arme
		dx_saut = 0;
		tire = false;
	}

	// Retire l'invincibilité
	//
	if (invincible > 0) {
		invincible -= 1;
	} else {
		inv_cow = false;
	}

	// Rouvre l'oeil fermé
	//
	if (a_mal > 0)
		a_mal -= 1;

	// Gère le sautillement permanent de Blip et Blop
	//
	if (ss_etape == 0) {
		sauti++;
		sauti %= 4;
	}

	// Gère le "deux fois en bas vite fait"
	//
	if (ctrl->bas()) {
		if (time_down > 0 && time_down < 10 && etat == ETAT_NORMAL)
			time_down = -1;		// Deux fois en bas rapide
		else
			time_down = 0;		// Trop lent, juste en bas
	} else {
		time_down += 1;
	}


	// Change la direction
	//
	if (etat != ETAT_LOCKEDV || !locked_dir)
		manageDirection();

	switch (etat) {
		case ETAT_NORMAL:
			onNormal();
			break;

		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_SALETO:
			onSaleto();
			break;

		case ETAT_SAUTE:
		case ETAT_TOMBE:
			onSaute();
			break;

		case ETAT_LOCKEDV:
			onVehicule();
			break;
	}


	// Plateformes glissantes
	//
	if (etat == ETAT_NORMAL || etat == ETAT_AVANCE) {
		int nplat = plat2(x, y);

		if (nplat >= 6 && x > 10 && x > offset + 30 && x < offset + 610) {
			int ytmp1 = y_plat[nplat][x + 10] - y;
			int ytmp2 = y_plat[nplat][x - 10] - y;

			if (ytmp1 < 10 && ytmp1 > -10)
				latence_glisse += ytmp1;
			if (ytmp2 < 10 && ytmp2 > -10)
				latence_glisse -= ytmp2;

			if (latence_glisse > 0) {
				if (ctrl->droite())
					latence_glisse += 25;
				else if (ctrl->gauche())
					latence_glisse -= 10;
				else
					latence_glisse -= 1;
			} else if (latence_glisse < 0) {
				if (ctrl->gauche())
					latence_glisse -= 25;
				else if (ctrl->droite())
					latence_glisse += 10;
				else
					latence_glisse += 1;
			} else {
				if (ctrl->droite())
					latence_glisse += 25;
				else if (ctrl->gauche())
					latence_glisse -= 25;
			}

			if (latence_glisse > 600)
				latence_glisse = 600;
			else if (latence_glisse < -600)
				latence_glisse = -600;

			if (latence_glisse > 0)
				dx_glisse = latence_glisse / 200 + 1;
			else if (latence_glisse < 0)
				dx_glisse = latence_glisse / 200 - 1;
			else
				dx_glisse = 0;
		} else {
			dx_glisse = latence_glisse = 0;
		}
	} else {
		dx_glisse = latence_glisse = 0;
	}

	// Pour les collisions
	//
	colFromPic();

	// On s'occupe de l'arme
	//
	if (etat != ETAT_SALETO) // && !( etat == ETAT_LOCKEDV && !locked_fire))
		updateArme();

	return;
}


//-----------------------------------------------------------------------------

void Couille::onNormal()
{

	// Deux fois en bas très vite
	//
	if (time_down == -1 && !mur_opaque(x, y + 5) && !mur_opaque(x, y + 10) && !mur_opaque(x, y + 15) && !mur_opaque(x, y + 20) && !mur_opaque(x, y + 25)) {
		y += 10;
		dy = 5;
		etat = ETAT_TOMBE;
		lat_grav = 0;
		dx_saut = dx_glisse;
		time_down = 0;
		onSaute();
		return;
	}


	// Si on appuie sur SAUT on saute ('tain c'est pas con ça!)
	//
	if (ctrl->saut() && !mur_opaque(x, y - 5)) {
		etat = ETAT_SAUTE;
		dy = -5;
		lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur

		dx_saut = dx_glisse;

		if (ctrl->gauche() && dx_saut > -2)
			dx_saut = -2;
		else if (ctrl->droite() && dx_saut < 2)
			dx_saut = 2;

		jump_released = false;
		onSaute();
		return;
	}


	// Si on va à gauche ou à droite on passe dans l'etat AVANCE
	//
	if (ctrl->gauche() || ctrl->droite() || dx_glisse != 0) {
		etat = ETAT_AVANCE;
		onAvance();
		return;
	}


	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		dx_saut = dx_glisse;

		if (ctrl->gauche() && dx_saut > -2)
			dx_saut = -2;
		else if (ctrl->droite() && dx_saut < 2)
			dx_saut = 2;

//		onSaute();
		return;
	}


	// Pour l'affichage (NORMAL)
	//
	if (dir <= BBLIM_DROITE)
		pic = pbk_own[anime(anim_blip_marche_droite, 4, 8)];
	else
		pic = pbk_own[anime(anim_blip_marche_gauche, 4, 8)];
}



//-----------------------------------------------------------------------------

void Couille::onAvance()
{

	// Si on appuie sur SAUT on saute ('tain c'est pas con ça!)
	//
	if (ctrl->saut() && !mur_opaque(x, y - 5)) {
		etat = ETAT_SAUTE;
		dy = -5;
		lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur

		dx_saut = dx_glisse;

		if (ctrl->gauche() && dx_saut > -2)
			dx_saut = -2;
		else if (ctrl->droite() && dx_saut < 2)
			dx_saut = 2;

		jump_released = false;
		onSaute();
		return;
	}


	int destx = x + dx_glisse;


	if ((dx_glisse > 0 && !mur_opaque(destx, y) && destx < offset + 620)
	        || (dx_glisse < 0 && !mur_opaque(destx, y) && destx > offset + 20))
		marche(dx_glisse);
	else {
		if (ctrl->droite() && (!mur_opaque(x + 2, y) && x + 2 < offset + 620)) {
			// Avance droite
			//
			marche(2);
		} else if (ctrl->gauche() && (!mur_opaque(x - 2, y) && x - 2 > offset + 20)) {
			// Avance gauche
			//
			marche(-2);
		} else {
			// On avance plus
			//
			etat = ETAT_NORMAL;
		}
	}


	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		dx_saut = dx_glisse;

		if (ctrl->gauche() && dx_saut > -2)
			dx_saut = -2;
		else if (ctrl->droite() && dx_saut < 2)
			dx_saut = 2;

		onSaute();
		return;
	}


	// Pour l'affichage (AVANCE)
	//
	if (dir <= BBLIM_DROITE)
		pic = pbk_own[anime(anim_blip_marche_droite, 4, 5)];
	else
		pic = pbk_own[anime(anim_blip_marche_gauche, 4, 5)];
}



//-----------------------------------------------------------------------------

void Couille::onSaute()
{
	int		yp;


	// Pour gérer le saleto
	//
	if (!ctrl->saut())
		jump_released = true;

	if (ctrl->saut() && jump_released && etat == ETAT_SAUTE && dy < 3) {
		dy = -5;
		etat = ETAT_SALETO;
		etape = 0;
		ss_etape = 0;
		tire = false;
		etape_arme = ss_etape_arme = 0;
		onSaleto();
		return;
	}

	// Le classique tombor (cf. classe Sprite)
	//
	tombe2();

	// Si on ne laisse pas appuyer sur saut on saute moins haut
	//
	if (dy < 0 && !ctrl->saut()) {
		lat_grav += 1;
		lat_grav %= LATENCE_GRAVITE;

		if (lat_grav == 0) {
			dy += 1;
		}
	}


	// Et si on arrêtait de tomber ?
	//
	if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
		etat = ETAT_NORMAL;
		latence_glisse = 200 * dx_saut;
		dy = 0;
		y = yp;
		onNormal();
		return;
	}

	// Même en tombant on peut se diriger à droite/gauche
	//
	if (!ctrl->inertia() || (!ctrl->bas() && !ctrl->haut())) {
		if (ctrl->droite() && dx_saut < 2)
			dx_saut = 2;
		else if (ctrl->gauche() && dx_saut > -2)
			dx_saut = -2;
		else if (!ctrl->inertia())
			dx_saut = 0;
	}

	int xx = x + dx_saut;

	if (!mur_opaque(xx, y) && xx > offset + 20 && xx < offset + 620)
		x = xx;


	// Pour l'affichage (SAUTE/TOMBE)
	//
	if (dir <= BBLIM_DROITE)
		pic = pbk_own[anim_blip_saute_droite[dy + 5]];
	else
		pic = pbk_own[anim_blip_saute_gauche[dy + 5]];

}

//-----------------------------------------------------------------------------

void Couille::manageDirection()
{
	// Gere la direction désirée (pas de diagonales pour le laser)
	//
	if (ctrl->haut()) {
		if (ctrl->droite())
			dir = BBDIR_HAUT_DROITE;
		else if (ctrl->gauche())
			dir = BBDIR_HAUT_GAUCHE;
		else {
			if (dir <= BBLIM_DROITE)
				dir = BBDIR_HAUT_H_D;
			else
				dir = BBDIR_HAUT_H_G;
		}
	} else if (ctrl->bas()) {
		if (ctrl->droite())
			dir = BBDIR_BAS_DROITE;
		else if (ctrl->gauche())
			dir = BBDIR_BAS_GAUCHE;
		else {
			if (dir <= BBLIM_DROITE)
				dir = BBDIR_BAS_B_D;
			else
				dir = BBDIR_BAS_B_G;
		}
	} else if (ctrl->droite()) {
		dir = BBDIR_DROITE;
	} else if (ctrl->gauche()) {
		dir = BBDIR_GAUCHE;
	} else {	// Aucune direction -> on retourne à l'horizontale
		if (dir <= BBLIM_DROITE)
			dir = BBDIR_DROITE;
		else
			dir = BBDIR_GAUCHE;
	}

	// Gére la direction de l'arme
	//
	if (dir <= BBLIM_DROITE && dir_arme > BBLIM_DROITE)
		dir_arme = BBDIR_BAS_B_G - dir_arme;
	else if (dir > BBLIM_DROITE && dir_arme <= BBLIM_DROITE)
		dir_arme = 17 - dir_arme;

	etape_bouge_arme += 1;
	etape_bouge_arme %= poid_arme;

	if (etape_bouge_arme == 0) {
		if (dir_arme < dir)
			dir_arme += 1;
		else if (dir_arme > dir)
			dir_arme -= 1;
	}
}


//-----------------------------------------------------------------------------

void Couille::updateArme()
{
	if (etat == ETAT_LOCKEDV)
		return;

	int yback = y;	// Sauvegarde la valeur de y

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			y -= anime_sautille[sauti];
			break;

		case ETAT_SAUTE:
		case ETAT_TOMBE:
			if (dy < 0)
				y += dy - 2;
			break;
	}


	// Gere les détonations
	//
	if (tire) {
		ss_etape_arme += 1;
		ss_etape_arme %= latence_arme;

		if (ss_etape_arme == 0)
			etape_arme += 1;

		if (etape_arme == nb_etape_arme)
			tire = false;
	}


	// Si le joueur appuie sur 'FEU' on passe en mode TIR
	//
	if (!tire && ctrl->fire() && !hold_fire) {
		tire = true;
		etape_arme = 0;
		ss_etape_arme = 0;

		switch (id_arme) {
			case ID_M16:
				break;

			case ID_PM:
				sbk_bb.play(0);
				break;

			case ID_LF:
				break;

			case ID_FUSIL:
				break;

			case ID_LASER:
				break;

		}

		pruno = cadence_arme - 1;
	}

	// Gère le recul
	//
	etape_recul += 1;
	etape_recul %= 5;


	// Gère les balles
	//
	pruno += 1;
	pruno %= cadence_arme;


	if (tire && pruno == 0 && !(poid_arme <= 1 && dir_arme != dir)) {
		int d_arme;


		d_arme = dir_arme / 2;
		if (dir_arme > BBLIM_DROITE)
			d_arme += 1;


		TirBB * t = NULL;
		int i;

		switch (id_arme) {
			case ID_M16:

				sbk_bb.play(3);

//			t = new TirBBM16;

				next_m16 = (next_m16 + 1) % NB_TIRS_M16;
				t = &tirs_m16[next_m16];
				t->a_detruire = false;


				t->joueur = this;
				t->x = x + dx_tir_m16[d_arme] + rand() % 11 - 5;
				t->y = y + dy_tir_m16[d_arme] + rand() % 11 - 5;

				if (etat == ETAT_LOCKEDV)
					t->dxReferentiel = scroll_speed;
				else
					t->dxReferentiel = 0;

				t->setDir(dir);
				list_tirs_bb.ajoute((void*) t);
				break;

			case ID_PM:
//			t = new TirBBPM;

				next_pm = (next_pm + 1) % NB_TIRS_PM;
				t = &tirs_pm[next_pm];
				t->a_detruire = false;

				t->joueur = this;
				t->x = x + dx_tir_pm[d_arme] + rand() % 11 - 5;
				t->y = y + dy_tir_pm[d_arme] + rand() % 11 - 5;

				if (etat == ETAT_LOCKEDV)
					t->dxReferentiel = scroll_speed;
				else
					t->dxReferentiel = 0;

				t->setDir(dir_arme);
				list_tirs_bb.ajoute((void*) t);
				break;

			case ID_FUSIL:

				sbk_bb.play(1);

				for (i = 0; i < 17; i++) {
//				t = new TirBBFusil;

					next_fusil = (next_fusil + 1) % NB_TIRS_FUSIL;
					t = &tirs_fusil[next_fusil];
					t->a_detruire = false;

					t->joueur = this;
					t->x = x + dx_tir_fusil[d_arme] + rand() % 11 - 5;
					t->y = y + dy_tir_fusil[d_arme] + rand() % 11 - 5;

					if (etat == ETAT_LOCKEDV)
						t->dxReferentiel = scroll_speed;
					else
						t->dxReferentiel = 0;

					t->setDir(dir);
					list_tirs_bb.ajoute((void*) t);
				}
				break;

			case ID_LASER:
//			t = new TirBBLaser;

				next_laser = (next_laser + 1) % NB_TIRS_LASER;
				t = &tirs_laser[next_laser];
				t->a_detruire = false;

				t->joueur = this;
				t->x = x + dx_tir_laser[d_arme] + x_recul[d_arme][etape_recul];
				t->y = y + dy_tir_laser[d_arme] + y_recul[d_arme][etape_recul];
				t->setDir(dir);
				t->etape = etape_arme;
				list_tirs_bb.ajoute((void*) t);
				break;

			case ID_LF:
				next_lf = (next_lf + 1) % NB_TIRS_LF;
				t = &tirs_lf[next_lf];
				t->a_detruire = false;

				((TirBBLF*)t)->deg = 2;
				t->joueur = this;
				t->x = x + dx_tir_lf[d_arme] + x_recul[d_arme][etape_recul];
				t->y = y + dy_tir_lf[d_arme] + y_recul[d_arme][etape_recul];
				t->setDir(dir_arme);

				list_tirs_bb.ajoute((void*) t);

				next_lf = (next_lf + 1) % NB_TIRS_LF;
				t = &tirs_lf[next_lf];
				t->a_detruire = false;

				((TirBBLF*)t)->deg = 1;
				t->joueur = this;
				t->x = x + dx_tir_lf[d_arme] + x_recul[d_arme][etape_recul];
				t->y = y + dy_tir_lf[d_arme] + y_recul[d_arme][etape_recul];
				t->setDir(dir_arme);

				list_tirs_bb.ajoute((void*) t);
				break;
		}

		if(t != NULL)
		{
		    t->hasangle = true;
		    t->angle = in.angle;
		}

		if (id_arme != ID_M16) {
			ammo -= 1;

			if (ammo <= 0) {
				id_arme = ID_M16;
				latence_arme = 3;
				nb_etape_arme = 5;
				cadence_arme = 10;
				poid_arme = 1;
				tire = false;
			}
		}
	}

	y = yback;
}



//-----------------------------------------------------------------------------

void Couille::estTouche(const Tir * tir)
{

}


//-----------------------------------------------------------------------------

void Couille::estTouche(int degats)
{
	if (invincible > 0 || etat == ETAT_MEURE)
		return;

	pv -= degats;
	perfect = false;
	/*
		if ( id_couille == ID_BLIP)
		{
			sbk_bb.play( 6);
		}
		else
		{
			sbk_bb.play( 7);
		}
	*/
	if (pv <= 0) {
		pv = 0;
		etat = ETAT_MEURE;
		tire = false;
		etape_arme = ss_etape_arme = 0;
		etape = 0;
		ss_etape = 0;
		col_on = false;
		no_scroll1 = true;
	} else {
		invincible = 200;
		a_mal = 100;
	}
}


//-----------------------------------------------------------------------------

void Couille::onMeure()
{
	if (dy < 0)
		dy = 0;

	tombe();

	ss_etape += 1;
	ss_etape %= 7;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 15) {
		nb_life -= 1;

		if (nb_life == 0) {
			a_detruire = true;
			no_scroll1 = false;
			return;
		}

		etat = ETAT_COME_BACK;
		y_to_go = y;
		y = -50;
		col_on = true;
		pv = 5;
		dir_arme = dir = BBDIR_DROITE;
		invincible = 400;

		rearme();

		pic = pbk_own[8];
		dy = -5;			// Pour bien afficher l'oeil et l'arme
		dx_saut = 0;
		tire = false;

		if (cowBombOn)
			nb_cow_bomb = 1;
	} else if (etape == 5 && ss_etape == 0 && plat(x, y) != 0) {
		if (dir <= BBLIM_DROITE)
			grave(x, y, pbk_own[16]);
		else
			grave(x, y, pbk_own[21]);
	} else if (etape < 5) {
		if (dir <= BBLIM_DROITE)
			pic = pbk_own[12 + etape];
		else
			pic = pbk_own[17 + etape];
	}

}


//-----------------------------------------------------------------------------

void Couille::afficheMeure()
{
	if (etape < 5)
		Sprite::affiche();
}


//-----------------------------------------------------------------------------

void Couille::onComeBack()
{
	no_scroll1 = true;

	if (y < y_to_go) {
		ss_etape += 1;
		ss_etape %= 3;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 8;
		}

		y += 5;

		pic = pbk_own[109 + id_arme * 8 + etape];
	} else {
		y = y_to_go;
		etat = ETAT_NORMAL;
		etape = 0;
		ss_etape = 0;
		no_scroll1 = false;
	}
}


//-----------------------------------------------------------------------------

void Couille::onSaleto()
{
	int		yp;

	ss_etape += 1;
	ss_etape %= 3;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 8;
	}

	// Le classique tombor (cf. classe Sprite)
	//
	tombe2();

	// Et si on arrêtait de tomber ?
	//
	if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
		etat = ETAT_NORMAL;
		latence_glisse = 200 * dx_saut;
		dy = 0;
		y = yp;
		onNormal();
		return;
	}

	// Même en tombant on peut se diriger à droite/gauche
	//
	if (ctrl->droite() && dx_saut < 2)
		dx_saut = 2;
	else if (ctrl->gauche() && dx_saut > -2)
		dx_saut = -2;


	int xx = x + dx_saut;


	if (!mur_opaque(xx, y) && xx > offset + 20 && xx < offset + 620)
		x = xx;


	// Pour l'affichage
	//
	pic = pbk_own[109 + id_arme * 8 + etape];
}

//-----------------------------------------------------------------------------

bool Couille::okBonus()
{
	return (id_arme == ID_M16 ||
	        (id_arme == ID_PM && ammo <= 30) ||
	        (id_arme == ID_FUSIL && ammo <= 4) ||
	        (id_arme == ID_LF && ammo <= 100) ||
	        (id_arme == ID_LASER && ammo <= 100));
}

//-----------------------------------------------------------------------------

void Couille::setSuperWeapon()
{
	if (id_couille == ID_BLIP || !okLanceFlame) {
		id_arme = ID_LASER;
		ammo = 750;
		latence_arme = 3;
		nb_etape_arme = 4;
		cadence_arme = 1;
		poid_arme = 1;

		etape_arme = 0;
		ss_etape_arme = 0;
		etape_recul = 0;
		tire = false;
	} else {
		id_arme = ID_LF;
		ammo = 1000;
		latence_arme = 3;
		nb_etape_arme = 5;
		cadence_arme = 1;
		poid_arme = 5;

		etape_arme = 0;
		ss_etape_arme = 0;
		etape_recul = 0;
		tire = false;
	}
}

//-----------------------------------------------------------------------------

void Couille::colFromPic()
{
	Sprite::colFromPic();

	if (etat == ETAT_SALETO) {
		x1 += 15;
		x2 -= 15;
		y1 += 15;
		y2 -= 15;
	} else {
		x1 += 10;
		x2 -= 10;
		y1 += 10;
		y2 -= 10;
	}
}

//-----------------------------------------------------------------------------

void Couille::lockVehicule(bool can_fire, bool can_dir)
{
//	etape = ss_etape = 0;
	etat = ETAT_LOCKEDV;
	locked_fire = !can_fire;
	locked_dir = !can_dir;

	if (!can_fire) {
		tire = false;
		etape_arme = ss_etape_arme = 0;
	}
}

//-----------------------------------------------------------------------------

void Couille::unlockVehicule()
{
	etape = ss_etape = 0;
	etat = ETAT_SALETO;
	dy = -5;
	dx_saut = 0;
	tire = false;
	etape_arme = ss_etape_arme = 0;
}


//-----------------------------------------------------------------------------

void Couille::onVehicule()
{
}

//-----------------------------------------------------------------------------

void Couille::afficheVehicule()
{
	// Pour l'affichage (NORMAL)
	//
	if (dir <= BBLIM_DROITE)
		pic = pbk_own[0];
	else
		pic = pbk_own[3];

	Sprite::affiche();
	afficheOeil(x, y);

	afficheArme(x, y);
}

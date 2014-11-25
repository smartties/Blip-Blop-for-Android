
#include "ennemi_bisou_zombi.h"
#include "gore_pied_bisou_zombi.h"

#define ETAT_CARBONISE_HAUT	102

#define	ETAT_RAMPE	100
#define ETAT_COUPE	101

static int etape_moan	= 199;
static int num_moan		= 0;
static bool local_phase;

EnnemiBisouZombi::EnnemiBisouZombi() : etape2(0)
{
	pv = 1000;
	tresor = 10;
}


void EnnemiBisouZombi::update()
{
	if (blood > 0)
		blood -= 1;

	if (game_flag[0] == 7 && etat != ETAT_CARBONISE && etat != ETAT_CARBONISE_HAUT) {
		etape = ss_etape = 0;

		if (etat == ETAT_COUPE)
			etat = ETAT_CARBONISE_HAUT;
		else
			etat = ETAT_CARBONISE;
	}

	if (local_phase != phase && game_flag[2] == 0) {
		etape_moan += 1;
		etape_moan %= 200;

		if (etape_moan == 0) {
			num_moan += 1;
			num_moan %= 3;

			sbk_niveau.play(10 + num_moan);
		}

		local_phase = phase;
	}

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_COUPE:
			onCoupe();
			break;

		case ETAT_TOMBE:
			onTombe();
			break;

		case ETAT_RAMPE:
			onRampe();
			break;

		case ETAT_MEURE:
			onMeure();
			break;

		case ETAT_CARBONISE:
			onCarbonise();
			break;

		case ETAT_CARBONISE_HAUT:
			onCarboniseHaut();
			break;
	}

	updateADetruire();
}

void EnnemiBisouZombi::onAvance()
{
	static const int SPEED = 1;

	tombe();

	ss_etape += 1;
	ss_etape %= 15;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 8;
	}

	// Marche
	//
	my_phase = !my_phase;

	if (my_phase) {
		if (x - SPEED < xmin || mur_opaque(x - SPEED, y))
			dir = SENS_DROITE;
		else if (x + SPEED > offset + 640 || mur_opaque(x + SPEED, y))
			dir = SENS_GAUCHE;

		if (dir == SENS_DROITE) {
			marche(SPEED);
			pic = pbk_ennemis[262 + etape];
		} else {
			marche(-SPEED);
			pic = pbk_ennemis[270 + etape];
		}
	}

	colFromPic();
}

void EnnemiBisouZombi::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 7, 10, 7, 0, -7, -10, -7 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	static const int dy_giclure2 [] = { 0, -10, -10, -10, -20, -10, -10, -10 };

	int back_etat = etat;
	int back_etape = etape;
	int back_ss_etape = ss_etape;

	int blessure = tir->degats();

	if (blessure < pv) {
		tir->aTouche(blessure);
		pv -= blessure;

		if (pv < 500 && (etat == ETAT_NORMAL || etat == ETAT_AVANCE) && !tir->enflame()) {
			etape = ss_etape = 0;
			col_on = false;
			etat = ETAT_COUPE;
		}
	} else {
		tir->aTouche(pv);
		tir->aTue();
		pv = 0;
		col_on = false;

		game_flag[FLAG_NB_KILL] += 1;

		if (etat == ETAT_RAMPE) {
			etape = 0;
			ss_etape = 0;

			if (tir->enflame() == 2) {
				etape = ss_etape = 0;
				col_on = false;
				etat = ETAT_CARBONISE_HAUT;
			} else {
				etape = ss_etape = 0;
				col_on = false;
				etat = ETAT_MEURE;
			}
		} else {
			if (tir->enflame()) {
				etape = ss_etape = 0;
				col_on = false;
				etat = ETAT_CARBONISE;
			} else if (etat != ETAT_COUPE) {
				etape = ss_etape = 0;
				col_on = false;
				etat = ETAT_COUPE;
			}
		}
	}


	if (etat == ETAT_RAMPE)
		gicle(tir, dx_giclure, dy_giclure2);
	else
		gicle(tir, dx_giclure, dy_giclure);
}


void EnnemiBisouZombi::onTombe()
{
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0 && etape < 3)
		etape += 1;

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[308 + etape];
		x += 1;
	} else {
		pic = pbk_ennemis[312 + etape];
		x -= 1;
	}

	tombe();

	if (plat(x, y) != 0 && etape >= 3) {
		etape = ss_etape = 0;
		etat = ETAT_RAMPE;
		col_on = true;
		onRampe();
	}
}

void EnnemiBisouZombi::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0 && etape < 3)
		etape += 1;

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[292 + etape];
	else
		pic = pbk_ennemis[296 + etape];


	if (etape >= 3) {
		grave(x, y, pic);
		a_detruire = true;
	}
}

void EnnemiBisouZombi::onCoupe()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 4) {
		GorePiedsBisouZombi * pieds = new GorePiedsBisouZombi();

		pieds->x = x;
		pieds->dir = dir;
		pieds->y = y;

		list_gore.ajoute((void*) pieds);

		y -= 19;
		dy = 0;
		etape = 0;
		ss_etape = 0;
		etat = ETAT_TOMBE;
		onTombe();
	} else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[278 + etape];
		else
			pic = pbk_ennemis[282 + etape];
	}
}

void EnnemiBisouZombi::onRampe()
{
	static const int anim_droite [] = { 286, 287, 288, 287 };
	static const int anim_gauche [] = { 289, 290, 291, 290 };
	static const int SPEED = 1;

	if (pv <= 0) {
		etape = ss_etape = 0;
		etat = ETAT_MEURE;
		col_on = false;
		onMeure();
		return;
	}

	tombe();

	// Marche
	//

	etape2 = (etape2 + 1) % 4;

	if (etape2 == 0) {
		if (x - SPEED < xmin || mur_opaque(x - SPEED, y))
			dir = SENS_DROITE;
		else if (x + SPEED > offset + 640 || mur_opaque(x + SPEED, y))
			dir = SENS_GAUCHE;

		if (dir == SENS_DROITE)
			marche(SPEED);
		else
			marche(-SPEED);

		colFromPic();
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[anime(anim_droite, 4, 16)];
	else
		pic = pbk_ennemis[anime(anim_gauche, 4, 16)];
}

void EnnemiBisouZombi::onCarbonise()
{
	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape += 1;

		if (etape > 6) {
			a_detruire = true;
			return;
		}
	}

	if (dir == SENS_DROITE)
		pic = pbk_ennemis[605 + etape];
	else
		pic = pbk_ennemis[612 + etape];
}

void EnnemiBisouZombi::onCarboniseHaut()
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
		pic = pbk_ennemis[619 + etape];
	else
		pic = pbk_ennemis[627 + etape];
}

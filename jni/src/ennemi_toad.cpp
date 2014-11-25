
#include "ennemi_toad.h"

const int anim_toad_marche_droite[] = { 0, 1, 2, 1};
const int anim_toad_marche_gauche[] = { 4, 5, 6, 5};

static int	wait_brain_hurts = 1000;
static bool	local_phase;
static int	brain_hurts = 9;

EnnemiToad::EnnemiToad(): speed(0), etape_speed(0), charge_delay(50 + rand() % 250), wait_for_charge(0), hokuto(rand() % 5)
{
	tresor = 7;
	pv = 300;
}

void EnnemiToad::update()
{
	if (local_phase != phase) {
		wait_brain_hurts++;
		local_phase = phase;
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

		case ETAT_TIRE:  //Toad charge(ETAT_TIRE)
			onCharge();
			break;
	}

	updateADetruire();
}

void EnnemiToad::onAvance()
{
	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		etape = 0;
		ss_etape = 0;
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
	wait_for_charge++;
	if (wait_for_charge >= charge_delay) {
		if ((plat2(tete_turc->x, tete_turc->y) == plat2(x, y)) &&
		        (((dir == SENS_DROITE) && (x < tete_turc->x)) ||
		         ((dir == SENS_GAUCHE) && (x > tete_turc->x)))) {
			charge_etape = 0;
			speed = 0;
			etape = 0;
			ss_etape = 0;
			dy = 0;
			etat = ETAT_TIRE;
			sbk_niveau.play(34);
			onCharge();
			return;
		} else {
			wait_for_charge = 0;
			charge_delay = 50 + rand() % 250;
			etape = 0;
			ss_etape = 0;
			etat = ETAT_SAUTE;
			dy = -7;
			lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur
			onSaute();
			return;
		}
	}
	if (dir == SENS_DROITE) {
		marche(speed);
		pic = pbk_ennemis[anime(anim_toad_marche_droite, 4, 12 - 3 * speed)];
	} else {
		marche(-speed);
		pic = pbk_ennemis[anime(anim_toad_marche_gauche, 4, 12 - 3 * speed)];
	}
	if (speed < TOAD_SPEED) {
		etape_speed++;
		if (etape_speed >= 30) {
			etape_speed = 0;
			speed++;
		}
	}
	colFromPic();
}

void EnnemiToad::onMeure()
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
	if ((etape > 4) && (hokuto > 0)) {
		hokuto--;
		etape -= 4;
	}

	if (etape == 5 && ss_etape == 0) {
		sbk_misc.play(9 + rand() % 2);
	}

	if (etape >= 10) {
		int		yy = plat(x, y);

		if (yy != 0 && yy != y_plat[4][x]) {
			grave(x, y, pic);
			a_detruire = true;
		}
	} else {
		if (dir == SENS_GAUCHE) {
			if (!mur_opaque(x - speed, y) && plat(x, y) == 0)
				x -= speed;
			pic = pbk_ennemis[18 + etape];
		} else {
			if (!mur_opaque(x + speed, y) && plat(x, y) == 0)
				x += speed;
			pic = pbk_ennemis[8 + etape];
		}
	}
}

void EnnemiToad::onCharge()
{
	speed = TOAD_CHARGE_SPEED;
	if (x - speed < xmin || mur_opaque(x - speed, y)) {
		dir = SENS_DROITE;
		speed = 1;
		etat = ETAT_AVANCE;
		wait_for_charge = 0;
		charge_delay = 50 + rand() % 250;
		etape = 0;
		ss_etape = 0;
		onAvance();
		return;
	} else if (x + speed > offset + 640 || mur_opaque(x + speed, y)) {
		dir = SENS_GAUCHE;
		speed = 1;
		etat = ETAT_AVANCE;
		wait_for_charge = 0;
		charge_delay = 50 + rand() % 250;
		etape = 0;
		ss_etape = 0;
		onAvance();
		return;
	}
	charge_etape += 1;
	if (charge_etape < 80) {
		if (dir == SENS_DROITE) {
			//marche(speed);
			pic = pbk_ennemis[anime(anim_toad_marche_droite, 4, 3)];
		} else {
			//marche( -speed);
			pic = pbk_ennemis[anime(anim_toad_marche_gauche, 4, 3)];
		}
	} else {
		if (dir == SENS_DROITE) {
			marche(speed);
			pic = pbk_ennemis[anime(anim_toad_marche_droite, 4, 2)];
		} else {
			marche(-speed);
			pic = pbk_ennemis[anime(anim_toad_marche_gauche, 4, 2)];
		}
	}


	colFromPic();
}

void EnnemiToad::onSaute()
{
	int		yp;

	tombe();

	// Et si on arrêtait de tomber ?
	//
	if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
		etat = ETAT_NORMAL;
		dy = 0;
		y = yp;
		etape = 0;
		ss_etape = 0;
		onAvance();
		return;
	}


	if (dir == SENS_DROITE) {
		x += speed;
		pic = pbk_ennemis[3];
	} else {
		x -= speed;
		pic = pbk_ennemis[7];
	}

	colFromPic();

}

void EnnemiToad::onCarbonise()
{
	tombe();
	ss_etape ++;
	ss_etape %= 5;

	if (ss_etape == 0) {
		etape ++;
	}

	if (etape >= 13)
		a_detruire = true;
	else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[434 + etape];
		else
			pic = pbk_ennemis[447 + etape];
	}
}

void EnnemiToad::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (etat == ETAT_MEURE) {
		if (wait_brain_hurts >= 140 && wait_brain_hurts <= 200) {
			wait_brain_hurts = 250;
			sbk_niveau.play(29);
			hokuto = 7;
		} else {
			brain_hurts += 1;
			brain_hurts %= 10;

			if (brain_hurts == 0) {
				wait_brain_hurts = 0;
				hokuto = 6;
				sbk_niveau.play(28);
			} else {
				sbk_niveau.play(30 + rand() % 2);
			}
		}
	}
}
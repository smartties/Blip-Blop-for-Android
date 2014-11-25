
#include "ennemi_com_volant.h"

EnnemiCOMVolant::EnnemiCOMVolant(): speed(0), attack(true)
{
	pv = 100;
	if (tete_turc != NULL) {
		y_cible = tete_turc->y;
	} else {
		y_cible = 100 + rand() % 200;;
	}
}


void EnnemiCOMVolant::update()
{

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_MEURE:
		case ETAT_CARBONISE:
			onMeure();
			break;
	}

	updateADetruire();
}


void EnnemiCOMVolant::onAvance()
{
	ss_etape += 1;
	ss_etape %= 8;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 2;
	}

	// vole
	//
	if ((dir == SENS_GAUCHE) && (x - speed < offset || mur_opaque(x - speed, y))) {
		dir = SENS_DROITE;
		attack = false;
		if (tete_turc != NULL) {
			y_cible = tete_turc->y;
		} else {
			y_cible = 100 + rand() % 200;;
		}
	} else if ((dir == SENS_DROITE) && (x + speed > offset + 640 || mur_opaque(x + speed, y))) {
		dir = SENS_GAUCHE;
		attack = false;
		if (tete_turc != NULL) {
			y_cible = tete_turc->y;
		} else {
			y_cible = 100 + rand() % 200;;
		}
	}

	if (attack) {
		if (y_cible <= y) {
			speed = 6;
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
	} else {
		if (y < (y_cible - 110)) {
			y += 5;
		} else if (y > (y_cible - 100)) {
			y -= 3;
		} else {
			attack = true;
		}
	}

	if (dir == SENS_DROITE)
		x += speed;
	else
		x -= speed;

	pic = pbk_ennemis[98 + etape];

	colFromPic();
}


void EnnemiCOMVolant::onMeure()
{
	if (ss_etape == 0 && etape == 0) {
		sbk_niveau.play(6);
	}

	ss_etape += 1;
	ss_etape %= 3;

	if (ss_etape == 0 && etape < 22)
		etape += 1;

	if (etape >= 22) {
		a_detruire = true;
	} else {
		pic = pbk_ennemis[76 + etape];
	}
}

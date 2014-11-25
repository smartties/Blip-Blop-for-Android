/******************************************************************
*
*
*		-----------------------------
*		  EnnemiSnorkyHyporider.cpp
*		-----------------------------
*
*		(giclures faites... sauf peut-etre vers le bas a cause de l'hypo...)
*
*		Mephisto / LOADED -   V 0.2 - 28 Decembre 2000
*
*
*
******************************************************************/

#include "ennemi_snorky_hyporider.h"
#include "morceaux_tete_snorky.h"

EnnemiSnorkyHyporider::EnnemiSnorkyHyporider(): wait_for_charge(0), charge_delay(50 + rand() % 200), nageoire(1), attack_etape(0)
{
	pv = 350;
	dy = 0;
}


void EnnemiSnorkyHyporider::update()
{
	switch (etat) {
		case ETAT_TOMBE:
		case ETAT_SAUTE:

		case ETAT_AVANCE:
		case ETAT_NORMAL:
			onAvance();
			break;

		case ETAT_MEURE:
			onMeure();
			break;

		case ETAT_CARBONISE:
			onCarbonise();
			break;

		case ETAT_TIRE:
			onCharge();
			break;
	}

	updateADetruire();

}

void EnnemiSnorkyHyporider::onAvance()
{
	wait_for_charge ++;
	if ((wait_for_charge > charge_delay) && ((dir == SENS_DROITE && x > offset + 80) || (dir == SENS_GAUCHE && x < offset + 560))) {
		wait_for_charge = 0;
		charge_delay = 50 + rand() % 200;
		etape = 0;
		ss_etape = 0;
		etat = ETAT_TIRE;
		attack_etape = 0;
		onCharge();
		return;
	}

	ss_etape ++;
	ss_etape %= 6;
	if (ss_etape == 0) {
		etape ++;
		etape %= 4;
	}

	if (dir == SENS_GAUCHE) {
		x -=  HYPORIDER_SPEED;
		pic = pbk_ennemis[291];

		if (mur_opaque(x - HYPORIDER_SPEED, y) || (x - HYPORIDER_SPEED < xmin))
			dir = SENS_DROITE;
	} else {
		x += HYPORIDER_SPEED;

		pic = pbk_ennemis[286];

		if (mur_opaque(x + HYPORIDER_SPEED, y) || (x + HYPORIDER_SPEED > offset + 640))
			dir = SENS_GAUCHE;
	}

	colFromPic();
}


void EnnemiSnorkyHyporider::onMeure()
{
	ss_etape += 1;
	if (etape < 7) {
		ss_etape %= 3;
	} else {
		ss_etape %= 5;
	}

	if (ss_etape == 0)
		etape += 1;

	if (etape == 7 && ss_etape == 0) {
		Sprite * s;
		if (dir == SENS_DROITE) {
			s = new MorceauSnorkyHyporidercorp(-1);
		} else {
			s = new MorceauSnorkyHyporidercorp(1);
		}

		s->dir = dir;
		s->y = y;
		s->x = x;

		list_giclures.ajoute((void*) s);

		sbk_niveau.play(8);
		dy = 0;
	}
	if (etape >= 7) {
		nageoire = 0;
		if (dir == SENS_GAUCHE) {
			x -= 4;
			pic = pbk_ennemis[325];
		} else {
			x += 4;
			pic = pbk_ennemis[312];
		}
	} else {
		if (dir == SENS_GAUCHE) {
			x -= HYPORIDER_SPEED;
			pic = pbk_ennemis[313 + etape];
		} else {
			x += HYPORIDER_SPEED;
			pic = pbk_ennemis[300 + etape];
		}
	}
}

void EnnemiSnorkyHyporider::onCharge()
{
	ss_etape ++;
	ss_etape %= 2;

	if (ss_etape == 0) {
		etape ++;
		etape %= 4;
	}

	attack_etape++;

	if (attack_etape > 40) {
		nageoire = 0;
		if (dir == SENS_DROITE) {
			if (mur_opaque(x + HYPORIDER_SPEED, y) || (x + HYPORIDER_SPEED > offset + 640)) {
				etape = 0;
				ss_etape = 0;
				etat = ETAT_AVANCE;
				nageoire = 1;
				onAvance();
				return;
				dir = SENS_DROITE;
			}

			x += HYPORIDER_CHARGE_SPEED;
			pic = pbk_ennemis[297];
		} else {
			if (mur_opaque(x - HYPORIDER_CHARGE_SPEED, y) || (x - HYPORIDER_CHARGE_SPEED < xmin)) {
				etape = 0;
				ss_etape = 0;
				etat = ETAT_AVANCE;
				nageoire = 1;
				onAvance();
				return;
				dir = SENS_DROITE;
			}

			x -= HYPORIDER_CHARGE_SPEED;
			pic = pbk_ennemis[299];
		}
	} else {
		if (dir == SENS_DROITE) {
			pic = pbk_ennemis[296];
		} else {
			pic = pbk_ennemis[298];
		}
	}
	colFromPic();
}

void EnnemiSnorkyHyporider::onCarbonise()
{
	nageoire = 0;
	ss_etape ++;
	ss_etape %= 4;

	if (ss_etape == 0)
		etape ++;

	if (dir == SENS_DROITE) {
		x += 6;
		pic = pbk_ennemis[312];
	} else {
		x -= 6;
		pic = pbk_ennemis[325];
	}

	if ((x - 6 < xmin) || (x + 6 > offset + 640)) {
		a_detruire = true;
	}

}

void EnnemiSnorkyHyporider::affiche()
{
	Sprite::affiche();

	if ((etat == ETAT_CARBONISE) && (etape < 9)) {
		if (dir == SENS_DROITE) {
			draw(x, y, pbk_ennemis[326 + etape]);
		} else {
			draw(x, y, pbk_ennemis[335 + etape]);
		}
	}

	if (nageoire) {
		if (dir == SENS_DROITE) {
			draw(x + 15, y + 20, pbk_ennemis[287 + etape % 4]);
		} else {
			draw(x - 15, y + 20, pbk_ennemis[292 + etape % 4]);
		}
	}
}

void EnnemiSnorkyHyporider::estTouche(Tir * tir)
{
	static const int dx_giclure_hyporider [] = { 0, 0, 7, 3, 0, -3, -7, 0 };
	static const int dy_giclure_hyporider [] = { -15, -15, -15, -25, -25, -25, -15, -15 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_hyporider, dy_giclure_hyporider);

	if (etat == ETAT_MEURE) {
		sbk_niveau.play(7);
	}
}

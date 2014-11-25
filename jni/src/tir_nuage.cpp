
#include "enemy.h"
#include "tir_nuage.h"

TirNuage::TirNuage() : etape_shoot(0), etat(0), eclair(0), delta_eclair(0)
{
	duree_vie = 600 + rand() % 400;
}

void TirNuage::update()
{
	switch (etat) {
		case 0:
			onCreation();
			break;

		case 1:
			onNormal();
			break;

		case 2:
			onDestruction();
			break;

		case 3:
			onTire();
			break;
	}

	updateADetruire();
}

void TirNuage::onCreation()
{
	static const int SPEED = 1;

	ss_etape += 1;
	ss_etape %= 10;

	if (dir == SENS_DROITE) {
		x += SPEED;

		if (x > offset + 600)
			dir = SENS_GAUCHE;
	} else {
		x -= SPEED;

		if (x < offset + 30)
			dir = SENS_DROITE;
	}

	if (ss_etape == 0) {
		etape += 1;

		if (etape >= 3) {
			ss_etape = etape = 0;
			etat = 1;
		} else {
			pic = pbk_ennemis[250 + etape];
		}
	}

	noCol();
}

void TirNuage::onDestruction()
{
	static const int SPEED = 1;

	ss_etape += 1;
	ss_etape %= 6;

	if (dir == SENS_DROITE)
		x += SPEED;
	else
		x -= SPEED;

	if (ss_etape == 0) {
		etape += 1;

		if (etape >= 3)
			a_detruire = true;
		else
			pic = pbk_ennemis[252 - etape];
	}

	noCol();
}

void TirNuage::onNormal()
{
	static const int anim [] = { 253, 254, 255, 254 };
	static const int SPEED = 1;

	duree_vie -= 1;

	if (duree_vie <= 0) {
		etape = ss_etape = 0;
		etat = 2;
	}


	pic = pbk_ennemis[anime(anim, 4, 9)];


	if (dir == SENS_DROITE) {
		x += SPEED;

		if (x > offset + 600)
			dir = SENS_GAUCHE;
	} else {
		x -= SPEED;

		if (x < offset + 30)
			dir = SENS_DROITE;
	}

	if (etape_shoot == 0) {
		if (tete_turc != NULL && tete_turc->y > y) {
			int	ddx = x - tete_turc->x;

			if (ddx > -10 && ddx < 10) {
				etape_shoot = 0;
				etat = 3;
			}
		}
	} else {
		etape_shoot -= 1;
	}

	noCol();
}


void TirNuage::onTire()
{
	static const int anim [] = { 253, 254, 255, 254 };
	static const int SPEED = 1;

	delta_eclair += 1;
	delta_eclair %= 2;

	if (delta_eclair == 0) {
		eclair += 1;
		eclair %= 4;
	}

	duree_vie -= 1;

	if (duree_vie <= 0) {
		etape = ss_etape = 0;
		etat = 2;
	}


	pic = pbk_ennemis[anime(anim, 4, 9)];

	etape_shoot += 1;

	if (etape_shoot == 50) {
		sbk_niveau.play(24);
	}

	if (etape_shoot >= 100) {
		etat = 1;
		etape_shoot = 100;
		colFromPic();
	} else if (etape_shoot > 50) {
		x1 = x - 20;
		x2 = x + 20;
		y1 = y - 10;
		y2 = 480;
		col_on = true;
	}

	dy = rand() % 20;
}

void TirNuage::affiche()
{
	int de = eclair;

	if (etat == 3 && etape_shoot > 50) {
		for (int yy = y - 10 + dy; yy < 480; yy += 100) {
			draw(x, yy, pbk_ennemis[256 + de]);

			de = (de + 1) % 4;
		}
	}

	Sprite::affiche();
}
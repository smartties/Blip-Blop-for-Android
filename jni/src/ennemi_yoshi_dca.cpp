#include "ennemi_yoshi_dca.h"
#include "tir_carapace.h"


EnnemiYoshiDCA::EnnemiYoshiDCA(): attack_delay(50 + rand() % 150), wait_for_attack(0)
{
	tresor = 12;
	pv = 400;
}

void EnnemiYoshiDCA::update()
{
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

		/*case ETAT_TOMBE:
			onTombe();
			break;*/

		case ETAT_TIRE:  //YoshiDCA balance des carapaces
			onTire();
			break;
	}

	updateADetruire();
}

void EnnemiYoshiDCA::onAvance()
{
	tombe();
	//pour attaquer
	wait_for_attack++;
	if (wait_for_attack >= attack_delay && x <= offset + 640) {
		wait_for_attack = 0;
		attack_delay = 50 + rand() % 150;
		if (tete_turc->x > x) {
			dir = SENS_DROITE;
		} else {
			dir = SENS_GAUCHE;
		}
		etape = 0;
		etat = ETAT_TIRE;
		sbk_niveau.play(35);
		onTire();
		return;
	}

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[28];
	} else {
		pic = pbk_ennemis[31];
	}

	colFromPic();
}


void EnnemiYoshiDCA::onMeure()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0 && etape < 9)
		etape += 1;

	if (etape >= 9) {
		int		yy = plat(x, y);

		if (yy != 0 && yy != y_plat[4][x])
			grave(x, y, pic);

		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[71 + etape];
		else
			pic = pbk_ennemis[62 + etape];
	}
}

void EnnemiYoshiDCA::onTire()
{

	ss_etape += 1;
	ss_etape %= 15;

	if (ss_etape == 0)
		etape += 1;

	if (etape >= 2) {
		TirCarapace *	tir = new TirCarapace();

		tir->setDir(dir);

		if (dir == SENS_GAUCHE)
			tir->x = x - 23;
		else
			tir->x = x + 23;

		tir->y = y - 23;


		list_tirs_ennemis.ajoute((void*) tir);

		etape = 0;
		etat = ETAT_AVANCE;
		return;
	}


	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[54 + etape];
	} else {
		pic = pbk_ennemis[56 + etape];
	}

	colFromPic();
}

void EnnemiYoshiDCA::onCarbonise()
{
	tombe();
	ss_etape ++;
	ss_etape %= 5;

	if (ss_etape == 0)
		etape ++;

	if (etape >= 14)
		a_detruire = true;
	else {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[460 + etape];
		else
			pic = pbk_ennemis[474 + etape];
	}
}

void EnnemiYoshiDCA::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (etat == ETAT_MEURE) {
		sbk_misc.play(6 + rand() % 3);
	}
}

#include "ennemi_bisou_nuage.h"
#include "tir_nuage.h"

EnnemiBisouNuage::EnnemiBisouNuage() : etape_shoot(0)
{
	pv = 250;
	wait_shoot = 150 + rand() % 150;
}

void EnnemiBisouNuage::update()
{
	if (blood > 0)
		blood -= 1;

	etape_shoot += 1;

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onNormal();
			break;

		case ETAT_MEURE:
		case ETAT_CARBONISE:
			onMeureWait();
			break;

		case ETAT_MEURE_2:
			onMeureTombe();
			break;


		case ETAT_MEURE_4:
			onMeureFin();
			break;
	}

	updateADetruire();
}

void EnnemiBisouNuage::onMeureFin()
{
	if (etape < 6) {
		ss_etape += 1;
		ss_etape %= 3;

		if (ss_etape == 0)
			etape += 1;

		if (dir == SENS_DROITE) {
//			x += 2;
			pic = pbk_ennemis[236 + etape];
		} else {
//			x -= 2;
			pic = pbk_ennemis[243 + etape];
		}
	} else {
		grave(x, y, pic);
		a_detruire = true;
	}
}




void EnnemiBisouNuage::onMeureTombe()
{
	tombe();

	ss_etape += 1;
	ss_etape %= 8;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 2;
	}

	if (dir == SENS_GAUCHE)
		pic = pbk_ennemis[234 + etape];
	else
		pic = pbk_ennemis[232 + etape];

	if (plat(x, y) != 0) {
		etape = ss_etape = 0;
		etat = ETAT_MEURE_4;
//		sbk_niveau.play( 25);
	}
}

void EnnemiBisouNuage::onMeureWait()
{
	etape += 1;

	if (dir == SENS_GAUCHE)
		pic = pbk_ennemis[261];
	else
		pic = pbk_ennemis[260];

	if (etape >= 30) {
		etape = ss_etape = 0;
		etat = ETAT_MEURE_2;
	}
}

void EnnemiBisouNuage::onNormal()
{
	static const int anim_gauche [] = { 229, 230, 231, 230 };
	static const int anim_droite [] = { 226, 227, 228, 227 };

	if (x > (offset + 320)) {
		dir = SENS_GAUCHE;
		pic = pbk_ennemis[anime(anim_gauche, 4, 10)];
	} else {
		dir = SENS_DROITE;
		pic = pbk_ennemis[anime(anim_droite, 4, 10)];
	}

	if (etape_shoot >= wait_shoot && x <= offset + 640) {
		Sprite * s = new TirNuage();

		s->x = x;
		s->y = y - 17;
		s->dir = dir;

		list_tirs_ennemis.ajoute((void*) s);

		etape_shoot = 0;
		wait_shoot = 250 + rand() % 250;
	}

	colFromPic();
}

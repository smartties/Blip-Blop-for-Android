
#include "tir_epee_laser.h"
#include "ennemi_bisou_jedi.h"


TirEpeeLaser::TirEpeeLaser() : isdead(false), cible(NULL), retour(false), lanceur(NULL), accel(1)
{
	duree_vie = 200 + rand() % 100;
	sbk_niveau.play(13, SOUND_LOOP);
}

TirEpeeLaser::~TirEpeeLaser()
{
	sbk_niveau.stop(13);
}

void TirEpeeLaser::update()
{
	ss_etape += 1;
	ss_etape %= 4;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 24;
	}

	pic = pbk_ennemis[525 + etape];


	x += dx / 10;
	y += dy / 10;

	int		xc = offset - 400;
	int		yc = 240;

	if (!isdead) {
		if (lanceur->a_detruire || ((Ennemi*)lanceur)->etat == ETAT_MEURE) {
			isdead = true;
		}
	}

	if (isdead) {
		updateADetruire();

		if (a_detruire) {
			sbk_niveau.stop(13);
		}
	} else if (retour) {
		xc = lanceur->x;
		yc = lanceur->y - 25;

		int ddx = xc - x;
		int ddy = yc - y;

		if (ddx > -10 && ddx < 10 && ddy > -10 && dy < 10) {
			a_detruire = true;
			sbk_niveau.stop(13);
			((EnnemiBisouJedi*)lanceur)->a_epee = true;
		}
	} else {
		duree_vie -= 1;

		if (cible->a_detruire || duree_vie < 0) {
			accel = 4;
			retour = true;
		} else {
			xc = cible->x;
			yc = cible->y - 15;
		}

	}

	if (xc > x && dx < 50) dx += accel;
	else if (dx > -50) dx -= accel;

	if (yc > y && dy < 50) dy += accel;
	else if (dy > -50) dy -= accel;

	colFromPic();
}

#include "ennemi_bisou_auto.h"
#include "gore_bisou_auto.h"
#include "explosion.h"


static const int GO_LEFT  = 0;
static const int GO_RIGHT = 1;


EnnemiBisouAuto::EnnemiBisouAuto() : cible(tete_turc), dx(0), togo(GO_LEFT), trick(false)
{
	pv = 800;
}


void EnnemiBisouAuto::update()
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


void EnnemiBisouAuto::onAvance()
{
	static const int anim_droite [] = { 559, 560, 561, 560 };
	static const int anim_gauche [] = { 562, 563, 564, 563};

	static const int SPEED = 200;
	static const int ACCELX = 2;
	static const int ACCELY = 5;



	if (cible == NULL || cible->a_detruire) {
		cible = tete_turc;

		if (cible == NULL)
			return;
	}

	int gox;

	if (x > (offset + 440))
		togo = GO_LEFT;
	else if (x < (offset + 300))
		togo = GO_RIGHT;

	if (togo == GO_LEFT)
		gox = offset + 140;
	else
		gox = offset + 500;

	int goy = (cible->y - 20);

	if (gox < x && dx > -SPEED) dx -= ACCELX;
	else if (gox > x && dx < SPEED) dx += ACCELX;

	if (goy < y && dy > -SPEED) dy -= ACCELY;
	else if (goy > y && dy < SPEED) dy += ACCELY;

	gox = dx / 40;
	goy = dy / 40;

	if (!mur_opaque(x + gox, y)) x += gox;
	if (!mur_opaque(x, y + goy)) y += goy;

	if (dx > 0)
		pic = pbk_ennemis[anime(anim_droite, 4, 8)];
	else
		pic = pbk_ennemis[anime(anim_gauche, 4, 8)];

	colFromPic();
}

void EnnemiBisouAuto::onMeure()
{
	static const int anim_droite [] = { 559, 560, 561, 560 };
	static const int anim_gauche [] = { 562, 563, 564, 563};

	static const int SPEED = 200;
	static const int ACCELX = 2;
	static const int ACCELY = 5;


	int gox;

	if (dx <= 0)
		gox = offset - 640;
	else
		gox = offset + 900;


	if (gox < x && dx > -SPEED) dx -= ACCELX;
	else if (gox > x && dx < SPEED) dx += ACCELX;

	if (dy < SPEED)
		dy += ACCELY;

	x += dx / 40;
	y += dy / 40;

	if (mur_opaque(x, y) || plat(x, y) != 0)
		dy = -200;

	if (dx > 0)
		pic = pbk_ennemis[anime(anim_droite, 4, 8)];
	else
		pic = pbk_ennemis[anime(anim_gauche, 4, 8)];

	if ((ss_etape % 2) == 0) {
		Sprite * s = new Explosion();

		s->x = x - 20 + rand() % 40;
		s->y = y - 20 + rand() % 40;

		list_impacts.ajoute((void*) s);
	}

	updateADetruire();

}



#ifndef _GoreBisouBoom_
#define _GoreBisouBoom_

#include "sprite.h"

class GorePiedBisouBoom : public Sprite
{
public:
	virtual void update()
	{
		tombe();

		if (etape < 5) {
			ss_etape += 1;
			ss_etape %= 8;

			if (ss_etape == 0)
				etape += 1;

			if (dir == SENS_DROITE)
				pic = pbk_ennemis[190 + etape];
			else
				pic = pbk_ennemis[196 + etape];
		}


		if ((plat(x, y) != 0 && etape >= 5) || mur_opaque(x, y)) {
			grave(x, y, pic);
			a_detruire = true;
			sbk_misc.play(6 + (rand() % 2));
		} else {
			if (dir == SENS_DROITE)
				x -= 2;
			else
				x += 2;
		}


		updateADetruire();
	};
};

class GoreTeteBisouBoom : public Sprite
{
public:
	virtual void update()
	{
		tombe();

		if (etape < 5) {
			ss_etape += 1;
			ss_etape %= 8;

			if (ss_etape == 0)
				etape += 1;

			if (dir == SENS_DROITE)
				pic = pbk_ennemis[202 + etape];
			else
				pic = pbk_ennemis[208 + etape];
		}


		if ((plat(x, y) != 0 && etape >= 5) || mur_opaque(x, y)) {
			grave(x, y, pic);
			a_detruire = true;
			sbk_misc.play(6 + (rand() % 2));
		} else {
			if (dir == SENS_DROITE)
				x += 2;
			else
				x -= 2;
		}

		updateADetruire();
	};
};

class GoreBideBisouBoom : public Sprite
{
public:
	virtual void update()
	{
		tombe();

		if (etape < 5) {
			ss_etape += 1;
			ss_etape %= 8;

			if (ss_etape == 0)
				etape += 1;

			if (dir == SENS_DROITE)
				pic = pbk_ennemis[214 + etape];
			else
				pic = pbk_ennemis[220 + etape];
		}


		if ((plat(x, y) != 0 && etape >= 5) || mur_opaque(x, y)) {
			grave(x, y, pic);
			sbk_misc.play(6 + (rand() % 2));
			a_detruire = true;
		} else {
			if (dir == SENS_DROITE)
				x += 1;
			else
				x -= 1;
		}

		updateADetruire();
	};
};

#endif

#ifndef _TirEtoile_
#define _TirEtoile

#include "tir.h"

class TirEtoile : public Tir
{
public:
	int		life_time;

	TirEtoile() : life_time(500)
	{
	};

	virtual void update()
	{
		static const int SPEED = 2;

		tombe();

		if (plat(x, y) != 0 || plat(x, y + 5))
			dy = -3 - rand() % 2;

		ss_etape += 1;
		ss_etape %= 3;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 24;
		}

		pic = pbk_ennemis[130 + etape];

		if (dir == SENS_DROITE) {
			if (mur_opaque(x + SPEED, y))
				dir = SENS_DROITE;
			else
				x += SPEED;
		} else {
			if (mur_opaque(x - SPEED, y))
				dir = SENS_DROITE;
			else
				x -= SPEED;
		}

		life_time -= 1;

		if (mur_opaque(x, y) || life_time <= 0)
			a_detruire = true;

		colFromPic();
		updateADetruire();
	};
};

#endif

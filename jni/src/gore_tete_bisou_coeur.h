
#ifndef _GoreTeteBisouCoeur_
#define _GoreTeteBisouCoeur_

#include "sprite.h"

class GoreTeteBisouCoeur : public Sprite
{
public:

	int		dx;
	bool	joue_son;

	GoreTeteBisouCoeur() : joue_son(false)
	{
		dy = -1 - rand() % 3;
		dx = -2 + rand() % 5;
	};

	virtual void update()
	{
		tombe();

		ss_etape += 1;
		ss_etape %= 5;

		if (plat(x, y) == 0) {
			x += dx;
		}

		if (ss_etape == 0 && (etape < 3 || plat(x, y) != 0)) {
			if (!joue_son && plat(x, y) != 0) {
				sbk_misc.play(6 + (rand() % 2));
				joue_son = true;
			}

			etape += 1;

			if (etape > 6) {
				grave(x, y, pic);
				a_detruire = true;
				return;
			}
		}

		if (dir == SENS_DROITE)
			pic = pbk_ennemis[447 + etape];
		else
			pic = pbk_ennemis[454 + etape];
	};
};

#endif
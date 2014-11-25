#ifndef _GoreBisouAuto_
#define _GoreBisouAuto_

#include "sprite.h"

class GoreBisouAuto : public Sprite
{
public:

	bool	sol;

	GoreBisouAuto() : sol(false)
	{
	}

	virtual void update()
	{
		static const int anim_droite [] = { 589, 590, 591, 592, 591, 590 };
		static const int anim_gauche [] = { 603, 604, 605, 606, 605, 604 };
		static const int SPEED = 2;

		tombe();

		if (plat(x, y) && !sol) {
			sol = true;
			etape = ss_etape = 0;
		}

		if (sol) {
			ss_etape += 1;
			ss_etape %= 5;

			if (ss_etape == 0) {
				etape += 1;

				if (etape >= 10) {
					a_detruire = true;
					grave(x, y, pic);
					return;
				}
			}

			if (dir == SENS_DROITE)
				pic = pbk_ennemis[593 + etape];
			else
				pic = pbk_ennemis[607 + etape];
		} else {
			if (dir == SENS_DROITE)
				pic = pbk_ennemis[anime(anim_droite, 6, 6)];
			else
				pic = pbk_ennemis[anime(anim_gauche, 6, 6)];
		}

		if (dir == SENS_DROITE && !mur_opaque(x + SPEED, y))
			x += SPEED;
		else if (dir == SENS_GAUCHE && !mur_opaque(x - SPEED, y))
			x -= SPEED;

		updateADetruire();
	};
};

#endif
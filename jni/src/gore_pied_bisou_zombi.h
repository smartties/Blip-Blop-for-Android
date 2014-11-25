
#ifndef _GorePiedsBisouZombi_
#define _GorePiedsBisouZombi_

#include "sprite.h"

class GorePiedsBisouZombi : public Sprite
{
public:
	virtual void update()
	{
		tombe();

		if (etape < 3) {
			ss_etape += 1;
			ss_etape %= 6;

			if (ss_etape == 0)
				etape += 1;
		}

		if (dir == SENS_DROITE) {
			marche(-1);
			pic = pbk_ennemis[300 + etape];
		} else {
			marche(1);
			pic = pbk_ennemis[304 + etape];
		}

		if (etape == 3 && plat(x, y) != 0) {
			grave(x, y, pic);
			a_detruire = true;
		}
	};
};

#endif

#ifndef _GorePiedsBisouCiel_
#define _GorePiedsBisouCiel_

#include "sprite.h"

class GorePiedsBisouCiel : public Sprite
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
			pic = pbk_ennemis[etape];
		} else {
			marche(1);
			pic = pbk_ennemis[4 + etape];
		}

		if (etape == 3 && plat(x, y) != 0) {
			grave(x, y, pic);
			a_detruire = true;
		}
	};
};

#endif
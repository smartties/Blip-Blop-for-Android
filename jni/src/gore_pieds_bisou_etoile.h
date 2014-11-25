
#ifndef _GorePiedsBisouEtoile_
#define _GorePiedsBisouEtoile_

#include "sprite.h"

class GorePiedsBisouEtoile : public Sprite
{
public:

	int		etat;
	int		nb;

	GorePiedsBisouEtoile() : etat(0), nb(0)
	{
	}

	virtual void update()
	{
		static const int anim_droite [] = { 97, 98, 99, 98 };
		static const int anim_gauche [] = { 103, 104, 105, 104 };

		if (etat == 0) {
			tombe();

			if (etape < 3) {
				ss_etape += 1;
				ss_etape %= 6;

				if (ss_etape == 0)
					etape += 1;
			}

			if (dir == SENS_DROITE) {
				marche(-1);
				pic = pbk_ennemis[94 + etape];
			} else {
				marche(1);
				pic = pbk_ennemis[100 + etape];
			}

			if (etape == 3 && plat(x, y) != 0) {
				etat = 1;
				ss_etape = etape = 0;
			}
		} else {
			nb += 1;

			if (dir == SENS_DROITE)
				pic = pbk_ennemis[ anime(anim_droite, 4, 5)];
			else
				pic = pbk_ennemis[anime(anim_gauche, 4, 5)];

			if (nb >= 100) {
				grave(x, y, pic);
				a_detruire = true;
			}
		}
	};
};

#endif

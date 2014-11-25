
#include "tir_coeur_bisou.h"
#include "ben_maths.h"

TirCoeurBisou::TirCoeurBisou() : ok(false)
{
	phi = rand() % 360;
}

void TirCoeurBisou::update()
{
	y += 1;

	phi += 5;
	phi %= 360;

	x = xbase + ((10 * bCos[phi]) >> COSINUS);

	if (!ok) {
		ss_etape += 1;
		ss_etape %= 6;

		if (ss_etape == 0) {
			etape += 1;

			if (etape >= 2)
				ok = true;
		}

		pic = pbk_ennemis[461 + etape];
	}

	if (mur_opaque(x, y))
		a_detruire = true;


	colFromPic();
	updateADetruire();
}
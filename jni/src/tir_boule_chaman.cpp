
#include "tir_boule_chaman.h"

TirBouleChaman::TirBouleChaman() : ok(false), boom(false)
{
}

void TirBouleChaman::update()
{
	if (!boom) {
		x += dx;
		y += dy;
	}

	ss_etape += 1;
	ss_etape %= 4;

	if (boom) {
		if (ss_etape == 0) {
			etape += 1;

			if (etape > 4) {
				a_detruire = true;
				return;
			}
		}

		if (dx > 0)
			pic = pbk_ennemis[384 + etape];
		else
			pic = pbk_ennemis[389 + etape];

	} else if (ok) {
		if (ss_etape == 0) {
			etape += 1;
			etape %= 5;
		}

		if (mur_opaque(x, y)) {
			etape = ss_etape = 0;
			boom = true;
		}

		if (dx > 0)
			pic = pbk_ennemis[374 + etape];
		else
			pic = pbk_ennemis[379 + etape];
	} else {
		if (ss_etape == 0) {
			etape += 1;

			if (etape > 4) {
				ok = true;
				return;
			}
		}

		if (dx > 0)
			pic = pbk_ennemis[364 + etape];
		else
			pic = pbk_ennemis[369 + etape];
	}

	colFromPic();
	updateADetruire();
}
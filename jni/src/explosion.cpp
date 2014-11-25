
#include "explosion.h"


Explosion::Explosion() : fini(false)
{
	type = rand() % 2;

	if (type == 1)
		speed = 2 + rand() % 2;
	else
		speed = 4 + rand() % 3;
}

void Explosion::update()
{
	ss_etape += 1;
	ss_etape %= speed;

	if (ss_etape == 0) {

		if (fini) {
			etape -= 1;

			if (type == 0) {
				if (etape < 0)
					a_detruire = true;
				else
					pic = pbk_bb[212 + etape];
			} else if (type == 1) {
				if (etape < 0)
					a_detruire = true;
				else
					pic = pbk_bb[219 + etape];
			} else {
				if (etape < 0)
					a_detruire = true;
				else
					pic = pbk_bb[231 + etape];
			}
		} else {
			etape += 1;

			if (type == 0) {
				if (etape >= 5)
					fini = true;
				else
					pic = pbk_bb[212 + etape];
			} else if (type == 1) {
				if (etape >= 10)
					fini = true;
				else
					pic = pbk_bb[219 + etape];
			} else {
				if (etape >= 5)
					fini = true;
				else
					pic = pbk_bb[231 + etape];
			}
		}
	}
}

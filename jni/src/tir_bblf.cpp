
#include "tir_bblf.h"
#include "alpha_blend.h"


void TirBBLF::aTouche(int pts)
{
	if (!a_detruire) {
		TirBB::aTouche(pts);
		a_detruire = false;
	}
}

void TirBBLF::setDir(int d)
{
	TirBB::setDir(d);

	etape	 = 0;
	ss_etape = 0;
	latence  = 0;
	type	 = rand() % 2;
	fini	 = false;
	pic		 = NULL;


	if (type == 1)
		speed = 2 + rand() % 2;
	else if (type == 0)
		speed = 4 + rand() % 3;
	else
		speed = 5 + rand() % 3;


	switch (dir) {
		case 0:
			dx = 1 - rand() % 3;
			dy = 3 + rand() % 3;
			break;

		case 1:
			dx = 1 + rand() % 3;
			dy = 2 + rand() % 3;
			break;

		case 2:
			dx = 3 + rand() % 3;
			dy = 1 + rand() % 3;
			break;

		case 3:
			dx = 3 + rand() % 3;
			dy = rand() % 3;
			break;

		case 4:
			dx = 3 + rand() % 3;
			dy = 1 - rand() % 3;
			break;

		case 5:
			dx = 3 + rand() % 3;
			dy = - rand() % 3;
			break;

		case 6:
			dx = 3 + rand() % 3;
			dy = -1 - rand() % 3;
			break;

		case 7:
			dx = rand() % 3;
			dy = -2 - rand() % 3;
			break;

		case 8:
			dx = 1 - rand() % 3;
			dy = -3 - rand() % 3;
			break;

		case 9:
			dx = - rand() % 3;
			dy = -3 - rand() % 3;
			break;

		case 10:
			dx = -3 - rand() % 3;
			dy = -1 - rand() % 3;
			break;

		case 11:
			dx = -3 - rand() % 3;
			dy = - rand() % 3;
			break;

		case 12:
			dx = -3 - rand() % 3;
			dy = 1 - rand() % 3;
			break;

		case 13:
			dx = -3 - rand() % 3;
			dy = rand() % 3;
			break;

		case 14:
			dx = -3 - rand() % 3;
			dy = 1 + rand() % 3;
			break;

		case 15:
			dx = -1 - rand() % 3;
			dy = 2 + rand() % 3;
			break;
	}
}

void TirBBLF::update()
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

	//x += dx;
	//y += dy;
	update_tir(x, y, dx, dy, angle);

	latence += 1;
	latence %= 17;

	if (latence == 0 && dy > -3)
		dy--;

	colFromPic();
	updateADetruire();
}

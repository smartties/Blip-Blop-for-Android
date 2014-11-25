
#include <stdlib.h>
#include "fond_lampe_2.h"

#define ETAT_CLIGNOTE	100

FondLumiere2::FondLumiere2() :  allume(false), wait_for_cligno(0)
{
	delai_cligno = 50 + rand() % 200;
	pic = pbk_niveau[17];
}

void FondLumiere2::update()
{
	static const int anim_cligno [] = {2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 0, 0};

	wait_for_cligno += 1;

	if (allume) {
		if (wait_for_cligno >= delai_cligno) {
			allume = false;
			ss_etape = 0;
			etape = 0;
		}
	} else {
		pic = pbk_niveau[17 + anime(anim_cligno, 58, 3)];

		if (etape == 57) {
			allume = true;
			wait_for_cligno = 0;
			delai_cligno = 50 + rand() % 200;
		}
	}

	if (x < offset - 300)
		a_detruire = true;
}
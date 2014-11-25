/******************************************************************
*
*
*		-----------------------------
*		    FondRocherHyperspace.cpp
*		-----------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 18 Janvier 2001
*
*
*
******************************************************************/


#include "fond_rocher_hyperspace.h"
#include "ben_maths.h"


const int rocher_levitation[] = {0, 0, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 0, 0};

FondRocherHyperspace::FondRocherHyperspace(): placer(1), delta(rand() % 360), y_base(0), sinusoide_delay(1)
{
	//x_delay = 1 + rand()%6;
	//pic = pbk_niveau[64 + rand()%7];
}

void FondRocherHyperspace::update()
{

	delta += sinusoide_delay;
	delta %= 360;

	if (placer) {
		if ((x >= 0) && (x < 200)) {
			//x_delay = 1 + rand()%2;
			x_delay = 2 + rand() % 3;
			plan_rocher = 2;
			pic = pbk_niveau[64 + rand() % 7];
			sinusoide_delay = 2 + rand() % 2;
		} else if ((x >= 200) && (x < 420)) {
			//x_delay = 2 + rand()%3;
			x_delay = 4 + rand() % 5;
			plan_rocher = 1;
			pic = pbk_niveau[71 + rand() % 5];
			sinusoide_delay = 3 + rand() % 2;
		} else if ((x >= 420) && (x < 640)) {
			//x_delay = 4 + rand()%4;
			x_delay = 8 + rand() % 4;
			plan_rocher = 0;
			pic = pbk_niveau[77 + rand() % 5];
			sinusoide_delay = 4 + rand() % 2;
		}
		x = rand() % 640;
		y_base = rand() % 380;
		y = rand() % 380;
		placer = 0;
	}
	ss_etape++;
	ss_etape %= x_delay;
	x += x_delay;

	switch (plan_rocher) {
		case 0:
			y = y_base + bCos[delta] / 92;
			break;

		case 1:
			y = y_base + bCos[delta] / 128;
			break;

		case 2:
			y = y_base + bCos[delta] / 192;
			break;
	}


	if (x > offset + 700) {
		x = offset - 80;
		y_base = rand() % 380;
		y = rand() % 380;
		switch (plan_rocher) {
			case 0:
				//x_delay = 4 + rand()%4;
				x_delay = 8 + rand() % 4;
				pic = pbk_niveau[77 + rand() % 5];
				sinusoide_delay = 4 + rand() % 2;
				break;

			case 1:
				//x_delay = 2 + rand()%3;
				x_delay = 4 + rand() % 5;
				pic = pbk_niveau[71 + rand() % 5];
				sinusoide_delay = 3 + rand() % 2;
				break;

			case 2:
				//x_delay = 1 + rand()%2;
				x_delay = 2 + rand() % 3;
				pic = pbk_niveau[64 + rand() % 7];
				sinusoide_delay = 2 + rand() % 2;
				break;
		}
	}
}

void FondRocherHyperspace::affiche()
{
	if (!placer) {
		Sprite::affiche();
	}
}

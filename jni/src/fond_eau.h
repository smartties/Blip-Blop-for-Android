
#include <stdio.h>
#include "sprite.h"

#ifndef _FondEau_
#define _FondEau_

int water_seed  = 0;
int water_seed2 = 5;

class FondEau1 : public Sprite
{
public:
	virtual void update()
	{
		pic = pbk_niveau[7 + water_seed];

		if (x < offset - 400)
			a_detruire = true;
	};
};

class FondEau2 : public Sprite
{
	virtual void update()
	{
		pic = pbk_niveau[7 + water_seed2];

		if (x < offset - 400)
			a_detruire = true;
	};
};

class FondEau : public Sprite
{
public:
	FondEau()
	{
		Sprite *	ptr;
		bool		b = false;


		for (int i = 0; i < (((level_size) / pbk_niveau[7]->xSize()) + 1); i++) {
			if (b)
				ptr = new FondEau1();
			else
				ptr = new FondEau2();

			ptr->x = x;
			ptr->y = 454;

			x += 376;
			b = !b;


			list_fonds_animes.ajoute((void*) ptr);
		}
	};


	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 7;

		if (ss_etape == 0) {
			water_seed += 1;
			water_seed %= 10;

			water_seed2 += 1;
			water_seed2 %= 10;
		}
	};
};

#endif
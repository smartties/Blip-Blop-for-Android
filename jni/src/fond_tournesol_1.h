#ifndef _FondTournesol1_
#define _FondTournesol1_

#include "sprite.h"

class FondTournesol1 : public Sprite
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 10;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 2;
		}

		pic = pbk_niveau[20 + etape];
	};
};

#endif
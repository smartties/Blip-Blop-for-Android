#ifndef _FondTournesol2_
#define _FondTournesol2_

#include "sprite.h"

class FondTournesol2 : public Sprite
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

		pic = pbk_niveau[22 + etape];
	};
};

#endif
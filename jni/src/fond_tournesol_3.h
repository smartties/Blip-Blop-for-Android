#ifndef _FondTournesol3_
#define _FondTournesol3_

#include "sprite.h"

class FondTournesol3 : public Sprite
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

		pic = pbk_niveau[24 + etape];
	};
};

#endif
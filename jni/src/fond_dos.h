
#ifndef _FondDos_
#define _FondDos_

#include "sprite.h"

class FondDos : public Sprite
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 40;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 2;
		}

		pic = pbk_niveau[58 + etape];
		updateADetruire();
	};

};

#endif
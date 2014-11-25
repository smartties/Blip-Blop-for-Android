/******************************************************************
*
*
*		---------------------------
*		    FondEcranneige.h
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/

#ifndef _FondEcranNeige_
#define _FondEcranNeige_

#include "sprite.h"

class FondEcranneige : public Sprite
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 4;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 4;
		}

		pic = pbk_niveau[45 + etape];
		updateADetruire();
	};

};

#endif
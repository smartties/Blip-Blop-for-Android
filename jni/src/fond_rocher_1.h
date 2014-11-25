/******************************************************************
*
*
*		---------------------------
*		    FondRocher1.h
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/


#ifndef _FondRocher1_
#define _FondRocher1_

#include "sprite.h"

class FondRocher1 : public Sprite
{
public:
	int ss_etape_levitation;
	int etape_levitation;

	FondRocher1();
	virtual void update();
};

#endif
/******************************************************************
*
*
*		---------------------------
*		    FondRocherHyperspace.h
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 18 Janvier 2001
*
*
*
******************************************************************/


#ifndef _FondRocherhyperspace_
#define _FondRocherhyperspace_

#include "sprite.h"

class FondRocherHyperspace : public Sprite
{
public:

	int plan_rocher;
	int placer;
	int delta;
	int x_delay;
	int sinusoide_delay;
	int y_base;

	FondRocherHyperspace();
	virtual void update();
	virtual void affiche();
};

#endif

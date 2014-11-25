/******************************************************************
*
*
*		---------------------------
*		    FondEcrancamera.h
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/

#include "sprite.h"

#ifndef _FondCamera_
#define _FondCamera_


class FondEcrancamera : public Sprite
{
public:

	virtual void update();
	virtual void affiche();
};

#endif
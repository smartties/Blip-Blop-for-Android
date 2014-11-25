/******************************************************************
*
*
*		-----------------------
*		    TirCruiserLaser.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 17 Decembre 2000
*
*
*
******************************************************************/

#ifndef _FondTircruiserlaser_
#define _FondTircruiserlaser_

#include "sprite.h"

class TirCruiserLaser : public Sprite
{
public:

	int dx;
	int npic;

	TirCruiserLaser(int vx, int nb_pic);
	virtual void update();
};

#endif
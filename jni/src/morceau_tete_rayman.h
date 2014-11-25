/******************************************************************
*
*
*		-----------------------
*		    MorceauTeteRayman.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 23 Fevrier 2001
*
*
*
******************************************************************/

#ifndef _MorceauTeteRayman_
#define _MorceauTeteRayman_

#include "sprite.h"


//-----------------------------------------------------------------------------
//		Définition de la classe MorceauTeteRayman
//----------------------------------------------------------------------------

class MorceauTeteRayman : public Sprite
{
private:

	int dx;

public:

	//methodes "habituelles"
	MorceauTeteRayman(int vx, int vy);
	virtual void update();
};

#endif

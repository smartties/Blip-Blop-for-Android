/******************************************************************
*
*
*		-----------------------
*		   MorceauRayman.h
*		-----------------------
*
*		Poing1 & 2 qui giclent + jambes qui giclent..
*
*		Mephisto / LOADED -   V 0.1 - 20 Decembre 2000
*
*
*
******************************************************************/


#ifndef _MorceauSonicRing_
#define _MorceauSonicRing_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "sprite.h"


//-----------------------------------------------------------------------------
//		Définition de la classe MorceauRayman
//-----------------------------------------------------------------------------

class MorceauSonicRing : public Sprite
{
public:
	int		dx;

	MorceauSonicRing(int vx , int vy);

	virtual void update();

};

#endif

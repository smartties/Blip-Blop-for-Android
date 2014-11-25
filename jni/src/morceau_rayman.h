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


#ifndef _MorceauRayman_
#define _MorceauRayman_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "sprite.h"


//-----------------------------------------------------------------------------
//		Définition de la classe MorceauRayman
//-----------------------------------------------------------------------------

class MorceauRayman : public Sprite
{
public:
	int		dx;
	int		n_pic;

	MorceauRayman(int m_pic , int vx , int vy);

	virtual void update();

};

#endif

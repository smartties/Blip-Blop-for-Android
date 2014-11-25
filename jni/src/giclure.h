/******************************************************************
*
*
*		-------------------
*		    Giclure.h
*		-------------------
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _Giclure_
#define _Giclure_

#include "personnage.h"

class Giclure : public Sprite
{
public:
	Personnage *pere;
	int			deltax;
	int			deltay;

	virtual void update();
};

#endif
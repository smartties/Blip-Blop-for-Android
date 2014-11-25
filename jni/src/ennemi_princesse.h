/******************************************************************
*
*
*		-----------------------
*		    EnnemiPrincesse.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.9 - 31 Janvier 2001
*
*
*
******************************************************************/


#ifndef _EnnemiPrincesse_
#define _EnnemiPrincesse_

#include "enemy.h"

#define PRINCESSE_SPEED 1

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiPrincesse
//----------------------------------------------------------------------------

class EnnemiPrincesse : public Ennemi
{
private:
	bool avance;
	bool aide;

public:
	EnnemiPrincesse();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();

	virtual void estTouche(Tir * tir);
};

#endif
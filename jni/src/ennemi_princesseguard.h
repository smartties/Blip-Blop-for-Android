/******************************************************************
*
*
*		-----------------------
*		    EnnemiPrincesseguard.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.9 - 21 Janvier 2001
*
*
*
******************************************************************/

#ifndef _EnnemiGuard_
#define _EnnemiGuard_

#include "enemy.h"
#include "ennemi_princesse.h"


#define GUARD_SPEED 1

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiPrincesseGuard
//----------------------------------------------------------------------------

class EnnemiPrincesseguard : public Ennemi
{
private:
	int distance_couverture;

public:
	EnnemiPrincesse * princesse;


	EnnemiPrincesseguard(EnnemiPrincesse* Princesse, int distance);
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void estTouche(Tir * tir);
};

#endif
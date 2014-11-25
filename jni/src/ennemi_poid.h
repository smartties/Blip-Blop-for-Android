/******************************************************************
*
*
*		-----------------------
*		    EnnemiPoid.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 21 Fevrier 2001
*
*
*
******************************************************************/

#ifndef _EnnemiPoid_
#define _EnnemiPoid_

#include "enemy.h"

#define LATENCE_BOUGE		1

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiPoid
//----------------------------------------------------------------------------

class EnnemiPoid : public Ennemi
{

private:
	int nb_colision;

public:
	EnnemiPoid();
	virtual void update();
	virtual int degats();
	virtual void onMeure();
	virtual void estTouche(Tir * tir);
	virtual bool count()
	{
		return false;
	};
};

#endif
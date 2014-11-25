/******************************************************************
*
*
*		-----------------------
*		    EnnemiTeteRayman.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 22 Fevrier 2001
*
*
*
******************************************************************/

#ifndef _EnnemiTeteRayman_
#define _EnnemiTeteRayman_

#include "enemy.h"


//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiTeteRayman
//----------------------------------------------------------------------------

class EnnemiTeteRayman : public Ennemi
{
private:

	int dx;

public:

	//methodes "habituelles"
	EnnemiTeteRayman();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();

	virtual bool count()
	{
		return false;
	};

	virtual int degats();

	virtual void estTouche(Tir * tir);
};

#endif
/******************************************************************
*
*
*		-----------------------
*		    EnnemiPic.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 21 Fevrier 2001
*
*
*
******************************************************************/

#ifndef _EnnemiPic_
#define _EnnemiPic_

#include "enemy.h"


//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiPic
//----------------------------------------------------------------------------

class EnnemiPic : public Ennemi
{
private:
	int y_origine;

public:
	EnnemiPic();
	virtual void update();
	virtual void affiche();
	virtual void colFromPic();
	virtual void estTouche(Tir * tir);
	virtual int degats()
	{
		return 5;
	};

	virtual bool count()
	{
		return false;
	};
};

#endif
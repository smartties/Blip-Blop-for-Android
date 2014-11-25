/******************************************************************
*
*
*		-----------------------
*		    EnnemiPacman.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 10 Avril 2001
*
*
*
******************************************************************/

#ifndef _EnnemiPacman_
#define _EnnemiPacman_

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiPacman
//----------------------------------------------------------------------------

class EnnemiPacman : public Ennemi
{
private:
	int tir;
	int etape_tir;
	int ss_etape_tir;

	int dx;

public:
	EnnemiPacman();
	virtual void update();
	virtual int degats();
	virtual void affiche();
	virtual void estTouche(Tir * tir);

	virtual bool count()
	{
		return false;
	};
};

#endif
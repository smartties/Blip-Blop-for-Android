/******************************************************************
*
*
*		----------------
*		    Ennemi.h
*		----------------
*
*		Classe mère de tous les ennemis
*
*
*		Prosper / LOADED -   V 0.1 - 3 Aout 2000
*
*
*
******************************************************************/

#ifndef _Ennemi_
#define _Ennemi_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "personnage.h"
#include "tir.h"


//-----------------------------------------------------------------------------
//		La tête de turc
//-----------------------------------------------------------------------------

#ifndef ENNEMI_CPP
extern Personnage *	tete_turc;
#endif

//-----------------------------------------------------------------------------
//		Définition de la classe Ennemi
//-----------------------------------------------------------------------------

class Ennemi : public Personnage
{
public:
	Ennemi();

	int		xmin;
	int		blood;
	int		tresor;

	virtual bool count()
	{
		return true;
	};

	virtual void estTouche(Tir * tir);

	virtual int degats()
	{
		return 1;
	};

	virtual void gicle(const Tir * tir, const int * dxg, const int * dyg);

	void tirEnCloche(int xtir, int ytir, int xci, int yci, int & xspeed, int & yspeed) const;
};


#endif
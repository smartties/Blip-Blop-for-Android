/******************************************************************
*
*
*		---------------------------------
*		    TirSnorkyGouverneur.h
*		---------------------------------
*
*
*
*		Mephisto / LOADED -   V 0.3 - 27 Decembre 2000
*
*
*
******************************************************************/

#ifndef _TirSnorkyGouverneur_
#define _TirSnorkyGouverneur_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"
#include "personnage.h"


#define INERTIE_TIR   6
#define SPEED_MAX   6
#define TIME_MAX    100

//-----------------------------------------------------------------------------
//		Définition de la classe TirSnorkyGouverneur
//-----------------------------------------------------------------------------

class TirSnorkyGouverneur : public Tir
{
public:

	int dx;
	int etape_dx;
	int etape_dy;
	int time;
	Personnage * joueur_cible;

	TirSnorkyGouverneur(Personnage * cible, int vx , int vy);

	virtual int degats() const
	{
		return 1;
	};

	virtual int enflame() const
	{
		return 0;
	};

	virtual void setDir(int d)
	{
		dir = d;
	};

	virtual void update();

};

#endif
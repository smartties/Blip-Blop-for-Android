/******************************************************************
*
*
*		-------------------------------
*		    TirMarioFireballVertical.h
*		-------------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 14 Decembre 2000
*
*
*
******************************************************************/

#ifndef _TirMarioFireballVertical_
#define _TirMarioFireballVertical

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"



#define GRAVITE_FIREBALL  15
#define LATENCE_FIREBALL   10
//-----------------------------------------------------------------------------
//		Définition de la classe TirMarioFireballVertical
//-----------------------------------------------------------------------------

class TirMarioFireballVertical : public Tir
{
public:
	int		dx;
	int x_cible;

	TirMarioFireballVertical(int vx, int xc);

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
	virtual void fireball_tombe();

};

#endif
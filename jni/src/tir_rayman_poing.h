/******************************************************************
*
*
*		-----------------------
*		    EnnemiRaymanPoing.h
*		-----------------------
*
*		Tir Poing Rayman (les 2)
*
*		Mephisto / LOADED -   V 0.1 - 12 Decembre 2000
*
*
*
******************************************************************/

#ifndef _TirRaymanPoing_
#define _TirRaymanPoing_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"




//-----------------------------------------------------------------------------
//		Définition de la classe TirRaymanPoing
//-----------------------------------------------------------------------------
#define LATENCE_POING	  8

class TirRaymanpoing : public Tir
{
public:
	int		dx;
	int     x_cible;
	int     n_pic;

	TirRaymanpoing(int dx0, int xc);

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
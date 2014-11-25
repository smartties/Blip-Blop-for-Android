/******************************************************************
*
*
*		-----------------------
*		    EnnemiSoniceclair.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.5 - 08 Decembre 2000
*
*
*
******************************************************************/

#ifndef _TirSoniceclair_
#define _TirSoniceclair_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"

//-----------------------------------------------------------------------------
//		Définition de la classe Tir
//-----------------------------------------------------------------------------

class TirSoniceclair : public Tir
{
public:

	TirSoniceclair();

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
	virtual void affiche();

};

#endif
/******************************************************************
*
*
*		---------------------------------
*		    TirSnorkyMage.h
*		---------------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 16 Decembre 2000
*
*
*
******************************************************************/

#ifndef _TirSnorkyMage_
#define _TirSnorkyMage_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"


//-----------------------------------------------------------------------------
//		Définition de la classe TirSnorkyMage
//-----------------------------------------------------------------------------

class TirSnorkyMage : public Tir
{
public:

	int dx;

	TirSnorkyMage();

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
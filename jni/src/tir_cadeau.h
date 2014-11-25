/******************************************************************
*
*
*		----------------
*		   TirCadeau.h
*		----------------
*
*		Boum... Boum ! Boum !
*
*		Mortimus / LOADED -   V 0.1 - 20 Octobre 2000
*
*
*
******************************************************************/

#ifndef _TirCadeau_
#define _TirCadeau_


//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"

class TirCadeau : public Tir
{
public :
	TirCadeau() ;
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
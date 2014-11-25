/******************************************************************
*
*
*		----------------
*		TirSmurfSauvage.h
*		----------------
*
*		Le PM du schtroumph brujah
*
*		Mortimus / LOADED -   V 0.1 - 20 Octobre 2000
*
*
*
******************************************************************/

#ifndef _TirSmurfSauvage_
#define _TirSmurfSauvage_


//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"

class TirSmurfSauvage : public Tir
{
public :
	int dx ;
	int dy ;

	TirSmurfSauvage() ;
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

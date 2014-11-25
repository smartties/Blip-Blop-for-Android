/******************************************************************
*
*
*		----------------
*		   TirBouleChaman.h
*		----------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _TirBouleChaman_
#define _TirBouleChaman_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"

//-----------------------------------------------------------------------------
//		Définition de la classe Tir
//-----------------------------------------------------------------------------

class TirBouleChaman : public Tir
{
public:
	int		dx;
	bool	ok;
	bool	boom;

	TirBouleChaman();

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

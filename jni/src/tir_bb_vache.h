/******************************************************************
*
*
*		------------------
*		    TirBBVache.h
*		------------------
*
*		The mighty cow bomb!
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _TirBBVache_
#define _TirBBVache_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "joueur.h"
#include "tir_bb.h"

//-----------------------------------------------------------------------------
//		Définition de la classe TirBBVache
//-----------------------------------------------------------------------------

class TirBBVache : public TirBB
{
public:


	inline virtual int degats() const
	{
		return 50;
	};

	inline virtual int enflame() const
	{
		return 2;
	};

	inline virtual void aTouche(int pts)
	{
		joueur->addPoints(pts);
	};

	virtual void update();
};

#endif
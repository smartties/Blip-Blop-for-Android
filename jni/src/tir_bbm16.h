/******************************************************************
*
*
*		----------------
*		    TirBBM16.h
*		----------------
*
*		Pour les tirs de M16 de Blip/Blop
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _TirBBM16_
#define _TirBBM16_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "joueur.h"
#include "tir_bb.h"

//-----------------------------------------------------------------------------
//		Définition de la classe TirBBM16
//-----------------------------------------------------------------------------

class TirBBM16 : public TirBB
{
public:


	inline virtual int degats() const
	{
		return 40;
	};

	inline virtual int enflame() const
	{
		return 0;
	};

	virtual void update();

};

#endif

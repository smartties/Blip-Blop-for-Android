/******************************************************************
*
*
*		----------------
*		    TirBBPM.h
*		----------------
*
*		Pour les tirs de PM de Blip/Blop
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _TirBBPM_
#define _TirBBPM_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "joueur.h"
#include "tir_bb.h"

//-----------------------------------------------------------------------------
//		Définition de la classe TirBBPM
//-----------------------------------------------------------------------------

class TirBBPM : public TirBB
{
public:


	inline virtual int degats() const
	{
		return 75;
	};

	inline virtual int enflame() const
	{
		return 0;
	};

	virtual void update();

};

#endif

/******************************************************************
*
*
*		----------------
*		  TirBBFusil.h
*		----------------
*
*		Pour les tirs de fusil de Blip/Blop
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _TirBBFusil_
#define _TirBBFusil_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "joueur.h"
#include "tir_bb.h"

//-----------------------------------------------------------------------------
//		Définition de la classe TirBBM16
//-----------------------------------------------------------------------------

class TirBBFusil : public TirBB
{
public:

	int		dx;
	int		ddx;
	int		ddy;
	int		etape_dx;
	int		latence_x;
	int		latence_y;
	int		etape_dy;
	int		duree_vie;
	int		vie;

	inline virtual int degats() const
	{
		if (vie < duree_vie)
			return 40;
		else
			return 30;
	};

	inline virtual int enflame() const
	{
		return 0;
	};

	virtual void setDir(int d);
	virtual void update();

};

#endif

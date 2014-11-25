#ifndef _TirDebouchechiote_
#define _TirDebouchechiote_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"

//-----------------------------------------------------------------------------
//		Définition de la classe TirDecoucheChiote
//-----------------------------------------------------------------------------
#define DEBOUCHE_CHIOTE_SPEED      10

class TirDebouchechiote : public Tir
{
public:
	int		dx;

	TirDebouchechiote(int n_pbk_ennemis, int vx, int vy);

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
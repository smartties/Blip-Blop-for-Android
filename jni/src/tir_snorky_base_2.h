#ifndef _TirSnorkyBase2_
#define _TirSnorkyBase2_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"

//-----------------------------------------------------------------------------
//		Définition de la classe TirSnorkyBase2
//-----------------------------------------------------------------------------

class TirSnorkyBase2 : public Tir
{
public:
	int		dx;

	TirSnorkyBase2(int vx, int vy);

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

#ifndef _TirCarapace_
#define _TirCarapace_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"

//-----------------------------------------------------------------------------
//		Définition de la classe TirCarapace
//-----------------------------------------------------------------------------
#define CARAPACE_SPEED      6

class TirCarapace : public Tir
{
public:
	int		dx;
	bool	rebond;

	TirCarapace();

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
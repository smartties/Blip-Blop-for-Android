
#ifndef _TirBBLF_
#define _TirBBLF_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "joueur.h"
#include "tir_bb.h"


class TirBBLF : public TirBB
{
public:
	int		type;
	int		dx;
	int		latence;
	bool	fini;
	int		speed;
	int		deg;

	virtual void setDir(int d);

	inline virtual int degats() const
	{
		return deg;
	};

	inline virtual int enflame() const
	{
		return 2;
	};

	virtual void update();

	virtual void aTouche(int pts);
};

#endif

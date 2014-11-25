/******************************************************************
*
*
*		-----------------------
*		    TirMarioFireball.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 13 Decembre 2000
*
*
*
******************************************************************/

#ifndef _TirSnorkybase_
#define _TirSnorkybase_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"


#define DELAY_ACCELERATION 8

//-----------------------------------------------------------------------------
//		Définition de la classe TirMarioFireball
//-----------------------------------------------------------------------------

class TirMarioFireball : public Tir
{
public:
	int speed_etape;
	int		dx;

	TirMarioFireball(int vx);

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

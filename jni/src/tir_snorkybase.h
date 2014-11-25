/******************************************************************
*
*
*		-----------------------
*		    TirSnorkyBase.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 12 Decembre 2000
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


#define DELAY_ACCELERATION 20

//-----------------------------------------------------------------------------
//		Définition de la classe Tir
//-----------------------------------------------------------------------------

class TirSnorkybase : public Tir
{
public:
	int oscilation_etape;
	int speed_etape;
	int		dx;


	TirSnorkybase(int vx);

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

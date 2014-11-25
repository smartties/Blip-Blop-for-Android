/******************************************************************
*
*
*		---------------------------------
*		    TirTornade.h
*		---------------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 22 Decembre 2000
*
*
*
******************************************************************/

#ifndef _TirTornade_
#define _TirTornade_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"


#define SPEED_MAX				7
#define TORNADE_ACCELERATION    10
#define TOUR_MAX				1
#define LATENCE_TORNADE			21


//-----------------------------------------------------------------------------
//		Définition de la classe TirTornade
//-----------------------------------------------------------------------------

class TirTornade : public Tir
{
public:

	int dx;
	int etape_speed;
	int nb_tour;

	TirTornade(int vx);

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
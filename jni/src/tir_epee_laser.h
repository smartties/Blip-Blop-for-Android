/******************************************************************
*
*
*		----------------
*		   TirEpeeLaser.h
*		----------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _TirEpeeLaser_
#define _TirEpeeLaser_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"

//-----------------------------------------------------------------------------
//		Définition de la classe Tir
//-----------------------------------------------------------------------------

class TirEpeeLaser : public Tir
{
public:
	Sprite *	cible;
	Sprite *	lanceur;
	bool		isdead;
	bool		retour;
	int			dx;
	int			duree_vie;
	int			accel;

	TirEpeeLaser();
	virtual ~TirEpeeLaser();

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
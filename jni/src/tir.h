/******************************************************************
*
*
*		----------------
*		     Tir.h
*		----------------
*
*		Pour les tirs de Blip et ceux des ennemis
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _Tir_
#define _Tir_

#ifndef SENS
#define SENS_GAUCHE		0
#define SENS_DROITE		1
#endif

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "sprite.h"

//-----------------------------------------------------------------------------
//		Définition de la classe Tir
//-----------------------------------------------------------------------------

class Tir : public Sprite
{
public:

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

	virtual void aTue()
	{
	};

	virtual int getGiclureDir() const
	{
		return dir / 2;
	};

	inline virtual void aTouche()
	{
		a_detruire = true;
		col_on = false;
	};

	inline virtual void aTouche(int pts)
	{
		a_detruire = true;
		col_on = false;
	};

	virtual ~Tir()
	{
	};
};

#endif

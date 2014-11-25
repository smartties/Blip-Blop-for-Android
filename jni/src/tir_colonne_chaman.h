/******************************************************************
*
*
*		----------------
*		   TirColonneChaman.h
*		----------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _TirColonneChaman_
#define _TirColonneChaman_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"

//-----------------------------------------------------------------------------
//		Définition de la classe Tir
//-----------------------------------------------------------------------------

class TirColonneChaman : public Tir
{
public:
	int		duree_vie;
	int		etat; // 0:cree - 1:normal - 2:detruit

	TirColonneChaman();

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
	virtual void deplace();

};

#endif

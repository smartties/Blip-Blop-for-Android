/******************************************************************
*
*
*		--------------------
*		    EnnemiSmurf.h
*		--------------------
*
*		Le schtroumpf de base!
*
*
*		Prosper / LOADED -   V 0.1 - 3 Aout 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSmurf_
#define _EnnemiSmurf_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSmurf
//-----------------------------------------------------------------------------

class EnnemiSmurf : public Ennemi
{
public:
	int			wait_for_jump;
	int			jump_delay;
	int			dy_saut ;
	int			speed ;

	EnnemiSmurf();

	virtual void update();
	virtual void onAvance();
	virtual void onSaute();
	virtual void onMeure();
	virtual void onCarbonise();

	virtual void estTouche(Tir * tir);
};

#endif
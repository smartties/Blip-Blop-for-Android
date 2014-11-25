/******************************************************************
*
*
*		-----------------------
*		    EnnemiSnorkyBase2.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 14 Decembre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSnorkyBase2_
#define _EnnemiSnorkyBase2_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define SNORKY_BASE_SPEED		2

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSnorkyBase1
//-----------------------------------------------------------------------------

class EnnemiSnorkyBase2 : public Ennemi
{
public:

	int wait_for_shoot;
	int shoot_delay;
	int y_cible;
	int x_cible;

	EnnemiSnorkyBase2();

	virtual void update();
	virtual void onAvance();
	virtual void onTombe();
	virtual void onMeure();
	virtual void onTire();
	virtual void onCarbonise();

	virtual void estTouche(Tir * tir);
};

#endif
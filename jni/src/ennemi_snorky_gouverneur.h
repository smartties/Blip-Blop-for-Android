/******************************************************************
*
*
*		-----------------------
*		    EnnemiSnorkyGouverneur.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 15 Decembre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSnorkyGouverneur_
#define _EnnemiSnorkyGouverneur_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define GOUVERNEUR_SPEED		1

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSnorkyBase1
//-----------------------------------------------------------------------------

class EnnemiSnorkyGouverneur : public Ennemi
{
public:

	int nb_tir;
	int wait_for_shoot;
	int shoot_delay;

	EnnemiSnorkyGouverneur();

	virtual void update();
	virtual void onAvance();
	virtual void onTombe();
	virtual void onMeure();
	virtual void onTire();
	virtual void onCarbonise();

	virtual void estTouche(Tir * tir);
};

#endif
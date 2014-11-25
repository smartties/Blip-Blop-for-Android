/******************************************************************
*
*
*		-----------------------
*		    EnnemiSnorkInBlack.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 10 Avril 2001
*
*
*
******************************************************************/

#ifndef _EnnemiSnorkInBlack_
#define _EnnemiSnorkInBlack_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define SNORK_IN_BLACK_SPEED		2
#define SNORK_IN_BLACK_MAX_TIR		6

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSnorkyBase1
//-----------------------------------------------------------------------------

class EnnemiSnorkInBlack : public Ennemi
{
private:
	int x_cible;
	int y_cible;
	int nb_tir;

public:

	int wait_for_shoot;
	int shoot_delay;

	EnnemiSnorkInBlack();

	virtual void update();
	virtual void onAvance();
	virtual void onTombe();
	virtual void onMeure();
	virtual void onTire();
	virtual void onCarbonise();

	virtual void estTouche(Tir * tir);
};

#endif
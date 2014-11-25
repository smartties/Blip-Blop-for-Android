/******************************************************************
*
*
*		-----------------------
*		    EnnemiSnorkyMage.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 15 Decembre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSnorkyMage_
#define _EnnemiSnorkyMage_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define SNORKY_MAGE_SPEED		1

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSnorkyBase1
//-----------------------------------------------------------------------------

class EnnemiSnorkyMage : public Ennemi
{
public:

	int wait_for_shoot;
	int shoot_delay;
	int oscilation_etape;
	int concentration;

	EnnemiSnorkyMage();

	virtual void update();
	virtual void onAvance();
	virtual void onTombe();
	virtual void onMeure();
	virtual void onTire();
	virtual void onCarbonise();

	virtual void estTouche(Tir * tir);
};

#endif
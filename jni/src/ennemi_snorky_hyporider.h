/******************************************************************
*
*
*		-----------------------
*		    EnnemiSnorkyHyporider.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 18 Decembre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSnorkyHyporider_
#define _EnnemiSnorkyHyporider_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define HYPORIDER_SPEED		1
#define HYPORIDER_CHARGE_SPEED   8

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSnorkyBase1
//-----------------------------------------------------------------------------

class EnnemiSnorkyHyporider : public Ennemi
{
public:

	int wait_for_charge;
	int charge_delay;
	int nageoire;
	int attack_etape;

	EnnemiSnorkyHyporider();

	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onCharge();
	virtual void affiche();
	virtual void onCarbonise();

	virtual void estTouche(Tir * tir);
};

#endif
/******************************************************************
*
*
*		-----------------------
*		    EnnemiToad.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.9 - 12 Decembre 2000
*
*
*
******************************************************************/


#ifndef _EnnemiToad_
#define _EnnemiToad_

#include "enemy.h"

#define TOAD_SPEED 3
#define TOAD_CHARGE_SPEED 7

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiToad
//----------------------------------------------------------------------------

class EnnemiToad : public Ennemi
{
private:
	int speed;    //vitesse courante
	int etape_speed; //delai d'acceleration
	//static int toad_speed;    //vitesse maximum
	int charge_delay;
	int wait_for_charge;
	int charge_etape;
	int hokuto;

public:
	EnnemiToad();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onSaute();
	//virtual void onTombe();
	virtual void onCharge();
	virtual void onCarbonise();
	virtual void estTouche(Tir * tir);
};

#endif
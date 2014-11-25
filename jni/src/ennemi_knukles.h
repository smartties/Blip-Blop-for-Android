/******************************************************************
*
*
*		-----------------------
*		    EnnemiKnuckles.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.5 - 12 Decembre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiKnukles_
#define _EnnemiKnukles_

#include "enemy.h"

#define KNUKLES_SPEED 3
#define KNUKLES_CHARGE_SPEED 6
#define KNUKLES_JUMP_SPEED 12
#define KNUKLES_GRAVITE_MAX 7


//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiKnukles
//----------------------------------------------------------------------------

class EnnemiKnukles : public Ennemi
{
private:
	int speed;    //vitesse courante
	int etape_speed; //delai d'acceleration
	int charge_delay;
	int wait_for_charge;

public:
	EnnemiKnukles();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onTombe();
	virtual void onCarbonise();
	virtual void onCharge();
	virtual void onSaute();
	virtual void estTouche(Tir * tir);
	virtual void tombe();
};

#endif
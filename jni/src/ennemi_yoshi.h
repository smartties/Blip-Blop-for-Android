#ifndef _EnnemiYoshi_
#define _EnnemiYoshi_
/******************************************************************
*
*
*		-----------------------
*		    EnnemiYoshi.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.9 - 12 Decembre 2000
*
*
*
******************************************************************/


//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"


#define YOSHI_SPEED 3

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiYoshi
//----------------------------------------------------------------------------

class EnnemiYoshi : public Ennemi
{
private:
	bool attack; //type d'attaque false=carapace, true=contact(langue)
	int attack_delay;
	int wait_for_attack;
public:

	EnnemiYoshi();

	virtual void update();
	virtual void onAvance();
	virtual void onTombe();
	virtual void onMeure();
	virtual void onAttaque();
	virtual void onTire();
	virtual void onCarbonise();

	virtual void estTouche(Tir * tir);
};

#endif
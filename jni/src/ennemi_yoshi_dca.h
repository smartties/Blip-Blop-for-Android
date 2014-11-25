/******************************************************************
*
*
*		-----------------------
*		    EnnemiYoshiDCA.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.9 - 12 Decembre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiYoshiDCA_
#define _EnnemiYoshiDCA_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"


//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiYoshiDCA
//----------------------------------------------------------------------------

class EnnemiYoshiDCA : public Ennemi
{
private:
	int attack_delay;
	int wait_for_attack;
public:

	EnnemiYoshiDCA();

	virtual void update();
	virtual void onAvance();
	//virtual void onTombe();
	virtual void onMeure();
	//virtual void onAttaque();
	virtual void onTire();
	virtual void onCarbonise();

	virtual void estTouche(Tir * tir);
};

#endif
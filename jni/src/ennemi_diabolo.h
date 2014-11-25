/******************************************************************
*
*
*		-----------------------
*		    EnnemiDiabolo.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 20 Decembre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiDiabolo_
#define _EnnemiDiabolo_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"


#define DIABOLO_KICK_SPEED		8
#define LATENCE_DIABOLO_GRAVITE 5
#define DIABOLO_GRAVITE_MAX     8

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiDiabolo
//-----------------------------------------------------------------------------

class EnnemiDiabolo : public Ennemi
{
public:

	int wait_for_attack;
	int attack_delay;
	int dx;
	int attack_type;

	EnnemiDiabolo();

	virtual void update();
	virtual void onAvance();
	virtual void onTombe();
	virtual void onMeure();
	virtual void onAttack();
	virtual void onCoupdelatte();
	virtual void onTornade();
	virtual void onCoupdegenou();
	virtual void onCarbonise();
	virtual void tombe_diabolo();
	virtual void colFromPic();

	virtual void estTouche(Tir * tir);
};

#endif
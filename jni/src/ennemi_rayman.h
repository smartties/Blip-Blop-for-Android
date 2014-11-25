/******************************************************************
*
*
*		-----------------------
*		    EnnemiRayman.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 06 Decembre 2000
*
*
*
******************************************************************/


#ifndef _EnnemiRayman_
#define _EnnemiRayman_

#include "enemy.h"
#include "tir_rayman_poing.h"


#define RAYMAN_SPEED			3
#define RAYMAN_CRITICAL_SPEED   6
#define RAYMAN_POING1_SPEED		7
#define RAYMAN_POING2_SPEED		10
#define PV_SOUS_CRITIQUE		10000
#define PV_CRITIQUE             5000
#define PV_SUR_CRITIQUE			1000

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiRayman
//----------------------------------------------------------------------------

class EnnemiRayman : public Ennemi
{
private:

	int attack_delay;
	int wait_for_attack;
	int attack_etape;
	int x_cible;
	int range_poing;
	int poing1;
	int poing2;
	int pieds;
	int dorkemon;

	TirRaymanpoing *    tir_poing;

public:
	EnnemiRayman();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onTombe();
	virtual void onTire();
	virtual void estTouche(Tir * tir);
};

#endif
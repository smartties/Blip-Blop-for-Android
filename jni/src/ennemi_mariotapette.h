/******************************************************************
*
*
*		-----------------------
*		    EnnemiMariotapette.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.9 - 12 Decembre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiMariotapette_
#define _EnnemiMariotapette_

#include "enemy.h"

#define MARIO_SPEED				5
#define MARIO_CHARGE_SPEED		7
#define LATENCE_MARIO_GRAVITE	12
#define NABO_TRANSFORMATION		300
#define MARIO_ENDURANCE			80
#define MULTIPLICATEUR_RECUL_SOL		20
#define MULTIPLACATEUR_VITESSE_AU_SOL	100
#define MULTIPLICATEUR_RECUL_AERIEN		15
#define MULTIPLICATEUR_VITESSE_AERIEN	80

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiMarioTapette
//----------------------------------------------------------------------------

class EnnemiMariotapette : public Ennemi
{
private:
	int aide_luigi;
	int speed;    //vitesse courante
	int etape_speed; //delai d'acceleration

	int attack_delay;
	int wait_for_attack;
	int attack_etape;
	int nabo_delay;

	int nabo;
	int encaissement;

public:
	EnnemiMariotapette();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onSaute();
	virtual void onCharge();
	virtual void onCarbonise();
	virtual void tombe_mario();
	virtual void estTouche(Tir * tir);
};

#endif
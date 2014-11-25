/******************************************************************
*
*
*		-----------------------
*		    EnnemiTails.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.9 - 12 Decembre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiTails_
#define _EnnemiTails_

#include "enemy.h"

#define TAILS_SPEED 3
#define TAILS_FLY_SPEED 6

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiTails
//----------------------------------------------------------------------------

class EnnemiTails : public Ennemi
{
private:
	int speed;    //vitesse courante
	int etape_speed; //delai d'acceleration
	int fly_delay;
	int wait_for_fly;
	int x_cible;
	int y_cible;
	bool attack;      //attaque ou se met a la bonne hauteur
	bool fly;
	int direction;

public:
	EnnemiTails();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onTombe();
	virtual void onVolle();
	virtual void onCarbonise();
	virtual void estTouche(Tir * tir);
};

#endif
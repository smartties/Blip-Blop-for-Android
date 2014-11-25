
#ifndef _EnnemiSonic_
#define _EnnemiSonic_

#include "enemy.h"

#define SONIC_SPEED 7
#define SONIC_CHARGE_SPEED 8

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiToad
//----------------------------------------------------------------------------

/******************************************************************
*
*
*		-----------------------
*		    EnnemiSonic.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.9 - 12 Decembre 2000
*
*
*
******************************************************************/

class EnnemiSonic : public Ennemi
{
private:
	int speed;    //vitesse courante
	int etape_speed; //delai d'acceleration
	//static int toad_speed;    //vitesse maximum
	int attack_delay;
	int wait_for_attack;
	int attack_phase;
	int attack_type;
	int x_cible;
	int y_cible;
	int ss_etape_attack;
	int etape_attack;
	int nb_tir;
	int vie_sous_critique;
	int vie_critique;
	int vie_sur_critique;
	int ring;
	int wait_sang_tombe;

public:
	EnnemiSonic();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onSaute();
	//virtual void onTombe();
	virtual void onCharge();
	virtual void onAttackhorizontal();
	virtual void onAttackvertical();
	virtual void onAttackepine();
	virtual void onAttackeclair();
	virtual void onBalancering();
	virtual void balance_epines();
	virtual void onCarbonise();
	virtual void estTouche(Tir * tir);
};

#endif
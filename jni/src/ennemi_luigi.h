/******************************************************************
*
*
*		-----------------------
*		    EnnemiLuigi.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.7 - 27 Decembre 2000
*
*
*
******************************************************************/


#ifndef _EnnemiLuigi_
#define _EnnemiLuigi_

#include "enemy.h"

#define LUIGI_SPEED 6
//#define LUIGI_CHARGE_SPEED 7
#define LATENCE_LUIGI_GRAVITE 12
#define EXPLOSE_DELAY		180
#define NOMBRE_GICLURES     90

#define MULTIPLICATEUR_RECUL_SOL		20
#define MULTIPLACATEUR_VITESSE_AU_SOL	100
#define MULTIPLICATEUR_RECUL_AERIEN		15
#define MULTIPLICATEUR_VITESSE_AERIEN	80

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiLuigi
//----------------------------------------------------------------------------

class EnnemiLuigi : public Ennemi
{
private:
	int speed;    //vitesse courante
	int etape_speed; //delai d'acceleration

	int attack_delay;
	int wait_for_attack;
	int attack_etape;
	int attack_type;
	int ss_etape_attack;
	int etape_attack;
	int nb_tir;
	int encaissement;

	//int attaque_speciale;

public:
	EnnemiLuigi();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onSaute();
	//virtual void onCharge();
	virtual void onAttack();
	virtual void onCarbonise();
	virtual void tombe_luigi();
	virtual void estTouche(Tir * tir);
};

#endif
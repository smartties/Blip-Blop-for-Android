#ifndef _EnnemiMarioHologramme_
#define _EnnemiMarioHologramme_

#include "enemy.h"
/******************************************************************
*
*
*		------------------------------
*		    EnnemiMarioHologramme.h
*		------------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 27 Decembre 2000
*
*
*
******************************************************************/

#define MARIO_SPEED 5
#define LATENCE_MARIO_GRAVITE 12
#define NB_CLIGNO 4

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiMarioHologramme
//----------------------------------------------------------------------------

class EnnemiMarioHologramme : public Ennemi
{
private:
	int speed;    //vitesse courante
	int etape_speed; //delai d'acceleration
	int fireball;     //boule de feu dans les mains ou non
	int wait_for_cligno;
	int cligno_delay;
	int decalage_cligno;


	int attack_delay;
	int wait_for_attack;
	int attack_etape;
	int attack_type;
	int attack_phase;
	int x_cible;
	int y_cible;

public:
	EnnemiMarioHologramme();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onSaute();
	virtual void onCharge();
	virtual void onCarbonise();
	virtual void onTire();
	virtual void onTireverticale();
	virtual void tombe_mario();
	virtual inline void boule_de_feu();
	virtual void affiche();
	virtual void estTouche(Tir * tir);
};

#endif
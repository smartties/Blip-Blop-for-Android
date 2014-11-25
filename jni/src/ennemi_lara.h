/******************************************************************
*
*
*		-----------------------
*		    EnnemiLara.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.3 - 15 Fevrier 2001
*
*
*
******************************************************************/

#ifndef _EnnemiLara_
#define _EnnemiLara_

#include "enemy.h"

#define LARA_TIR_SPEED  10
#define ATTACK_DELAY    10

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiLara
//----------------------------------------------------------------------------

class EnnemiLara : public Ennemi
{
private:

	int numero_image_buste;
	int attack_delay;
	int wait_for_attack;
	int attack_etape;
	int attack_ss_etape;
	int attack_type;
	int attack_phase;
	int nb_pluie;
	int x_cible;
	int y_cible;
	int pics;
	int tete_rayman;

public:

	//methodes "habituelles"
	EnnemiLara();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onTire();


	virtual void affiche();
	virtual void estTouche(Tir * tir);
};

#endif
#ifndef _EnnemiMario_
#define _EnnemiMario_

#include "enemy.h"
/******************************************************************
*
*
*		-----------------------
*		    EnnemiMario.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.3 - 3 Janvier 2001
*
*
*
******************************************************************/

#define MARIO_SPEED					 5
#define MARIO_CHARGE_SPEED			 7
#define LATENCE_MARIO_GRAVITE		12
#define MARIO_PV_SOUS_CRITIQUE   17500
#define MARIO_PV_CRITIQUE        11500
#define MARIO_PV_SUR_CRITIQUE     8500

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiMario
//----------------------------------------------------------------------------

class EnnemiMario : public Ennemi
{
private:
	int speed;    //vitesse courante
	int etape_speed; //delai d'acceleration
	int fireball;     //boule de feu dans les mains ou non
	int hologramme;


	int attack_delay;
	int wait_for_attack;
	int attack_etape;
	int attack_ss_etape;
	int attack_type;
	int attack_phase;
	int nb_pluie;
	int x_cible;
	int y_cible;

public:

	//methodes "habituelles"
	EnnemiMario();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onSaute();
	virtual void onCharge();
	virtual void onCarbonise();
	virtual void tombe_mario();

	//tirs "standards"
	virtual void onTirehorizontale();
	virtual void onTireverticale();
	virtual void onTirecross();

	//rafales horizontales
	virtual void onRafalehorizontale();
	virtual void onRafalehorizontaledouble();
	virtual void onRafalehorizontaleconstante();
	virtual void onRafalehorizontalechercheuse();

	//rafales verticales
	virtual void onRafaleverticale();
	virtual void onRafaleverticaleinverser();
	virtual void onRafaleverticaledouble();
	virtual void onRafaleverticalechercheuse();
	virtual void onRafaleverticaleconstante();
	virtual void onPluiedefeu();

	//rafales des 2 types en meme temps
	virtual void onRafaleberserker();
	virtual void onRafalecrosschercheuse();
	virtual void onRafalecross();

	//balance des boules de feu pour eviter de recopier ca partout(horizontale seulement...)
	virtual inline void boule_de_feu(int vitesse);

	virtual void affiche();
	virtual void estTouche(Tir * tir);
};

#endif
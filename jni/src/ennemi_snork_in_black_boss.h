/******************************************************************
*
*
*		-----------------------------
*		    EnnemiSnorkInBlackBoss.h
*		-----------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 23 Avril 2001
*
*
*
******************************************************************/

#ifndef _EnnemiSnorkInBlackBoss_
#define _EnnemiSnorkInBlackBoss_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

//#define SNORK_IN_BLACK_MAX_TIR		6
#define tolerance		5

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSnorkyInBlackBoss
//-----------------------------------------------------------------------------

class EnnemiSnorkInBlackBoss : public Ennemi
{
private:
	int nb_tir;
	int position;
	int type_attack;
	int dx;
	bool attack;

	int x_shark;
	int y_shark;
	bool shark;
	bool saut;

public:

	EnnemiSnorkInBlackBoss();

	virtual void update();
	virtual void onAvance();
	virtual void onTombe();
	virtual void onMeure();
	virtual void onTire();
	virtual void affiche();


	virtual void estTouche(Tir * tir);
};

#endif
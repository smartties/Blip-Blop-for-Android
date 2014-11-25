/******************************************************************
*
*
*		---------------------------
*		    FondBattlecruiser.h
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/

#include "sprite.h"

#ifndef _FondBattlecruiser_
#define _FondBattlecruiser_

#define TIR_SPEED  2

class FondBattlecruiser : public Sprite
{
public:
	int x_adversaire;
	int y_adversaire;
	int attack_etape;
	int feu_etape;
	int feu_ss_etape;

	FondBattlecruiser();

	virtual void update();
	virtual void affiche();
};

#endif
/******************************************************************
*
*
*		-----------------------
*		    FondSnorkSas.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 18 Janvier 2001
*
*
*
******************************************************************/


#ifndef _FondSnorkSas_
#define _FondSnorkSas_

#include "sprite.h"

class FondSnorkSas1 : public Sprite
{
private:
	int nb_joueur;

public:

	static int etat;

	FondSnorkSas1();
	virtual void update();
	virtual void affiche();
};

class FondSnorkSas2 : public Sprite
{
public:
	FondSnorkSas2();
	virtual void update();
	virtual void affiche();
};

#endif
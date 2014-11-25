/******************************************************************
*
*
*		---------------------------
*		    FondBombe.h
*		---------------------------
*
*		Detonator... Boum
*
*		Mephisto / LOADED -   V 0.1 - 17 Janvier 2001
*
*
*
******************************************************************/

#include "sprite.h"

#ifndef _FondBombe_
#define _FondBombe_


class FondBombe : public Sprite
{
private:
	int etape_compteur;

	int seconde;
	int centieme;

	int armed;

	int etape_warning;
	int ss_etape_warning;

	int etape_nuke;
	int ss_etape_nuke;
public:

	FondBombe();

	virtual void update();
	virtual void affiche();
};

#endif

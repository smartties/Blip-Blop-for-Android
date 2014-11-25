/******************************************************************
*
*
*		---------------------------
*		    FondPokeCaisseTombante.h
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 21 Janvier 2001
*
*
*
******************************************************************/


#ifndef _FondPokeCaisseTombante_
#define _FondPokeCaisseTombante_

#include "sprite.h"

#define UNLOCK_DELAY   32


class FondPokeCaisseTombante : public Sprite
{
public:

	FondPokeCaisseTombante();
	virtual void update();
	virtual void affiche();
};

#endif
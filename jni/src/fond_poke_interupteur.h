/******************************************************************
*
*
*		---------------------------
*		    FondPokeInterupteur.h
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 21 Janvier 2001
*
*
*
******************************************************************/

#ifndef _FondPokeInterupteur_
#define _FondPokeInterupteur_



class FondPokeInterupteur : public Sprite
{
private:

	bool etat;
	bool wait_msg;
	bool ascenc_msg;
	bool bravo;

public:
	FondPokeInterupteur();
	virtual void update();

};

#endif
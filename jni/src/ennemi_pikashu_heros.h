/******************************************************************
*
*
*		------------------------
*		  EnnemiPikachuHeros.h
*		------------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 10 Janvier 2001
*
*
*
******************************************************************/



#ifndef _EnnemiPikachuHeros_
#define _EnnemiPikachuHeros_

#include "enemy.h"

class EnnemiPikachuHeros : public Ennemi
{
private:
	int dx;
	int dorkeball;

public:
	EnnemiPikachuHeros();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void estTouche(Tir * tir);
};

#endif
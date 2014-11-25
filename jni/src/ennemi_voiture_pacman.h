/******************************************************************
*
*
*		-----------------------
*		    EnnemiVoiturepacman.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 4 Mars 2001
*
*
*
******************************************************************/

#ifndef _EnnemiVoiturePacman_
#define _EnnemiVoiturePacman_

#include "enemy.h"


#define LATENCE_GRAVITE_VOITURE		5
#define GRAVITE_MAX_VOITURE			8

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiVoiturePacman
//----------------------------------------------------------------------------

class EnnemiVoiturePacman : public Ennemi
{
private:
	int invoc_pacman;
	int wait_end;

public:
	EnnemiVoiturePacman();
	virtual void update();
	virtual int degats();
	virtual void tombeVoiture();
	virtual void affiche();
	virtual void estTouche(Tir * tir);
};

#endif
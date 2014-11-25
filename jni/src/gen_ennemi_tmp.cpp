/******************************************************************
*
*
*		-----------------
*		  GenEnnemi.cpp
*		-----------------
*
*		Classe Générateur ennemi
*
*
*		Prosper / LOADED -   5 Aout 2000
*
*
*
******************************************************************/


#include "gen_ennemi_tmp.h"
#include "event_ennemi.h"

#ifndef SENS_GAUCHE
#define SENS_GAUCHE		0
#define SENS_DROITE		1
#endif


void GenEnnemiTMP::update()
{
	if (game_flag[FLAG_GEN_OFF] != 0)
		return;

	t += 1;
	t %= periode;

	if (t == 0) {
		EventEnnemi	e;

		e.id_ennemi = id_ennemi;
		e.sens = sens;
		e.x = x;
		e.y = y;
		e.doEvent();

		capacite -= 1;

		if (capacite <= 0)
			a_detruire = true;
	}

	if ((sens == SENS_DROITE && x < offset - 200) || (sens == SENS_GAUCHE && x < offset + 690))
		a_detruire = true;
}

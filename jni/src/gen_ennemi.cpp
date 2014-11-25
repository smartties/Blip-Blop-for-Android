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

#include "sprite.h"
#include "gen_ennemi.h"
#include "event_ennemi.h"

#ifndef SENS_GAUCHE
#define SENS_GAUCHE		0
#define SENS_DROITE		1
#endif

GenEnnemi::GenEnnemi() : t(0), a_detruire(false)
{
}

void GenEnnemi::update()
{
	if (game_flag[FLAG_GEN_OFF] != 0)
		return;

	t += 1;
	t %= periode;

	if (t == 0) {
		Sprite *	s;
		bool		ok = true;

		list_joueurs.start();

		while (!list_joueurs.fin() && ok) {
			s = (Sprite*) list_joueurs.info();

			ok = (s->x < x - 100 || s->x > x + 100 || s->y < y - 100 || s->y > y + 100);

			list_joueurs.suivant();
		}

		if (ok) {
			EventEnnemi	e;

			e.id_ennemi = id_ennemi;
			e.sens = sens;
			e.x = x;
			e.y = y;
			e.doEvent();
		}

		capacite -= 1;

		if (capacite <= 0)
			a_detruire = true;
	}

	if (x < offset - 100)
		a_detruire = true;
}

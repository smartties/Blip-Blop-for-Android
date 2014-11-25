/******************************************************************
*
*
*		-----------------
*		  GenBonus.cpp
*		-----------------
*
*
*
*		Prosper / LOADED -   5 Aout 2000
*
*
*
******************************************************************/

#include <cstdlib>
#include "globals.h"
#include "gen_bonus.h"
#include "make_bonus.h"

GenBonus::GenBonus() : t(0), a_detruire(false)
{
}

void GenBonus::update()
{
	if (list_bonus.taille() < 3) {
		t += 1;
		t %= periode;

		if (t == 0) {
			MakeBonus(offset + 320 - 200 + rand() % 400, -50);
		}

		if (offset > x + 500)
			a_detruire = true;
	}
}



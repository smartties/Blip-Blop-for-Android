/******************************************************************
*
*
*		----------------
*		  BonusFusil.h
*		----------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _BonusFusil_
#define _BonusFusil_

#include "bonus.h"

class BonusFusil : public Bonus
{
public:

	BonusFusil()
	{
		pic = pbk_misc[9];
		col_on = true;
	};

	virtual void estPris(Couille * c)
	{
		if ((c->id_arme == ID_LF && c->ammo >= 100) || (c->id_arme == ID_LASER && c->ammo >= 100))
			return;

		sbk_misc.play(0);

		if (c->id_arme == ID_FUSIL) {
			c->ammo += 20;

			if (c->ammo > 40)
				c->ammo = 40;
		} else {
			c->id_arme = ID_FUSIL;
			c->ammo = 20;
			c->latence_arme = 3;
			c->nb_etape_arme = 15;
			c->cadence_arme = 45;
			c->poid_arme = 1;

			c->etape_arme = 0;
			c->ss_etape_arme = 0;
			c->etape_recul = 0;
			c->tire = false;
		}

		Bonus::estPris(c);
	};
};

#endif
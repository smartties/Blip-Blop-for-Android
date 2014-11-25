/******************************************************************
*
*
*		----------------
*		    Bonus.h
*		----------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _BonusPM_
#define _BonusPM_

#include "bonus.h"

class BonusPM : public Bonus
{
public:

	BonusPM()
	{
		pic = pbk_misc[8];
		col_on = true;
	};

	virtual void estPris(Couille * c)
	{
		if ((c->id_arme == ID_LF && c->ammo >= 100) || (c->id_arme == ID_LASER && c->ammo >= 100))
			return;

		sbk_misc.play(4);

		if (c->id_arme == ID_PM) {
			c->ammo += 200;

			if (c->ammo > 400)
				c->ammo = 400;
		} else {
			c->id_arme = ID_PM;
			c->ammo = 200;
			c->latence_arme = 3;
			c->nb_etape_arme = 5;
			c->cadence_arme = 5;
			c->poid_arme = 5;

			c->etape_arme = 0;
			c->ss_etape_arme = 0;
			c->etape_recul = 0;
			c->tire = false;
		}

		Bonus::estPris(c);
	};
};

#endif
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

#ifndef _BonusLF_
#define _BonusLF_

#include "bonus.h"

class BonusLF : public Bonus
{
public:

	BonusLF()
	{
		pic = pbk_misc[11];
		col_on = true;
	};

	virtual void estPris(Couille * c)
	{
		sbk_misc.play(2);

		if (c->id_arme == ID_LF) {
			c->ammo += 1000;

			if (c->ammo > 2000)
				c->ammo = 2000;
		} else {
			c->id_arme = ID_LF;
			c->ammo = 1000;
			c->latence_arme = 3;
			c->nb_etape_arme = 5;
			c->cadence_arme = 1;
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
/******************************************************************
*
*
*		----------------
*		  BonusLaser.h
*		----------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _BonusLaser_
#define _BonusLaser_

#include "bonus.h"

class BonusLaser : public Bonus
{
public:

	BonusLaser()
	{
		pic = pbk_misc[10];
		col_on = true;
	};

	virtual void estPris(Couille * c)
	{
		sbk_misc.play(3);

		if (c->id_arme == ID_LASER) {
			c->ammo += 750;

			if (c->ammo > 1500)
				c->ammo = 1500;
		} else {
			c->id_arme = ID_LASER;
			c->ammo = 750;
			c->latence_arme = 3;
			c->nb_etape_arme = 4;
			c->cadence_arme = 1;
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
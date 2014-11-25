/******************************************************************
*
*
*		---------------
*		  BonusBeer.h
*		---------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _BonusBeer_
#define _BonusBeer_

#include "bonus.h"

class BonusBeer : public Bonus
{
public:

	BonusBeer()
	{
		pic = pbk_misc[13];
		col_on = true;
	};

	virtual void estPris(Couille * c)
	{
		if (c->pv == 5)
			return;

		sbk_misc.play(5);

		c->pv += 2;

		if (c->pv > 5)
			c->pv = 5;

		Bonus::estPris(c);
	};
};

#endif
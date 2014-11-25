/******************************************************************
*
*
*		---------------------
*		  BonusInvincible.h
*		---------------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _BonusInvincible_
#define _BonusInvincible_

#include "bonus.h"

class BonusInvincible : public Bonus
{
public:

	BonusInvincible()
	{
		pic = pbk_misc[12];
		col_on = true;
	};

	virtual void estPris(Couille * c)
	{
		c->invincible = 550;

		Bonus::estPris(c);
	};
};

#endif



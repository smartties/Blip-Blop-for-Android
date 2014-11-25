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

#ifndef _Bonus_
#define _Bonus_

#include "sprite.h"
#include "couille.h"
#include "ben_maths.h"

#define DIST_BITONIO	25

class Bonus : public Sprite
{
public:

	int		phi;
	bool	local_phase;

	Bonus() : phi(0)
	{
	};

	virtual void estPris(Couille * c)
	{
		a_detruire = true;
		col_on = false;
	};

	virtual void update()
	{
		tombe();

		phi += 12;
		phi %= 360;

		etape += 1;
		etape %= 10;

		if (etape == 0)
			local_phase = !local_phase;

		if (x < offset - 50)
			a_detruire = true;

		y -= 15;
		colFromPic();
		y += 15;
	};

	virtual void affiche()
	{
		int		base;

		y -= 15;
		Sprite::affiche();

		if (local_phase)
			base = 0;
		else
			base = 4;

		int d = (8 * bSin[phi]) >> COSINUS;

		draw(x - DIST_BITONIO - d, y - DIST_BITONIO - d, pbk_misc[base + 3]);
		draw(x + DIST_BITONIO + d, y - DIST_BITONIO - d, pbk_misc[base + 2]);
		draw(x + DIST_BITONIO + d, y + DIST_BITONIO + d, pbk_misc[base]);
		draw(x - DIST_BITONIO - d, y + DIST_BITONIO + d, pbk_misc[base + 1]);

		y += 15;
	};

	virtual void colFromPic()
	{
		Sprite::colFromPic();

		x1 -= 10;
		y1 -= 10;
		x2 += 10;
		y2 += 10;
	};

};


#endif







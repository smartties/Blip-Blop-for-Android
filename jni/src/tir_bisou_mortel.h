
#ifndef _TirBisouMortel_
#define _TirBisouMortel_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir.h"

//-----------------------------------------------------------------------------
//		Définition de la classe Tir
//-----------------------------------------------------------------------------

class TirBisouMortel : public Tir
{
public:
	Sprite *	cible;
	int			dx;
	int			duree_vie;

	TirBisouMortel() : dx(0), duree_vie(235)
	{
	};

	virtual int degats() const
	{
		return 1;
	};

	virtual int enflame() const
	{
		return 0;
	};

	virtual void setDir(int d)
	{
		dir = d;
	};

	virtual void update()
	{
		static const int ACCEL = 1;

		ss_etape += 1;
		ss_etape %= 5;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 2;
		}

		if (dx > 0)
			dir = SENS_DROITE;
		else
			dir = SENS_GAUCHE;

		if (dir == SENS_DROITE)
			pic = pbk_ennemis[311 + etape];
		else
			pic = pbk_ennemis[313 + etape];


		x += dx / 13;
		y += dy / 13;

		duree_vie -= 1;

		if (duree_vie <= 0 || cible->a_detruire) {
			a_detruire = true;
			return;
		}

		int xc = cible->x;
		int yc = cible->y - 15;

		if (xc > x && dx < 36) dx += ACCEL;
		else if (dx > -36) dx -= ACCEL;

		if (yc > y && dy < 36) dy += ACCEL;
		else if (dy > -36) dy -= ACCEL;

		colFromPic();
		updateADetruire();
	};

};

#endif
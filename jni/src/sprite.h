/******************************************************************
*
*
*		----------------
*		    Sprite.h
*		----------------
*
*		La classe surpuissante!
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _SPRITE_
#define _SPRITE_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "picture.h"
#include "globals.h"

//-----------------------------------------------------------------------------
//		Définition de la classe Sprite
//-----------------------------------------------------------------------------

class Sprite
{
public:

	int			x;
	int			y;
	int			dy;
	int			etape;
	int			ss_etape;
	Picture *	pic;
	bool		a_detruire;
	int			dir;
	int			lat_grav;

	int			wait_bulle;

	int			x1;	// Pour les collisions
	int			y1;
	int			x2;
	int			y2;
	bool		col_on;

	Sprite();

	inline virtual int getX() const
	{
		return x;
	};
	inline virtual int getY() const
	{
		return y;
	};
	inline virtual int getEtape() const
	{
		return etape;
	};
	inline virtual Picture * getPic() const
	{
		return pic;
	};
	inline virtual bool aDetruire() const
	{
		return a_detruire;
	};

	inline virtual bool estSurMur() const   // (sanglant)
	{
		return mur_sanglant(x, y);
	}

	inline virtual int anime(const int * tab, int nb_etapes, int latence)
	{
		ss_etape += 1;
		ss_etape %= latence;

		if (ss_etape == 0)
			etape += 1;

		if (etape < 0)
			etape = 0;

		etape %= nb_etapes;
		return tab[etape];
	};

	inline virtual void affiche()
	{
		draw(x, y, pic);
	};

	inline virtual void updateADetruire()
	{
		if (x < offset - 250 || x > offset + 900 || y < -200 || y > 600)
			a_detruire = true;
	};

	virtual void update() = 0;

	virtual void tombe();
	virtual void tombe2();
	virtual void marche(int speed);
	virtual void colFromPic();
	virtual void noCol();

	inline virtual bool collision(const Sprite * s) const
	{
		if (!col_on || !s->col_on)
			return false;
		else
			return !((s->x2 < x1) || (s->x1 > x2) || (s->y2 < y1) || (s->y1 > y2));
	};

	virtual ~Sprite()
	{
	};

};

#endif
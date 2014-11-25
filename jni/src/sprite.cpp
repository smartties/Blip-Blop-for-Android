/******************************************************************
*
*
*		----------------
*		    Sprite.cpp
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

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "sprite.h"

//-----------------------------------------------------------------------------
//		Constructeur

Sprite::Sprite() : pic(NULL), dy(0), dir(0), a_detruire(false), etape(0), ss_etape(0),
	lat_grav(0), x(0), y(0), x1(-1000), y1(-1000), x2(-2000), y2(-2000), col_on(false), wait_bulle(0)
{
}

//-----------------------------------------------------------------------------
//		Tombor

void Sprite::tombe()
{
	lat_grav += 1;
	lat_grav %= LATENCE_GRAVITE;

	if (lat_grav == 0 && dy < GRAVITE_MAX)
		dy += 1;

	if (dy < 0 && mur_opaque(x, y + dy))
		dy = GRAVITE_MAX;

	int ny = plat(x, y + dy);

	if (ny != 0 && dy > 0)
		y = ny;
	else
		y += dy;
}

//-----------------------------------------------------------------------------
//		Tombor2 : n'arrête pas la chute (utile pour les sauts)

void Sprite::tombe2()
{
	lat_grav += 1;
	lat_grav %= LATENCE_GRAVITE;

	if (lat_grav == 0 && dy < GRAVITE_MAX)
		dy += 1;

	if (dy < 0 && mur_opaque(x, y + dy))
		dy = GRAVITE_MAX;

	int ny = plat(x, y + dy);

	if (ny != 0 && dy > 0 && plat(x, y) == 0)
		y = ny;
	else
		y += dy;
}

//-----------------------------------------------------------------------------
//		Marchor

void Sprite::marche(int ndx)
{
	x += ndx;

	int ny = plat(x, y);

	if (ny != 0) {
		y = ny;
	} else {
		ny = plat(x, y + 5);

		if (ny != 0) {
			y = ny;
		} else {
			ny = plat(x, y - 5);

			if (ny != 0)
				y = ny;
		}
	}
}

//-----------------------------------------------------------------------------
//		Collisor

void Sprite::colFromPic()
{
	if (pic == NULL) {
		col_on = false;
	} else {
		x1 = x - pic->xSpot();
		y1 = y - pic->ySpot();

		x2 = x1 + pic->xSize();
		y2 = y1 + pic->ySize();

		col_on = true;
	}
}


//-----------------------------------------------------------------------------
//		Evitor de collisor

void Sprite::noCol()
{
	col_on = false;
}


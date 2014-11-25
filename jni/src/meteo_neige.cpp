
#include "meteo_neige.h"
#include "ben_maths.h"

void MeteoNeige::update()
{
	// Update angle
	//
	phi += 3;
	phi %= 360;

	xbase -= 2;

	// Deplacement
	//
	x = xbase + ((xwide * bCos[phi]) >> COSINUS);
	y += dy;

	// Conditions de destructions/teleportation
	//
	if (y > -25  && y < -10 && mur_opaque(x, 0)) {
		a_detruire = true;
	} else if ((plat(x, y) != 0 && ((rand() % 6) == 0)) || mur_opaque(x, y)) {
		/*
				if ( y > 10)
					grave( x, y, pic);
		*/
		a_detruire = true;
	} else if (y > 500) {
		a_detruire = true;
	} else if (xbase < offset - 10) {
		if (!mur_opaque(offset + 640, 0))
			xbase += 660;
		else
			a_detruire = true;
	}
}
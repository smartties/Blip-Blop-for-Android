
#include "meteo_pluie.h"

void MeteoPluie::update()
{
	y += dy;

	if (x < offset || (y > -100  && mur_opaque(x, 0)) || mur_opaque(x, y) || y > 540)
		a_detruire = true;
}
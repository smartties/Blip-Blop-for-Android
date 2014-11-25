
#include "ben_maths.h"
#include "bulle.h"

Bulle::Bulle() : phi(0)
{
}

void Bulle::update()
{
	phi += dphi;
	phi %= 360;

	y += dy;

	x = xbase + ((10 * bCos[phi]) >> COSINUS);

	if (xbase < offset - 10 || y < -10 || mur_opaque(x, y))
		a_detruire = true;
}
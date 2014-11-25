
#include "vehivule_cigogne.h"


#include "vehicule_hypo.h"

static bool first;

VehiculeCigogne::VehiculeCigogne()
{
	pic = pbk_ennemis[66];
	hasBeenUsed = false;
	first = true;
};

void VehiculeCigogne::affiche()
{
	Sprite::affiche();
}

void VehiculeCigogne::updateUsed()
{
	static const int bas_ailes [] = { 0, 1, 2, 3, 2, 1 };
	static const int SPEED = 8;

	can_be_used = false;
	/*
		if ( offset < level_size-640)
			x += scroll_speed*2;

		if ( ctrl->gauche() && x > offset+40 && !mur_opaque( x-SPEED, y))
		{
			x -= SPEED;
		}

		if ( ctrl->droite() && x < offset+600 && !mur_opaque( x+SPEED, y))
		{
			x += SPEED;
		}

		if ( ctrl->haut() && y > 40 && !mur_opaque( x, y-SPEED))
		{
			y -= SPEED;
		}

		if ( ctrl->bas() && y < 440 && !mur_opaque( x, y+SPEED))
		{
			y += SPEED;
		}

		pic = pbk_niveau[anime( bas_ailes, 6, 4)];
	*/
	x += SPEED;

	joueur->dir = BBDIR_DROITE;
	joueur->dir_arme = BBDIR_DROITE;
	joueur->x = x;
	joueur->y = y - 20;

	if (x >= 1480) {
		if (first)
			joueur->y = y - 80;
		else
			joueur->y = y - 40;

		joueur->unlockVehicule();
		joueur = NULL;
		hasBeenUsed = true;
		first = false;
	}
}


void VehiculeCigogne::updateNotUsed()
{
	x += 8;
}

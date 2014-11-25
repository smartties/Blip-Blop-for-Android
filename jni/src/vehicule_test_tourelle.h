
#ifndef _VehiculeTestTourelle_
#define _VehiculeTestTourelle_

class VehiculeTestTourelle : public Vehicule
{
public:

	int		lat;

	VehiculeTestTourelle() : lat(0)
	{
		pic = pbk_ennemis[525];
	}

	virtual bool canFire()
	{
		return false;
	};

	virtual void updateNotUsed() {};

	virtual void updateUsed()
	{
		if (joueur->etat != ETAT_LOCKEDV || joueur->a_detruire) {
			joueur = NULL;
			return;
		}

		if (ctrl->gauche() && lat > -10) {
			lat--;

			if (lat <= -10 && dir > 0) {
				dir--;
				lat = 0;
			}
		}

		if (ctrl->droite() && lat < 10) {
			lat++;

			if (lat >= 10 && dir < 23) {
				dir++;
				lat = 0;
			}
		}

		pic = pbk_ennemis[525 + dir];

		if (ctrl->saut()) {
			joueur->unlockVehicule();
			joueur = NULL;
		}
	}
};

#endif
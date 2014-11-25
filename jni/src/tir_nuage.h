
#ifndef _TirNuage_
#define _TirNuage_

#include "tir.h"

class TirNuage : public Tir
{
public:
	int etat;
	int	etape_shoot;
	int delta_eclair;
	int eclair;
	int duree_vie;

	TirNuage();
	virtual void update();
	virtual void onCreation();
	virtual void onDestruction();
	virtual void onNormal();
	virtual void onTire();
	virtual void affiche();
};

#endif
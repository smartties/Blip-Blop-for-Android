
#ifndef _EnnemiBisouEtoile_
#define _EnnemiBisouEtoile_

#include "enemy.h"

class EnnemiBisouEtoile : public Ennemi
{
public:
	int		wait_shoot;
	int		etape_shoot;

	EnnemiBisouEtoile();
	virtual void onAvance();
	virtual void onTire();
	virtual void onMeureEntier();
	virtual void onMeureHaut();
	virtual void onMeureHautFin();
	virtual void onCarbonise();
	virtual void estTouche(Tir * tir);
	virtual void update();
};

#endif
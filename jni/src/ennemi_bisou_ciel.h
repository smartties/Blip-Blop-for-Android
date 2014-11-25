
#ifndef _EnnemiBisouCiel_
#define _EnnemiBisouCiel_

#include "enemy.h"

class EnnemiBisouCiel : public Ennemi
{
public:
	int		wait_for_pisser;

	EnnemiBisouCiel();
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
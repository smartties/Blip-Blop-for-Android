
#ifndef _EnnemiSmurfCostaud_
#define _EnnemiSmurfCostaud_

#include "enemy.h"

class EnnemiSmurfCostaud : public Ennemi
{
public:
	int	etape_shoot;
	int wait_shoot;
	int dx;
	int dypunch;

	EnnemiSmurfCostaud();

	virtual void update();
	virtual void onAvance();
	virtual void onTire();
	virtual void onTireHadoken();
	virtual void onTireDragonPunch();
	virtual void onTireHurricanKick();
	virtual void estTouche(Tir * tir);
	virtual void onCarbonise();
	virtual void onMeure();
};

#endif
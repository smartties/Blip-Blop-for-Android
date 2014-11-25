
#ifndef _EnnemiBisouZombi_
#define _EnnemiBisouZombi_

#include "enemy.h"

class EnnemiBisouZombi : public Ennemi
{
public:

	bool	my_phase;
	bool	my_phase2;
	int		etape2;

	EnnemiBisouZombi();
	virtual void onCoupe();
	virtual void onAvance();
	virtual void onTombe();
	virtual void onRampe();
	virtual void onMeure();
	virtual void onCarbonise();
	virtual void onCarboniseHaut();
	virtual void estTouche(Tir * tir);
	virtual void update();
};

#endif
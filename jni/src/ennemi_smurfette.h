
#ifndef _EnnemiSmurfette_
#define _EnnemiSmurfette_

#include "enemy.h"

class EnnemiSmurfette : public Ennemi
{
public:

	int	etape_shoot;
	int wait_shoot;

	EnnemiSmurfette();

	virtual void update();
	virtual void onAvance();
	virtual void onTire();
	virtual void estTouche(Tir * tir);
	virtual void onCarbonise();
	virtual void onMeure();
};

#endif
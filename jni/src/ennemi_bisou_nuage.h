
#ifndef _EnnemiBisouNuage_
#define _EnnemiBisouNuage_

#include "enemy.h"

class EnnemiBisouNuage : public Ennemi
{
public:
	int		wait_shoot;
	int		etape_shoot;

	EnnemiBisouNuage();
	virtual void onNormal();
	virtual void update();
	virtual void onMeureWait();
	virtual void onMeureTombe();
	virtual void onMeureFin();
};

#endif
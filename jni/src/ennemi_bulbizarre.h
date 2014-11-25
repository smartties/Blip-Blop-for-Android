
#ifndef _EnnemiBulbizarre_
#define _EnnemiBulbizarre_

#include "enemy.h"

class EnnemiBulbizarre : public Ennemi
{
public:
	EnnemiBulbizarre();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onCarbonise();
	virtual void estTouche(Tir * tir);
};

#endif
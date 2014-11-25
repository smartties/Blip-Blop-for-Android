
#ifndef _EnnemiBisouSIB_
#define _EnnemiBisouSIB_

#include "enemy.h"

class EnnemiBisouSIB : public Ennemi
{
public:

	int		encaisse;

	EnnemiBisouSIB();

	virtual void update();
	virtual void estTouche(Tir * tir);
};

#endif
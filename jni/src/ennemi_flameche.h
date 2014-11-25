
#ifndef _EnnemiFlameche_
#define _EnnemiFlameche_

#include "enemy.h"

class EnnemiFlameche : public Ennemi
{
public:
	EnnemiFlameche();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void estTouche(Tir * tir);
};

#endif

#ifndef _EnnemiPikachu_
#define _EnnemiPikachu_

#include "enemy.h"

class EnnemiPikachu : public Ennemi
{
public:
	EnnemiPikachu();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onCarbonise();
	virtual void estTouche(Tir * tir);
};

#endif
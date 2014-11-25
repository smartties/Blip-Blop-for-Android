
#ifndef _Vehicule_
#define _Vehicule_

#include "sprite.h"
#include "couille.h"
#include "controlor.h"

class Vehicule : public Sprite
{
public:

	bool	can_be_used;

	Couille *	joueur;
	Controlor *	ctrl;

	Vehicule();

	virtual void update();
	virtual Couille * scanne();

	virtual bool canFire() = 0;
	virtual bool canChangeDir() = 0;
	virtual void updateUsed() = 0;
	virtual void updateNotUsed() = 0;

};

#endif

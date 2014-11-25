
#ifndef _EnnemiCOM_
#define _EnnemiCOM_

#include "enemy.h"

class EnnemiCOM : public Ennemi
{
public:
	EnnemiCOM();
	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
};

#endif
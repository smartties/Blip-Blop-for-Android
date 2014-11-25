
#ifndef _EnnemiBisouAuto_
#define _EnnemiBisouAuto_

#include "enemy.h"

class EnnemiBisouAuto : public Ennemi
{
public:

	Sprite*	cible;
	int		dx;
	int		togo;
	bool	trick;

	EnnemiBisouAuto();
	virtual void onAvance();
	virtual void onMeure();
	virtual void update();
};

#endif
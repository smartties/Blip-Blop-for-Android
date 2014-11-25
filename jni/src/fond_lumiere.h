
#ifndef _FondLumiere_
#define _FondLumiere_

#include "sprite.h"

class FondLumiere : public Sprite
{
public:
	bool	allume;
	int		wait_for_cligno;
	int		delai_cligno;

	FondLumiere();

	virtual void update();
};

#endif
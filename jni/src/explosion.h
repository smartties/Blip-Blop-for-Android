
#ifndef _Explosion_
#define _Explosion_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "sprite.h"


class Explosion : public Sprite
{
public:
	int		type;
	bool	fini;
	int		speed;

	Explosion();
	virtual void update();
};

#endif

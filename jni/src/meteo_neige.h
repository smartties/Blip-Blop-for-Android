
#ifndef _MeteoNeige_
#define _MeteoNeige_

#include "sprite.h"

class MeteoNeige : public Sprite
{
public:
	int		xbase;
	int		phi;
	int		xwide;

	void update();
};

#endif

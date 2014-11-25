
#ifndef _PPlanTest_
#define _PPlanTest_

#include "sprite.h"

class PPlanTest : public Sprite
{
public:
	PPlanTest()
	{
		pic = pbk_niveau[2];
	};

	virtual void update()
	{
		if (x < offset - 300)
			a_detruire = true;
	};
};

#endif
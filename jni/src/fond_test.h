
#ifndef _FondTest_
#define _FondTest_

#include "sprite.h"

class FondTest : public Sprite
{
public:
	virtual void update()
	{
		if (phase)
			pic = pbk_niveau[0];
		else
			pic = pbk_niveau[1];

		if (x < offset - 100)
			a_detruire = true;
	};
};

#endif
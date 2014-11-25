
#ifndef _FondPokeFleche_
#define _FondPokeFleche_

#include "sprite.h"

class FondPokeFleche : public Sprite
{
public:
	virtual void update()
	{
		static const int anim_go [] = {42, 43, 44, 45, 46, 47, 46, 45, 44, 43, 42};

		/*ss_etape += 1;
		ss_etape %= 5;

		if ( ss_etape == 0)
		{
			etape += 1;
			etape %= 6;
		}*/

		pic = pbk_niveau[anime(anim_go, 11, 3)];
	};
};

#endif

#include "fond_worldmap.h"

const int anim_Worldmap [] = {13, 14, 13, 14, 13, 14, 15, 16, 17, 18, 19, 20, 19, 20, 19, 20, 21, 22, 23, 24, 25, 26, 25, 26, 25, 26, 25, 26, 26, 26, 26, 26, 26, 26, 26};


void FondWorldmap::update()
{
	pic = pbk_niveau[anime(anim_Worldmap, 35, 10)];
}
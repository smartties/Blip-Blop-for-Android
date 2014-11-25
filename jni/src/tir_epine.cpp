
//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_epine.h"
//#include "bendebug.h"

TirEpine::TirEpine(int n_pbk_ennemis, int vx, int vy)
{
	pic = pbk_ennemis[n_pbk_ennemis];
	dy = vy;
	dx = vx;
	traverse = false;
}


void TirEpine::update()
{
	x += dx;
	y += dy;

	if (x < offset - 100 || x > offset + 700 || y > 520 || y < -50 || (!traverse && mur_opaque(x, y)))
		a_detruire = true;

	colFromPic();
}

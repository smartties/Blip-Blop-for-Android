
//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_debouche_chiote.h"
//#include "bendebug.h"

TirDebouchechiote::TirDebouchechiote(int n_pbk_ennemis, int vx, int vy)
{
	pic = pbk_ennemis[n_pbk_ennemis];
	dy = vy;
	dx = vx;
}


void TirDebouchechiote::update()
{
	x += dx;
	y += dy;

	if (x < offset - 100 || x > offset + 700 || y > 520 || y < -50)
		a_detruire = true;

	colFromPic();
}

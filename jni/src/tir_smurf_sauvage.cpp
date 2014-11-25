//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_smurf_sauvage.h"

TirSmurfSauvage::TirSmurfSauvage()
{
	pic = pbk_ennemis[144];
}

void TirSmurfSauvage::update()
{
	x += dx ;
	y += dy ;

	if (mur_opaque(x, y) || x < offset - 20 || x > offset + 660 || y < -20 || y > 500) {
		pic = NULL;
		noCol();
		a_detruire = true;
	} else {
		colFromPic();
	}
}

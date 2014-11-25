//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "tir_cadeau.h"

TirCadeau::TirCadeau()
{
	pic = pbk_ennemis[56] ;
	noCol() ;
}

void TirCadeau::update()
{
	if (!mur_opaque(x, y))
		tombe() ;

	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0) {
		etape += 1;

		if (etape == 20) {
			sbk_misc.play(11);
		}
	}

	if (etape >= 20) {
		col_on = true ;
		pic = pbk_ennemis[80 + etape] ;
	}

	if (etape > 35)
		a_detruire = true ;

	colFromPic();

	if (etape >= 30)
		noCol() ;
}

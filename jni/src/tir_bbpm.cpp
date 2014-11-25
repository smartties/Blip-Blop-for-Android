/******************************************************************
*
*
*		-------------------
*		    TirBBPM.cpp
*		-------------------
*
*		Pour les tirs de PM de Blip/Blop
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/


//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------


#include "tir_bbpm.h"

const int dx_tirbb_PM [] = { 0, 5, 8, 11, 12, 11, 8, 5, 0, -5, -8, -11, -12, -11, -8, -5 };
const int dy_tirbb_PM [] = { 12, 11, 8, 5, 0, -5, -8, -11, -12, -11, -8, -5, 0, 5, 8, 11 };

void TirBBPM::update()
{
    update_tir(x, y, 0, 12, angle);
	/*x += dx_tirbb_PM[dir];
	y += dy_tirbb_PM[dir];*/

	x += dxReferentiel;


	if (mur_opaque(x, y) || x < offset - 20 || x > offset + 690 || y < -20 || y > 500) {
		pic = NULL;
		noCol();
		a_detruire = true;
	} else {
		pic = pbk_bb[88 + dir];
		colFromPic();
	}
}

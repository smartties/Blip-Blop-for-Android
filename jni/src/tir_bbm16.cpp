/******************************************************************
*
*
*		-------------------
*		    TirBBM16.cpp
*		-------------------
*
*		Pour les tirs de M16 de Blip/Blop
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


#include "tir_bbm16.h"

const int dx_tirbb_m16 [] = { 0, 3, 6, 8, 9, 8, 6, 3, 0, -3, -6, -8, -9, -8, -6, -3 };
const int dy_tirbb_m16 [] = { 9, 8, 6, 3, 0, -2, -6, -8, -9, -8, -6, -3, 0, 3, 6, 8 };

void TirBBM16::update()
{
    //LOGI("SHOOOT");
    update_tir(x, y, 0, 9, angle);
	/*x += dx_tirbb_m16[dir];
	y += dy_tirbb_m16[dir];*/


	x += dxReferentiel;

	if (mur_opaque(x, y) || x < offset - 20 || x > offset + 690 || y < -20 || y > 500) {
		pic = NULL;
		noCol();
		a_detruire = true;
	} else {
		pic = pbk_bb[72 + dir];
		colFromPic();
	}
}

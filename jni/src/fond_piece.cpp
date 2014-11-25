/******************************************************************
*
*
*		---------------------------
*		    FondPiece.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/

#include "sprite.h"
#include "fond_piece.h"

int FondPiece::etape_synchro = 0;
int FondPiece::ss_etape_synchro = 0;
bool FondPiece::synchro = false;

void FondPiece::update()
{
	if (synchro != phase) {
		synchro = phase;
		ss_etape_synchro += 1;
		ss_etape_synchro %= 6;
		if (ss_etape_synchro == 0) {
			etape_synchro += 1;
			etape_synchro %= 4;
		}
	}
	pic = pbk_niveau[9 + etape_synchro];
	if (x < offset - 100)
		a_detruire = true;
};
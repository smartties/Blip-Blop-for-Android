/******************************************************************
*
*
*		---------------------------
*		    FondAssembleur.cpp
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 12 Janvier 2001
*
*
*
******************************************************************/

#include "globals.h"
#include "fond_assembleur.h"

FondAssembleur::FondAssembleur()
{
	//pic = pbk_niveau[53];
}

void FondAssembleur::update()
{
	etape += 1;
	etape %= 432;

	//colFromPic();
}

void FondAssembleur::affiche()
{
	//Sprite::affiche();

	SDL::Surface *	surf;
	int						xs;
	int						ys;
	RECT					r;
	int						largeur;

	surf = pbk_niveau[53]->Surf();
	xs = pbk_niveau[53]->xSize();
	ys = pbk_niveau[53]->ySize();

	r.top		= etape;
	r.left		= 0;

	if (x + 75 > offset + 640)
		largeur = offset + 640 - x;
	else
		largeur = 75;

	r.right		= largeur;
	r.bottom	= 87 + etape;

	backSurface->BltFast(x - offset, y, surf, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

}
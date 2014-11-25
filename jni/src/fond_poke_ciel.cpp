
#include "globals.h"
#include "fond_poke_ciel.h"

FondPokeCiel::FondPokeCiel()
{
	pic = pbk_niveau[48];
}

void FondPokeCiel::update()
{
	etape += 4;
	etape %= 384;

	colFromPic();
}

void FondPokeCiel::affiche()
{
	Sprite::affiche();

	SDL::Surface *	surf;
	int						xs;
	int						decalage = 0;
	int						ys;
	RECT					r;
	int						largeur;

	surf = pbk_niveau[50]->Surf();
	xs = pbk_niveau[50]->xSize();
	ys = pbk_niveau[50]->ySize();

	r.top		= 0;
	r.left		= etape;

	if (x + 192 > offset + 640) {
		largeur = offset + 640 - x;
	}

	else if (x < offset) {
		largeur = 192 ;
		r.left = offset - x + etape;
		decalage = offset - x;
	} else {
		largeur = 192;
	}

	r.right		= etape + largeur;
	r.bottom	= ys;

	/*if ( x+53 > offset+640)
		largeur = offset+640-x;
	else if (x < offset)
	{
		largeur = 53;
		r.left = offset - x;
		decalage = offset - x;
	}
	else
		largeur = 53;*/


	backSurface->BltFast(x - offset + decalage, y + 50, surf, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);


	draw(x, y, pbk_niveau[49]);
}
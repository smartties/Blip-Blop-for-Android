/******************************************************************
*
*
*		-----------------------
*		    FondSnorkSas.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 18 Janvier 2001
*
*
*
******************************************************************/


#include "globals.h"
#include "fond_snork_sas.h"
#include "enemy.h"

int FondSnorkSas1::etat = 0; // 0 pour etat du sas 1 ouvert , 1 pour fermé

FondSnorkSas1::FondSnorkSas1(): nb_joueur(0)
{
	etape = 0;
	//pic = pbk_niveau[53];
}

void FondSnorkSas1::update()
{
	if (!etat) { // si le sas n'est pas fermé..
		if ((tete_turc != NULL) && (tete_turc->x > 1400)) {
			nb_joueur ++;
			if (etape < 222) {
				if (nb_joueur >= 2) {
					etape += 2;
				}
				/*
				else
					il y en a peut etre un autre sous la porte..
				*/
			} else {
				etat = 1; // Sas 1 fermé...
			}
		} else {
			nb_joueur = 0;
		}




		if (etape % 8 == 0) {
			murs_opaques [(y + etape) / 8][(x + 8) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 16) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 24) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 32) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 40) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 48) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 56) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 64) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 72) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 80) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 88) / 8] = true;
			murs_opaques [(y + etape) / 8][(x + 96) / 8] = true;

		}
	}
}

void FondSnorkSas1::affiche()
{
	//Sprite::affiche();

	SDL::Surface *	surf;
	int						xs;
	int						ys;
	RECT					r;
	int						largeur;
	int                     decalage = 0;

	surf = pbk_niveau[1]->Surf();
	xs = pbk_niveau[1]->xSize();
	ys = pbk_niveau[1]->ySize();

	r.top		= 222 - etape;
	r.left		= 0;

	if (x + 53 > offset + 640)
		largeur = offset + 640 - x;
	else if (x < offset) {
		largeur = 53;
		r.left = offset - x;
		decalage = offset - x;
	} else
		largeur = 53;

	r.right		= largeur;
	r.bottom	= 222;

	backSurface->BltFast(x - offset + decalage, y , surf, &r, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
}


FondSnorkSas2::FondSnorkSas2()
{
	etape = 222;
}

void FondSnorkSas2::update()
{
	//si le sas 1 est verouillé...
	if ((FondSnorkSas1::etat) && (etape > 0)) {
		etape --;
	}


	if (etape % 8 == 0) {
		murs_opaques[(y + etape) / 8][(x + 8) / 8] = false;
		murs_opaques[(y + etape) / 8][(x + 16) / 8] = false;
		murs_opaques[(y + etape) / 8][(x + 24) / 8] = false;
		murs_opaques[(y + etape) / 8][(x + 32) / 8] = false;
		murs_opaques[(y + etape) / 8][(x + 40) / 8] = false;
		murs_opaques[(y + etape) / 8][(x + 48) / 8] = false;
	}
}

void FondSnorkSas2::affiche()
{
	//Sprite::affiche();

	SDL::Surface *	surf;
	int						xs;
	int						ys;
	RECT					r;
	int						largeur;
	int                     decalage = 0;

	surf = pbk_niveau[1]->Surf();
	xs = pbk_niveau[1]->xSize();
	ys = pbk_niveau[1]->ySize();

	r.top		= 222 - etape;
	r.left		= 0;

	if (x + 53 > offset + 640)
		largeur = offset + 640 - x;
	else if (x < offset) {
		largeur = 53;
		r.left = offset - x;
		decalage = offset - x;
	} else
		largeur = 53;

	r.right		= largeur;
	r.bottom	= 222;

	backSurface->BltFast(x - offset + decalage, y , surf, &r, DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
}
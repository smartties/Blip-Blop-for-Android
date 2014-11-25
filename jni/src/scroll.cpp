/******************************************************************
*
*
*		------------------
*		    Scroll.cpp
*		------------------
*
*
*		Fonctions pour le scroll. Gère le scrolling
*		avec le super buffer qui marche bizarrement sur cette
*		merde de GeForce.
*
*
*		Prosper / LOADED -   V 0.1 - 2 Aout 2000
*
*
*
******************************************************************/


//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "graphics.h"
#include "sprite.h"
#include "globals.h"
#include "scroll.h"
#include "ben_debug.h"
///MODIF SDL
#include "../SDL/include/SDL.h"

int vbuffer_wide = WANTED_VBUFFER_WIDE;
int	next_x = 0;
int	xTex = 0;
int	n_img = 0;
int n_cache = 0;

//-----------------------------------------------------------------------------

void drawScrolling()
{
	RECT		r;

	// Pour éviter les mauvaises surprises
	//
	if (offset < 0)
		offset = 0;
	else if (offset > level_size - 640)
		offset = level_size - 640;

	int	x1 = offset % vbuffer_wide;
	int x2 = (offset + 640) % vbuffer_wide;
	int x3 = (offset + vbuffer_wide - 2) % vbuffer_wide;

	r.top	= 0;
	r.bottom = 480;



	while (n_img < ((offset + vbuffer_wide - 2) / 640) || (n_img < scr_level_size && (next_x != ((x3 + 1) % vbuffer_wide)) && (next_x != ((x3) % vbuffer_wide)))) {

		/*static int counter = 0;
		char buf[128];
		sprintf(buf, "test/%d.bmp", counter);
		if (counter >200 && counter<250)
			SDL_SaveBMP(videoA->Get(), buf);
		counter++;*/

		r.left	= xTex;
		r.right = xTex + 2;

		videoA->BltFast(next_x, 0, pbk_decor[num_decor[n_img]]->Surf(), &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

		xTex += 2;

		if (xTex == 640) {
			xTex = 0;
			n_img += 1;
		}

		next_x += 2;

		if (next_x == vbuffer_wide) {
			next_x = 0;
			n_cache += 1;
		}
	}

	if (x1 <= vbuffer_wide - 640) {
		r.left	= x1;
		r.right = x1 + 640;

		backSurface->BltFast(0, 0, videoA, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	} else {
		r.left	= x1;
		r.right = vbuffer_wide;

		backSurface->BltFast(0, 0, videoA, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

		r.left	= 0;
		r.right = x2;

		backSurface->BltFast(vbuffer_wide - x1, 0, videoA, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
	}
}

//-----------------------------------------------------------------------------

void updateScrolling(bool forceOk)
{
	if (scroll_locked) {
		if (offset < x_lock)
			offset = x_lock;
	} else if (scroll_speed != 0 && forceOk) {
		offset += scroll_speed;
	} else if (list_joueurs.taille() > 0) {
		Sprite *	s;
		int			x_moy = 0;

		list_joueurs.start();

		while (!list_joueurs.fin()) {
			s = (Sprite*) list_joueurs.info();
			x_moy += s->x;
			list_joueurs.suivant();
		}

		x_moy /= list_joueurs.taille();
		x_moy -= 320;	// Pour centrer (320=640/2)

		if (x_moy > offset) {
			if ((x_moy - offset) >= 2)
				offset += 2;
			else
				offset = x_moy;
		}
	}

	if (offset < 0)
		offset = 0;
	else if (offset > level_size - 640)
		offset = level_size - 640;
}

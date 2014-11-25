/******************************************************************
*
*
*		----------------
*		  DD_gfx.cpp
*		----------------
*
*
*
******************************************************************/


//-----------------------------------------------------------------------------
//		Protection pour ne pas déclarer 'ddraw' 2 fois (une fois dans le .h)
//-----------------------------------------------------------------------------

#define GFX_CPP_FILE

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <stdio.h>
#include "lgx_packer.h"
#include "dd_gfx.h"
#include "globals.h"
#include "ben_debug.h"
#include "config.h"
#include "l_timer.h"

//-----------------------------------------------------------------------------
//		Objet 'ddraw' global REEL
//-----------------------------------------------------------------------------

Graphics *	graphicInstance	= NULL;

static int	oldRefreshRate	= -1;

//-----------------------------------------------------------------------------
// Nom: DDInitDirectDraw
// Desc: Ouvre DirectDraw
//-----------------------------------------------------------------------------

bool DDInitDirectDraw()
{
	if (graphicInstance != NULL) {
		debug << "Graphic engine already initialized!\n";
		return false;
	}
	graphicInstance = new Graphics();
	return graphicInstance->Init();
}


//-----------------------------------------------------------------------------
// Nom: DDCloseDirectDraw()
// Desc: Ferme Direct Draw
//-----------------------------------------------------------------------------

void DDCloseDirectDraw()
{
	graphicInstance->Close();
}

//-----------------------------------------------------------------------------
// Nom: DDSetCooperativeLevel
// Desc: Règle la priorité graphique à celle par défaut (GROS BILL)
//-----------------------------------------------------------------------------

bool DDSetCooperativeLevel(HWND wh)
{
	return graphicInstance->SetCooperativeLevel(wh, /*DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN*/0);
}


//-----------------------------------------------------------------------------
// Nom: DDSetCooperativeLevel
// Desc: Règle la priorité graphique
//-----------------------------------------------------------------------------

bool DDSetCooperativeLevel(HWND wh, int flags)
{
	return graphicInstance->SetCooperativeLevel(wh, flags);
}


//-----------------------------------------------------------------------------
// Nom: DDSetGfxMode
// Desc: Règle la résolution graphique X Y NbBits/Pixel
//-----------------------------------------------------------------------------

bool DDSetGfxMode(int x, int y, int d)
{
	debug << "DDSetGfxMode (" << x << "," << y << ")" << "\n";
	return graphicInstance->SetGfxMode(x, y, d);
}

//-----------------------------------------------------------------------------
// Nom: DDCreateSurface
// Desc: Crée une Surface de taille X*Y
//-----------------------------------------------------------------------------

SDL::Surface * DDCreateSurface(int x, int y)
{
	debug << "DDCreateSurface (" << x << ","<<y<< ")" << "\n";
	return graphicInstance->CreateSurface(x, y, DDSURF_BEST);
}

//-----------------------------------------------------------------------------
// Nom: DDCreateSurface
// Desc: Crée une Surface de taille X*Y en mém VIDEO / SYSTEM (cf DDOpenBMP)
//-----------------------------------------------------------------------------

SDL::Surface * DDCreateSurface(int x, int y, int flags)
{
	return graphicInstance->CreateSurface(x, y, flags);
}

//-----------------------------------------------------------------------------
// Nom: DDCreatePrimary
// Desc: Crée une Primary Surface sans double buffer
//-----------------------------------------------------------------------------

SDL::Surface * DDCreatePrimary()
{
	debug << "DDCreatePrimary ()" << "\n";
	return graphicInstance->CreatePrimary();

}


//-----------------------------------------------------------------------------
// Nom: DDCreatePrimary
// Desc: Crée une Primary Surface avec double buffer (le paramètre)
//-----------------------------------------------------------------------------

SDL::Surface * DDCreatePrimary(SDL::Surface * & back)
{
	debug << "DDCreatePrimary (back)" << "\n";
	return graphicInstance->CreatePrimary(back);
}


//-----------------------------------------------------------------------------
// Nom: DDLoadBMP
// Desc: Crée une surface ayant pour contenu une image (BMP)
//-----------------------------------------------------------------------------

SDL::Surface * DDLoadBMP(char * file)
{
	debug << "DDLoadBMP ("<<file<<")" << "\n";
	return graphicInstance->LoadBMP(file, DDSURF_BEST);
}


//-----------------------------------------------------------------------------
// Nom: DDLoadBMP
// Desc: Crée une surface ayant pour contenu l'image
//-----------------------------------------------------------------------------

SDL::Surface * DDLoadBMP(char * file, int flags)
{
	debug << "DDLoadBMP (" << file << ")" << "\n";
	return graphicInstance->LoadBMP(file, flags);
}


//-----------------------------------------------------------------------------
// Nom: DDCopyBMP
// Desc: Copie une image Bitmap dans une surface
//-----------------------------------------------------------------------------

HRESULT	DDCopyBMP(SDL::Surface *pdds, HBITMAP hbm)
{
	debug << "DDCopyBMP ()" << "\n";
	return graphicInstance->CopyBMP(pdds, hbm);
}


//-----------------------------------------------------------------------------
// Nom: DDFindColor
// Desc: Trouve la couleur correspondant à un RGB
//-----------------------------------------------------------------------------

DWORD DDFindColor(SDL::Surface *pdds, COLORREF rgb)
{
	return graphicInstance->FindColor(pdds, rgb);

}


//-----------------------------------------------------------------------------
// Nom: DDSetColorKey
// Desc: Règle la couleur transparente d'une surface
//-----------------------------------------------------------------------------

HRESULT DDSetColorKey(SDL::Surface *surf, COLORREF rgb)
{
	//debug << "DDSetColorKey ()" << "\n";
	return graphicInstance->SetColorKey(surf, rgb);

}


//-----------------------------------------------------------------------------
// Nom: DDLoadPalette
// Desc: Charge une palette d'un fichier
//-----------------------------------------------------------------------------

void * DDLoadPalette(char * file)
{
	return graphicInstance->LoadPalette(file);

}


void DDFlip()
{
	//debug << "DDFlip ()" << "\n";
	graphicInstance->Flip();
}

void DDFlipV()
{
	//debug << "DDFlipV ()" << "\n";
	graphicInstance->FlipV();
}

/******************************************************************
*
*
*		----------------
*		  DD_gfx.h
*		----------------
*
*
*		Fonctions graphiques PROPRES
*
*
*		Prosper / LOADED -   V 0.1
*
*
*
******************************************************************/


#ifndef _GFX_UTIL_
#define _GFX_UTIL_


//-----------------------------------------------------------------------------
//		Constantes pour la création des surfaces
//-----------------------------------------------------------------------------

#define DDSURF_VIDEO	1	// Mettre la surface en mémoire VIDEO
#define DDSURF_SYSTEM	2	// Mettre la surface en mémoire SYSTEM
#define DDSURF_BEST		4	// Mettre la surf en VIDEO si possible, SYSTEM sinon

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "graphics.h"

//-----------------------------------------------------------------------------
//		Objet 'ddraw' global (avec protection pour gfxutil.cpp)
//-----------------------------------------------------------------------------

#ifndef GFX_CPP_FILE
extern Graphics *	graphicInstance;
#endif

//-----------------------------------------------------------------------------
//		Prototypes
//-----------------------------------------------------------------------------

bool					DDInitDirectDraw();
bool					DDSetCooperativeLevel(HWND wh);
bool					DDSetCooperativeLevel(HWND wh, int flags);
bool					DDSetGfxMode(int x, int y, int d);
void					DDCloseDirectDraw();
SDL::Surface *	DDCreatePrimary();
SDL::Surface *	DDCreatePrimary(SDL::Surface * & back);
SDL::Surface *	DDCreateSurface(int x, int y);
SDL::Surface *	DDCreateSurface(int x, int y, int flags);
SDL::Surface *	DDLoadBMP(char * file);
SDL::Surface *	DDLoadBMP(char * file, int flags);
HRESULT					DDCopyBMP(SDL::Surface *surf, HBITMAP hbm);
void *	DDLoadPalette(char * file);
DWORD					DDFindColor(SDL::Surface *surf, COLORREF rgb);
HRESULT					DDSetColorKey(SDL::Surface *surf, COLORREF rgb);
void					DDFlip();
void					DDFlipV();

#endif

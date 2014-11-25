#pragma once

#include <iostream>

///MODIF WINDOWS
#if defined (WIN32)
#include <windows.h>
#else
#include "Engine/windows.h"
#endif

///MODIF SDL
#include "../SDL/include/SDL.h"


#include "ben_debug.h"

struct RenderRect
{
	int left;
	int right;
	int top;
	int bottom;
	unsigned int dwFillColor;
	int dwSize;
};


typedef RenderRect DDBLTFX;

#include "sdl_surface.h"
#include "sdl_texture.h"

/*Nulled dd flags*/
#define DDBLTFAST_WAIT 0
#define DDBLTFAST_NOCOLORKEY 0
#define DDBLTFAST_SRCCOLORKEY 0
#define DDBLT_WAIT 0

#define DD_OK true
/**/
#define DDBLT_COLORFILL (0x1<<2)

using namespace std;

SDL::Surface *	CreateSDLSurface(int x, int y, int b);

class Graphics
{
private:
	SDL_Window *window;
	SDL_Renderer *renderer;

public:
	Graphics();

	bool					Init();
	bool					SetCooperativeLevel(HWND wh);
	bool					SetCooperativeLevel(HWND wh, int flags);
	bool					SetGfxMode(int x, int y, int d);
	void					Close();
	SDL::Surface *	CreatePrimary();
	SDL::Surface *	CreatePrimary(SDL::Surface * & back);
	SDL::Surface *	CreateSurface(int x, int y);
	SDL::Surface *	CreateSurface(int x, int y, int flags);
	SDL_Surface *	CreateSDLSurface(int x, int y);
	SDL::Surface *	LoadBMP(char * file);
	SDL::Surface *	LoadBMP(char * file, int flags);
	HRESULT					CopyBMP(SDL::Surface *surf, HBITMAP hbm);
	void *	LoadPalette(char * file);
	DWORD					FindColor(SDL::Surface *surf, COLORREF rgb);
	HRESULT					SetColorKey(SDL::Surface *surf, COLORREF rgb);
	void					Flip();
	void					FlipV();

	void Clear(int r = 0, int g = 0, int b = 0);
	void Clear(int);
	void Clear(RenderRect);

	void RestoreAllSurfaces(){};


	static unsigned long RGB16ToRGB32(unsigned short a)
	{

			/* 1. Extract the red, green and blue values */

			/* from rrrr rggg gggb bbbb */
			unsigned long r = (a & 0xF800) >11;
			unsigned long g = (a & 0x07E0) >5;
			unsigned long b = (a & 0x001F);

			/* 2. Convert them to 0-255 range:
			There is more than one way. You can just shift them left:
			to 00000000 rrrrr000 gggggg00 bbbbb000
			r <<= 3;
			g <<= 2;
			b <<= 3;
			But that means your image will be slightly dark and
			off-colour as white 0xFFFF will convert to F8,FC,F8
			So instead you can scale by multiply and divide: */
			r = r * 255 / 31;
			g = g * 255 / 63;
			b = b * 255 / 31;
			/* This ensures 31/31 converts to 255/255 */

			/* 3. Construct your 32-bit format (this is 0RGB): */
			return (r << 16) | (g << 8) | b;

			/* Or for BGR0:
			return (r << 8) | (g << 16) | (b << 24);
			*/

	}
};

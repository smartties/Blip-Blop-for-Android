
#ifndef _AlphaBlend_
#define _AlphaBlend_

#include "graphics.h"


//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------

extern BOOL		g_isMMX;


//-----------------------------------------------------------------------------
// Structures
//-----------------------------------------------------------------------------

typedef struct {
	RGBQUAD depth;		// How many bits of precision per channel
	RGBQUAD Position;	// At what bit position does the color start
	UINT bpp;
} RGBFORMAT;


//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------

/*HRESULT TransAlphaImproved(LPDIRECTDRAWSURFACE7 src, LPDIRECTDRAWSURFACE7 dest,
                           LONG lDestX, LONG lDestY, RECT srcRect, WORD ALPHA, DWORD ColorKey, WORD BPP);

HRESULT TransAlphaImproved(LPDIRECTDRAWSURFACE7 src, LPDIRECTDRAWSURFACE7 dest,
                           LONG lDestX, LONG lDestY, RECT srcRect, WORD ALPHA, WORD BPP);

BOOL GetRGBFormat(LPDIRECTDRAWSURFACE7 surf, RGBFORMAT* rgb);*/

BOOL __cdecl IsMMX(void);


#endif


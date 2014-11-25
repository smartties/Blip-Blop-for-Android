
#include "graphics.h"
#include "alpha_blend.h"

BOOL					g_isMMX	= FALSE;
RGBFORMAT				g_pixelFormat;


//////////////////////////////////////////////////////////////////////////////////
// TransAlphaImproved -
//////////////////////////////////////////////////////////////////////////////////
/*HRESULT TransAlphaImproved(LPDIRECTDRAWSURFACE7 src, LPDIRECTDRAWSURFACE7 dest,
                           LONG lDestX, LONG lDestY, RECT srcRect, WORD ALPHA, DWORD ColorKey, WORD BPP)
{
	int register i, j;
	int height, width;
	BYTE* lpSprite;
	BYTE* lpDest;
	WORD dPitch, SpritePitch;
	DWORD sColorKey;
	DWORD sTemp, dTemp;
	DWORD sr, sg, sb, dr, dg, db;
	WORD sbuf, dbuf;
	DWORD Result;
	BOOL oddWidth = FALSE;
	DDSURFACEDESC2 srcDDSD, destDDSD;
	DWORD REDC, GREENC, BLUEC;
	DWORD PLUS64;
	DWORD ALPHABY4;
	DWORD doubleColorKey;


	// Check the ALPHA value
	if (ALPHA < 0)
		ALPHA = 0;
	else if (ALPHA > 256)
		ALPHA = 256;

	// Set height and width of SPRITE
	height = srcRect.bottom - srcRect.top;
	width = srcRect.right - srcRect.left;

	// Lock down both surfaces for read and write
	ZeroMemory(&srcDDSD, sizeof(srcDDSD));
	srcDDSD.dwSize = sizeof(srcDDSD);
	src->Lock(NULL, &srcDDSD, DDLOCK_WAIT, NULL);

	ZeroMemory(&destDDSD, sizeof(destDDSD));
	destDDSD.dwSize = sizeof(destDDSD);
	dest->Lock(NULL, &destDDSD, DDLOCK_WAIT, NULL);

	// Get the color key for sprite surface
	sColorKey = ColorKey;

	// Set the pitch for both surfaces
	SpritePitch = (WORD)srcDDSD.lPitch;
	dPitch      = (WORD)destDDSD.lPitch;

	// Initialize the pointers to the upper left hand corner of surface
	lpSprite = (BYTE*)srcDDSD.lpSurface;
	lpDest   = (BYTE*)destDDSD.lpSurface;

	// Do some work outside of the loop
	PLUS64         = 64 | (64 << 16);
	ALPHABY4      = (ALPHA / 4) | ((ALPHA / 4) << 16);
	doubleColorKey = ColorKey | (ColorKey << 16);

	switch (BPP) {
		case 8:
			// IMHO paletized modes are a thing of the past please feel free to
			// implement this if you so desire.
			break;

		case 15:  ////////////////////////////////////////////////////////////////////////
			//
			//  WARNING!!!: I do not have a video card that uses the 5-5-5 format
			//              this barnch of code has not be tested.
			//
			////////////////////////////////////////////////////////////////////////

			// Initialize the pointers to the first pixel in the rectangle
			lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 2);
			lpDest   += (lDestY * dPitch) + (lDestX * 2);

			// Set the horizontal padding
			sbuf = (WORD)(SpritePitch - (2 * width));
			dbuf = (WORD)(dPitch - (2 * width));

			// Is the Sprite width odd or even?
			if (width % 2 == 1) {
				oddWidth = TRUE;
				width = (width - 1) / 2; //div by 2, processing 2 pixels at a time.
			} else
				width = width / 2;  //div by 2, processing 2 pixels at a time.

			i = height;
			do {
				if (oddWidth) {
					sTemp = *((WORD*)lpSprite);

					if (sTemp != sColorKey) {
						dTemp = *((WORD*)lpDest);
						sb = sTemp & 0x1f;
						db = dTemp & 0x1f;
						sg = (sTemp >> 5) & 0x1f;
						dg = (dTemp >> 5) & 0x1f;
						sr = (sTemp >> 10) & 0x1f;
						dr = (dTemp >> 10) & 0x1f;

						*((WORD*)lpDest) = (WORD)((ALPHA * (db - sb) >> 8) + sb |
						                          ((ALPHA * (dg - sg) >> 8) + sg) << 5 |
						                          ((ALPHA * (dr - sr) >> 8) + sr) << 10);
					}

					lpDest += 2;
					lpSprite += 2;
				}
				j = width;
				do {
					sTemp = *((DWORD*)lpSprite);

					if (sTemp != doubleColorKey) {
						dTemp = *((DWORD*)lpDest);

						sb = sTemp & 0x001F001F;
						db = dTemp & 0x001F001F;
						sg = (sTemp >> 5)  & 0x001F001F;
						dg = (dTemp >> 5)  & 0x001F001F;
						sr = (sTemp >> 10) & 0x001F001F;
						dr = (dTemp >> 10) & 0x001F001F;

						BLUEC  = ((((ALPHA * ((sb + PLUS64) - db)) >> 8) + db) - ALPHABY4) & 0x001F001F;
						GREENC = (((((ALPHA * ((sg + PLUS64) - dg)) >> 8) + dg) - ALPHABY4) & 0x001F001F) << 5;
						REDC   = (((((ALPHA * ((sr + PLUS64) - dr)) >> 8) + dr) - ALPHABY4) & 0x001F001F) << 10;

						Result = BLUEC | GREENC | REDC;

						if ((sTemp >> 16) == ColorKey)
							Result = (Result & 0xFFFF) | (dTemp & 0xFFFF0000);
						else if ((sTemp & 0xFFFF) == ColorKey)
							Result = (Result & 0xFFFF0000) | (dTemp & 0xFFFF);

						*((DWORD*)lpDest) = Result;
					}
					lpDest    += 4;
					lpSprite  += 4;

				} while (--j > 0);

				lpDest   += dbuf;
				lpSprite += sbuf;

			} while (--i > 0);

			break;

		case 16:

			// Initialize the pointers to the first pixel in the rectangle
			lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 2);
			lpDest   += (lDestY * dPitch) + (lDestX * 2);

			// Set the horizontal padding
			sbuf = (WORD)(SpritePitch - (2 * width));
			dbuf = (WORD)(dPitch - (2 * width));

			// Is the Sprite width odd or even?
			if (width % 2 == 1) {
				oddWidth = TRUE;
				width = (width - 1) / 2; //div by 2, processing 2 pixels at a time.
			} else
				width = width / 2;  //div by 2, processing 2 pixels at a time.


			i = height;
			do {
				if (oddWidth) {
					sTemp = *((WORD*)lpSprite);

					if (sTemp != ColorKey) {
						dTemp = *((WORD*)lpDest);
						sb = sTemp & 0x1f;
						db = dTemp & 0x1f;
						sg = (sTemp >> 5) & 0x3f;
						dg = (dTemp >> 5) & 0x3f;
						sr = (sTemp >> 11) & 0x1f;
						dr = (dTemp >> 11) & 0x1f;

						*((WORD*)lpDest) = (WORD)((ALPHA * (sb - db) >> 8) + db |
						                          ((ALPHA * (sg - dg) >> 8) + dg) << 5 |
						                          ((ALPHA * (sr - dr) >> 8) + dr) << 11);
					}

					lpDest   += 2;
					lpSprite += 2;
				}
				j = width;
				do {
					sTemp = *((DWORD*)lpSprite);

					if (sTemp != doubleColorKey) {
						dTemp = *((DWORD*)lpDest);

						sb = sTemp & 0x001F001F;
						db = dTemp & 0x001F001F;
						sg = (sTemp >> 5)  & 0x003F003F;
						dg = (dTemp >> 5)  & 0x003F003F;
						sr = (sTemp >> 11) & 0x001F001F;
						dr = (dTemp >> 11) & 0x001F001F;

						BLUEC  = ((((ALPHA * ((sb + PLUS64) - db)) >> 8) + db) - ALPHABY4) & 0x001F001F;
						GREENC = (((((ALPHA * ((sg + PLUS64) - dg)) >> 8) + dg) - ALPHABY4) & 0x003F003F) << 5;
						REDC   = (((((ALPHA * ((sr + PLUS64) - dr)) >> 8) + dr) - ALPHABY4) & 0x001F001F) << 11;

						Result = BLUEC | GREENC | REDC;

						if ((sTemp >> 16) == ColorKey)
							Result = (Result & 0xFFFF) | (dTemp & 0xFFFF0000);
						else if ((sTemp & 0xFFFF) == ColorKey)
							Result = (Result & 0xFFFF0000) | (dTemp & 0xFFFF);

						*((DWORD*)lpDest) = Result;
					}
					lpDest    += 4;
					lpSprite  += 4;

				} while (--j > 0);

				lpDest   += dbuf;
				lpSprite += sbuf;

			} while (--i > 0);

			break;

		case 24:  ////////////////////////////////////////////////////////////////////////
			//
			//  WARNING!!!: I do not have a video card capable of 24bit rendering
			//              this barnch of code has not be tested.
			//
			////////////////////////////////////////////////////////////////////////

			// Initialize the pointers to the first pixel in the rectangle
			lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 3);
			lpDest   += (lDestY * dPitch) + (lDestX * 3);

			// Set the horizontal padding
			sbuf = (WORD)(SpritePitch - (3 * width));
			dbuf = (WORD)(dPitch - (3 * width));

			i = height;
			do {
				j = width;
				do {
					sTemp = *((DWORD*)lpSprite);

					if ((sTemp & 0xFFFFFF) != sColorKey) {
						dTemp = *((DWORD*)lpDest);
						sb = sTemp & 0xFF;
						db = dTemp & 0xFF;
						sg = (sTemp >> 8) & 0xFF;
						dg = (dTemp >> 8) & 0xFF;
						sr = (sTemp >> 16) & 0xFF;
						dr = (dTemp >> 16) & 0xFF;

						Result = (DWORD)((ALPHA * (db - sb) >> 8) + sb |
						                 ((ALPHA * (dg - sg) >> 8) + sg) << 8 |
						                 ((ALPHA * (dr - sr) >> 8) + sr) << 16);

						*((WORD*)lpDest) = (WORD)(Result & 0xFFFF);
						lpDest += 2;
						*lpDest = (BYTE)(Result >> 16);
						lpDest++;
					} else {
						lpDest += 3;
					}

					lpSprite += 3;

				} while (--j > 0);
				lpDest   += dbuf;
				lpSprite += sbuf;

			} while (--i > 0);
			break;

		case 32:

			// Initialize the pointers to the first pixel in the rectangle
			lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 4);
			lpDest   += (lDestY * dPitch) + (lDestX * 4);

			// Set the horizontal padding
			sbuf = (WORD)(SpritePitch - (4 * width));
			dbuf = (WORD)(dPitch - (4 * width));

			i = height;
			do {
				j = width;
				do {
					sTemp = *((DWORD*)lpSprite);

					if ((sTemp & 0xFFFFFF) != sColorKey) {
						dTemp = *((DWORD*)lpDest);
						sb = sTemp & 0xFF;
						db = dTemp & 0xFF;
						sg = (sTemp >> 8) & 0xFF;
						dg = (dTemp >> 8) & 0xFF;
						sr = (sTemp >> 16) & 0xFF;
						dr = (dTemp >> 16) & 0xFF;

						Result = (DWORD)((ALPHA * (db - sb) >> 8) + sb |
						                 ((ALPHA * (dg - sg) >> 8) + sg) << 8 |
						                 ((ALPHA * (dr - sr) >> 8) + sr) << 16);

						*((WORD*)lpDest) = (WORD)(Result & 0xFFFF);
						lpDest += 2;
						*lpDest = (BYTE)(Result >> 16);
						lpDest += 2;
					} else {
						lpDest += 4;
					}

					lpSprite += 4;

				} while (--j > 0);
				lpDest   += dbuf;
				lpSprite += sbuf;

			} while (--i > 0);
			break;
	} // End RGB Format switch statement


	src->Unlock(NULL);
	dest->Unlock(NULL);

	return DD_OK;
}
*/
//////////////////////////////////////////////////////////////////////////////////
// TransAlphaImproved - Sans COLORKEY
//////////////////////////////////////////////////////////////////////////////////
/*HRESULT TransAlphaImproved(LPDIRECTDRAWSURFACE7 src, LPDIRECTDRAWSURFACE7 dest,
                           LONG lDestX, LONG lDestY, RECT srcRect, WORD ALPHA, WORD BPP)
{
	int register i, j;
	int height, width;
	BYTE* lpSprite;
	BYTE* lpDest;
	WORD dPitch, SpritePitch;
	DWORD sTemp, dTemp;
	DWORD sr, sg, sb, dr, dg, db;
	WORD sbuf, dbuf;
	DWORD Result;
	BOOL oddWidth = FALSE;
	DDSURFACEDESC2 srcDDSD, destDDSD;
	DWORD REDC, GREENC, BLUEC;
	DWORD PLUS64;
	DWORD ALPHABY4;


	// Check the ALPHA value
	if (ALPHA < 0)
		ALPHA = 0;
	else if (ALPHA > 256)
		ALPHA = 256;

	// Set height and width of SPRITE
	height = srcRect.bottom - srcRect.top;
	width = srcRect.right - srcRect.left;

	// Lock down both surfaces for read and write
	ZeroMemory(&srcDDSD, sizeof(srcDDSD));
	srcDDSD.dwSize = sizeof(srcDDSD);
	src->Lock(NULL, &srcDDSD, DDLOCK_WAIT, NULL);

	ZeroMemory(&destDDSD, sizeof(destDDSD));
	destDDSD.dwSize = sizeof(destDDSD);
	dest->Lock(NULL, &destDDSD, DDLOCK_WAIT, NULL);


	// Set the pitch for both surfaces
	SpritePitch = (WORD)srcDDSD.lPitch;
	dPitch      = (WORD)destDDSD.lPitch;

	// Initialize the pointers to the upper left hand corner of surface
	lpSprite = (BYTE*)srcDDSD.lpSurface;
	lpDest   = (BYTE*)destDDSD.lpSurface;

	// Do some work outside of the loop
	PLUS64         = 64 | (64 << 16);
	ALPHABY4      = (ALPHA / 4) | ((ALPHA / 4) << 16);

	switch (BPP) {
		case 8:
			// IMHO paletized modes are a thing of the past please feel free to
			// implement this if you so desire.
			break;

		case 15:  ////////////////////////////////////////////////////////////////////////
			//
			//  WARNING!!!: I do not have a video card that uses the 5-5-5 format
			//              this barnch of code has not be tested.
			//
			////////////////////////////////////////////////////////////////////////

			// Initialize the pointers to the first pixel in the rectangle
			lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 2);
			lpDest   += (lDestY * dPitch) + (lDestX * 2);

			// Set the horizontal padding
			sbuf = (WORD)(SpritePitch - (2 * width));
			dbuf = (WORD)(dPitch - (2 * width));

			// Is the Sprite width odd or even?
			if (width % 2 == 1) {
				oddWidth = TRUE;
				width = (width - 1) / 2; //div by 2, processing 2 pixels at a time.
			} else
				width = width / 2;  //div by 2, processing 2 pixels at a time.

			i = height;
			do {
				if (oddWidth) {
					sTemp = *((WORD*)lpSprite);

					dTemp = *((WORD*)lpDest);
					sb = sTemp & 0x1f;
					db = dTemp & 0x1f;
					sg = (sTemp >> 5) & 0x1f;
					dg = (dTemp >> 5) & 0x1f;
					sr = (sTemp >> 10) & 0x1f;
					dr = (dTemp >> 10) & 0x1f;

					*((WORD*)lpDest) = (WORD)((ALPHA * (db - sb) >> 8) + sb |
					                          ((ALPHA * (dg - sg) >> 8) + sg) << 5 |
					                          ((ALPHA * (dr - sr) >> 8) + sr) << 10);

					lpDest += 2;
					lpSprite += 2;
				}
				j = width;
				do {
					sTemp = *((DWORD*)lpSprite);

					dTemp = *((DWORD*)lpDest);

					sb = sTemp & 0x001F001F;
					db = dTemp & 0x001F001F;
					sg = (sTemp >> 5)  & 0x001F001F;
					dg = (dTemp >> 5)  & 0x001F001F;
					sr = (sTemp >> 10) & 0x001F001F;
					dr = (dTemp >> 10) & 0x001F001F;

					BLUEC  = ((((ALPHA * ((sb + PLUS64) - db)) >> 8) + db) - ALPHABY4) & 0x001F001F;
					GREENC = (((((ALPHA * ((sg + PLUS64) - dg)) >> 8) + dg) - ALPHABY4) & 0x001F001F) << 5;
					REDC   = (((((ALPHA * ((sr + PLUS64) - dr)) >> 8) + dr) - ALPHABY4) & 0x001F001F) << 10;

					Result = BLUEC | GREENC | REDC;


					*((DWORD*)lpDest) = Result;

					lpDest    += 4;
					lpSprite  += 4;

				} while (--j > 0);

				lpDest   += dbuf;
				lpSprite += sbuf;

			} while (--i > 0);

			break;

		case 16:

			// Initialize the pointers to the first pixel in the rectangle
			lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 2);
			lpDest   += (lDestY * dPitch) + (lDestX * 2);

			// Set the horizontal padding
			sbuf = (WORD)(SpritePitch - (2 * width));
			dbuf = (WORD)(dPitch - (2 * width));

			// Is the Sprite width odd or even?
			if (width % 2 == 1) {
				oddWidth = TRUE;
				width = (width - 1) / 2; //div by 2, processing 2 pixels at a time.
			} else
				width = width / 2;  //div by 2, processing 2 pixels at a time.


			i = height;
			do {
				if (oddWidth) {
					sTemp = *((WORD*)lpSprite);

					dTemp = *((WORD*)lpDest);
					sb = sTemp & 0x1f;
					db = dTemp & 0x1f;
					sg = (sTemp >> 5) & 0x3f;
					dg = (dTemp >> 5) & 0x3f;
					sr = (sTemp >> 11) & 0x1f;
					dr = (dTemp >> 11) & 0x1f;

					*((WORD*)lpDest) = (WORD)((ALPHA * (sb - db) >> 8) + db |
					                          ((ALPHA * (sg - dg) >> 8) + dg) << 5 |
					                          ((ALPHA * (sr - dr) >> 8) + dr) << 11);

					lpDest   += 2;
					lpSprite += 2;
				}
				j = width;
				do {
					sTemp = *((DWORD*)lpSprite);

					dTemp = *((DWORD*)lpDest);

					sb = sTemp & 0x001F001F;
					db = dTemp & 0x001F001F;
					sg = (sTemp >> 5)  & 0x003F003F;
					dg = (dTemp >> 5)  & 0x003F003F;
					sr = (sTemp >> 11) & 0x001F001F;
					dr = (dTemp >> 11) & 0x001F001F;

					BLUEC  = ((((ALPHA * ((sb + PLUS64) - db)) >> 8) + db) - ALPHABY4) & 0x001F001F;
					GREENC = (((((ALPHA * ((sg + PLUS64) - dg)) >> 8) + dg) - ALPHABY4) & 0x003F003F) << 5;
					REDC   = (((((ALPHA * ((sr + PLUS64) - dr)) >> 8) + dr) - ALPHABY4) & 0x001F001F) << 11;

					Result = BLUEC | GREENC | REDC;


					*((DWORD*)lpDest) = Result;

					lpDest    += 4;
					lpSprite  += 4;

				} while (--j > 0);

				lpDest   += dbuf;
				lpSprite += sbuf;

			} while (--i > 0);

			break;

		case 24:  ////////////////////////////////////////////////////////////////////////
			//
			//  WARNING!!!: I do not have a video card capable of 24bit rendering
			//              this barnch of code has not be tested.
			//
			////////////////////////////////////////////////////////////////////////

			// Initialize the pointers to the first pixel in the rectangle
			lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 3);
			lpDest   += (lDestY * dPitch) + (lDestX * 3);

			// Set the horizontal padding
			sbuf = (WORD)(SpritePitch - (3 * width));
			dbuf = (WORD)(dPitch - (3 * width));

			i = height;
			do {
				j = width;
				do {
					sTemp = *((DWORD*)lpSprite);

					dTemp = *((DWORD*)lpDest);
					sb = sTemp & 0xFF;
					db = dTemp & 0xFF;
					sg = (sTemp >> 8) & 0xFF;
					dg = (dTemp >> 8) & 0xFF;
					sr = (sTemp >> 16) & 0xFF;
					dr = (dTemp >> 16) & 0xFF;

					Result = (DWORD)((ALPHA * (db - sb) >> 8) + sb |
					                 ((ALPHA * (dg - sg) >> 8) + sg) << 8 |
					                 ((ALPHA * (dr - sr) >> 8) + sr) << 16);

					*((WORD*)lpDest) = (WORD)(Result & 0xFFFF);
					lpDest += 2;
					*lpDest = (BYTE)(Result >> 16);
					lpDest++;

					lpSprite += 3;

				} while (--j > 0);
				lpDest   += dbuf;
				lpSprite += sbuf;

			} while (--i > 0);
			break;

		case 32:

			// Initialize the pointers to the first pixel in the rectangle
			lpSprite += (srcRect.top * SpritePitch) + (srcRect.left * 4);
			lpDest   += (lDestY * dPitch) + (lDestX * 4);

			// Set the horizontal padding
			sbuf = (WORD)(SpritePitch - (4 * width));
			dbuf = (WORD)(dPitch - (4 * width));

			i = height;
			do {
				j = width;
				do {
					sTemp = *((DWORD*)lpSprite);

					dTemp = *((DWORD*)lpDest);
					sb = sTemp & 0xFF;
					db = dTemp & 0xFF;
					sg = (sTemp >> 8) & 0xFF;
					dg = (dTemp >> 8) & 0xFF;
					sr = (sTemp >> 16) & 0xFF;
					dr = (dTemp >> 16) & 0xFF;

					Result = (DWORD)((ALPHA * (db - sb) >> 8) + sb |
					                 ((ALPHA * (dg - sg) >> 8) + sg) << 8 |
					                 ((ALPHA * (dr - sr) >> 8) + sr) << 16);

					*((WORD*)lpDest) = (WORD)(Result & 0xFFFF);
					lpDest += 2;
					*lpDest = (BYTE)(Result >> 16);
					lpDest += 2;

					lpSprite += 4;

				} while (--j > 0);
				lpDest   += dbuf;
				lpSprite += sbuf;

			} while (--i > 0);
			break;
	} // End RGB Format switch statement


	src->Unlock(NULL);
	dest->Unlock(NULL);

	return DD_OK;
}


*/

////////////////////////////////////////////////////////////////////////
//
//  GetRGBFormat
//
//  Fills out a RGBFORMAT structure.
//
////////////////////////////////////////////////////////////////////////
/*
BOOL GetRGBFormat(LPDIRECTDRAWSURFACE7 surf, RGBFORMAT* rgb)
{
	DDSURFACEDESC2 ddsd;
	BYTE shiftcount;

	//get a surface description
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_PIXELFORMAT;

	if (surf->GetSurfaceDesc(&ddsd) != DD_OK)
		return FALSE;

	// Check if the surface is 4 or 8 bpp
	if (ddsd.ddpfPixelFormat.dwRGBBitCount <= 8) {
		rgb->bpp = ddsd.ddpfPixelFormat.dwRGBBitCount;

		rgb->depth.rgbRed      = 0;
		rgb->Position.rgbRed   = 0;

		rgb->depth.rgbGreen    = 0;
		rgb->Position.rgbGreen = 0;

		rgb->depth.rgbBlue     = 0;
		rgb->Position.rgbBlue  = 0;

		return TRUE;
	}

	//Get the RED channel data for 15, 16, 24, or 32 bpp surface
	shiftcount = 0;
	while (!(ddsd.ddpfPixelFormat.dwRBitMask & 1) && (shiftcount < 32)) {
		ddsd.ddpfPixelFormat.dwRBitMask >>= 1;
		shiftcount++;
	}

	// depth is the highest possible value that this channel could
	// be set to. It is cast to a BYTE because 255 is the highest
	// value for all modes.
	rgb->depth.rgbRed = (BYTE) ddsd.ddpfPixelFormat.dwRBitMask;

	// Position represents where the color channel starts, bitwise,
	// in the pixel. Another way of saying this that Position is
	// eqaul to the number of zeros to the right of the channel's
	// bitmask.
	rgb->Position.rgbRed = shiftcount;

	//Get the GREEN channel data for 15, 16, 24, or 32 bpp surface
	shiftcount = 0;
	while (!(ddsd.ddpfPixelFormat.dwGBitMask & 1) && (shiftcount < 32)) {
		ddsd.ddpfPixelFormat.dwGBitMask >>= 1;
		shiftcount++;
	}
	rgb->depth.rgbGreen = (BYTE)ddsd.ddpfPixelFormat.dwGBitMask;
	rgb->Position.rgbGreen = shiftcount;

	//Get the BLUE channel data for 15, 16, 24, or 32 bpp surface
	shiftcount = 0;
	while (!(ddsd.ddpfPixelFormat.dwBBitMask & 1) && (shiftcount < 32)) {
		ddsd.ddpfPixelFormat.dwBBitMask >>= 1;
		shiftcount++;
	}
	rgb->depth.rgbBlue = (BYTE)ddsd.ddpfPixelFormat.dwBBitMask;
	rgb->Position.rgbBlue = shiftcount;

	//  Determine the bpp for the surface. (15, 16, 24, or 32)
	if (ddsd.ddpfPixelFormat.dwFlags & DDPF_RGB) {
		if (ddsd.ddpfPixelFormat.dwRGBBitCount == 16) {
			if ((rgb->depth.rgbBlue + rgb->depth.rgbGreen + rgb->depth.rgbRed) == 93)
				rgb->bpp = 15;
			else
				rgb->bpp = 16;
		} else if (ddsd.ddpfPixelFormat.dwRGBBitCount == 24)
			rgb->bpp = 24;
		else if (ddsd.ddpfPixelFormat.dwRGBBitCount == 32)
			rgb->bpp = 32;
		else
			rgb->bpp = 0;
	} else {
		rgb->bpp = 0;
		return FALSE;
	}

	return TRUE;
}

*/
////////////////////////////////////////////////////////////////////////
//
//  IsMMX
//
//  Is the machine capable of MMX instructions
//
////////////////////////////////////////////////////////////////////////

BOOL __cdecl IsMMX(void)
{
#ifdef _WIN32
	SYSTEM_INFO si;
	int nCPUFeatures = 0;
	GetSystemInfo(&si);
	if (si.dwProcessorType != PROCESSOR_INTEL_386 && si.dwProcessorType != PROCESSOR_INTEL_486) {
		try {
			__asm {
				/*;
				we must push/pop the registers << CPUID>>  writes to, as the
				;
				optimiser doesn't know about << CPUID>> , and so doesn't expect
				;
				these registers to change.*/
				push eax
				push ebx
				push ecx
				push edx

				/*;
				        << CPUID>>
				;*/
				/*eax=0, 1, 2 -> CPU info in eax, ebx, ecx, edx*/
				mov eax, 1
				_emit 0x0f
				_emit 0xa2
				mov nCPUFeatures, edx

				pop edx
				pop ecx
				pop ebx
				pop eax
			}
		} catch (...) { // just to be sure...
			return false;
		}
	}
	return (nCPUFeatures & 0x00800000) != 0;
#else
	return false;
#endif
}

#ifndef DDRAW_H
#define DDRAW_H

#include "windows.h"

struct IDirectDrawPalette;

typedef struct _DDCOLORKEY {
	DWORD dwColorSpaceLowValue;
	DWORD dwColorSpaceHighValue;
} DDCOLORKEY, *LPDDCOLORKEY;

typedef struct _DDCAPS {
} DDCAPS, *LPDDCAPS;

#define DDSCAPS_VIDEOMEMORY 0x1
#define DDSCAPS_OFFSCREENPLAIN  0x2
#define DDSCAPS_SYSTEMMEMORY 0x4
#define DDSCAPS_COMPLEX 0x8
#define DDSCAPS_PRIMARYSURFACE 0x16
#define DDSCAPS_FLIP 0x32
#define DDSCAPS_BACKBUFFER 0x64
typedef struct _DDSCAPS2 {
	DWORD dwCaps;
	DWORD dwCaps2;
	DWORD dwCaps3;
	union {
		DWORD dwCaps4;
		DWORD dwVolumeDepth;
	} DUMMYUNIONNAMEN(1);
} DDSCAPS2, *LPDDSCAPS2;

typedef struct _DDPIXELFORMAT {
	DWORD dwSize;
	DWORD dwFlags;
	DWORD dwFourCC;
	union {
		DWORD dwRGBBitCount;
		DWORD dwYUVBitCount;
		DWORD dwZBufferBitDepth;
		DWORD dwAlphaBitDepth;
		DWORD dwLuminanceBitCount;
		DWORD dwBumpBitCount;
		DWORD dwPrivateFormatBitCount;
	} DUMMYUNIONNAMEN(1);
	union {
		DWORD dwRBitMask;
		DWORD dwYBitMask;
		DWORD dwStencilBitDepth;
		DWORD dwLuminanceBitMask;
		DWORD dwBumpDuBitMask;
		DWORD dwOperations;
	} DUMMYUNIONNAMEN(2);
	union {
		DWORD  dwGBitMask;
		DWORD  dwUBitMask;
		DWORD  dwZBitMask;
		DWORD  dwBumpDvBitMask;
		struct {
			WORD wFlipMSTypes;
			WORD wBltMSTypes;
		} MultiSampleCaps;
	} DUMMYUNIONNAMEN(3);
	union {
		DWORD dwBBitMask;
		DWORD dwVBitMask;
		DWORD dwStencilBitMask;
		DWORD dwBumpLuminanceBitMask;
	} DUMMYUNIONNAMEN(4);
	union {
		DWORD dwRGBAlphaBitMask;
		DWORD dwYUVAlphaBitMask;
		DWORD dwLuminanceAlphaBitMask;
		DWORD dwRGBZBitMask;
		DWORD dwYUVZBitMask;
	} DUMMYUNIONNAMEN(5);
} DDPIXELFORMAT, *LPDDPIXELFORMAT;

struct DDSURFACEDESC {
};
typedef struct _DDSURFACEDESC2 : DDSURFACEDESC {
	DWORD      dwSize;
	DWORD      dwFlags;
	DWORD      dwHeight;
	DWORD      dwWidth;
	union {
		LONG  lPitch;
		DWORD dwLinearSize;
	};
	union {
		DWORD dwBackBufferCount;
		DWORD dwDepth;
	};
	union {
		DWORD dwMipMapCount;
		DWORD dwRefreshRate;
		DWORD dwSrcVBHandle;
	};
	DWORD      dwAlphaBitDepth;
	DWORD      dwReserved;
	LPVOID     lpSurface;
	union {
		DDCOLORKEY ddckCKDestOverlay;
		DWORD      dwEmptyFaceColor;
	};
	DDCOLORKEY ddckCKDestBlt;
	DDCOLORKEY ddckCKSrcOverlay;
	DDCOLORKEY ddckCKSrcBlt;
	union {
		DDPIXELFORMAT ddpfPixelFormat;
		DWORD         dwFVF;
	};
	DDSCAPS2   ddsCaps;
	DWORD      dwTextureStage;
} DDSURFACEDESC2, *LPDDSURFACEDESC2;

#define DDSD_HEIGHT 0x2
#define DDSD_WIDTH 0x4
#define DDSD_CAPS 0x8
#define DDSD_BACKBUFFERCOUNT 0x16
#define DDPCAPS_8BIT 0x8
#define DD_OK 0x0

#define DDBLT_WAIT 0x1
#define DDBLT_COLORFILL 0x2
#define DDBLTFAST_WAIT 0x1
#define DDBLTFAST_SRCCOLORKEY 0x2
#define DDBLTFAST_NOCOLORKEY 0x4
#define DDFLIP_WAIT 0x1
#define DDFLIP_NOVSYNC 0x2
#define DDSD_PIXELFORMAT 0x1
#define DDPF_RGB 0x1

struct IDirectDrawSurface7;
typedef IDirectDrawSurface7* LPDIRECTDRAWSURFACE7;
typedef IDirectDrawSurface7* LPDIRECTDRAWSURFACE;

typedef struct _DDBLTFX {
	DWORD      dwSize;
	DWORD      dwDDFX;
	DWORD      dwROP;
	DWORD      dwDDROP;
	DWORD      dwRotationAngle;
	DWORD      dwZBufferOpCode;
	DWORD      dwZBufferLow;
	DWORD      dwZBufferHigh;
	DWORD      dwZBufferBaseDest;
	DWORD      dwZDestConstBitDepth;
	union {
		DWORD               dwZDestConst;
		LPDIRECTDRAWSURFACE lpDDSZBufferDest;
	} DUMMYUNIONNAMEN(1);
	DWORD      dwZSrcConstBitDepth;
	union {
		DWORD               dwZSrcConst;
		LPDIRECTDRAWSURFACE lpDDSZBufferSrc;
	} DUMMYUNIONNAMEN(2);
	DWORD      dwAlphaEdgeBlendBitDepth;
	DWORD      dwAlphaEdgeBlend;
	DWORD      dwReserved;
	DWORD      dwAlphaDestConstBitDepth;
	union {
		DWORD               dwAlphaDestConst;
		LPDIRECTDRAWSURFACE lpDDSAlphaDest;
	} DUMMYUNIONNAMEN(3);
	DWORD      dwAlphaSrcConstBitDepth;
	union {
		DWORD               dwAlphaSrcConst;
		LPDIRECTDRAWSURFACE lpDDSAlphaSrc;
	} DUMMYUNIONNAMEN(4);
	union {
		DWORD               dwFillColor;
		DWORD               dwFillDepth;
		DWORD               dwFillPixel;
		LPDIRECTDRAWSURFACE lpDDSPattern;
	} DUMMYUNIONNAMEN(5);
	DDCOLORKEY ddckDestColorkey;
	DDCOLORKEY ddckSrcColorkey;
} DDBLTFX, *LPDDBLTFX;

#define DDSCL_EXCLUSIVE 0x1
#define DDSCL_FULLSCREEN 0x2

#define DDLOCK_SURFACEMEMORYPTR 0x1
#define DDLOCK_WAIT 0x2
#define DDLOCK_WRITEONLY 0x4
#define DDERR_WASSTILLDRAWING 0x1
#define DDCKEY_SRCBLT 0x1

struct IDirectDrawPalette {
};
typedef struct IDirectDrawPalette    FAR *LPDIRECTDRAWPALETTE;

struct IDirectDraw7 {
	void RestoreAllSurfaces();
	HRESULT GetAvailableVidMem(LPDDSCAPS2 lpDDSCaps2, LPDWORD lpdwTotal, LPDWORD lpdwFree);
	void Release();
	HRESULT SetCooperativeLevel(HWND hWnd, DWORD dwFlags);
	HRESULT SetDisplayMode(DWORD dwWidth,  DWORD dwHeiight, DWORD dwBPP, DWORD dwRefreshRate,  DWORD dwFlags);
	HRESULT CreateSurface(LPDDSURFACEDESC2 lpDDSurfaceDesc2, LPDIRECTDRAWSURFACE7 FAR *lplpDDSurface, void* unused);
	HRESULT CreatePalette(DWORD dwFlags,LPPALETTEENTRY lpDDColorArray,LPDIRECTDRAWPALETTE FAR *lplpDDPalette,void FAR *pUnkOuter);
};
struct IDirectDrawSurface7 {
	void BltFast(int x, int y, IDirectDrawSurface7* surf, RECT*, int flags);
	bool IsLost();
	void Release();
	HRESULT Restore();
	HRESULT GetSurfaceDesc(DDSURFACEDESC *pSurfaceDesc);
	void Flip(void* unused, int flags);
	HRESULT Blt(LPRECT lpDestRect, LPDIRECTDRAWSURFACE7 lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx);
	HRESULT GetAttachedSurface(LPDDSCAPS2 lpDDSCaps, LPDIRECTDRAWSURFACE7 FAR *lplpDDAttachedSurface);
	HRESULT GetDC(HDC FAR *lphDC);
	HRESULT ReleaseDC(HDC hDC);
	HRESULT Lock(LPRECT lpDestRect, LPDDSURFACEDESC2 lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent);
	HRESULT Unlock(LPRECT lpRect);
	HRESULT SetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey);
	HRESULT GetPixelFormat(LPDDPIXELFORMAT lpDDPixelFormat);
};

#define IID_IDirectDraw7 0
HRESULT WINAPI DirectDrawCreateEx(void* unused1, LPVOID *lplpDD, int unused2, void* unused3);


#endif

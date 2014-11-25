#include "windows.h"
#include "ddraw.h"

void IDirectDraw7::RestoreAllSurfaces() {}
HRESULT IDirectDraw7::GetAvailableVidMem(LPDDSCAPS2 lpDDSCaps2, LPDWORD lpdwTotal, LPDWORD lpdwFree) {}
void IDirectDraw7::Release() {}
HRESULT IDirectDraw7::SetCooperativeLevel(HWND hWnd, DWORD dwFlags) {}
HRESULT IDirectDraw7::SetDisplayMode(DWORD dwWidth,  DWORD dwHeiight, DWORD dwBPP, DWORD dwRefreshRate,  DWORD dwFlags) {}
HRESULT IDirectDraw7::CreateSurface(LPDDSURFACEDESC2 lpDDSurfaceDesc2, LPDIRECTDRAWSURFACE7 FAR *lplpDDSurface, void* unused) {}
HRESULT IDirectDraw7::CreatePalette(DWORD dwFlags,LPPALETTEENTRY lpDDColorArray,LPDIRECTDRAWPALETTE FAR *lplpDDPalette,void FAR *pUnkOuter) {}

void IDirectDrawSurface7::BltFast(int x, int y, IDirectDrawSurface7* surf, RECT*, int flags) {}
bool IDirectDrawSurface7::IsLost() {}
void IDirectDrawSurface7::Release() {}
HRESULT IDirectDrawSurface7::Restore() {}
HRESULT IDirectDrawSurface7::GetSurfaceDesc(DDSURFACEDESC *pSurfaceDesc) {}
void IDirectDrawSurface7::Flip(void* unused, int flags) {}
HRESULT IDirectDrawSurface7::Blt(LPRECT lpDestRect, LPDIRECTDRAWSURFACE7 lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx) {}
HRESULT IDirectDrawSurface7::GetAttachedSurface(LPDDSCAPS2 lpDDSCaps, LPDIRECTDRAWSURFACE7 FAR *lplpDDAttachedSurface) {}
HRESULT IDirectDrawSurface7::GetDC(HDC FAR *lphDC) {}
HRESULT IDirectDrawSurface7::ReleaseDC(HDC hDC) {}
HRESULT IDirectDrawSurface7::Lock(LPRECT lpDestRect, LPDDSURFACEDESC2 lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent) {}
HRESULT IDirectDrawSurface7::Unlock(LPRECT lpRect) {}
HRESULT IDirectDrawSurface7::SetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey) {}
HRESULT IDirectDrawSurface7::GetPixelFormat(LPDDPIXELFORMAT lpDDPixelFormat) {}

HRESULT WINAPI DirectDrawCreateEx(void* unused1, LPVOID *lplpDD, int unused2, void* unused3) {}


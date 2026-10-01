#include "windows.h"
#include "ddraw.h"

void IDirectDraw7::RestoreAllSurfaces() {}
HRESULT IDirectDraw7::GetAvailableVidMem(LPDDSCAPS2 lpDDSCaps2, LPDWORD lpdwTotal, LPDWORD lpdwFree) { return 0; }
void IDirectDraw7::Release() {}
HRESULT IDirectDraw7::SetCooperativeLevel(HWND hWnd, DWORD dwFlags) { return 0; }
HRESULT IDirectDraw7::SetDisplayMode(DWORD dwWidth,  DWORD dwHeiight, DWORD dwBPP, DWORD dwRefreshRate,  DWORD dwFlags) { return 0; }
HRESULT IDirectDraw7::CreateSurface(LPDDSURFACEDESC2 lpDDSurfaceDesc2, LPDIRECTDRAWSURFACE7 FAR *lplpDDSurface, void* unused) { return 0; }
HRESULT IDirectDraw7::CreatePalette(DWORD dwFlags,LPPALETTEENTRY lpDDColorArray,LPDIRECTDRAWPALETTE FAR *lplpDDPalette,void FAR *pUnkOuter) { return 0; }

void IDirectDrawSurface7::BltFast(int x, int y, IDirectDrawSurface7* surf, RECT*, int flags) {}
bool IDirectDrawSurface7::IsLost() { return false; }
void IDirectDrawSurface7::Release() {}
HRESULT IDirectDrawSurface7::Restore() { return 0; }
HRESULT IDirectDrawSurface7::GetSurfaceDesc(DDSURFACEDESC *pSurfaceDesc) { return 0; }
void IDirectDrawSurface7::Flip(void* unused, int flags) {}
HRESULT IDirectDrawSurface7::Blt(LPRECT lpDestRect, LPDIRECTDRAWSURFACE7 lpDDSrcSurface, LPRECT lpSrcRect, DWORD dwFlags, LPDDBLTFX lpDDBltFx) { return 0; }
HRESULT IDirectDrawSurface7::GetAttachedSurface(LPDDSCAPS2 lpDDSCaps, LPDIRECTDRAWSURFACE7 FAR *lplpDDAttachedSurface) { return 0; }
HRESULT IDirectDrawSurface7::GetDC(HDC FAR *lphDC) { return 0; }
HRESULT IDirectDrawSurface7::ReleaseDC(HDC hDC) { return 0; }
HRESULT IDirectDrawSurface7::Lock(LPRECT lpDestRect, LPDDSURFACEDESC2 lpDDSurfaceDesc, DWORD dwFlags, HANDLE hEvent) { return 0; }
HRESULT IDirectDrawSurface7::Unlock(LPRECT lpRect) { return 0; }
HRESULT IDirectDrawSurface7::SetColorKey(DWORD dwFlags, LPDDCOLORKEY lpDDColorKey) { return 0; }
HRESULT IDirectDrawSurface7::GetPixelFormat(LPDDPIXELFORMAT lpDDPixelFormat) { return 0; }

HRESULT WINAPI DirectDrawCreateEx(void* unused1, LPVOID *lplpDD, int unused2, void* unused3) { return 0; }


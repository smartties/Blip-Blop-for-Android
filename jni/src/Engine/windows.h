#ifndef WINDOWS_H
#define WINDOWS_H

#include <cstdlib> // so NULL is defined everywhere

using namespace std;

#define CALLBACK
#define WINAPI
#define __cdecl

///MODIF TYPE
#include <inttypes.h>
#include "asset.h"
#include "log.h"

#define TRUE true
#define FALSE false
#define MAX_PATH 260

typedef unsigned short WORD;
typedef WORD ATOM;
typedef long LONG;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef char CHAR;
typedef bool BOOL;
typedef void VOID;
typedef DWORD *LPDWORD;
typedef unsigned int UINT;
typedef VOID* PVOID;
typedef PVOID LPVOID;
typedef PVOID HANDLE;
typedef LONG HRESULT;
typedef size_t SIZE_T;
#define CONST const
typedef CONST CHAR *LPCSTR;
typedef HANDLE HDC;
typedef HANDLE HWND;
typedef unsigned int UINT_PTR;
typedef UINT_PTR WPARAM;
typedef long LONG_PTR;
typedef unsigned long ULONG_PTR;
typedef long long LONGLONG;
typedef ULONG_PTR DWORD_PTR;
typedef LONG_PTR LPARAM;
typedef LONG_PTR LRESULT;
typedef HANDLE HINSTANCE;
typedef HANDLE HBITMAP;
typedef CHAR *LPSTR;
typedef HANDLE HMENU;
typedef DWORD COLORREF;
typedef HINSTANCE HMODULE;
typedef HANDLE HGDIOBJ;
typedef HANDLE HRSRC;
typedef HANDLE HGLOBAL;
typedef void* LPUNKNOWN;


void stop_music();
void resume_music();

#if defined (WIN32)

#else
typedef int64_t __int64;
#endif

typedef struct _RECT {
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
} RECT, *PRECT, *LPRECT;

typedef struct {
	unsigned long Data1;
	unsigned short Data2;
	unsigned short Data3;
	BYTE Data4[8];
} GUID, UUID, *PGUID;
typedef GUID IID;
typedef IID* REFIID;
typedef GUID* REFGUID;

#ifdef UNICODE
typedef WCHAR TCHAR;
typedef LPCWSTR LPCTSTR;
#else
typedef char TCHAR;
typedef LPCSTR LPCTSTR;
#endif

//typedef union _LARGE_INTEGER {
//	struct {
//		DWORD LowPart;
//		LONG  HighPart;
//	};
//	struct {
//		DWORD LowPart;
//		LONG  HighPart;
//	} u;
//	LONGLONG QuadPart;
//} LARGE_INTEGER, *PLARGE_INTEGER;
typedef int64_t LARGE_INTEGER;

#define CS_HREDRAW 0x1
#define CS_VREDRAW 0x2
typedef long(*WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef struct tagBITMAP {
	LONG   bmType;
	LONG   bmWidth;
	LONG   bmHeight;
	LONG   bmWidthBytes;
	WORD   bmPlanes;
	WORD   bmBitsPixel;
	LPVOID bmBits;
} BITMAP, *PBITMAP;


typedef struct tagWNDCLASS {
	UINT      style;
	WNDPROC   lpfnWndProc;
	int       cbClsExtra;
	int       cbWndExtra;
	HINSTANCE hInstance;
	int     hIcon; //TODO
	int   hCursor; //TODO
	int    hbrBackground; //TODO
	LPCTSTR   lpszMenuName;
	LPCTSTR   lpszClassName;
} WNDCLASS, *PWNDCLASS;

#define DUMMYUNIONNAMEN(x)

typedef struct _POINTL {
	LONG x;
	LONG y;
} POINTL, *PPOINTL;
#define CCHDEVICENAME 32
#define CCHFORMNAME 32
typedef struct _devicemode {
	TCHAR dmDeviceName[CCHDEVICENAME];
	WORD  dmSpecVersion;
	WORD  dmDriverVersion;
	WORD  dmSize;
	WORD  dmDriverExtra;
	DWORD dmFields;
	union {
		struct {
			short dmOrientation;
			short dmPaperSize;
			short dmPaperLength;
			short dmPaperWidth;
			short dmScale;
			short dmCopies;
			short dmDefaultSource;
			short dmPrintQuality;
		};
		struct {
			POINTL dmPosition;
			DWORD  dmDisplayOrientation;
			DWORD  dmDisplayFixedOutput;
		};
	};
	short dmColor;
	short dmDuplex;
	short dmYResolution;
	short dmTTOption;
	short dmCollate;
	TCHAR dmFormName[CCHFORMNAME];
	WORD  dmLogPixels;
	DWORD dmBitsPerPel;
	DWORD dmPelsWidth;
	DWORD dmPelsHeight;
	union {
		DWORD dmDisplayFlags;
		DWORD dmNup;
	};
	DWORD dmDisplayFrequency;
#if (WINVER >= 0x0400)
	DWORD dmICMMethod;
	DWORD dmICMIntent;
	DWORD dmMediaType;
	DWORD dmDitherType;
	DWORD dmReserved1;
	DWORD dmReserved2;
#if (WINVER >= 0x0500) || (_WIN32_WINNT >= 0x0400)
	DWORD dmPanningWidth;
	DWORD dmPanningHeight;
#endif
#endif
} DEVMODE, *PDEVMODE, *LPDEVMODE;

typedef struct tagRGBQUAD {
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
} RGBQUAD;
#define DM_BITSPERPEL 0x1
#define DM_PELSWIDTH 0x2
#define DM_PELSHEIGHT 0x4
#define DM_DISPLAYFREQUENCY 0x8
#define DISP_CHANGE_SUCCESSFUL 0x1
#define CDS_TEST 0x1
#define CDS_FULLSCREEN 0x2
#define MB_OK 0x1
#define MB_ICONERROR 0x2
#define MB_ICONWARNING 0x4
#define MB_YESNO 0x8
#define MB_ICONQUESTION 0x16
#define IDYES 6

#define WS_POPUP 0x1

#define FAR
#define NEAR

enum {
	WM_SETCURSOR,
	WM_ACTIVATE,
	WM_CLOSE,
	WM_DESTROY,
	WM_TIMER,
};

void ZeroMemory(PVOID Destination, SIZE_T Length);

LONG ChangeDisplaySettings(DEVMODE *lpDevMode, DWORD dwflags);
int MessageBox(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);

void SetCursor(void*);
WORD HIWORD(DWORD dwValue);
VOID WINAPI PostQuitMessage(int nExitCode);
LRESULT WINAPI DefWindowProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
ATOM WINAPI RegisterClass(const WNDCLASS *lpWndClass);
#define SM_CXSCREEN 0x1
#define SM_CYSCREEN 0x2
int WINAPI GetSystemMetrics(int nIndex);
HWND WINAPI CreateWindowEx(DWORD dwExStyle, LPCTSTR lpClassName, LPCTSTR lpWindowName, DWORD dwStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam);
BOOL WINAPI ShowWindow(HWND hWnd, int nCmdShow);
BOOL UpdateWindow(HWND hWnd);

typedef VOID(*TIMERPROC)(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
UINT_PTR WINAPI SetTimer(HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc);
BOOL WINAPI DestroyWindow(HWND hWnd);

void Sleep(int);
DWORD WINAPI GetTickCount(void);

COLORREF RGB(BYTE byRed, BYTE byGreen, BYTE byBlue);

HMODULE WINAPI GetModuleHandle(LPCTSTR lpModuleName);

#define IMAGE_BITMAP 0x1
#define LR_CREATEDIBSECTION 0x1
#define LR_LOADFROMFILE 0x2
HANDLE WINAPI LoadImage(HINSTANCE hinst, LPCTSTR lpszName, UINT uType, int cxDesired, int cyDesired, UINT fuLoad);

#define E_FAIL 0x1
int GetObject(HGDIOBJ hgdiobj, int cbBuffer, LPVOID lpvObject);
BOOL DeleteObject(HGDIOBJ hObject);
HDC CreateCompatibleDC(HDC hdc);
HGDIOBJ SelectObject(HDC hdc, HGDIOBJ hgdiobj);

#define SRCCOPY 0x1
BOOL StretchBlt(HDC hdcDest, int nXOriginDest, int nYOriginDest, int nWidthDest, int nHeightDest, HDC hdcSrc, int nXOriginSrc, int nYOriginSrc, int nWidthSrc, int nHeightSrc, DWORD dwRop);

#define CLR_INVALID 0x1
COLORREF GetPixel(HDC hdc, int nXPos, int nYPos);
COLORREF SetPixel(HDC hdc, int X, int Y, COLORREF crColor);
BOOL SetPixelV(HDC hdc, int X, int Y, COLORREF crColor);

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;
	LONG  biWidth;
	LONG  biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG  biXPelsPerMeter;
	LONG  biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;
typedef PBITMAPINFOHEADER LPBITMAPINFOHEADER;
typedef struct tagBITMAPFILEHEADER {
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagPALETTEENTRY {
	BYTE peRed;
	BYTE peGreen;
	BYTE peBlue;
	BYTE peFlags;
} PALETTEENTRY, *LPPALETTEENTRY;

#define RT_BITMAP "BITMAP?"

BOOL DeleteDC(HDC hdc);
LPVOID WINAPI LockResource(HGLOBAL hResData);
HGLOBAL WINAPI LoadResource(HMODULE hModule, HRSRC hResInfo);
HRSRC WINAPI FindResource(HMODULE hModule, LPCTSTR lpName, LPCTSTR lpType);

#define GENERIC_READ 0x1
#define FILE_SHARE_READ 0x2
#define OPEN_EXISTING 0x4
#define FILE_ATTRIBUTE_NORMAL 0x8
#define INVALID_HANDLE_VALUE NULL

typedef struct _OVERLAPPED {
	ULONG_PTR Internal;
	ULONG_PTR InternalHigh;
	union {
		struct {
			DWORD Offset;
			DWORD OffsetHigh;
		};
		PVOID  Pointer;
	};
	HANDLE    hEvent;
} OVERLAPPED, *LPOVERLAPPED;

HANDLE WINAPI CreateFile(LPCTSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, void* unused, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
BOOL WINAPI ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
BOOL WINAPI CloseHandle(HANDLE hObject);
long _filelength(int fd);
DWORD timeGetTime(void);
BOOL WINAPI QueryPerformanceFrequency(LARGE_INTEGER *lpFrequency);
BOOL WINAPI QueryPerformanceCounter(LARGE_INTEGER *lpPerformanceCount);

#define PM_NOREMOVE 0x1
typedef struct tagPOINT {
	LONG x;
	LONG y;
} POINT, *PPOINT;
typedef struct tagMSG {
	HWND   hwnd;
	UINT   message;
	WPARAM wParam;
	LPARAM lParam;
	DWORD  time;
	POINT  pt;
} MSG, *PMSG, *LPMSG;
BOOL WINAPI PeekMessage(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax,UINT wRemoveMsg);
LRESULT WINAPI DispatchMessage(const MSG *lpmsg);
BOOL WINAPI TranslateMessage(const MSG *lpMsg);
BOOL WINAPI GetMessage(LPMSG lpMsg,HWND hWnd,UINT wMsgFilterMin,UINT wMsgFilterMax);

char* _itoa(int value, char* str, int base);

#endif

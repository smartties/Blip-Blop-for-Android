/******************************************************************
*
*
*		----------------
*		   BenDivers.cpp
*		----------------
*
*
*		Fonction très diverses
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------
///MODIF INCLUDE ENGINE
#if defined (WIN32)
#include <windows.h>
#else
#include "Engine/windows.h"
#endif

bool active = false;
bool app_killed = false;
bool want_to_kill_app = false;

//-----------------------------------------------------------------------------

int manageMsg()
{
	MSG		msg;

	if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		if (!GetMessage(&msg, NULL, 0, 0))
			return msg.wParam;
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

//-----------------------------------------------------------------------------

void wait(int t)
{
	unsigned int i = GetTickCount();

	while (GetTickCount() < (i + t));
}



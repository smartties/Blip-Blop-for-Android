
///MODIF INCLUDE ENGINE
#if defined (WIN32)
#include <windows.h>
#else
#include "Engine/windows.h"
#endif

#include "ben_debug.h"

bool		perfTimerOn;
__int64		perfTimerFreq;
__int64		perfTimerStart;
float		perfTimerRes;

void LInitTimer()
{
	// We firstly try to use a performance timer. If no one is available,
	// we'll just use the inaccurate GetTickCount
	//
	if (QueryPerformanceFrequency((LARGE_INTEGER *) &perfTimerFreq)) {
		perfTimerOn = true;
		QueryPerformanceCounter((LARGE_INTEGER *) &perfTimerStart);
		perfTimerRes = (float)((double)1.0 / (double)perfTimerFreq);
		debug << "Performance counter available.\n";
	} else {
		debug << "No performance counter vailable.\n";
		debug << "Warning : using inaccurate timer. Synchronisation may suffer.\n";
		perfTimerOn = false;
	}
}


DWORD LGetTime()
{
	// If we have a properly initialised performance timer, we use it
	//
	if (perfTimerOn) {
		__int64	time;

		QueryPerformanceCounter((LARGE_INTEGER *) &time);

		return DWORD(((time - perfTimerStart) * perfTimerRes) * 10000.0f);
	} else {
		return (GetTickCount() * 10);;
	}
}

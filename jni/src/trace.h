
#ifndef TRACE

#include "globals.h"
#include "ben_debug.h"

#ifdef _DEBUG

#define TRACE if ( total_debug) debug<<(__FILE__)<<" : "<<(__LINE__)<<"\n";

#else

#define TRACE ;

#endif

#endif

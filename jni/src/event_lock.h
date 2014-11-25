/******************************************************************
*
*
*		---------------
*		  EventLock.h
*		---------------
*
*		Classe Evenement Lock
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventLock_
#define _EventLock_

#include "event.h"

class EventLock : public Event
{
public:

	int		cond;
	int		flag;
	int		val;

	virtual void doEvent();
};

#endif

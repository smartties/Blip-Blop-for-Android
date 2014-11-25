/******************************************************************
*
*
*		----------------------
*		  EventPremierPlan.h
*		----------------------
*
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventPremierPlan_
#define _EventPremierPlan_


#include "event.h"
#include "globals.h"


class EventPremierPlan : public Event
{
public:
	int		x;
	int		y;
	int		id_fond;

	virtual void doEvent();
};

#endif

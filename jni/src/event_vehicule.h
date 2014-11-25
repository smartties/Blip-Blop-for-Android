/******************************************************************
*
*
*		-----------------
*		  EventVehicule.h
*		-----------------
*
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventVehicule_
#define _EventVehicule_

#include "event.h"

class EventVehicule : public Event
{
public:

	int		id_vehicule;
	int		x;
	int		y;
	int		dir;

	virtual void doEvent();
};

#endif

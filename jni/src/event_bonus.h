/******************************************************************
*
*
*		--------------------
*		  EventBonus.h
*		--------------------
*
*
*
*		Prosper / LOADED -   5 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventBonus_
#define _EventBonus_


#include "event.h"

#define BPM	0
#define BFUSIL	1
#define BLASER	2
#define BBEER	3
#define BINV	4
#define BTONNO	5
#define BCOW	6
#define BLF		7


class EventBonus : public Event
{
public:
	int		type;
	int		x;
	int		y;

	virtual void doEvent();
};

#endif
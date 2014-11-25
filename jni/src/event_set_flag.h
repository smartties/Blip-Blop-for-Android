/******************************************************************
*
*
*		-------------------
*		  EventSetFlag.h
*		-------------------
*
*		Classe Evenement Set Flag
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventSetFlag_
#define _EventSetFlag_

#include "event.h"

class EventSetFlag : public Event
{
public:

	int		flag;
	int		val;

	virtual void doEvent()
	{
		game_flag[flag] = val;
	};
};

#endif
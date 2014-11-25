/******************************************************************
*
*
*		--------------
*		  EventRPG.h
*		--------------
*
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventRPG_
#define _EventRPG_

#include "event.h"

class EventRPG : public Event
{
public:

	int		num;
	int		flag;
	int		val;
	int		cond;

	inline virtual bool aActiver()
	{
		if (cond == 0)
			return true;
		else
			return (game_flag[flag] == val);
	};

	virtual void doEvent()
	{
		rpg_to_play = num;
	};
};

#endif
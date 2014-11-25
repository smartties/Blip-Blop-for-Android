/******************************************************************
*
*
*		-----------------
*		  EventTexte.h
*		-----------------
*
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#ifndef _EventTexte_
#define _EventTexte_

#include "event.h"
#include "texte_cool.h"
#include "ben_debug.h"

class EventTexte : public Event
{
public:

	int		ntxt;
	int		flag;
	int		val;
	int		cond;

	inline virtual bool aActiver()
	{
		if (cond == 0)
			return true;
		else if (cond == 1)
			return (game_flag[flag] == val);
		else
			return (game_flag[flag] >= val);
	};

	virtual void doEvent()
	{
		TexteCool * txt = new TexteCool();

		txt->ntxt = ntxt;

		list_txt_cool.ajoute((void*) txt);
	};
};

#endif


#ifndef _EventSon_
#define _EventSon_

#include "event.h"

class EventSon : public Event
{
public:

	int		nsnd;

	virtual void doEvent()
	{
		sbk_niveau.play(nsnd);
	};

};

#endif

#include "event_music.h"
#include "globals.h"

void EventMusic::doEvent()
{
	if (play) {
		if (current_zik != -1)
			mbk_niveau.stop(current_zik);

		mbk_niveau.play(id);
		current_zik = id;
	} else {
		mbk_niveau.stop(id);
		current_zik = -1;
	}
}


#include "globals.h"
#include "event_mi_fond.h"
#include "fond_statique.h"

void EventMiFond::doEvent()
{
	Sprite * s = new FondStatique();

	s->x = x;
	s->y = y;
	s->pic = pbk_niveau[id];

	list_fonds_statiques.ajoute((void*) s);
}

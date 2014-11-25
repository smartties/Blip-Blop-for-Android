
#include "event_vehicule.h"
#include "ben_debug.h"
#include "vehicule.h"
//#include "VehiculeHypo.h"
#include "vehivule_cigogne.h"

#define IDVEHICULE_CIGO	0


void EventVehicule::doEvent()
{
	Vehicule * v = NULL;

	switch (id_vehicule) {
		case IDVEHICULE_CIGO:
			v = new VehiculeCigogne();
			break;
	}

	if (v != NULL) {
		v->x = x;
		v->y = y;
		v->dir = dir;

		list_vehicules.ajoute((void*) v);
	} else {
		debug << "Unknown vehicle ID : " << id_vehicule << "\n";
	}
}

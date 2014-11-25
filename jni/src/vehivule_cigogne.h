
#ifndef _VehiculeCigogne_
#define _VehiculeCigogne_

#include "vehicule.h"

class VehiculeCigogne : public Vehicule
{
public:

	bool	hasBeenUsed;

	VehiculeCigogne();

	virtual bool canFire()
	{
		return false;
	};

	virtual bool canChangeDir()
	{
		return false;
	};

	virtual void updateUsed();
	virtual void updateNotUsed();
	virtual void affiche();
};

#endif

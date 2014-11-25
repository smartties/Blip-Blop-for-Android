/******************************************************************
*
*
*		--------------
*		    Blip.h
*		--------------
*
*		Let's rock!
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _Blip_
#define _Blip_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "couille.h"


//-----------------------------------------------------------------------------
//		Definition de la classe Blip
//-----------------------------------------------------------------------------

class Blip : public Couille
{

public:
	Blip()
	{
		pbk_own = pbk_blip.getPix();
		id_couille = ID_BLIP;
	}

	virtual void rearme()
	{
		id_arme = ID_PM;
		ammo = 100;
		latence_arme = 3;
		nb_etape_arme = 5;
		cadence_arme = 5;
		poid_arme = 5;

		etape_arme = 0;
		ss_etape_arme = 0;
		etape_recul = 0;
		tire = false;
	}
};

#endif

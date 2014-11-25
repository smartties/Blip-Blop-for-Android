/******************************************************************
*
*
*		--------------
*		    Blop.h
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

#ifndef _Blop_
#define _Blop_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "couille.h"


//-----------------------------------------------------------------------------
//		Definition de la classe Blop
//-----------------------------------------------------------------------------

class Blop : public Couille
{

public:
	Blop()
	{
		pbk_own = pbk_blop.getPix();
		id_couille = ID_BLOP;
	};

	virtual void rearme()
	{
		id_arme = ID_FUSIL;
		ammo = 10;
		latence_arme = 3;
		nb_etape_arme = 15;
		cadence_arme = 45;
		poid_arme = 1;

		etape_arme = 0;
		ss_etape_arme = 0;
		etape_recul = 0;
		tire = false;
	}
};

#endif

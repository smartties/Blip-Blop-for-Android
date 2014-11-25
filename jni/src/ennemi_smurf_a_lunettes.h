/******************************************************************
*
*
*		-----------------------
*		EnnemiSmurfALunettes.h
*		-----------------------
*		Schtroump de base.
*		Spécificité : Saute plus loin.
*
*		Mortimus / LOADED -   V 0.1 - 26 Octobre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSmurfALunettes_
#define _EnnemiSmurfALunettes_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "ennemi_smurf.h"

//-----------------------------------------------------------------------------
//		Définition de la classe
//-----------------------------------------------------------------------------

class EnnemiSmurfALunettes : public EnnemiSmurf
{
public:

	inline virtual void affiche()
	{
		EnnemiSmurf::affiche() ;
		if (etat != ETAT_MEURE && etat != ETAT_CARBONISE) {
			switch (dir) {
				case SENS_GAUCHE :
					draw(x - 4, y - 27, pbk_ennemis[145]) ;
					break ;
				case SENS_DROITE :
					draw(x + 4, y - 27, pbk_ennemis[146]) ;
					break ;
			}
		}
	}

	virtual void update()
	{
		if (etat == ETAT_SAUTE)
			speed = 2 ;
		else
			speed = 1 ;

		EnnemiSmurf::update() ;
	}
};

#endif
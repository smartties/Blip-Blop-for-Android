/******************************************************************
*
*
*		-----------------------
*		EnnemiSmurfFrileux.h
*		-----------------------
*		Schtroumph de base.
*		Spécificité : Mouvements tremblotants et semi-aléatoires.
*					  Encaisse moins du fait de sa constitution
*					  fragile :-)
*		Mortimus / LOADED -   V 0.1 - 26 Octobre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSmurfFrileux_
#define _EnnemiSmurfFrileux_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "ennemi_smurf.h"

//-----------------------------------------------------------------------------
//		Définition de la classe
//-----------------------------------------------------------------------------

class EnnemiSmurfFrileux : public EnnemiSmurf
{
public:

	EnnemiSmurfFrileux()
	{
		pv = 75 ;
	}

	inline virtual void affiche()
	{
		if (etat != ETAT_MEURE && etat != ETAT_CARBONISE) {
			switch (dir) {
				case SENS_GAUCHE :
					draw(x + 7, y - 18, pbk_ennemis[147]) ;
					EnnemiSmurf::affiche() ;
					draw(x, y - 20, pbk_ennemis[149]) ;
					break ;
				case SENS_DROITE :
					draw(x - 7, y - 18, pbk_ennemis[148]) ;
					EnnemiSmurf::affiche() ;
					draw(x, y - 20, pbk_ennemis[150]) ;
					break ;
			}
		} else
			EnnemiSmurf::affiche() ;
	}

	virtual void onAvance()
	{
		speed = 1 + rand() % 3 ;
		EnnemiSmurf::onAvance() ;
	}
};

#endif
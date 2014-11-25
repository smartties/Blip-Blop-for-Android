/******************************************************************
*
*
*		-----------------------
*		EnnemiSmurfCoquet.h
*		-----------------------
*		Schtroumph de base.
*		Spécificité : Saute (beaucoup !) plus haut.
*					  Vitesse tirée aléatoirement à la création.
*
*		Mortimus / LOADED -   V 0.1 - 26 Octobre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSmurfCoquet_
#define _EnnemiSmurfCoquet_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "ennemi_smurf.h"

//-----------------------------------------------------------------------------
//		Définition de la classe
//-----------------------------------------------------------------------------

class EnnemiSmurfCoquet : public EnnemiSmurf
{
public:

	EnnemiSmurfCoquet()
	{
		dy_saut = -6 ;
		speed = 1 + rand() % 2 ;
	}

	inline virtual void affiche()
	{
		EnnemiSmurf::affiche() ;
		if (etat != ETAT_MEURE && etat != ETAT_CARBONISE) {
			switch (dir) {
				case SENS_GAUCHE :
					draw(x + 3, y - 31, pbk_ennemis[151]) ;
					break ;
				case SENS_DROITE :
					draw(x - 3, y - 31, pbk_ennemis[151]) ;
					break ;
			}
		}
	}
};

#endif
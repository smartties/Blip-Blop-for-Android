/******************************************************************
*
*
*		--------------------
*		EnnemiSmurfPaysan.h
*		--------------------
*
*		Burn ! Burn ! Burn !
*
*
*		Mortimus / LOADED -   V 0.1 - 22 Octobre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSmurfPaysan_
#define _EnnemiSmurfPaysan_

#define SMURF_PAYSAN_SPEED		4
//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSmurf
//-----------------------------------------------------------------------------

class EnnemiSmurfPaysan : public Ennemi
{
public:
	int		tete_ss_etape ;
	int		tete_etape ;
	int		x_mort ;
	int		y_mort ;

	EnnemiSmurfPaysan();

	inline virtual void affiche()
	{
		Ennemi::affiche() ;
		if (etat == ETAT_MEURE && tete_etape < 5) {
			if (dir == SENS_GAUCHE)
				draw(x_mort, y_mort, pbk_ennemis[169 + tete_etape]) ;
			else
				draw(x_mort, y_mort, pbk_ennemis[164 + tete_etape]) ;
		}
	}

	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onCarbonise();

	virtual void estTouche(Tir * tir);
};

#endif
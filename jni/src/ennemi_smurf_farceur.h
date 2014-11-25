/******************************************************************
*
*
*		--------------------
*		EnnemiSmurfFarceur.h
*		--------------------
*
*		Le poseur de bombes
*
*
*		Mortimus / LOADED -   V 0.1 - 18 Octobre 2000
*
*
*
******************************************************************/

#ifndef _EnnemiSmurfFarceur_
#define _EnnemiSmurfFarceur_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define SMURF_FARCEUR_SPEED		2
#define ETAT_DEGAINE			11

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSmurf
//-----------------------------------------------------------------------------

const int anim_smurf_marche_droite[] = { 0, 1, 2, 3, 4, 3, 2, 1 };
const int anim_smurf_marche_gauche[] = { 5, 6, 7, 8, 9, 8, 7, 6 };

class EnnemiSmurfFarceur : public Ennemi
{
public:
	bool porte_bomb ;
	int new_bomb_delay ;
	int wait_for_new_bomb ;
	int bomb_delay ;
	int wait_for_bomb ;
	int decalage_y_cadeau ;

	EnnemiSmurfFarceur();

	inline virtual void affiche()
	{
		if (porte_bomb) {
			if (dir == SENS_DROITE)
				draw(x + 26, y - decalage_y_cadeau, pbk_ennemis[56]);
			else
				draw(x - 26, y - decalage_y_cadeau, pbk_ennemis[56]);
		}

		draw(x, y, pic) ;
	};

	virtual void update();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onCarbonise();
	virtual void estTouche(Tir * tir);
	virtual void onPoseCadeau();
	virtual void onDegaine();
};

#endif
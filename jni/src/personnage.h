/******************************************************************
*
*
*		-------------------
*		    Personnage.h
*		-------------------
*
*		Ennemis / joueurs
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _Personnage_
#define _Personnage_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "sprite.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define ETAT_AVANCE		0
#define ETAT_SAUTE		1
#define ETAT_TOMBE		2
#define ETAT_TIRE		3
#define ETAT_MEURE		4
#define ETAT_ATTEND		5
#define ETAT_NORMAL		6
#define ETAT_CARBONISE	7
#define ETAT_BRULE		8
#define ETAT_COME_BACK	9
#define ETAT_SALETO		10
#define ETAT_MEURE_2	11
#define ETAT_MEURE_3	12
#define ETAT_MEURE_4	13
#define ETAT_LOCKEDV	14

#ifndef SENS
#define SENS_GAUCHE		0
#define SENS_DROITE		1
#endif
//-----------------------------------------------------------------------------
//		Définition de la classe Personnage
//-----------------------------------------------------------------------------

class Personnage : public Sprite
{
public:
	int		pv;
	int		etat;

	Personnage();

	virtual void update();
};

#endif

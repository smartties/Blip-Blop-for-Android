/******************************************************************
*
*
*		----------------
*		    TirBB.h
*		----------------
*
*		Pour les tirs de Blip/Blop
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _TirBB_
#define _TirBB_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "joueur.h"
#include "tir.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#ifndef _BBCONST_
#define _BBCONST_

#define BBDIR_BAS_B_D		0
#define BBDIR_BAS_D			1
#define BBDIR_BAS_DROITE	2
#define BBDIR_DROITE_B		3
#define BBDIR_DROITE		4
#define BBDIR_DROITE_H		5
#define BBDIR_HAUT_DROITE	6
#define BBDIR_HAUT_D		7
#define BBDIR_HAUT_H_D		8
#define BBDIR_HAUT_H_G		9
#define BBDIR_HAUT_G		10
#define BBDIR_HAUT_GAUCHE	11
#define BBDIR_GAUCHE_H		12
#define BBDIR_GAUCHE		13
#define BBDIR_GAUCHE_B		14
#define BBDIR_BAS_GAUCHE	15
#define BBDIR_BAS_G			16
#define BBDIR_BAS_B_G		17

#define BBLIM_DROITE		8

#define ID_M16		0
#define ID_FUSIL	1
#define ID_PM		2
#define ID_LF		3
#define ID_LASER	4

#define ID_BLIP		0
#define ID_BLOP		1

#endif

//-----------------------------------------------------------------------------
//		Définition de la classe Tir
//-----------------------------------------------------------------------------

class TirBB : public Tir
{
public:
	Joueur *	joueur;
	int			dxReferentiel;

	float angle;
    bool hasangle;

	TirBB() : dxReferentiel(0), angle(0), hasangle(0) {};
	virtual int degats() const = 0;
	virtual int enflame() const = 0;

	virtual void aTue()
	{
		joueur->addKilled();
	};

	inline virtual void aTouche(int pts)
	{
		a_detruire = true;
		col_on = false;
		joueur->addPoints(pts);
	};


	virtual void setDir(int d);

};

#endif

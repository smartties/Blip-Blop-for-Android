/******************************************************************
*
*
*		---------------------------
*		    MorceauxTeteSnorky.h
*		---------------------------
*
*		Les bouts de tete qui giclent...
*		Le cadavre de l'hyporider qui tombe
*
*
*		Mephisto / LOADED -   V 0.2 - 18 Decembre 2000
*
*
*
******************************************************************/

#ifndef _MorceauxTeteSnorky_
#define _MorceauxTeteSnorky_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "sprite.h"


//-----------------------------------------------------------------------------
//		Définition de la classe MorceauSnorkyBaseTeteEntiere
//-----------------------------------------------------------------------------

class MorceauSnorkyBaseTeteEntiere : public Sprite
{
public:

	MorceauSnorkyBaseTeteEntiere();

	virtual void update();
};


//-----------------------------------------------------------------------------
//		Définition de la classe MorceauSnorkyBaseTetePartieArriere
//-----------------------------------------------------------------------------

class MorceauSnorkyBaseTetePartieArriere : public Sprite
{
public:

	int dx;

	MorceauSnorkyBaseTetePartieArriere(int vx, int vy);

	virtual void update();
};


//-----------------------------------------------------------------------------
//		Définition de la classe MorceauSnorkyHyporidercorp
//-----------------------------------------------------------------------------

class MorceauSnorkyHyporidercorp : public Sprite
{
public:

	int dx;

	MorceauSnorkyHyporidercorp(int vx);

	virtual void update();
};


//-----------------------------------------------------------------------------
//		Définition de la classe MorceauSnorkyBaseTrompe
//-----------------------------------------------------------------------------

class MorceauSnorkyBaseTrompe : public Sprite
{
public:

	int dx;

	MorceauSnorkyBaseTrompe(int vx, int vy);

	virtual void update();
};

#endif

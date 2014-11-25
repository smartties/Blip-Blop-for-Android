/******************************************************************
*
*
*		----------------
*		  ControlP1.h
*		----------------
*
*		Classe ControlorP1
*
*		Sert d'intermédiaire entre Blip/Blop et le joueur 1
*
*
*		Prosper / LOADED -   V 0.1
*
*
*
******************************************************************/

#ifndef _ControlP1_
#define _ControlP1_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "input.h"
#include "controlor.h"
#include "control_alias.h"

//-----------------------------------------------------------------------------
//		Définition de la classe ControlP1
//-----------------------------------------------------------------------------

class ControlP1 : public Controlor
{
protected:
public:
	virtual int gauche() const
	{
	    ///MODIF ctrl
		//return in.scanAlias(ALIAS_P1_LEFT);
		return in.gauche;
	};

	virtual int haut() const
	{
	    ///MODIF ctrl
		//return in.scanAlias(ALIAS_P1_UP);
		return in.haut;
	};

	virtual int droite() const
	{
	    ///MODIF ctrl
		//return in.scanAlias(ALIAS_P1_RIGHT);
		return in.droit;
	};

	virtual int bas() const
	{
	    ///MODIF ctrl
		//return in.scanAlias(ALIAS_P1_DOWN);
		return in.bas;
	};

	virtual int fire() const
	{
	    ///MODIF ctrl
		//return in.scanAlias(ALIAS_P1_FIRE);
		return in.tirer;
	};

	virtual int saut() const
	{
	    ///MODIF ctrl
		//return in.scanAlias(ALIAS_P1_JUMP);
		return in.sauter;
	};

	virtual int super() const
	{
	    ///MODIF ctrl
		//return in.scanAlias(ALIAS_P1_SUPER);
		return in.ulti;
	};
};


#endif


/******************************************************************
*
*
*		----------------
*		  ControlP2.h
*		----------------
*
*		Classe ControlorP2
*
*		Sert d'intermédiaire entre Blip/Blop et le joueur 1
*
*
*		Prosper / LOADED -   V 0.1
*
*
*
******************************************************************/

#ifndef _ControlP2_
#define _ControlP2_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "input.h"
#include "controlor.h"
#include "control_alias.h"

//-----------------------------------------------------------------------------
//		Définition de la classe ControlP2
//-----------------------------------------------------------------------------

class ControlP2 : public Controlor
{
protected:
public:
	virtual int gauche() const
	{
		return in.scanAlias(ALIAS_P2_LEFT);
	};

	virtual int haut() const
	{
		return in.scanAlias(ALIAS_P2_UP);
	};

	virtual int droite() const
	{
		return in.scanAlias(ALIAS_P2_RIGHT);
	};

	virtual int bas() const
	{
		return in.scanAlias(ALIAS_P2_DOWN);
	};

	virtual int fire() const
	{
		return in.scanAlias(ALIAS_P2_FIRE);
	};

	virtual int saut() const
	{
		return in.scanAlias(ALIAS_P2_JUMP);
	};

	virtual int super() const
	{
		return in.scanAlias(ALIAS_P2_SUPER);
	};
};


#endif


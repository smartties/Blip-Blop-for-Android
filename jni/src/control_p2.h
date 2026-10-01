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

// Player 2 plays with the second game controller (see Input::update), or
// with the keyboard keys of the original game (config.cpp
// set_default_config: Q S D F = up down left right, TAB = fire, G = jump,
// H = cow bomb). The keyboard keys of player 1 (Input key_map) never drive
// player 2.
class ControlP2 : public Controlor
{
protected:
public:
	virtual int gauche() const
	{
		return in.padHeld(1, ACT_LEFT) || in.scanAlias(ALIAS_P2_LEFT);
	};

	virtual int haut() const
	{
		return in.padHeld(1, ACT_UP) || in.scanAlias(ALIAS_P2_UP);
	};

	virtual int droite() const
	{
		return in.padHeld(1, ACT_RIGHT) || in.scanAlias(ALIAS_P2_RIGHT);
	};

	virtual int bas() const
	{
		return in.padHeld(1, ACT_DOWN) || in.scanAlias(ALIAS_P2_DOWN);
	};

	virtual int fire() const
	{
		return in.padHeld(1, ACT_FIRE) || in.scanAlias(ALIAS_P2_FIRE);
	};

	virtual int saut() const
	{
		return in.padHeld(1, ACT_JUMP) || in.scanAlias(ALIAS_P2_JUMP);
	};

	virtual int super() const
	{
		return in.ulti2 || in.scanAlias(ALIAS_P2_SUPER);
	};
};


#endif


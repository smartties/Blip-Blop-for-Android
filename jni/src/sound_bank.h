/******************************************************************
*
*
*		---------------
*		  SoundBank.h
*		---------------
*
*		Classe SoundBank
*
*		Représente un tableau/une banque de sons (Sound).
*
*
*		Prosper / LOADED -   V 0.1 - 16 Juillet 2000
*
*
*
******************************************************************/

#ifndef _SoundBank_
#define _SoundBank_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "sound.h"
#include "asset.h"


//-----------------------------------------------------------------------------
//		Définition de la classe SoundBank
//-----------------------------------------------------------------------------

class SoundBank
{
protected:
	Sound **	tab;
	int			nb_snd;
	char *		nom_f;

public:
	SoundBank();
	~SoundBank();

	inline Sound * operator[](int n) const
	{
		return tab[n];
	};
	inline Sound ** getTab(int n) const
	{
		return tab;
	};
	inline int getSize() const
	{
		return nb_snd;
	};

	virtual bool loadSFX(const char * nom_fic);

	void close();
	void reload();
	void reinit();
};

#endif







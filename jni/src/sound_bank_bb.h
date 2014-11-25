/******************************************************************
*
*
*		-----------------
*		  SoundBankBB.h
*		-----------------
*
*		Classe SoundBankBB
*
*		Cette classe est presque identique à la classe SoundBank.
*		Elle ne fait qu'ajouter le fait qu'on puisse avoir le son
*		on/off. (cf. config.h)
*
*
*		Prosper / LOADED -   V 0.1 - 16 Juillet 2000
*
*
*
******************************************************************/

#ifndef _SoundBankBB_
#define _SoundBankBB_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "sound_bank.h"

//-----------------------------------------------------------------------------
//		Définition de la classe SoundBank
//-----------------------------------------------------------------------------

class SoundBankBB : public SoundBank
{
public:

	void play(int n, int flags = 0);
	void stop(int n);
	void setVolume(int n, int vol);

	virtual bool loadSFX(const char * nom_fic);

};

#endif







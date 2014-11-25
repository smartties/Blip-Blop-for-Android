/******************************************************************
*
*
*		-------------------
*		  SoundBankBB.cpp
*		-------------------
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

#include <string.h>
#include "sound_bank_bb.h"
#include "config.h"
#include "ben_debug.h"

void SoundBankBB::play(int n, int flags)
{
	if (!sound_on)
		return;

	if (n >= nb_snd) {
		debug << "Tentative de jouer son " << n << "\n";
		return;
	}

	tab[n]->play(flags);
}


void SoundBankBB::setVolume(int n, int vol)
{
	if (!sound_on)
		return;

	tab[n]->setVolume(vol);
}


void SoundBankBB::stop(int n)
{
	if (!sound_on)
		return;

	tab[n]->stop();
}


bool SoundBankBB::loadSFX(const char * nom_fic)
{
	if (!sound_on) {
		if (nom_f != NULL)
			delete [] nom_f;

		nom_f = new char[strlen(nom_fic) + 1];
		strcpy(nom_f, nom_fic);

		return true;
	}

	return SoundBank::loadSFX(nom_fic);
}

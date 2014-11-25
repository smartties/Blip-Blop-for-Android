/******************************************************************
*
*
*		------------------
*		  SoundBank.cpp
*		------------------
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

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <malloc.h>
///MODIF INCLUDE ENGINE
#include "Engine/io.h"

#include <fcntl.h>
#include <string.h>
#include "ben_debug.h"
#include "sound_bank.h"
#include "sound.h"

//-----------------------------------------------------------------------------
//		Méthodes
//-----------------------------------------------------------------------------

SoundBank::SoundBank() : tab(NULL), nb_snd(0), nom_f(NULL)
{
}


SoundBank::~SoundBank()
{
	if (nom_f != NULL) {
		delete [] nom_f;
		nom_f = NULL;
	}

	if (tab != NULL)
		debug << "SoundBank non desallouée\n";
}



void SoundBank::close()
{
	if (tab == NULL)
		return;

	for (int i = 0; i < nb_snd; i++) {
		delete tab[i];
	}

	delete [] tab;
	tab = NULL;
	nb_snd = 0;
}


void SoundBank::reload()
{
	if (nom_f != NULL) {
		loadSFX(nom_f);
	}
}

void SoundBank::reinit()
{
	if (nom_f != NULL) {
		delete [] nom_f;
		nom_f = NULL;
	}
}


bool SoundBank::loadSFX(const char * nom_fic)
{
	int		fhh;		// File Handle
	int		n_buff;	// Nombre de buffers
	int		taille;	// Taille d'un WAV
	void *	ptr;

	LOGI("LOAD %s", nom_fic);

	if (tab != NULL) {
		debug << "SoundBank::loadSFX() -> SoundBank déjà ouverte!\n";
		return false;
	}

	///MODIF open
	//fhh = _open(nom_fic, _O_RDONLY | _O_BINARY);
	Parseur parseur;

	///MODIF open
	//if (fhh == -1) {
	if( parseur.open(nom_fic) == false) {
		debug << "SoundBank::loadSFX() -> Impossible d'ouvrir le fichier " << nom_fic << "\n";
		return false;
	}

	///MODIF read
	//_read(fhh, &nb_snd, sizeof(nb_snd));
	parseur.read(&nb_snd, sizeof(nb_snd));

	if (nb_snd < 1) {
		debug << "SoundBank::loadSFX() -> Fichier " << nom_fic << " corrompu\n";

		///MODIF close
		//_close(fhh);
		parseur.close();
		return false;
	}


	tab = new Sound * [nb_snd];


	for (int i = 0; i < nb_snd; i++) {

	    ///MODIF read
		//_read(fhh, &n_buff, sizeof(n_buff));	// Nombre de buffers
		//_read(fhh, &taille, sizeof(taille));	// Taille
		parseur.read(&n_buff, sizeof(n_buff));
		parseur.read(&taille, sizeof(taille));


		ptr = malloc(taille);

		if (ptr == NULL) {
			debug << "SoundBank::loadSFX() -> Pas assez de mémoire\n";
			_close(fhh);
			return false;
		}

		// Copie le schnuf en mémoire
		//
		///MODIF read
		//_read(fhh, ptr, taille);
		parseur.read(ptr, taille);

		tab[i] = new Sound;
		tab[i]->loadFromMem(ptr, taille);


		free(ptr);
	}

	///MODIF close
	//_close(fhh);
	parseur.close();

	if (nom_f != NULL)
		delete [] nom_f;

	nom_f = new char[strlen(nom_fic) + 1];
	strcpy(nom_f, nom_fic);

	return true;
}

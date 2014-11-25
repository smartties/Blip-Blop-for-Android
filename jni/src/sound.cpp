/******************************************************************
*
*
*		----------------
*		  Sound.cpp
*		----------------
*
*
*		Classe "Sound" pour gérer les sons
*
*
*		Prosper / LOADED -   V 0.1
*
*
*
******************************************************************/


//-----------------------------------------------------------------------------
//		Protection pour éviter de déclarer 'dsound' 2 fois (1 fois dans le .h)
//-----------------------------------------------------------------------------

#define BENSOUND_CPP_FILE

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

///MODIF INCLUDE ENGINE
#include "Engine/io.h"
#include <fcntl.h>
#include "ben_debug.h"
#include "sound.h"


//-----------------------------------------------------------------------------
//		Constructeur
//-----------------------------------------------------------------------------

Sound::Sound() : sample(NULL), channel(-1)
{
}

//-----------------------------------------------------------------------------
//		Constructeur
//-----------------------------------------------------------------------------

Sound::~Sound()
{
	close();
}

//-----------------------------------------------------------------------------
// Nom: Sound::load(const char * fic, int n)
// Desc: Load un fichier .WAV de nom 'fic'. Ce fichier peut être joué
//		 simultanément 'n' fois. Remarque : il prend également 'n' fois
//		 sa taille en mémoire !!!
//-----------------------------------------------------------------------------

bool Sound::load(const char * fic)
{
	sample = FSOUND_Sample_Load(FSOUND_FREE, fic, FSOUND_LOOP_OFF, 0);

	if (sample == NULL)
		return false;

	return true;
}

//-----------------------------------------------------------------------------
// Nom: Sound::load(void * ptr, int n)
// Desc: Load un fichier .WAV de nom 'fic'. Le fichier est déjà ouvert
//		 et son contenu copié en mémoire
//-----------------------------------------------------------------------------

bool Sound::loadFromMem(void * ptr, int taille)
{
    LOGI("LOAD %d", ptr);
	sample = FSOUND_Sample_Load(FSOUND_FREE, (char*)ptr, FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, taille);

	if (sample == NULL) {
		debug << "Sound::loadFromMem\n";
		LOGI("FAIL load");
		return false;
	}

	channel = -1;
	cpt_loop = 0;
	LOGI("SUCCES");


	return true;
}


//-----------------------------------------------------------------------------
// Nom: Sound::play(int flags)
// Desc: Joue le son avec des drapeaux
//-----------------------------------------------------------------------------

void Sound::play(int flags)
{
	if (flags & SOUND_LOOP) {
		FSOUND_Sample_SetLoopMode(sample, FSOUND_LOOP_NORMAL);

		if (cpt_loop++ == 0) {
			channel = FSOUND_PlaySound(FSOUND_FREE, sample);
		}
	} else {
		FSOUND_Sample_SetLoopMode(sample, FSOUND_LOOP_OFF);
		channel = FSOUND_PlaySound(FSOUND_FREE, sample);
	}
	LOGI("play sound %d", flags);
}

//-----------------------------------------------------------------------------
// Nom: Sound::setVolume(int v)
// Desc: Règle le volume. 'v' doit être négatif et représente l'atténuation
//		 en 100ième de décibels (conseil : utiliser les constantes)
//-----------------------------------------------------------------------------

void Sound::setVolume(int v)
{
}

//-----------------------------------------------------------------------------
// Nom: Sound::stop()
// Desc: Arrête le son. Il recommencera alors au début au prochain départ
//-----------------------------------------------------------------------------

void Sound::stop()
{
	if (channel != -1) {
		if (cpt_loop > 0) {
			if (--cpt_loop == 0) {
				FSOUND_StopSound(channel);
				channel = -1;
			}
		} else {
			FSOUND_StopSound(channel);
			channel = -1;
		}
	}
}

//-----------------------------------------------------------------------------
// Nom: Sound::close()
// Desc: Referme le tout
//-----------------------------------------------------------------------------

void Sound::close()
{
	FSOUND_Sample_Free(sample);
}







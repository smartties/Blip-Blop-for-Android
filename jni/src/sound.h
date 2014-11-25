/******************************************************************
*
*
*		----------------
*		   Sound.h
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


#ifndef _Sound_
#define _Sound_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

///MODIF INCLUDE
#include "fmod/fmod.h"
#include "log.h"

#define SOUND_LOOP		1


//-----------------------------------------------------------------------------
//		Définition de la classe Sound
//-----------------------------------------------------------------------------

class Sound
{
protected:

	FSOUND_SAMPLE * sample;

	int		channel;
	int		cpt_loop;

public:
	Sound();
	~Sound();

	bool load(const char * fic);
	bool loadFromMem(void * ptr, int taille);
	void play(int flags = 0);
	void setVolume(int v);
	void stop();
	void close();

};

/*
//-----------------------------------------------------------------------------
//		Prototypes des fonctions sonores associées
//-----------------------------------------------------------------------------

bool DSOpenDirectSound(HWND wh, int coop = DSSCL_PRIORITY);
bool DSCreatePrimary(int f = 44100, int nb = 16);
void DSCloseDirectSound();

//-----------------------------------------------------------------------------
//		Objet Direct Sound global et Primary buffer
//-----------------------------------------------------------------------------

#ifndef BENSOUND_CPP_FILE
	extern IDirectSound *		dsound;
	extern IDirectSoundBuffer *	PrimarySBuffer;
#endif
*/
#endif

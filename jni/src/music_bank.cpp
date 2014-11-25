
#include <fstream>
#include <stdio.h>
///MODIF INCLUDE ENGINE
#include "Engine/io.h"
#include <fcntl.h>
#include <stdlib.h>
#include "music_bank.h"
///MODIF INCLUDE
#include "fmod/fmod__errors.h"
#include "ben_debug.h"
#include "config.h"

#define TYPE_MOD	0
#define TYPE_MP3	1

#define MAX_ZIK		10

MusicManager musicmanager;

MusicBank::MusicBank() : nb_musiques(0), type(NULL), playing(NULL), tab_old(NULL),
	mp3(NULL), mod(NULL), channel(NULL)
{
    musicmanager.add(this);
}

MusicBank::~MusicBank()
{
	if (nb_musiques > 0) {
		debug << "MusicBank non desallouée\n";
		close();
	}
	musicmanager.erase(this);
}

bool MusicBank::open(const char * file, bool loop)
{
	if (!music_on)
		return true;

	char		buffer[200];

	///MODIF ifstream
	//ifstream	f;
	istringstream f;

	LOGI("OPEN SOUND");

	///MODIF open
	//f.open(file, ios::in);

	///MODIF is_open
	//if (f.is_open() == 0) {
	if( AAsset_istringstream(file, f) == false ) {
		debug << "MusicBank::load() -> Impossible d'ouvrir le fichier " << file << "\n";
		LOGI("A");
		return false;
	}

	f >> nb_musiques;

	if (nb_musiques < 1) {
	    ///MODIF close
		//f.close();
		f.str("");
		f.clear();

		debug << "MusicBank::load() -> Fichier " << file << " corrompu (" << nb_musiques << ")\n";
		LOGI("B");
		return false;
	}

	type = new int[nb_musiques];
	playing = new bool [nb_musiques];
	tab_old = new bool [nb_musiques];
//	mp3 = new FSOUND_SAMPLE * [nb_musiques];
	mp3 = new FSOUND_STREAM * [nb_musiques];
	mod = new FMUSIC_MODULE * [nb_musiques];
	channel = new int [nb_musiques];
	///MODIF SOUND
	mp3Data = new void * [nb_musiques];


	for (int i = 0; i < nb_musiques; i++) {
		f >> type[i];
		f >> buffer;

		if (type[i] == TYPE_MOD) {
			if ((mod[i] = FMUSIC_LoadSong(buffer)) == 0) {
				///MODIF close
	         	//f.close();
	        	f.str("");
		        f.clear();

				debug << "MusicBank::load() -> Ne peut pas charger le MOD " << buffer << "\n";
				nb_musiques = i;
				close();
				LOGI("C");
				return false;
			}
		} else { // TYPE_MP3
		    ///MODIF sound
			//mp3Data[i] = NULL;

			///MODIF fopen
			//FILE * ff2 = fopen(buffer, "rb");
			Parseur parseur;

			//if (ff2 == NULL) {
			if( parseur.open(buffer) == false) {
				///MODIF close
		        //f.close();
		        f.str("");
		        f.clear();

				debug << "MusicBank::load() -> Ne peut pas charger le MP3 " << buffer << "\n";
				nb_musiques = i;
				close();
				LOGI("-%s- not found", buffer);

				return false;
			}
			int size = parseur.length; //inutile sur android
			parseur.close();

			///MODIF SOUND
			/*fseek(ff2, 0, SEEK_END);
			int size = ftell(ff2);
			fseek(ff2, 0, SEEK_SET);
			mp3Data[i] = malloc(size);
			fread(mp3Data[i], size, 1, ff2);
			fflush(ff2);
			fclose(ff2);*/



			if (loop) {
				//mp3[i] = FSOUND_Sample_Load( FSOUND_FREE, (char*)mp3Data[i], FSOUND_LOADMEMORY | FSOUND_LOOP_NORMAL, size);
#ifdef _WIN32
				mp3[i] = FSOUND_Stream_OpenFile((char*)mp3Data[i], FSOUND_LOADMEMORY | FSOUND_LOOP_NORMAL, size);
#else
				mp3[i] = FSOUND_Stream_OpenFile(buffer, FSOUND_LOADMEMORY | FSOUND_LOOP_NORMAL, size);
#endif
			} else {
				//mp3[i] = FSOUND_Sample_Load( FSOUND_FREE, (char*)mp3Data[i], FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, size);
#ifdef _WIN32
				mp3[i] = FSOUND_Stream_OpenFile((char*)mp3Data[i], FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, size);
#else
				mp3[i] = FSOUND_Stream_OpenFile(buffer, FSOUND_LOADMEMORY | FSOUND_LOOP_OFF, size);
#endif
			}

			if (mp3[i] == NULL) {
				debug << "Cannot stream " << buffer << " FMOD Error :" << FMOD_ErrorString(FSOUND_GetError()) << "\n";
			}

			/*
			if ( loop)
			{
				if ((mp3[i] = FSOUND_Sample_LoadMpeg( FSOUND_FREE, buffer, FSOUND_LOOP_NORMAL)) == 0)
				{
					f.close();
					debug<<"MusicBank::load() -> Ne peut pas charger le MP3 "<<buffer<<"\n";
					nb_musiques = i;
					close();
					return false;
				}
			}
			else
			{
				if ((mp3[i] = FSOUND_Sample_LoadMpeg( FSOUND_FREE, buffer, FSOUND_LOOP_OFF)) == 0)
				{
					f.close();
					debug<<"MusicBank::load() -> Ne peut pas charger le MP3 "<<buffer<<"\n";
					nb_musiques = i;
					close();
					return false;
				}
			}
			*/
		}
		tab_old[i] = false;
		playing[i] = false;
	}

	///MODIF close
    //f.close();
    f.str("");
    f.clear();
    LOGI("SUCCES");
	return true;
}

void MusicBank::close()
{
	for (int i = 0; i < nb_musiques; i++) {
		if (type[i] == TYPE_MOD) {
			FMUSIC_FreeSong(mod[i]);
		} else {
			//FSOUND_Sample_Free(mp3[i]);
			FSOUND_Stream_Close(mp3[i]);
			///MODIF SOUND
			//if (mp3Data[i] != NULL)
            //free(mp3Data[i]);
		}
	}

	nb_musiques = 0;

	if (type != NULL) {
		delete [] type;
		type = NULL;
	}

	if (mod != NULL) {
		delete [] mod;
		mod = NULL;
	}

	if (mp3 != NULL) {
		delete [] mp3;
		mp3 = NULL;
	}
	///MODIF SOUND
	//if (mp3Data != NULL) {
		//delete [] mp3Data;
		//mp3Data = NULL;
	//}

	if (playing != NULL) {
		delete [] playing;
		playing = NULL;
	}

	if(tab_old != NULL) {
	    delete [] tab_old;
	    tab_old = NULL;
	}

	if (channel != NULL) {
		delete [] channel;
		channel = NULL;
	}
}

void MusicBank::play(int n)
{
	if (!music_on)
		return;

	if (n < 0 || n >= nb_musiques) {
		debug << "MusicBank::play() -> Tentative de jouer une musique non chargée : " << n << "\n";
		return;
	}

	if (type[n] == TYPE_MOD)
		FMUSIC_PlaySong(mod[n]);
	else {
//		channel[n] = FSOUND_PlaySound( 0, mp3[n]);
		channel[n] = FSOUND_Stream_Play(0, mp3[n]);
	}

	playing[n] = true;
}


void MusicBank::stop(int n)
{
	if (!music_on)
		return;

	if (n < 0 || n >= nb_musiques) {
		debug << "MusicBank::stop() -> Tentative de stoper une musique non chargée : " << n << "\n";
		LOGI("fail to stop");
		return;
	}

	if (!playing[n])
		return;

	if (type[n] == TYPE_MOD)
	{
	    LOGI("STOP SONG");
	    FMUSIC_StopSong(mod[n]);
	}

	else
	{
	    LOGI("STOP MP3");
	    FSOUND_Stream_Stop(mp3[n]);
	}
//		FSOUND_StopSound( channel[n]);

	playing[n] = false;
}

void MusicBank::stop()
{
	for (int i = 0; i < nb_musiques; i++) {
		if (playing[i])
		{
		    stop(i);
		    tab_old[i] = true;
		}
	}
}

void MusicBank::play()
{
    for(int i = 0; i <  nb_musiques; i++)
    {
        if(tab_old[i])
        {
            tab_old[i] = false;
            play(i);
        }
    }
}

void MusicBank::setVol(int v)
{
	if (!music_on)
		return;

	for (int i = 0; i < nb_musiques; i++) {
		if (type[i] == TYPE_MOD)
			FMUSIC_SetMasterVolume(mod[i], v);
	}
}

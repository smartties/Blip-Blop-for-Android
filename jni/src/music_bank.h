
#ifndef _MusicBank_
#define _MusicBank_

#define	CHANNEL_NUMBER	32

///MODIF INCLUDE
#include "fmod/fmod.h"
#include "asset.h"

#include <vector>
using namespace std;

class MusicBank
{
protected:
	int	*		type;

//	FSOUND_SAMPLE **	mp3;
	FSOUND_STREAM **	mp3;

	FMUSIC_MODULE **	mod;
	void **				mp3Data;

	bool *		playing;
	bool *      tab_old;
	int *		channel;

	int			nb_musiques;

public:

	MusicBank();
	~MusicBank();

	void setVol(int v);
	bool open(const char * file, bool loop = true);
	void close();
	void play(int n);
	void stop(int n);
	void stop(); // Stoppe TOUTES les musiques
	///MODIF new fonction
	void play(); // Joue   TOUTES les musiques
};

class MusicManager
{
    public:
    MusicManager()
    {

    }

    void add(MusicBank *ptr)
    {
        tab.push_back(ptr);
    }
    bool erase(MusicBank *ptr)
    {
        int i;

        for(i = 0; i < tab.size(); i++)
        {
            if(tab[i] == ptr)
            {
                tab.erase(tab.begin()+i);
                return true;
            }
        }

        return false;
    }
    void play()
    {
        int i;

        LOGI("PLAY %d music bank", tab.size());

        for(i = 0; i < tab.size(); i++)
        {
            if(tab[i] != NULL)
            tab[i]->play();
        }
    }
    void stop()
    {
        int i;

        LOGI("STOP %d music bank", tab.size());

        for(i = 0; i < tab.size(); i++)
        {
            if(tab[i] != NULL)
            tab[i]->stop();
        }
    }

    vector<MusicBank*> tab;
};

extern MusicManager musicmanager;


#endif

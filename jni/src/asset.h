#ifndef ASSET_H_INCLUDED
#define ASSET_H_INCLUDED

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <jni.h>
#include <sstream>
#include <stdio.h>
#include <string.h>

using namespace std;

#include "SDL_rwops.h"
#include "log.h"


extern JNIEnv *senv;
extern AAssetManager *smgr;

AAssetManager *get_asset_manager();

static SDLCALL long long int aa_rw_seek(struct SDL_RWops * ops, long long int offset, int whence);
static SDLCALL size_t aa_rw_read(struct SDL_RWops * ops, void *ptr, size_t size, size_t maxnum);
static SDLCALL int aa_rw_close(struct SDL_RWops * ops);

AAsset *AAsset_asset(const char *filename);
SDL_RWops * AAsset_RWFromAsset(const char *filename);
bool AAsset_istringstream(const char *filename, istringstream &iss);

void removeline(char *buff);

class Parseur
{
    public :
    Parseur()
    {
        pos = 0;
        length = 0;

        file = NULL;
        buffer = NULL;
    }

    bool open(const char *nme)
    {
        file = NULL;
        if(nme)
        {
        char *name = (char*) nme;
        int i;

        for(i = 0; i < strlen(name); i++)
        {
            if(name[i] == 92)
            name[i] = 47;
            if(name[i] < 32)
            name[i] = '\0';
        }


        file = AAsset_asset(name);
        if(file)
        {
            pos = 0;
            buffer = (void *)AAsset_getBuffer(file);
            length = AAsset_getLength(file);
        }
        }

        return file != NULL;
    }
    void read(void *buf, int size)
    {
        if(file != NULL && pos+size <= length)
        {
            memcpy ( buf, buffer+pos, size );
            pos += size;
        }
    }
    void close()
    {
        AAsset_close(file);
    }

    AAsset *file;
    void *buffer;

    long int pos;
    long int length;
};

#endif // ASSET_H_INCLUDED

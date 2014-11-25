#include "asset.h"

AAssetManager *smgr = NULL;

void removeline(char *buff)
{
    if(buff != NULL)
    {
        int i;

        for(i = 0; i < strlen(buff); i++)
        {
            if(buff[i] < 32)
            buff[i] = '\0';
        }
    }
}

AAssetManager * get_asset_manager()
{
    //LOGI("senv %d smgr %d", senv, smgr);
    if(senv)
    {
        //LOGI("version %d", senv->GetVersion());
    }

    if(smgr == NULL)
    {
	jclass sdlClass = senv->FindClass("org/libsdl/app/SDLActivity");

	if (sdlClass == 0)
	{
	    //LOGI("FindClass fail ");
		return NULL;
	}

	jfieldID assman = senv->GetStaticFieldID(sdlClass,
                          "mAssetMgr", "Landroid/content/res/AssetManager;");

	if (assman == 0)
	{
	    //LOGI("GetStaticFieldID fail ");
		return NULL;
	}

	jobject assets = senv->GetStaticObjectField(sdlClass, assman);

	if (assets == 0)
	{
	    //LOGI("GetStaticObjectField fail ");
		return NULL;
	}

	//LOGI("FINAL ");

	smgr = AAssetManager_fromJava(senv, assets);
    }

    return smgr;
}


static SDLCALL long long int aa_rw_seek(struct SDL_RWops * ops, long long int offset, int whence)
{
    return AAsset_seek((AAsset*)ops->hidden.unknown.data1, offset, whence);
}

static SDLCALL size_t aa_rw_read(struct SDL_RWops * ops, void *ptr, size_t size, size_t maxnum)
{
    return AAsset_read((AAsset*)ops->hidden.unknown.data1, ptr, maxnum * size) / size;
}

static SDLCALL int aa_rw_close(struct SDL_RWops * ops)
{
    AAsset_close((AAsset*)ops->hidden.unknown.data1);
	SDL_FreeRW(ops);

	return 0;
}


AAsset *AAsset_asset(const char *filename)
{
    AAssetManager *mgr = get_asset_manager();

    return AAssetManager_open(mgr, filename, AASSET_MODE_UNKNOWN);
}

SDL_RWops * AAsset_RWFromAsset(const char *filename)
{
    AAsset *asset = AAsset_asset(filename);

	if (!asset)
		return NULL;

	SDL_RWops *ops = SDL_AllocRW();

	if (!ops)
	{
		AAsset_close(asset);
		return NULL;
	}

	ops->hidden.unknown.data1 = asset;
	ops->read = aa_rw_read;
	ops->write = NULL;
	ops->seek = aa_rw_seek;
	ops->close = aa_rw_close;

	return ops;
}

bool AAsset_istringstream(const char *filename, istringstream &iss)
{
    if(filename == NULL)
    return false;

    //LOGI("trying to load %s", filename);

    smgr = get_asset_manager();

    if(smgr == NULL)
    {
        //LOGI("asset manager null");
        return false;
    }

    AAsset *asset = AAssetManager_open(smgr, filename, AASSET_MODE_UNKNOWN);

    if(asset == NULL)
    {
        //LOGI("asset null");
        return false;
    }

    char *buff = (char*) AAsset_getBuffer(asset);
    long int size = (long int)AAsset_getLength(asset);

    if(buff == NULL)
    {
        //LOGI("buff null");
        return false;
    }

    iss.str("");
    iss.clear();

    std::stringbuf *pbuf = iss.rdbuf();

    pbuf->pubsetbuf(buff, size);
    //LOGI("SUCCES");

    return true;
}

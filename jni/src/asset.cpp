#include "asset.h"
#include "SDL_system.h"

AAssetManager *smgr = NULL;
static jobject smgr_ref = NULL;

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

// Fetch the APK's AssetManager from the SDL activity (Activity.getAssets()).
// A global reference keeps the Java object, and so the native manager, alive.
AAssetManager * get_asset_manager()
{
    if(smgr == NULL)
    {
        JNIEnv *env = (JNIEnv *)SDL_AndroidGetJNIEnv();
        jobject activity = (jobject)SDL_AndroidGetActivity();

        if(env == NULL || activity == NULL)
        {
            LOGI("get_asset_manager: no JNI env or activity");
            return NULL;
        }

        jclass cls = env->GetObjectClass(activity);
        jmethodID getAssets = env->GetMethodID(cls, "getAssets", "()Landroid/content/res/AssetManager;");
        jobject assets = getAssets ? env->CallObjectMethod(activity, getAssets) : NULL;

        if(assets != NULL)
        {
            smgr_ref = env->NewGlobalRef(assets);
            smgr = AAssetManager_fromJava(env, smgr_ref);
            env->DeleteLocalRef(assets);
        }

        env->DeleteLocalRef(cls);
        env->DeleteLocalRef(activity);
    }

    return smgr;
}


static Sint64 SDLCALL aa_rw_size(struct SDL_RWops * ops)
{
    return AAsset_getLength64((AAsset*)ops->hidden.unknown.data1);
}

static Sint64 SDLCALL aa_rw_seek(struct SDL_RWops * ops, Sint64 offset, int whence)
{
    return AAsset_seek64((AAsset*)ops->hidden.unknown.data1, offset, whence);
}

static size_t SDLCALL aa_rw_read(struct SDL_RWops * ops, void *ptr, size_t size, size_t maxnum)
{
    if(size == 0)
        return 0;

    int r = AAsset_read((AAsset*)ops->hidden.unknown.data1, ptr, maxnum * size);

    return r > 0 ? (size_t)r / size : 0;
}

static size_t SDLCALL aa_rw_write(struct SDL_RWops * ops, const void *ptr, size_t size, size_t num)
{
    return 0;
}

static int SDLCALL aa_rw_close(struct SDL_RWops * ops)
{
    AAsset_close((AAsset*)ops->hidden.unknown.data1);
	SDL_FreeRW(ops);

	return 0;
}


AAsset *AAsset_asset(const char *filename)
{
    AAssetManager *mgr = get_asset_manager();

    if(mgr == NULL || filename == NULL)
        return NULL;

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

	ops->type = SDL_RWOPS_UNKNOWN;
	ops->hidden.unknown.data1 = asset;
	ops->size = aa_rw_size;
	ops->read = aa_rw_read;
	ops->write = aa_rw_write;
	ops->seek = aa_rw_seek;
	ops->close = aa_rw_close;

	return ops;
}

bool AAsset_istringstream(const char *filename, istringstream &iss)
{
    if(filename == NULL)
    return false;

    AAsset *asset = AAsset_asset(filename);

    if(asset == NULL)
    {
        LOGI("asset not found: %s", filename);
        return false;
    }

    const char *buff = (const char*) AAsset_getBuffer(asset);
    size_t size = (size_t)AAsset_getLength(asset);

    if(buff == NULL)
    {
        AAsset_close(asset);
        return false;
    }

    // libc++'s stringbuf::setbuf() is a no-op, so copy the data into the stream.
    iss.str(std::string(buff, size));
    iss.clear();

    AAsset_close(asset);

    return true;
}

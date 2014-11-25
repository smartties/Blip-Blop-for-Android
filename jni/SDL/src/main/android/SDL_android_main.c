#include "../../SDL_internal.h"
#ifdef __ANDROID__
#include "SDL_main.h"
#include <jni.h>

extern void SDL_Android_Init(JNIEnv* env, jclass cls);

JNIEnv* senv = NULL;

void Java_org_libsdl_app_SDLActivity_nativeInit(JNIEnv* env, jclass cls, jobject obj)
{
    SDL_Android_Init(env, cls);

    SDL_SetMainReady();

    senv = env;

    int status;
    char *argv[2];
    argv[0] = SDL_strdup("SDL_app");
    argv[1] = NULL;
    status = SDL_main(1, argv);
}

#endif

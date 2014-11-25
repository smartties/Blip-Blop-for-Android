#ifndef LOG_H_INCLUDED
#define LOG_H_INCLUDED

#if defined (WIN32)

#else
#include <jni.h>
#include <errno.h>
#include <EGL/egl.h>
#include <GLES/gl.h>
#include <android/sensor.h>
#include <android/configuration.h>
#include <android/log.h>
#define LOGI(x...)  __android_log_print(ANDROID_LOG_INFO,"NativeWOpenGL",x)
#endif

#include "../SDL/include/SDL.h"
#include <stdio.h>
#include <string.h>

extern char buff_path[2048];

char *create_path(const char * a, const char *b);
char *create_pathSDL(const char * a);

#endif // LOG_H_INCLUDED

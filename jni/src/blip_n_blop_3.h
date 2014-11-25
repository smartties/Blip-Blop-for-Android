#ifndef _blip_n_blop_
#define _blip_n_blop_

#define NAME			"Blip'n Blop"
///MODIF suppresion de "data/"
#define CONFIG_FILE		"bb.cfg"
#define	HISCORES_FILE	"bb.scr"

#define WIN32_LEAN_AND_MEAN

#include "graphics.h"
// #include <mmsystem.h> TODO?
#include <stdio.h>
#include <string.h>

#include "l_timer.h"
#include "scroll.h"
#include "picture.h"
#include "ben_debug.h"
#include "input.h"
#include "dd_gfx.h"
#include "ben_divers.h"
#include "fonte.h"
#include "globals.h"
#include "lgx_packer.h"
#include "picture_bank.h"
#include "sound_bank_bb.h"
#include "game.h"
#include "ben_maths.h"
#include "txt_data.h"
#include "config.h"
#include "music_bank.h"
///MODIF INCLUDE
#include "fmod/fmod.h"
#include "log.h"

extern "C"
{
    void Java_org_libsdl_app_SDLActivity_nativeStop(JNIEnv* env);
    void Java_org_libsdl_app_SDLActivity_nativeRestart(JNIEnv* env);
}

extern Game	game;
extern HWND	WinHandle;

static bool safeMode	= false;


void ReleaseAll(void);
void Bug(const char * txt);
void Warning(const char * txt);
bool Question(const char * txt);
long WINAPI WinProc(HWND WinHandle, UINT Msg, WPARAM wParam, LPARAM lParam);
static void analyseCmdLine(char * cmd);
bool InitApp(HINSTANCE hInstance, int nCmdShow);


#endif

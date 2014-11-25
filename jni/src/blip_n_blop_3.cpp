#include "blip_n_blop_3.h"

Game	game;
HWND	WinHandle=NULL;



void Java_org_libsdl_app_SDLActivity_nativeStop(JNIEnv* env)
{
    game.Pause();
}

void Java_org_libsdl_app_SDLActivity_nativeRestart(JNIEnv* env)
{
    game.Resume();
}




void ReleaseAll(void)
{
	if (graphicInstance != NULL) {
		fnt_menu.close();
		fnt_menus.close();
		fnt_cool.close();
		fnt_rpg.close();

		pbk_inter.close();

		LGXpaker.closePaker();

		if (videoA != NULL) {
			videoA->Release();
			videoA = NULL;
		}


		if (systemSurface != NULL) {
			systemSurface->Release();
			systemSurface = NULL;
		}

		if (primSurface != NULL) {
			primSurface->Release();
			primSurface = NULL;
		}

		DDCloseDirectDraw();
	}

	freeTxtData();
	freeMathsFunctions();

	mbk_inter.close();
	mbk_interl.close();

	FSOUND_Close();

	in.close();

	ChangeDisplaySettings(NULL, 0);

}

void Bug(const char * txt)
{
	MessageBox(WinHandle, txt, "Blip'n Blop : Error reporting", MB_OK | MB_ICONERROR);
}

void Warning(const char * txt)
{
	MessageBox(WinHandle, txt, "Blip'n Blop : Warning", MB_OK | MB_ICONWARNING);

}

bool Question(const char * txt)
{
	return (MessageBox(WinHandle, txt, "Blip'n Blop", MB_YESNO | MB_ICONQUESTION) == IDYES);
}

long WINAPI WinProc(HWND WinHandle, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg) {
		case WM_SETCURSOR:			// CURSEUR --------
			SetCursor(NULL);
			return TRUE;
			break;

		case WM_ACTIVATE:
			active = !((BOOL)HIWORD(wParam));

			if (!active && winSet) {
				ChangeDisplaySettings(NULL, 0);
			}

			break;

		case WM_CLOSE:
			app_killed = TRUE;
//		want_to_kill_app = true;
			return 0;
			break;

		case WM_DESTROY:			// ARG! -----------
			app_killed = TRUE;
			PostQuitMessage(0);
			break;

		case WM_TIMER:
			fps_count = fps_current_count;
			fps_current_count = 0;
			break;
	}

	return DefWindowProc(WinHandle, Msg, wParam, lParam);

}

static void analyseCmdLine(char * cmd)
{
	static const char sep [] = " ";
	char * token;

	token = strtok(cmd, sep);

	while (token != NULL) {
		if (strcmp(token, "/safe") == 0)
			safeMode = true;

		if (strcmp(token, "/cheat") == 0)
			cheat_on = true;

		if (strcmp(token, "/quiet") == 0)
			music_on = false;

		token = strtok(NULL, sep);
	}
}



bool InitApp(HINSTANCE hInstance, int nCmdShow)
{
	WNDCLASS			WinClass;

	//------------------------------------------------------------------
	//			Histoire d'avoir un joli fichier log
	//------------------------------------------------------------------

	debug << "---------------------------------------------------------------\n";
	debug << "Blip & Blop - (c) LOADED Studio - " << __DATE__ << "\n";
	debug << "---------------------------------------------------------------\n";

	//------------------------------------------------------------------
	//			Precalculs mathématiques
	//------------------------------------------------------------------

	preCalcMathsFunctions();


	//------------------------------------------------------------------
	//			FMOD / Sons
	//------------------------------------------------------------------

	if (!FSOUND_Init(22050, CHANNEL_NUMBER, 0)) {
		Warning("Cannot initialise FMOD. Sound will be turned off.");
		LOGI("BUG AUDIO");
		sound_on = false;
		music_on = false;
	} else {
		// Pour éviter que les musiques ne se fassent écraser par les sons
		//
		FSOUND_SetPriority(0, 255);
	}


	//------------------------------------------------------------------
	//			Timer
	//------------------------------------------------------------------

	LInitTimer();


	//------------------------------------------------------------------
	//			Charge la configuration
	//------------------------------------------------------------------


	load_BB3_config(CONFIG_FILE);

	//------------------------------------------------------------------
	//			Charge les hi scores
	//------------------------------------------------------------------

	hi_scores.init();

	if (!hi_scores.load(HISCORES_FILE)) {
		debug << "Cannot load hi-scores file. Use default hi-scores\n";
		hi_scores.init();
	} else {
		debug << "Using " << HISCORES_FILE << " as hiscores file\n";
	}


	//------------------------------------------------------------------
	//			Les fichiers textes
	//------------------------------------------------------------------

	if (lang_type == LANG_UK) {
		if (!loadTxtData("data/uk.dat")) {
			Bug("Cannot open the file 'data/uk.dat'");
			ReleaseAll();
			return false;
		}
	} else {
		if (!loadTxtData("data/fr.dat")) {
			Bug("Cannot open the file 'data/fr.dat'");
			ReleaseAll();
			return false;
		}
	}


	//------------------------------------------------------------------
	//			Direct Input
	//------------------------------------------------------------------


	if (!in.open(WinHandle, hInstance)) {
		Bug("Cannot initialise DirectInput. Make sure DirectX 7 or better is installed.");
		ReleaseAll();
		return false;
	}

	debug << "DI Initialized\n";

	//------------------------------------------------------------------
	//			Direct Draw (1ère partie)
	//------------------------------------------------------------------
	LOGI("first");
	if (!DDInitDirectDraw()) {
		Bug("Cannot initialise DirectDraw. Make sure DirectX 7 or better is installed.");
		ReleaseAll();
		return false;
	}

	debug << "DD Initialized\n";


	active = true;	//Activate the game loop
	LOGI("second");

	if (!DDSetCooperativeLevel(WinHandle)) {
		Bug("Cannot get EXCLUSIVE MODE. Close all other applications and launch Blip'n Blop again");
		ReleaseAll();
		return false;
	}

	debug << "Exclusive mode set\n";
	LOGI("third");

	static const int BEST_RATE = 85;

	if (safeMode) {
		debug << "Safe mode enabled, using default 640x480x16 refresh rate.\n";
		winSet = false;

		if (!DDSetGfxMode(640, 480, 16)) {
			Bug("Cannot set display mode to 640x480x16. Are you sure your video card meets the requirements ?");
			ReleaseAll();
			return false;
		}
	} else {

			debug << "Trying to create window\n";
			if (!DDSetGfxMode(640, 480, 16)) {
				Bug("Cannot set display mode to 640x480x16. Are you sure your video card meets the requirements ?");
				ReleaseAll();
				return false;
			}
			debug << "Window creation done\n";

	}

	LOGI("fouth");



	//------------------------------------------------------------------
	//			Direct Draw (suite)
	//------------------------------------------------------------------

	// Crée la surface primaire avec double buffer
	debug << "Creating primSurface\n";
	primSurface = DDCreatePrimary(backSurface);

	if (primSurface == NULL || backSurface == NULL) {
		Bug("Cannot get a primary surface. Please reboot your PC and try to launch Blip'n Blop again.\nBe sure you have at least 2 Mb of video memory on your video card.");
		ReleaseAll();
		return false;
	}
	debug << "primSurface created\n";

	LOGI("fifth");

	//------------------------------------------------------------------
	//			Surface système
	//------------------------------------------------------------------
	debug << "Creating systemSurface\n";
	systemSurface = DDCreateSurface(640, 480, DDSURF_SYSTEM);

	if (systemSurface == NULL) {
		Bug("Not enough memory. Blip'n Blop needs 32 Mo of free memory. Try to close all other applications and launch Blip'n Blop again.");
		ReleaseAll();
		return false;
	}
	debug << "systemSurface created\n";
	LOGI("sixth");


	//------------------------------------------------------------------
	//			LGX paker
	//------------------------------------------------------------------
	debug << "Initializing LGXpaker\n";
	if (!LGXpaker.init(primSurface)) {
		Bug("Cannot initialise LGX paker. Please get the latest drivers for your video card.");
		ReleaseAll();
		return false;
	}
	debug << "LGXpaker initialized\n";
	LOGI("seventh");

	//------------------------------------------------------------------
	//			Scroll buffers
	//------------------------------------------------------------------

	debug << "Creating video buffer of size " << (WANTED_VBUFFER_WIDE) << "...";
	videoA = DDCreateSurface(WANTED_VBUFFER_WIDE, 480, DDSURF_VIDEO);

	if (videoA == NULL) {
		debug << "Failed\n";
		debug << "Creating video buffer of size " << (WANTED_VBUFFER_WIDE - 100) << "...";
		videoA = DDCreateSurface(WANTED_VBUFFER_WIDE - 100, 480, DDSURF_VIDEO);

		if (videoA == NULL) {
			debug << "Failed\n";
			debug << "Creating video buffer (" << (WANTED_VBUFFER_WIDE - 200) << ")...";
			videoA = DDCreateSurface(WANTED_VBUFFER_WIDE - 200, 480, DDSURF_VIDEO);

			if (videoA == NULL) {
				debug << "Failed\n";
				videoA = DDCreateSurface(WANTED_VBUFFER_WIDE, 480, DDSURF_SYSTEM);

				if (videoA == NULL) {
					Bug("Not enough memory. Blip'n Blop needs 32 Mo of free memory. Try to close all other applications and launch Blip'n Blop again.");
					ReleaseAll();
					return false;
				}

				debug << "Cannot create video buffer. Use system buffer instead.\n";
				vbuffer_wide = WANTED_VBUFFER_WIDE;
				mem_flag = DDSURF_SYSTEM;
				video_buffer_on = false;
			} else {
				debug << "Ok\n";
				vbuffer_wide = WANTED_VBUFFER_WIDE - 200;
			}
		} else {
			debug << "Ok\n";
			vbuffer_wide = WANTED_VBUFFER_WIDE - 100;
		}
	} else {
		debug << "Ok\n";
		vbuffer_wide = WANTED_VBUFFER_WIDE;
	}

	LOGI("eighth");

	//------------------------------------------------------------------
	//			Chargement des fontes init
	//------------------------------------------------------------------

	if (!fnt_menu.load("data/menu.lft", mem_flag)) {
		Bug("Cannot open the file data/menu.lft");
		ReleaseAll();
		return false;
	}

	LOGI("nineth");

	if (!fnt_menus.load("data/menus.lft", mem_flag)) {
		Bug("Cannot open the file data/menus.lft");
		ReleaseAll();
		return false;
	}

	if (!fnt_cool.load("data/cool.lft", mem_flag)) {
		Bug("Cannot open the file data/cool.lft");
		ReleaseAll();
		return false;
	}

	if (!fnt_rpg.load("data/rpg.lft", mem_flag)) {
		Bug("Cannot open the file data/rpg.lft");
		ReleaseAll();
		return false;
	}

	LOGI("erz");

	//------------------------------------------------------------------
	//			Chargement de l'interface
	//------------------------------------------------------------------

	if (!pbk_inter.loadGFX("data/inter.gfx", DDSURF_BEST)) {
		debug << "Cannot load interface.\n";
		return false;
	} else {
		debug << "Successfully loaded interface.\n";
	}

	if (!mbk_inter.open("data/inter.mbk", false)) {
		debug << "Cannot load interface musics.\n";
		return false;
	}

	if (!mbk_interl.open("data/interl.mbk", true)) {
		debug << "Cannot load interface musics (p2).\n";
		return false;
	}
	LOGI("END");

	//------------------------------------------------------------------
	//			Mémoire video restante
	//------------------------------------------------------------------

	//------------------------------------------------------------------
	//			Mise en place du TIMER pour obtenir les FPS
	//------------------------------------------------------------------

	SetTimer(WinHandle, 1, 1000, NULL);

	return true; // C'est fini!

} // Init ---------------------------


/************************************
 *   WinMain
 */
/*
#ifndef _WIN32
int main(int argc, const char* argv[])
{
	HINSTANCE hInstance = 0;
	HINSTANCE hPrevInstance = 0;
	char lpCmdLine[512] = {0};
	for (int i = 1; i < argc; i++) {
		strcat(lpCmdLine, argv[i]);
		strcat(lpCmdLine, " ");
	}
	int nCmdShow = 0;
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
#endif
	//------------------------------------------------------------------
	//			Safe mode ?
	//------------------------------------------------------------------

	analyseCmdLine(lpCmdLine);

	//------------------------------------------------------------------
	//			Initialise l'application
	//------------------------------------------------------------------

	if (!InitApp(hInstance, nCmdShow))
		return -1;

	//------------------------------------------------------------------
	//			Joue la partie
	//------------------------------------------------------------------

	game.go();

	//------------------------------------------------------------------
	//			On quitte plus ou moins proprement
	//------------------------------------------------------------------

	debug << "---------------------------------------------------------------\n";
	debug << "Releasing Blip & Blop\n";
	debug << "---------------------------------------------------------------\n";

	// Désalloue tout ce qu'il faut (en théorie)
	//
	ReleaseAll();

	// Sauvegarde les hi-scores
	//
	if (!hi_scores.save(HISCORES_FILE)) {
		debug << "Cannot save hi-scores\n";
	} else {
		debug << "Saving " << HISCORES_FILE << " as hi-scores file.\n";
	}

	// Sauvegarde la configuration
	//
	save_BB3_config(CONFIG_FILE);

	// Détruit la fenêtre
	//
	DestroyWindow(WinHandle);

	return 0;

} // WinMain ------------------------
*/

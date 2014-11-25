#if defined (WIN32)
#include <windows.h>
#else
#include "Engine/windows.h"
#endif


#include "globals.h"
#include "config.h"
#include "scroll.h"
#include "ben_debug.h"

bool RestoreAll()
{
	if (winSet) {
		DEVMODE dm;

		ZeroMemory(&dm, sizeof(dm));
		dm.dmSize = sizeof(dm);
		dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
		dm.dmPelsWidth	= 640;
		dm.dmPelsHeight = 480;
		dm.dmBitsPerPel = 16;
		dm.dmDisplayFrequency = 85;

		if (ChangeDisplaySettings(&dm, CDS_TEST) != DISP_CHANGE_SUCCESSFUL ||
		        ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			debug << "Cannot restore display mode.\n";
		}
	}

	if (primSurface->Restore() != DD_OK) {
		debug << "Cannot restore primary surface.\n";
		return false;
	}

	fnt_menu.restoreAll();

	// Affiche un "LOADING..."
	//
	fnt_menu.printC(backSurface, 320, 210, "PLEASE WAIT");
	//primSurface->Flip(NULL, DDFLIP_WAIT);
	graphicInstance->Flip();

	graphicInstance->RestoreAllSurfaces();

	n_img = 0;
	xTex = 0;
	n_cache = 0;
	next_x = 0;

	pbk_decor.restoreAll();
	pbk_blip.restoreAll();
	pbk_blop.restoreAll();
	pbk_bb.restoreAll();
	pbk_misc.restoreAll();
	pbk_ennemis.restoreAll();
	pbk_niveau.restoreAll();
	pbk_rpg.restoreAll();
	pbk_rpg_bb.restoreAll();

	pbk_inter.restoreAll();

	fnt_score_blip.restoreAll();
	fnt_score_blop.restoreAll();
	fnt_ammo.restoreAll();
	fnt_ammo_used.restoreAll();
	fnt_cool.restoreAll();
	fnt_rpg.restoreAll();
	fnt_menus.restoreAll();

	in.reAcquire();

	return true;
}

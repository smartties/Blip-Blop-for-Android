/******************************************************************
*
*
*		--------------
*		  Config.cpp
*		--------------
*
*		Contient toutes les données sur la config
*		et quelques fonctions pour la gérer.
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#include <stdio.h>
#include "dd_gfx.h"
#include "ben_debug.h"
#include "config.h"
#include "input.h"
#include "control_alias.h"
///MODIF INCLUDE
#include "fmod/fmod.h"
#include "globals.h"

bool	vSyncOn = true;

int		mem_flag = DDSURF_BEST;
bool	video_buffer_on = true;
bool	mustFixGforceBug = false;

int		lang_type = LANG_UK;

bool	music_on = true;
bool	sound_on = true;

bool	cheat_on = false;

HiScores	hi_scores;

bool	winSet;


void load_BB3_config(const char * cfg_file)
{
	FILE *	fic;
	int		a;

	///MODIF PATH
	if(create_pathSDL(cfg_file))
	LOGI("PATH : _%s_ ", create_pathSDL(cfg_file));
	return ;

	fic = fopen(create_pathSDL(cfg_file), "rb");

	if (fic == NULL) {
		debug << "Cannot find config file. Will use default config.\n";
		LOGI("Cannot find config file. Will use default config");
		set_default_config(true);
	} else {
		debug << "Using " << cfg_file << " as configuration file.\n";
		LOGI("Using %s as configuration file.", cfg_file);

		fread(&vSyncOn, sizeof(vSyncOn), 1, fic);
		fread(&lang_type, sizeof(lang_type), 1, fic);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P1_UP, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P1_DOWN, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P1_LEFT, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P1_RIGHT, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P1_FIRE, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P1_JUMP, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P1_SUPER, a);


		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P2_UP, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P2_DOWN, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P2_LEFT, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P2_RIGHT, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P2_FIRE, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P2_JUMP, a);

		fread(&a, sizeof(a), 1, fic);
		in.setAlias(ALIAS_P2_SUPER, a);

		fclose(fic);
	}

	lang_type = LANG_UK;
}

void save_BB3_config(const char * cfg_file)
{
	FILE *	fic;
	int		a;

	fic = fopen(create_pathSDL(cfg_file), "wb");

	if (fic == NULL) {
		debug << "Cannot save config file.\n";
	} else {
		debug << "Saving " << cfg_file << " as configuration file.\n";


		fwrite(&vSyncOn, sizeof(vSyncOn), 1, fic);
		fwrite(&lang_type, sizeof(lang_type), 1, fic);

		a = in.getAlias(ALIAS_P1_UP);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_DOWN);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_LEFT);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_RIGHT);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_FIRE);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_JUMP);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P1_SUPER);
		fwrite(&a, sizeof(a), 1, fic);


		a = in.getAlias(ALIAS_P2_UP);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_DOWN);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_LEFT);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_RIGHT);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_FIRE);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_JUMP);
		fwrite(&a, sizeof(a), 1, fic);

		a = in.getAlias(ALIAS_P2_SUPER);
		fwrite(&a, sizeof(a), 1, fic);

		fclose(fic);
	}
}

void set_default_config(bool reset_lang)
{
	if (reset_lang)
		lang_type = LANG_UK;

	in.setAlias(ALIAS_P1_UP, DIK_UP);
	in.setAlias(ALIAS_P1_DOWN, DIK_DOWN);
	in.setAlias(ALIAS_P1_LEFT, DIK_LEFT);
	in.setAlias(ALIAS_P1_RIGHT, DIK_RIGHT);
	in.setAlias(ALIAS_P1_FIRE, DIK_LCONTROL);
	in.setAlias(ALIAS_P1_JUMP, DIK_LMENU);
	in.setAlias(ALIAS_P1_SUPER, DIK_SPACE);

	in.setAlias(ALIAS_P2_UP, DIK_Q);
	in.setAlias(ALIAS_P2_DOWN, DIK_S);
	in.setAlias(ALIAS_P2_LEFT, DIK_D);
	in.setAlias(ALIAS_P2_RIGHT, DIK_F);
	in.setAlias(ALIAS_P2_FIRE, DIK_TAB);
	in.setAlias(ALIAS_P2_JUMP, DIK_G);
	in.setAlias(ALIAS_P2_SUPER, DIK_H);
}

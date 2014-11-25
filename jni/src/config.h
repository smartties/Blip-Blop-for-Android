/******************************************************************
*
*
*		------------
*		  Config.h
*		------------
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

#ifndef _Config_
#define _Config_

#include "hi_scores.h"
#include "log.h"

extern bool		vSyncOn;

extern int		mem_flag;
extern bool		video_buffer_on;
extern bool		mustFixGforceBug;

#define LANG_FR		0
#define LANG_UK		1

extern int		lang_type;

extern bool		music_on;
extern bool		sound_on;

extern bool		cheat_on;

extern HiScores	hi_scores;

extern bool		winSet;

void load_BB3_config(const char * cfg_file);
void save_BB3_config(const char * cfg_file);
void set_default_config(bool reset_lang = false);

#endif

/******************************************************************
*
*
*		----------------
*		   Globals.h
*		----------------
*
*		Liste de tous les trucs globaux et donc accessibles
*		pour TOUT LE MONDE.
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#ifndef _BB_GLOBALS_
#define _BB_GLOBALS_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

// #include <ddraw.h>
#include "ben_debug.h"
#include "control_p1.h"
#include "control_p2.h"
#include "picture_bank.h"
#include "fonte.h"
#include "super_liste.h"
#include "sound_bank_bb.h"
#include "music_bank.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define LATENCE_GRAVITE		7
#define GRAVITE_MAX			4

#define	NB_MAX_PLAT			8

#define METEO_PLUIE			0
#define METEO_NEIGE			1
#define METEO_DEFORME		2

#define FLAG_USER0			0
#define FLAG_USER1			1
#define FLAG_USER2			2
#define FLAG_USER3			3

#define FLAG_BULLES			4
#define FLAG_BONUS			5
#define FLAG_TIMER			6
#define FLAG_GEN_OFF		7
#define FLAG_NB_KILL		8
#define FLAG_NB_ENN			9
#define FLAG_NB_GEN			10

//-----------------------------------------------------------------------------
//		Données sur la configuration
//-----------------------------------------------------------------------------

extern int			fps_count;
extern int			fps_current_count;

//-----------------------------------------------------------------------------
//		Surfaces
//-----------------------------------------------------------------------------

extern SDL::Surface	*	primSurface;	// Surface primaire
extern SDL::Surface	*	backSurface;	// pointeur sur le double buffer supposé
extern SDL::Surface  *	systemSurface;	// Pour optimiser les accès SYSTEM/SYSTEM
extern SDL::Surface  *	videoA;			// cache video

//-----------------------------------------------------------------------------
//		Données scroll et positions
//-----------------------------------------------------------------------------


extern int			offset;				// offset courant du scroll
extern int			scr_offset;			// = offset % 640

extern int			scroll_speed;

extern bool			scroll_locked;
extern int			x_lock;
extern int			cond_end_lock;
extern int			flag_end_lock;
extern int			val_end_lock;

extern bool			no_scroll1;			// Pour arrêter le scroll quand
extern bool			no_scroll2;			// blip ou blop meure

extern bool			okBonus;
extern bool			cowBombOn;
extern bool			okLanceFlame;

//-----------------------------------------------------------------------------
//		Données sur le niveau
//-----------------------------------------------------------------------------

extern int			scr_level_size;		// taille en écran du niveau
extern int			level_size;			// taille en pixels du niveau
extern int *		num_decor;			// Numéro ecran courant -> surface à utiliser


extern int	**		y_plat;				// Plateformes (ordonnées)

extern bool **		murs_opaques;		// Murs opaques (=true)
extern bool **		murs_sanglants;		// Murs sanglants (=true)


//-----------------------------------------------------------------------------
//		Pour les controles
//-----------------------------------------------------------------------------

extern ControlP1	ctrlP1;
extern ControlP2	ctrlP2;

//-----------------------------------------------------------------------------
//		Les listes
//-----------------------------------------------------------------------------

extern SuperListe	list_joueurs;
extern SuperListe	list_tirs_bb;
extern SuperListe	list_cow;
extern SuperListe	list_impacts;

extern SuperListe	list_vehicules;

extern SuperListe	list_event_endormis;
extern SuperListe	list_event;

extern SuperListe	list_ennemis;
extern SuperListe	list_tirs_ennemis;
extern SuperListe	list_gen_ennemis;

extern SuperListe	list_bonus;
extern SuperListe	list_gen_bonus;

extern SuperListe	list_fonds_animes;
extern SuperListe	list_fonds_statiques;
extern SuperListe	list_premiers_plans;
extern SuperListe	list_plateformes_mobiles;

extern SuperListe	list_txt_cool;

extern SuperListe	list_giclures;
extern SuperListe	list_gore;

extern SuperListe	list_meteo;
extern SuperListe	list_bulles;


//-----------------------------------------------------------------------------
//		Données sur les actions à faire
//-----------------------------------------------------------------------------

extern bool			phase;				// Pour les clignotements
extern bool			slow_phase;

extern int			game_flag[11];

extern bool			hold_fire;
extern int			flag_hold_fire;
extern int			val_hold_fire;

extern int			rpg_to_play;	// Le numéro de la phase RPG à actionner (-1:aucune)

extern int			nb_ennemis_created;

extern int			intensite_meteo;
extern int			type_meteo;

extern int			dy_tremblement;
extern int			etape_tremblement;
extern int			amplitude_tremblement;
extern int			ddy_tremblement;

extern bool			total_debug;

//-----------------------------------------------------------------------------
//		Les Picture Banks
//-----------------------------------------------------------------------------

extern PictureBank		pbk_decor;	// pbk des décors
extern PictureBank		pbk_blip;	// pbk de blip
extern PictureBank		pbk_blop;
extern PictureBank		pbk_bb;		// pbk commune à blip et blop
extern PictureBank		pbk_misc;	// pbk "diverse"
extern PictureBank		pbk_ennemis;// pbk des ennemis
extern PictureBank		pbk_niveau;	// pbk du niveau (fonds animes & co)
extern PictureBank		pbk_rpg;	// Gueules des RPGs du niveau
extern PictureBank		pbk_rpg_bb; // Les gueules de Blip et Blop
extern PictureBank		pbk_inter;	// L'interface

//-----------------------------------------------------------------------------
//		Les Sounds Banks
//-----------------------------------------------------------------------------

extern SoundBankBB		sbk_bb;		// Sons BB/divers communs à tous les niveaux
extern SoundBankBB		sbk_rpg;	// Les musiques des scènes RPG
extern SoundBankBB		sbk_misc;
extern SoundBankBB		sbk_niveau;

extern MusicBank		mbk_niveau;
extern MusicBank		mbk_inter;
extern MusicBank		mbk_interl;

extern char				current_sbk[];			// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
extern char				current_sbk_misc[];		// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
extern char				current_sbk_niveau[];	// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
extern char				current_mbk[];			// Nom de la MBK courante pour pouvoir la recharger si on enlève puis remet le son
extern int				current_zik;			// Numéro de la zik jouée

//-----------------------------------------------------------------------------
//		Les Fontes
//-----------------------------------------------------------------------------

extern Fonte			fnt_score_blip;
extern Fonte			fnt_score_blop;
extern Fonte			fnt_ammo;
extern Fonte			fnt_ammo_used;
extern Fonte			fnt_cool;
extern Fonte			fnt_rpg;
extern Fonte			fnt_menu;
extern Fonte			fnt_menus;

//-----------------------------------------------------------------------------
//		Les fonctions cool
//-----------------------------------------------------------------------------

int		plat(int x, int y);	// Retourne l'ordonnée de la plateforme (0 si pas de plat)
int		plat2(int x, int y);
bool	mur_opaque(int x, int y);
bool	mur_sanglant(int x, int y);
bool	grave(int x, int y, Picture * pic);
void	tremblement(int amp);
bool	checkRestore();


inline void draw(int x, int y, const Picture * pic)
{
	if (pic != NULL)
		pic->BlitTo(backSurface, x - offset, y);
}
inline void draw2(int x, int y, const Picture * pic)
{
    if (pic != NULL)
		pic->BlitTo(backSurface, x, y);
}
#endif

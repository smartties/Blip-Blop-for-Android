/******************************************************************
*
*
*		----------------
*		   Globals.cpp
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

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

// #include <ddraw.h>
#include "ben_divers.h"
#include "control_p1.h"
#include "control_p2.h"
#include "picture_bank.h"
#include "fonte.h"
#include "super_liste.h"
#include "sound_bank_bb.h"
#include "music_bank.h"
#include "scroll.h"
#include "restore.h"
#include "fond_statique.h"

#include "ben_debug.h"

#define NB_MAX_PLAT	8

//-----------------------------------------------------------------------------
//		Données sur la configuration
//-----------------------------------------------------------------------------

int			fps_count			= 0;
int			fps_current_count	= 0;

//-----------------------------------------------------------------------------
//		Surfaces
//-----------------------------------------------------------------------------

SDL::Surface	*	primSurface = NULL;		// Surface primaire
SDL::Surface	*	backSurface = NULL;		// pointeur sur le double buffer supposé
SDL::Surface *	systemSurface = NULL;		// Pour optimiser les accès SYSTEM/SYSTEM
SDL::Surface *	videoA			= NULL;		// cache video

//-----------------------------------------------------------------------------
//		Données scroll et positions
//-----------------------------------------------------------------------------

int			offset;				// offset courant du scroll
int			scr_offset;			// = offset % 640

int			scroll_speed;

bool		scroll_locked;
int			x_lock;
int			cond_end_lock;
int			flag_end_lock;
int			val_end_lock;

bool		no_scroll1;
bool		no_scroll2;

//-----------------------------------------------------------------------------
//		Données sur le niveau
//-----------------------------------------------------------------------------

int			scr_level_size;		// taille en écran du niveau
int			level_size;			// taille en pixels du niveau
int	*		num_decor	= NULL;	// Numéro ecran courant -> surface à utiliser


int	**		y_plat		= NULL;	// Plateformes (ordonnées)

bool **		murs_opaques;		// Murs opaques (=true)
bool **		murs_sanglants;		// Murs sanglants (=true)

//-----------------------------------------------------------------------------
//		Pour les controles
//-----------------------------------------------------------------------------

ControlP1	ctrlP1;
ControlP2	ctrlP2;

//-----------------------------------------------------------------------------
//		Les listes
//-----------------------------------------------------------------------------

SuperListe	list_joueurs;
SuperListe	list_tirs_bb;
SuperListe	list_cow;
SuperListe	list_impacts;

SuperListe	list_vehicules;

SuperListe	list_event_endormis;
SuperListe	list_event;

SuperListe	list_ennemis;
SuperListe	list_tirs_ennemis;
SuperListe	list_gen_ennemis;

SuperListe	list_bonus;
SuperListe	list_gen_bonus;

SuperListe	list_fonds_animes;
SuperListe	list_fonds_statiques;
SuperListe	list_premiers_plans;
SuperListe	list_plateformes_mobiles;

SuperListe	list_txt_cool;

SuperListe	list_giclures;
SuperListe	list_gore;

SuperListe	list_meteo;
SuperListe	list_bulles;


//-----------------------------------------------------------------------------
//		Données sur les actions à faire
//-----------------------------------------------------------------------------

bool			phase;			// Pour les clignotements
bool			slow_phase;

int				game_flag[11];

bool			hold_fire;
int				flag_hold_fire;
int				val_hold_fire;

int				rpg_to_play = -1;	// Le numéro de la phase RPG à actionner (-1:aucune)

int				nb_ennemis_created;

int				intensite_meteo;
int				type_meteo;

int				dy_tremblement = 0;
int				etape_tremblement = 0;
int				amplitude_tremblement = 0;
int				ddy_tremblement = 0;

bool			total_debug = false;

bool			okBonus;
bool			cowBombOn;
bool			okLanceFlame;


//-----------------------------------------------------------------------------
//		Les Picture Banks
//-----------------------------------------------------------------------------

PictureBank		pbk_decor;	// pbk des décors
PictureBank		pbk_blip;	// pbk de blip
PictureBank		pbk_blop;
PictureBank		pbk_bb;		// pbk commune à blip et blop
PictureBank		pbk_misc;	// pbk globale du jeu (bonus & co)
PictureBank		pbk_ennemis;// pbk des ennemis
PictureBank		pbk_niveau;	// pbk du niveau (fonds animes & co)
PictureBank		pbk_rpg;	// Gueules des RPGs du niveau
PictureBank		pbk_rpg_bb; // Les gueules de Blip et Blop
PictureBank		pbk_inter;	// L'interface

//-----------------------------------------------------------------------------
//		Les Sounds Banks
//-----------------------------------------------------------------------------

SoundBankBB		sbk_bb;		// Sons BB/divers communs à tous les niveaux
SoundBankBB		sbk_rpg;	// Les musiques des scènes RPG
SoundBankBB		sbk_misc;
SoundBankBB		sbk_niveau;

MusicBank		mbk_niveau;
MusicBank		mbk_inter;
MusicBank		mbk_interl;

char			current_sbk[200];			// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
char			current_sbk_misc[200];		// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
char			current_sbk_niveau[200];	// Nom de la SBK courante pour pouvoir la recharger si on enlève puis remet le son
char			current_mbk[200];			// Nom de la MBK courante pour pouvoir la recharger si on enlève puis remet le son
int				current_zik;				// Numéro de la zik jouée

//-----------------------------------------------------------------------------
//		Les Fontes
//-----------------------------------------------------------------------------

Fonte			fnt_score_blip;
Fonte			fnt_score_blop;
Fonte			fnt_ammo;
Fonte			fnt_ammo_used;
Fonte			fnt_cool;
Fonte			fnt_rpg;
Fonte			fnt_menu;
Fonte			fnt_menus;

//-----------------------------------------------------------------------------
//		Les fonctions cool
//-----------------------------------------------------------------------------


void tremblement(int amp)
{
	amplitude_tremblement = amp;
	ddy_tremblement = (amp >> 1) + 1;
	dy_tremblement = -amp;
	etape_tremblement = 0;
}


int	plat(int x, int y)
{
	if (x < 0 || x >= level_size || y >= 480)
		return 0;

	int	tmp;

	for (int i = 0; i < NB_MAX_PLAT; i++) {
		tmp = y_plat[i][x];

		if (y >= tmp && y <= tmp + 10)
			return tmp;
	}
	/*
		if ( mur_opaque( x, y))
			return ( y - (y%8 + 1));
	*/
	return 0;
}

int	plat2(int x, int y)
{
	if (x < 0 || x >= level_size || y < 0 || y >= 480)
		return -1;

	int	tmp;

	for (int i = 0; i < NB_MAX_PLAT; i++) {
		tmp = y_plat[i][x];

		if (y >= tmp && y <= tmp + 10)
			return i;
	}

	return -1;
}

bool mur_opaque(int x, int y)
{
	if (x < 0 || x >= level_size || y < 0 || y >= 480)
		return false;

	return murs_opaques[y / 8][x / 8];
}


bool mur_sanglant(int x, int y)
{
	if (x < 0 || x >= level_size || y < 0 || y >= 480)
		return false;

	return murs_sanglants[y / 8][x / 8];
}

inline void clipedBlit(SDL::Surface * surf, const Picture * pic, int x, int y, RECT * clip)
{
	if (pic == NULL)
		return;

	RECT	r;
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		xs = pic->xSize();
	int		ys = pic->ySize();

	x1 = x - pic->xSpot();
	y1 = y - pic->ySpot();

	x2 = x1 + xs;
	y2 = y1 + ys;

	if (x2 < clip->left || x1 > clip->right || y1 > clip->bottom || y2 < clip->top)
		return;

	if (x1 < clip->left) {
		r.left = clip->left - x1;
		x1 = clip->left;
	} else
		r.left = 0;

	if (y1 < clip->top) {
		r.top = clip->top - y1;
		y1 = clip->top;
	} else
		r.top = 0;

	if (x2 > clip->right)
		r.right = xs - (x2 - clip->right);
	else
		r.right = xs;

	if (y2 > clip->bottom)
		r.bottom = ys - (y2 - clip->bottom);
	else
		r.bottom = ys;

	surf->BltFast(x1, y1, pic->Surf(), &r, DDBLTFAST_WAIT | DDBLTFAST_SRCCOLORKEY);
}

bool grave(int x, int y, Picture * pic)
{
	if (pic == NULL || x > (offset + vbuffer_wide - pic->xSize()))
		return false;

	FondStatique	s;
	Sprite *		s2;

	s.x		= x;
	s.y		= y;
	s.pic	= pic;

	s.colFromPic();

	list_fonds_animes.start();

	while (!list_fonds_animes.fin()) {
		s2 = (Sprite*) list_fonds_animes.info();

		if (s.collision(s2))
			return false;

		list_fonds_animes.suivant();
	}

	list_plateformes_mobiles.start();

	while (!list_plateformes_mobiles.fin()) {
		s2 = (Sprite*) list_plateformes_mobiles.info();

		if (s.collision(s2))
			return false;

		list_plateformes_mobiles.suivant();
	}


	RECT	r;
	int		ni = x / /*640;*/vbuffer_wide;
//	int		no = offset / vbuffer_wide;

	r.top	= 0;
	r.bottom = 480;

	x %= vbuffer_wide;

	if (ni == n_cache - 1) {
		r.left = next_x;
		r.right = vbuffer_wide;

		clipedBlit(videoA, pic, x, y, &r);

		r.left = 0;
		r.right = next_x;

		clipedBlit(videoA, pic, x - vbuffer_wide, y, &r);

		return true;
	} else if (ni == n_cache) {
		r.left = 0;
		r.right = next_x;

		clipedBlit(videoA, pic, x, y, &r);

		r.left = next_x;
		r.right = vbuffer_wide;

		clipedBlit(videoA, pic, x + vbuffer_wide, y, &r);

		return true;
	}

	return false;
}

bool checkRestore()
{
	if (!active) {
		debug << "Blip'n Blop 3 has been desactivated\n";

		while (!active && !app_killed)
			manageMsg();


		for (int i = 0; i < 10; i++)
			manageMsg();

		debug << "Blip'n Blop 3 is active again\n";

		if (primSurface->IsLost()) {
			debug << "Restoring lost surfaces...";

			if (RestoreAll())
				debug << "ok\n";
		}

		return true;
	}

	return false;
}















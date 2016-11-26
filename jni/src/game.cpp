/******************************************************************
*
*
*		----------------
*		   Game.cpp
*		----------------
*
*		Classe Game
*
*		La classe représentant une partie
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#define GAME_CPP_FILE

//#include <windows.h>
#include <fcntl.h>
///MODIF INCLUDE ENGINE
#include "Engine/io.h"

#include <cstdio>
#include <cstring>
#include <malloc.h>

#include "cine_player.h"
#include "lgx_packer.h"
#include "globals.h"
#include "scroll.h"
#include "game.h"
#include "ben_divers.h"
#include "dd_gfx.h"
#include "ben_debug.h"
#include "input.h"
#include "tir_bb.h"
#include "event_ennemi.h"
#include "event_gen_ennemi.h"
#include "event_lock.h"
#include "event_scroll_speed.h"
#include "event_set_flag.h"
#include "event_hold_fire.h"
#include "event_gen_bonus.h"
#include "event_texte.h"
#include "event_fond_anime.h"
#include "event_premier_plan.h"
#include "event_rpg.h"
#include "event_music.h"
#include "event_mi_fond.h"
#include "event_meteo.h"
#include "event_bonus.h"
#include "event_vehicule.h"
#include "event_son.h"
#include "fic_events.h"
#include "enemy.h"
#include "gen_ennemi.h"
#include "bonus.h"
#include "gen_bonus.h"
#include "texte_cool.h"
#include "config.h"
#include "menu_game.h"
#include "make_bonus.h"
#include "txt_data.h"
#include "meteo_pluie.h"
#include "meteo_neige.h"
#include "bulle.h"
#include "blip.h"
#include "blop.h"
#include "restore.h"
#include "key_translator.h"
#include "menu_main.h"

#include "l_timer.h"
#include "trace.h"
#include "precache.h"

Personnage	dummyPlayer;
int glorf;

//-----------------------------------------------------------------------------

#define TXT_TIME		828


//-----------------------------------------------------------------------------

Game::Game(): player1(NULL), player2(NULL), next_goutte(0), next_flocon(0), show_fps(false), show_lists(false), tupdate(0), tdraw(12), in_game(false), go_to_menu(false)
{
	briefing = false;
}

//-----------------------------------------------------------------------------

Game::~Game()
{
}

void Game::Pause()
{
    if(player1 != NULL || player2 != NULL)
    go_to_menu = true;
    musicmanager.stop();

    stop_music();
}

void Game::Resume()
{
    musicmanager.play();

    resume_music();
}

//-----------------------------------------------------------------------------

void Game::jouePartie(int nbj, int idj)
{
	if (app_killed)
		return;

	CINEPlayer	cine;
	bool		letsgo = true;
	int			i;

	// Bidon
	//
	pbk_inter.close();///fait planter si selectplayer n'est pas appelé
	mbk_interl.stop();

	// Charge Tout
	//

	if (!chargePartie()) {
		releasePartie();
		return;
	}

	wait_for_death = 0;
	current_zik = -1;

	if (idj == 0)
		player1 = new Blip();
	else
		player1 = new Blop();


	player1->ctrl = &ctrlP1;
	list_joueurs.ajoute((void*) player1);

	if (nbj == 2) {
		if (idj == 0)
			player2 = new Blop();
		else
			player2 = new Blip();

		player2->ctrl = &ctrlP2;
		list_joueurs.ajoute((void*) player2);
	}


	// Joue à tous les niveaux
	//
	cowBombOn = false;
	last_perfect1 = last_perfect2 = false;
	int nbNiv = 0;
	i = 0;



	while (i < nb_part && letsgo && !app_killed) {


		if (type_part[i] == PART_LEVEL) {
		    LOGI("jouNiveau");
			letsgo = joueNiveau(fic_names[i], type_lvl[i]);

			if (!cowBombOn) {
				if (player1 != NULL)
					player1->nb_cow_bomb = 1;

				if (player2 != NULL)
					player2->nb_cow_bomb = 1;

				cowBombOn = true;
			}
		} else if (type_part[i] == PART_BRIEFING) {
			showBriefing(fic_names[i]);
		} else {
		    LOGI("PLAY scene");
			cine.playScene(fic_names[i], primSurface, backSurface);
		}

		i += 1;
	}


	if (letsgo && !app_killed) {
		MusicBank	mbk;
		MusicBank	mbk2;
		PictureBank	pbk;

		pbk.loadGFX("data/theend.gfx", DDSURF_BEST, false);
		mbk.open("data/credits.mbk");
		mbk2.open("data/end.mbk", false);
		cine.loadPBK("data/end.gfx");
		mbk.play(1);
		cine.playScene("data/end.cin", primSurface, backSurface);
		mbk.stop();

		pbk[1]->PasteTo(backSurface, 0, 0);
		DDFlip();
		pbk[1]->PasteTo(backSurface, 0, 0);
		DDFlip();

		if (!in.anyKeyPressed())
			mbk2.play(0);

		in.waitClean();
		in.waitKey();
		in.waitClean();
		mbk2.stop();

		mbk.play(0);
		showCredits(true);
		mbk2.close();

		pbk[0]->PasteTo(backSurface, 0, 0);
		DDFlip();
		pbk[0]->PasteTo(backSurface, 0, 0);
		DDFlip();

		pbk.close();
		/*in.waitClean();
		in.waitKey();
		in.waitClean();*/
		bool pre = false;
		while(1)
		{
		    in.update();
		    if(in.so_pressing())
		    pre = true;
		    if(in.so_up() && pre)
		    break;

		    in.refresh();
		}

		mbk.stop();
		mbk.close();

		showPE(false);
	}

	LOGI("LOADING quit");
	// Désalloue tout
	//
	releasePartie();

	pbk_inter.loadGFX("data/inter.gfx", DDSURF_BEST);

	if (!skipped && !app_killed) {
		if (!letsgo) {
			showGameOver();
		}

		getHiscore();
		showHighScores();
	}

	if (player1 != NULL) {
		delete player1;
		player1 = NULL;
	}

	if (player2 != NULL) {
		delete player2;
		player2 = NULL;
	}
}


//-----------------------------------------------------------------------------

bool Game::joueNiveau(const char * nom_niveau, int type)
{
	int		p1_life;	// Si il s'agit d'un niveau bonus on
	bool	p1_bringBack;
	int		p2_life;	// conserve le nombre de vies des joueurs
	bool	p2_bringBack;

	// Little init
	//
	joueurs_morts	 = false;
	niveau_fini		 = false;
	skipped			 = false;
	wait_for_victory = -1;

	etape_timer		 = 0;
	teta_go			 = 0;
	fleche_go		 = false;
	delai_go		 = 0;

	scroll_locked	= false;
	scroll_speed	= 0;
	no_scroll1		= false;
	no_scroll2		= false;

	hold_fire		= false;

	intensite_meteo			= 0;
	dy_tremblement			= 0;
	etape_tremblement		= 0;
	amplitude_tremblement	= 0;

	n_cache		= 0;

	for (int i = 0; i <= 10; i++)
		game_flag[i] = 0;

	clearTexteCool();

	if (!chargeNiveau(nom_niveau))
		return false;

	if (strcmp(nom_niveau, "data/snorkniv.lvl") == 0 || strcmp(nom_niveau, "data/snorkniv2.lvl") == 0) {
		okLanceFlame = false;
	} else {
		okLanceFlame = true;
	}

	// Place les joueurs et initialise qq trucs
	//
	if (player1 != NULL && player1->nb_life > 0) {
		player1->x = xstart1;
		player1->y = ystart1;
		player1->etat = ETAT_NORMAL;
		player1->etape = 0;
		player1->ss_etape = 0;
		player1->dir = BBDIR_DROITE;
		player1->tire = false;

		if (type == LVL_BONUS) {
			p1_life = player1->nb_life;
			p1_bringBack = true;

			if (p1_life > 0)
				player1->nb_life = 1;
		}
	} else {
		p1_bringBack = false;
	}

	if (player2 != NULL && player2->nb_life > 0) {
		player2->x = xstart2;
		player2->y = ystart2;
		player2->etat = ETAT_NORMAL;
		player1->etape = 0;
		player1->ss_etape = 0;
		player2->dir = BBDIR_DROITE;
		player2->tire = false;

		if (type == LVL_BONUS) {
			p2_life = player2->nb_life;
			p2_bringBack = true;

			if (p2_life > 0)
				player2->nb_life = 1;
		}
	} else {
		p2_bringBack = false;
	}

	// Règlages conditionnels
	//
	if (type == LVL_BONUS || type == LVL_COMPLETE || type == LVL_FIRST || type == LVL_END) {
		nb_ennemis_created = 0;

		if (player1 != NULL) {
			player1->setKilled(0);

			if (type != LVL_END) {
				player1->etat = ETAT_COME_BACK;
				player1->y = -50;
				player1->y_to_go = ystart1;
			}

			player1->id_arme = ID_M16;
			player1->latence_arme = 3;
			player1->nb_etape_arme = 5;
			player1->cadence_arme = 10;
			player1->poid_arme = 1;
			player1->perfect = true;
			player1->pv = 5;

			if (last_perfect1) {
				player1->setSuperWeapon();
			}
		}

		if (player2 != NULL) {
			player2->setKilled(0);

			if (type != LVL_END) {
				player2->etat = ETAT_COME_BACK;
				player2->y = -50;
				player2->y_to_go = ystart2;
			}

			player2->id_arme = ID_M16;
			player2->latence_arme = 3;
			player2->nb_etape_arme = 5;
			player2->cadence_arme = 10;
			player2->poid_arme = 1;
			player2->perfect = true;
			player2->pv = 5;

			if (last_perfect2) {
				player2->setSuperWeapon();
			}
		}
	}

	last_perfect1 = last_perfect2 = false;

	// Niveau bonus = temps limite
	//
	if (type == LVL_BONUS)
		niveau_bonus = true;
	else
		niveau_bonus = false;

	// Règle l'offset sur les joueurs
	//
	/*
		list_joueurs.start();
		Sprite * s = (Sprite*) list_joueurs.info();
		offset = s->x;
		offset -= (offset%640);

		n_img = offset / 640;
		xTex = 0;

		next_x = offset % vbuffer_wide;
		next_x = next_x - (next_x & 1);
	*/
	list_joueurs.start();
	Sprite * s = (Sprite*) list_joueurs.info();
	offset = s->x;
	offset -= (offset % 640);

	n_img = 0;
	xTex = 0;
	n_cache = 0;
	next_x = 0;

	debug << "---------------------------------------------------------------\n";
	debug << "Now getting into game loop.\n";
	debug << "---------------------------------------------------------------\n";

	/*DDSCAPS2		ddscaps2dummy;
	DWORD			vid_mem1;
	DWORD			vid_mem2;

	ZeroMemory(&ddscaps2dummy, sizeof(ddscaps2dummy));
	ddscaps2dummy.dwCaps = DDSCAPS_VIDEOMEMORY;
	graphicInstance->GetAvailableVidMem(&ddscaps2dummy, &vid_mem1, &vid_mem2);

	debug << "Available video memory : " << (vid_mem2 >> 10) << " Ko\n";*/

	Sleep(2000);

	if (briefing) {
		DDBLTFX		ddfx;
		RECT		r;

		ZeroMemory(&ddfx, sizeof(ddfx));
		ddfx.dwSize = sizeof(ddfx);
		ddfx.dwFillColor = 0; // Noir

		r.left	= 0;
		r.right = 640;
		r.top	= 0;
		r.bottom = 480;

		//backSurface->Blt(&r, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddfx);
		backSurface->FillRect(&r, 0);

		pbk_briefing[0]->PasteTo(backSurface, 0, 0);
		LOGI("PRESS a key");
		fnt_cool.printC(backSurface, 320,430, "TOUCH TO BEGIN");
		DDFlip();

		mbk_inter.play(2);
		///MODIF touch
		//in.waitClean();
		//in.waitKey();
		while(1)
		{
		    in.update();
		    if(in.so_up())
		    break;
		    in.refresh();
		}
		pbk_briefing.close();
		briefing = false;
	}

	// Update quelques trucs
	//
	updateEvents();
	updateAll();

	// Pour le mode automatique
	//
	time = LGetTime();
	dtime = 0;

	// Boucle principale
	//
	while (!joueurs_morts && !niveau_fini && !skipped && !app_killed)
	{
		gameLoop();
		updateVictoryAndDefeat();
	}

	if (joueurs_morts)
		debug << "Players died\n";
	if (niveau_fini)
		debug << "Level complete\n";
	if (skipped)
		debug << "User skipped\n";
	if (app_killed)
		debug << "Application killed\n";

	if (player1 != NULL) {
		player1->endLevel();
	}

	if (player2 != NULL) {
		player2->endLevel();
	}

	// Coupe les musiques
	//
	current_zik = -1;
	if (music_on)
		mbk_niveau.stop();

	// S'il s'agissait d'un niveau bonus on restaure les vies des
	// joueurs + on ne peut pas perdre
	//
	if (type == LVL_BONUS && !skipped && !app_killed) {
		if (player1 != NULL && p1_bringBack) {
			if (player1->a_detruire && p1_life > 0) {
				player1->a_detruire = false;
				list_joueurs.ajoute((void*) player1);
			}

			player1->nb_life = p1_life;
		}

		if (player2 != NULL && p2_bringBack) {
			if (player2->a_detruire  && p2_life > 0) {
				player2->a_detruire = false;
				list_joueurs.ajoute((void*) player2);
			}

			player2->nb_life = p2_life;
		}

		niveau_fini = true;
	}


	// Récapitulatif de fin de niveau
	//
	if (niveau_fini && !joueurs_morts && type != LVL_END) {
		drawAll(false);
		DDFlip();
		drawAll(false);

		if ((type == LVL_BONUS && !skipped && game_flag[FLAG_TIMER] > 0) || type == LVL_COMPLETE || type == LVL_LAST) {
			if (player1 != NULL) {
				last_perfect1 = player1->perfect;
			}

			if (player2 != NULL) {
				last_perfect2 = player2->perfect;
			}

			showPE((type == LVL_BONUS));
		} else if (type == LVL_BONUS) {
			showPE(true, true);
		}
	} else if (type == LVL_BONUS) {
		showPE(true, true);
	}

	drawAll(false);
	drawLoading();
	DDFlipV();

	// Libére la mémoire
	//
	releaseNiveau();

	return niveau_fini;
}


//-----------------------------------------------------------------------------

bool Game::chargeNiveau(const char * nom_niveau)
{
	int		fic;
	char	buffer[20];
	char	buffer2[70];

	///MODIF open
	//fic = _open(nom_niveau, _O_RDONLY | _O_BINARY);
	Parseur parseur;

	///MODIF open
	//if (fic == - 1) {
	if(parseur.open(nom_niveau) == false) {
		debug << "Game::chargeNiveau() -> Cannot load <" << nom_niveau << ">\n";
		return false;
	}

	debug << "---------------------------------------------------------------\n";
	debug << "Loading level <" << nom_niveau << ">\n";
	debug << "---------------------------------------------------------------\n";


	// GFX decors
	//
	///MODIF read
	//_read(fic, buffer, 20);
	parseur.read(buffer, 20);

	strcpy(buffer2, "data/");
	strcat(buffer2, buffer);

	if (!pbk_decor.loadGFX(buffer2, DDSURF_SYSTEM)) {
		debug << "Game::chargeNiveau() -> Cannot load " << buffer2 << " as background\n";
		return false;
	}

	debug << "Successfully loaded <" << buffer2 << "> as background\n";

	// GFX niveau (fonds animés & co)
	//
	///MODIF read
	//_read(fic, buffer, 20);
	parseur.read(buffer, 20);

	if (strlen(buffer) != 0) {
		strcpy(buffer2, "data/");
		strcat(buffer2, buffer);

		if (!pbk_niveau.loadGFX(buffer2, mem_flag)) {
			debug << "Game::chargeNiveau() -> Cannot load " << buffer2 << " as level stuff\n";
			return false;
		}

		debug << "Successfully loaded <" << buffer2 << "> as level stuff\n";
	}

	// GFX ennemis
	//
	///MODIF read
	//_read(fic, buffer, 20);
	parseur.read(buffer, 20);

	if (strlen(buffer) != 0) {
		strcpy(buffer2, "data/");
		strcat(buffer2, buffer);

		if (!pbk_ennemis.loadGFX(buffer2, mem_flag)) {
			debug << "Game::chargeNiveau() -> Cannot load " << buffer2 << " as ennemies\n";
			return false;
		}

		debug << "Successfully loaded <" << buffer2 << "> as ennemies\n";
	}

	// SBK ennemis
	//
	///MODIF read
	//_read(fic, buffer, 20);
	parseur.read(buffer, 20);

	if (strlen(buffer) != 0) {
		strcpy(buffer2, "data/");
		strcat(buffer2, buffer);

		if (!sbk_niveau.loadSFX(buffer2)) {
			debug << "Game::chargeNiveau() -> Cannot load " << buffer2 << " as SBK\n";
			return false;
		}

		debug << "Successfully loaded <" << buffer2 << "> as SBK\n";
	}

	// Fichier MBK
	//
	///MODIF read
	//_read(fic, buffer, 20);
	parseur.read(buffer, 20);

	if (strlen(buffer) != 0) {
		strcpy(buffer2, "data/");
		strcat(buffer2, buffer);
		strcpy(current_mbk, buffer2);

		if (music_on) {
			if (!mbk_niveau.open(buffer2)) {
				debug << "Game::chargeNiveau() -> Cannot load " << buffer2 << " as MKB\n";
				return false;
			}
			debug << "Successfully loaded <" << buffer2 << "> as MBK\n";
		}
	} else
		strcpy(current_mbk, "");


	// Fichier RPG itself
	//
	///MODIF read
	//_read(fic, buffer, 20);
	parseur.read(buffer, 20);

	if (strlen(buffer) != 0) {
		strcpy(buffer2, "data/");
		strcat(buffer2, buffer);
		rpg.attachFile(buffer2);

		// Precache le fichier RPG
		//
		Precache(buffer2);

		debug << "Successfully loaded <" << buffer2 << "> as RPG file\n";
	}


	// GFX rpg
	//
	///MODIF read
	//_read(fic, buffer, 20);
	parseur.read(buffer, 20);

	if (strlen(buffer) != 0) {
		strcpy(buffer2, "data/");
		strcat(buffer2, buffer);

		if (!pbk_rpg.loadGFX(buffer2, mem_flag)) {
			debug << "Game::chargeNiveau() -> Cannot load " << buffer2 << " as RPG GFX\n";
			return false;
		}

		debug << "Successfully loaded <" << buffer2 << "> as RPG GFX\n";
	}

	// Taille du niveau
	//
	///MODIF read
	//_read(fic, &scr_level_size, sizeof(scr_level_size));
	parseur.read(&scr_level_size, sizeof(scr_level_size));

	level_size = scr_level_size * 640;

	// Numéros des écrans à afficher (comme des tiles)
	//
	num_decor = new int[scr_level_size];
	for (int i = 0; i < scr_level_size; i++)
	{
	    ///MODIF read
	    //_read(fic, &num_decor[i], sizeof(int));
	    parseur.read(&num_decor[i], sizeof(int));
	}


	// Coordonnées de départ des joueurs
	//
	///MODIF read
	//_read(fic, &xstart1, sizeof(xstart1));
	//_read(fic, &ystart1, sizeof(ystart1));
	//_read(fic, &xstart2, sizeof(xstart2));
	//_read(fic, &ystart2, sizeof(ystart2));
	parseur.read(&xstart1, sizeof(xstart1));
	parseur.read(&ystart1, sizeof(ystart1));
	parseur.read(&xstart2, sizeof(xstart2));
	parseur.read(&ystart2, sizeof(ystart2));


	// Conditions de victoire
	//
	///MODIF read
	//_read(fic, &vic_x, sizeof(vic_x));
	//_read(fic, &vic_flag1, sizeof(vic_flag1));
	//_read(fic, &vic_val1, sizeof(vic_val1));
	//_read(fic, &vic_flag2, sizeof(vic_flag2));
	//_read(fic, &vic_val2, sizeof(vic_val2));
	parseur.read(&vic_x, sizeof(vic_x));
	parseur.read(&vic_flag1, sizeof(vic_flag1));
	parseur.read(&vic_val1, sizeof(vic_val1));
	parseur.read(&vic_flag2, sizeof(vic_flag2));
	parseur.read(&vic_val2, sizeof(vic_val2));

	//
	// Plateformes
	//
	y_plat = new int * [NB_MAX_PLAT];

	for (int i = 0; i < NB_MAX_PLAT; i++) {
		y_plat[i] = new int[level_size];
		///MODIF read
		//_read(fic, y_plat[i], (level_size)*sizeof(int));
		parseur.read(y_plat[i], (level_size)*sizeof(int));
	}

	//
	// Murs opaques
	//
	int	level_size_8 = level_size / 8;
	murs_opaques = new bool * [60];

	for (int i = 0; i < 60; i++) {
		murs_opaques[i] = new bool[level_size_8];
		///MODIF read
		//_read(fic, murs_opaques[i], (level_size_8)*sizeof(bool));
		parseur.read(murs_opaques[i], (level_size_8)*sizeof(bool));
	}

	//
	// Murs sanglants
	//
	murs_sanglants = new bool * [60];

	for (int i = 0; i < 60; i++) {
		murs_sanglants[i] = new bool[level_size_8];
		///MODIF read
		//_read(fic, murs_sanglants[i], (level_size_8)*sizeof(bool));
		parseur.read(murs_sanglants[i], (level_size_8)*sizeof(bool));
	}

	//
	// Charge les évenements
	//
	FICEVENT			ficevent;
	EventEnnemi*		event_ennemi;
	EventGenEnnemi *	event_gennemi;
	EventLock *			event_lock;
	EventScrollSpeed *	event_scroll_speed;
	EventSetFlag *		event_set_flag;
	EventHoldFire *		event_hold_fire;
	EventGenBonus *		event_gen_bonus;
	EventTexte *		event_texte;
	EventFondAnime *	event_fond_anime;
	EventPremierPlan *	event_pplan;
	EventRPG *			event_rpg;
	EventMusic *		event_music;
	EventMiFond *		event_mi_fond;
	EventMeteo *		event_meteo;
	EventBonus *		event_bonus;
	EventVehicule *		event_vehicule;
	EventSon *			event_son;
	int					nb_events;

	///MODIF read
	//_read(fic, &nb_events, sizeof(nb_events));
	parseur.read(&nb_events, sizeof(nb_events));


	for (int i = 0; i < nb_events; i++) {
	    ///MODIF read
		//_read(fic, &ficevent, sizeof(ficevent));
		parseur.read(&ficevent, sizeof(ficevent));

		switch (ficevent.event_id) {
			case EVENTID_ENNEMI:
				event_ennemi = new EventEnnemi();

				event_ennemi->x_activation = ficevent.x_activation;
				event_ennemi->id_ennemi = ficevent.id;
				event_ennemi->x = ficevent.x;
				event_ennemi->y = ficevent.y;
				event_ennemi->sens = ficevent.sens;

				list_event_endormis.ajoute((void*) event_ennemi);
				break;

			case EVENTID_ENNEMI_GENERATOR:
				event_gennemi = new EventGenEnnemi();

				event_gennemi->x_activation = ficevent.x_activation;
				event_gennemi->id_ennemi = ficevent.id;
				event_gennemi->x = ficevent.x;
				event_gennemi->y = ficevent.y;
				event_gennemi->sens = ficevent.sens;
				event_gennemi->capacite = ficevent.capacite;
				event_gennemi->periode = ficevent.periode;
				event_gennemi->tmp = ficevent.tmp;

				list_event_endormis.ajoute((void*) event_gennemi);
				break;

			case EVENTID_LOCK:
				event_lock = new EventLock();

				event_lock->x_activation = ficevent.x_activation;
				event_lock->cond = ficevent.cond;
				event_lock->flag = ficevent.flag;
				event_lock->val = ficevent.val;

				list_event_endormis.ajoute((void*) event_lock);
				break;

			case EVENTID_FORCE_SCROLL:
				event_scroll_speed = new EventScrollSpeed();

				event_scroll_speed->x_activation = ficevent.x_activation;
				event_scroll_speed->speed = ficevent.speed;

				list_event_endormis.ajoute((void*) event_scroll_speed);
				break;

			case EVENTID_FLAG:
				event_set_flag = new EventSetFlag();

				event_set_flag->x_activation = ficevent.x_activation;
				event_set_flag->flag = ficevent.flag;
				event_set_flag->val = ficevent.val;

				list_event_endormis.ajoute((void*) event_set_flag);
				break;

			case EVENTID_HOLD_FIRE:
				event_hold_fire = new EventHoldFire();

				event_hold_fire->x_activation = ficevent.x_activation;
				event_hold_fire->flag = ficevent.flag;
				event_hold_fire->val = ficevent.val;

				list_event_endormis.ajoute((void*) event_hold_fire);
				break;

			case EVENTID_BONUS_GENERATOR:
				event_gen_bonus = new EventGenBonus();

				event_gen_bonus->x_activation = ficevent.x_activation;
				event_gen_bonus->type = ficevent.id;
				event_gen_bonus->periode = ficevent.periode;

				list_event_endormis.ajoute((void*) event_gen_bonus);
				break;

			case EVENTID_TEXT:
				event_texte = new EventTexte();

				event_texte->x_activation = ficevent.x_activation;
				event_texte->ntxt = ficevent.n_txt;
				event_texte->cond = ficevent.cond;
				event_texte->flag = ficevent.flag;
				event_texte->val = ficevent.val;

				list_event_endormis.ajoute((void*) event_texte);
				break;

			case EVENTID_FOND_ANIME:
				event_fond_anime = new EventFondAnime();

				event_fond_anime->x_activation = ficevent.x_activation;
				event_fond_anime->id_fond = ficevent.id;
				event_fond_anime->x = ficevent.x;
				event_fond_anime->y = ficevent.y;

				list_event_endormis.ajoute((void*) event_fond_anime);
				break;

			case EVENTID_MIFOND:
				event_mi_fond = new EventMiFond();

				event_mi_fond->x_activation = ficevent.x_activation;
				event_mi_fond->id = ficevent.id;
				event_mi_fond->x = ficevent.x;
				event_mi_fond->y = ficevent.y;

				list_event_endormis.ajoute((void*) event_mi_fond);
				break;

			case EVENTID_PREMIER_PLAN:
				event_pplan = new EventPremierPlan();

				event_pplan->id_fond = ficevent.id;
				event_pplan->x_activation = ficevent.x_activation;
				event_pplan->x = ficevent.x;
				event_pplan->y = ficevent.y;

				list_event_endormis.ajoute((void*) event_pplan);
				break;

			case EVENTID_RPG:
				event_rpg = new EventRPG();

				event_rpg->x_activation = ficevent.x_activation;
				event_rpg->num = ficevent.id;
				event_rpg->cond = ficevent.cond;
				event_rpg->flag = ficevent.flag;
				event_rpg->val = ficevent.val;

				list_event_endormis.ajoute((void*) event_rpg);
				break;

			case EVENTID_MUSIC:
				event_music = new EventMusic();

				event_music->x_activation = ficevent.x_activation;
				event_music->id = ficevent.id;
				event_music->play = ficevent.play;

				list_event_endormis.ajoute((void*) event_music);
				break;

			case EVENTID_METEO:
				event_meteo = new EventMeteo();

				event_meteo->x_activation = ficevent.x_activation;
				event_meteo->intensite = ficevent.intensite;
				event_meteo->type = ficevent.id;

				list_event_endormis.ajoute((void*) event_meteo);
				break;

			case EVENTID_BONUS:
				event_bonus = new EventBonus();
				event_bonus->x_activation = ficevent.x_activation;
				event_bonus->type = ficevent.id;
				event_bonus->x = ficevent.x;
				event_bonus->y = ficevent.y;

				list_event_endormis.ajoute((void*) event_bonus);
				break;

			case EVENTID_TURRET:
				event_vehicule = new EventVehicule();
				event_vehicule->x_activation = ficevent.x_activation;
				event_vehicule->id_vehicule = ficevent.id;
				event_vehicule->x = ficevent.x;
				event_vehicule->y = ficevent.y;
				event_vehicule->dir = ficevent.dir;

				list_event_endormis.ajoute((void*) event_vehicule);
				break;

			case EVENTID_SON:
				event_son = new EventSon();
				event_son->x_activation = ficevent.x_activation;
				event_son->nsnd = ficevent.id;

				list_event_endormis.ajoute((void*) event_son);
				break;
		}
	}

	///MODIF close
	//_close(fic);
	parseur.close();


	debug << "Successfully loaded all level files\n";

	return true;
}


//-----------------------------------------------------------------------------

void Game::releaseNiveau()
{
	if (num_decor != NULL) {
		delete [] num_decor;
		num_decor = NULL;
	}

	if (y_plat != NULL) {
		for (int i = 0; i < NB_MAX_PLAT; i++)
			delete [] y_plat[i];

		delete [] y_plat;
		y_plat = NULL;
	}

	if (murs_sanglants != NULL) {
		for (int i = 0; i < 60; i++)
			delete [] murs_sanglants[i];

		delete [] murs_sanglants;
		murs_sanglants = NULL;
	}

	if (murs_opaques != NULL) {
		for (int i = 0; i < 60; i++)
			delete [] murs_opaques[i];

		delete [] murs_opaques;
		murs_opaques = NULL;
	}

	mbk_niveau.close();

	sbk_niveau.close();

	pbk_ennemis.close();
	pbk_decor.close();
	pbk_niveau.close();
	pbk_rpg.close();

	list_event_endormis.vide();
	list_event.vide();

	list_tirs_bb.vide_porc();
	list_cow.vide();
	list_impacts.vide_porc();

	list_vehicules.vide();

	list_ennemis.vide();
	list_tirs_ennemis.vide();
	list_gen_ennemis.vide();

	list_bonus.vide();
	list_gen_bonus.vide();

	list_txt_cool.vide();

	list_fonds_animes.vide();
	list_fonds_statiques.vide();
	list_premiers_plans.vide();
	list_plateformes_mobiles.vide();

	list_giclures.vide();
	list_gore.vide();

	list_meteo.vide_porc();
	list_bulles.vide();
}


//-----------------------------------------------------------------------------

void Game::updateAll()
{
	/*
		if ( scroll_speed < 1)
			scroll_speed = 1;
	*/

	tupdate = LGetTime();

	manageMsg();	// Fucking windaube!!!

	if (checkRestore())
		time = LGetTime();

	phase = !phase;

	if (phase)
		slow_phase = !slow_phase;

	// Met à jour les touches
	//
	///in.update();  //dans le gameloop
	box_manager.manage(99);
	updateTouch();
	//LOGI("updateAll");///UPDATE du jeu
	// Ok bonus ?
	//
	okBonus = false;

	if (player1 != NULL) {
		okBonus = okBonus || player1->okBonus();
	}

	if (player2 != NULL) {
		okBonus = okBonus || player2->okBonus();
	}

	// Update tout ce qu'il faut
	//
	if (!no_scroll1 && !no_scroll2)
		updateScrolling(false);

	updateEvents();

	// On update le scroll une deuxième fois à cause des Locks
	//
	if (!no_scroll1 && !no_scroll2)
		updateScrolling();

	updateCheat();
	updateTremblements();

	if (game_flag[FLAG_BULLES])
		updateBulles();

	if (type_meteo == METEO_PLUIE || type_meteo == METEO_NEIGE)
		updateMeteo();

	updateFondsStatiques();
	updateFondsAnimes();
	updatePlateformesMobiles();
	updateVehicules();
	updateJoueurs();
	updateTirsJoueurs();
	updateImpacts();
	updateEnnemis();
	updateGore();
	updateTirsEnnemis();
	updateGiclures();
	updateBonus();
	updatePremiersPlans();

	updateTexteCool();
	updateGenEnnemis();
	updateGenBonus();
	updateLock();
	updateHoldFire();
	updateTeteTurc();
	updateFlags();
	updateFlecheGo();

	if (type_meteo == METEO_DEFORME && intensite_meteo != 0)
		updateDeformation();


	manageCollisions();


	// Retire les trucs inutiles des listes
	//
	cleanLists();

	updateMenu();

	tupdate = tupdate - LGetTime();

	updateRPG();

	///in.refresh(); //dans le gameloop
}

void Game::drawTools()
{
    if(in.padded )
    {
    int xx = in.pad_x-85;
    int yy = in.pad_y-100;

    //if(in.haut == false && in.bas == false && in.droit == false && in.gauche == false)
    draw2(xx, yy, &p_joystick);

    float p_x, p_y;
    float ang = (M_PI*in.angle)/180.f;
    float coef = 0;

    coef = in.dist/85.f;
    if(coef >= 1)
    coef = 1;

    p_x = (coef*cos(ang)*85.f)-30.f;
    p_x+=in.pad_x;
    p_y = -(coef*sin(ang)*85.f)-35.f;
    p_y+=in.pad_y;

    if(in.dist != 0 && in.pad_x != 0 && in.pad_y != 0 && in.angle != 0)
    draw2(p_x, p_y, &stick);

    /*if(in.haut == true)
    {
        if(in.droit == false && in.gauche == false)
        draw2(xx, yy, &p_pad0);
        if(in.droit == true)
        draw2(xx, yy, &p_pad1);
        if(in.gauche == true)
        draw2(xx, yy, &p_pad7);
    }
    else if(in.bas == true)
    {
        if(in.droit == false && in.gauche == false)
        draw2(xx, yy, &p_pad4);
        if(in.droit == true)
        draw2(xx, yy, &p_pad3);
        if(in.gauche == true)
        draw2(xx, yy, &p_pad5);
    }
    else if(in.droit == true)
    draw2(xx, yy, &p_pad2);
    else if(in.gauche == true)
    draw2(xx, yy, &p_pad6);*/

    }


    draw2(595, 5,  &p_pause);

    if(in.tirer)
    draw2(495, 400, &p_shoot_p);
    else
    draw2(495, 400, &p_shoot);

    if(in.sauter)
    draw2(560, 320, &p_jump_p);
    else
    draw2(560, 320, &p_jump);

    if(player1 != NULL && player1->nb_cow_bomb >= 1)
    {
        if(box_manager.get_state("ulti") == TOUCH_DOWN)
        draw2(575, 405, &p_ulti_p);
        else
        draw2(575, 405, &p_ulti);
    }

    /*
    p_ulti
    p_jump
    p_shoot*/
}


//-----------------------------------------------------------------------------

void Game::drawAll(bool flip)
{
	manageMsg();	// Fucking windaube!!!

	if (checkRestore())
		time = LGetTime();

	tdraw = LGetTime();

	if (!flip) {
		phase = false;
		slow_phase = false;
	}

	fps_current_count += 1;

	/*if (mustFixGforceBug) {
		RECT	r;

		r.top	= 10;
		r.bottom = 150;
		r.left	= 200;
		r.right = 440;

		backSurface->Blt(&r, videoA, NULL, DDBLT_WAIT, 0);
	}*/

	drawScrolling();
	drawFondsStatiques();


	drawFondsAnimes();

	if (game_flag[FLAG_BULLES])
		drawBulles();


	drawPlateformesMobiles();
	drawGiclures();
	drawGore();

	drawEnnemis();
	drawTirsEnnemis();
	drawBonus();
	drawTirsJoueurs();
	drawJoueurs();
	drawVehicules();
	drawImpacts();
	drawCow();
	drawMeteo();
	drawPremiersPlans();


	if (type_meteo == METEO_DEFORME && intensite_meteo != 0)
		drawDeformation();

	drawTremblements();
	drawHUB();
	drawTimer();
	drawFlecheGo();
	drawTexteCool();

	drawDebugInfos();


	// Virer la bande qui déconne si besoin est
	//
	if (vbuffer_wide == 640) {
		DDBLTFX         ddfx;
		RECT	r;

		ZeroMemory(&ddfx, sizeof(ddfx));
		ddfx.dwSize = sizeof(ddfx);
		ddfx.dwFillColor = 0; // Noir

		r.left	= 638;
		r.right = 640;
		r.top	= 0;
		r.bottom = 480;

		backSurface->/*Blt(&r, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddfx)*/FillRect(&r,0);
	}
	drawTools();

	RECT	r;

	r.top	 = 0;
	r.left	 = 0;
	r.right	 = 640;
	r.bottom = 480;

	if (flip) {
		DDFlip();
	}

	tdraw = LGetTime() - tdraw;
}


//-----------------------------------------------------------------------------

void Game::gameLoop()
{
	static const int GOOD = 118;
	static const int INT_SIZE = 50;
	static const int MARGE = 10;

	static int	marge[INT_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	                             };
	static int	im = 0;

	dtime += LGetTime() - time;
	time = LGetTime();

	int sum = 0;

	for (int i = 0; i < INT_SIZE; i++) {
		sum += marge[i];
	}

	glorf = sum / INT_SIZE;

	in.update();

	if (glorf >= -MARGE && glorf <= MARGE) {
		updateAll();
		dtime = 0;
	} else {
		while (dtime >= GOOD) {
			updateAll();
			dtime -= GOOD;
		}
	}

	im += 1;
	im %= INT_SIZE;

	drawAll();
	in.refresh();

	DWORD ttotal = tupdate + tdraw;

	if (ttotal <= 0)
		ttotal = GOOD;
	else if (ttotal >= 5000)
		ttotal = GOOD;

	marge[im] = ttotal - GOOD;
}


//-----------------------------------------------------------------------------

void Game::releasePartie()
{
	pbk_blip.close();
	pbk_blop.close();
	pbk_bb.close();
	pbk_misc.close();
	pbk_rpg_bb.close();

	fnt_score_blip.close();
	fnt_score_blop.close();
	fnt_ammo.close();
	fnt_ammo_used.close();

	sbk_bb.close();
	sbk_misc.close();

	list_joueurs.vide_porc();
}



//-----------------------------------------------------------------------------

bool Game::chargePartie()
{
	// Charge les joueurs
	//
	debug << "---------------------------------------------------------------\n";
	debug << "Loading global game files...\n";
	debug << "---------------------------------------------------------------\n";

	if (!pbk_blip.loadGFX("data/blip.gfx", mem_flag))
		return false;

	debug << "Successfully loaded <blip.gfx>\n";

	if (!pbk_blop.loadGFX("data/blop.gfx", mem_flag))
		return false;

	debug << "Successfully loaded <blop.gfx>\n";

	// Charge BB
	//
	if (!pbk_bb.loadGFX("data/bb.gfx", mem_flag))
		return false;

	debug << "Successfully loaded <bb.gfx>\n";

	// Charge Divers
	//
	if (!pbk_misc.loadGFX("data/misc.gfx", mem_flag))
		return false;

	debug << "Successfully loaded <misc.gfx>\n";

	// Charge gueules BB
	//
	if (!pbk_rpg_bb.loadGFX("data/rpg_bb.gfx", mem_flag))
		return false;

	debug << "Successfully loaded <rpg_bb.gfx>\n";

	// Fonte score blip
	//
	if (!fnt_score_blip.load("data/scorei.lft", mem_flag))
		return false;

	debug << "Successfully loaded <scorei.lft>\n";

	// Fonte score blop
	//
	if (!fnt_score_blop.load("data/scoreo.lft", mem_flag))
		return false;

	debug << "Successfully loaded <scoreo.lft>\n";

	// Fonte munitions
	//
	if (!fnt_ammo.load("data/ammo1.lft", mem_flag))
		return false;

	debug << "Successfully loaded <ammo1.lft>\n";

	// Fonte munitions utilisées
	//
	if (!fnt_ammo_used.load("data/ammo2.lft", mem_flag))
		return false;

	debug << "Successfully loaded <ammo2.lft>\n";

	// Sons globaux
	//
	if (!sbk_misc.loadSFX("data/misc.sfx"))
		return false;

	debug << "Successfully loaded <misc.sfx>\n";

	// Sons BB
	//
	if (!sbk_bb.loadSFX("data/bb.sfx"))
		return false;

	debug << "Successfully loaded <bb.sfx>\n";

	// La liste des niveaux
	//
	if (!loadList("data/bb.lst"))
		return false;

	debug << "Successfully loaded <bb.lst>\n";
	debug << "Successfully loaded all needed global game files\n";

	return true;
}



//-----------------------------------------------------------------------------

void Game::updateJoueurs()
{
	Couille *	pl;

	list_joueurs.start();

	while (!list_joueurs.fin()) {
		pl = (Couille*) list_joueurs.info();
		pl->update();
		list_joueurs.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::updateTirsJoueurs()
{
	TirBB *		t;

	list_tirs_bb.start();

	while (!list_tirs_bb.fin()) {
		t = (TirBB*) list_tirs_bb.info();
		t->update();
		list_tirs_bb.suivant();
	}

	list_cow.start();

	while (!list_cow.fin()) {
		t = (TirBB*) list_cow.info();
		t->update();
		list_cow.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::drawJoueurs()
{
	Couille *	pl;

	list_joueurs.start();

	while (!list_joueurs.fin()) {
		pl = (Couille*) list_joueurs.info();
		pl->affiche();
		list_joueurs.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::drawTirsJoueurs()
{
	TirBB *		t;

	list_tirs_bb.start();

	while (!list_tirs_bb.fin()) {
		t = (TirBB*) list_tirs_bb.info();
		t->affiche();
		list_tirs_bb.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::cleanLists()
{
	Sprite *	s;

	list_joueurs.start();

	while (!list_joueurs.fin()) {
		s = (Sprite *) list_joueurs.info();

		if (s->aDetruire())
			list_joueurs.supprimePorc();
		else
			list_joueurs.suivant();
	}

	list_fonds_statiques.start();

	while (!list_fonds_statiques.fin()) {
		s = (Sprite *) list_fonds_statiques.info();

		if (s->aDetruire())
			list_fonds_statiques.supprime();
		else
			list_fonds_statiques.suivant();
	}

	list_tirs_bb.start();

	while (!list_tirs_bb.fin()) {
		s = (Sprite *) list_tirs_bb.info();

		if (s->aDetruire())
			list_tirs_bb.supprimePorc();
		else
			list_tirs_bb.suivant();
	}

	list_cow.start();

	while (!list_cow.fin()) {
		s = (Sprite *) list_cow.info();

		if (s->aDetruire())
			list_cow.supprime();
		else
			list_cow.suivant();
	}

	list_bulles.start();

	while (!list_bulles.fin()) {
		s = (Sprite *) list_bulles.info();

		if (s->aDetruire())
			list_bulles.supprime();
		else
			list_bulles.suivant();
	}

	list_impacts.start();

	while (!list_impacts.fin()) {
		s = (Sprite *) list_impacts.info();

		if (s->aDetruire())
			list_impacts.supprime();
		else
			list_impacts.suivant();
	}

	list_ennemis.start();

	while (!list_ennemis.fin()) {
		s = (Sprite *) list_ennemis.info();

		if (s->aDetruire())
			list_ennemis.supprime();
		else
			list_ennemis.suivant();
	}

	list_bonus.start();

	while (!list_bonus.fin()) {
		s = (Sprite *) list_bonus.info();

		if (s->aDetruire())
			list_bonus.supprime();
		else
			list_bonus.suivant();
	}

	GenEnnemi *	gennemi;

	list_gen_ennemis.start();

	while (!list_gen_ennemis.fin()) {
		gennemi = (GenEnnemi *) list_gen_ennemis.info();

		if (gennemi->aDetruire())
			list_gen_ennemis.supprime();
		else
			list_gen_ennemis.suivant();
	}

	GenBonus *	gbonus;

	list_gen_bonus.start();

	while (!list_gen_bonus.fin()) {
		gbonus = (GenBonus *) list_gen_bonus.info();

		if (gbonus->aDetruire())
			list_gen_bonus.supprime();
		else
			list_gen_bonus.suivant();
	}

	TexteCool *	txt;

	list_txt_cool.start();

	while (!list_txt_cool.fin()) {
		txt = (TexteCool *) list_txt_cool.info();

		if (txt->aDetruire())
			list_txt_cool.supprime();
		else
			list_txt_cool.suivant();
	}

	list_fonds_animes.start();

	while (!list_fonds_animes.fin()) {
		s = (Sprite *) list_fonds_animes.info();

		if (s->aDetruire())
			list_fonds_animes.supprime();
		else
			list_fonds_animes.suivant();
	}

	list_premiers_plans.start();

	while (!list_premiers_plans.fin()) {
		s = (Sprite *) list_premiers_plans.info();

		if (s->aDetruire())
			list_premiers_plans.supprime();
		else
			list_premiers_plans.suivant();
	}

	list_giclures.start();

	while (!list_giclures.fin()) {
		s = (Sprite *) list_giclures.info();

		if (s->aDetruire())
			list_giclures.supprime();
		else
			list_giclures.suivant();
	}

	list_tirs_ennemis.start();

	while (!list_tirs_ennemis.fin()) {
		s = (Sprite *) list_tirs_ennemis.info();

		if (s->aDetruire())
			list_tirs_ennemis.supprime();
		else
			list_tirs_ennemis.suivant();
	}

	list_meteo.start();

	while (!list_meteo.fin()) {
		s = (Sprite *) list_meteo.info();

		if (s->aDetruire())
			list_meteo.supprimePorc();
		else
			list_meteo.suivant();
	}

	list_gore.start();

	while (!list_gore.fin()) {
		s = (Sprite *) list_gore.info();

		if (s->aDetruire())
			list_gore.supprime();
		else
			list_gore.suivant();
	}

	list_plateformes_mobiles.start();

	while (!list_plateformes_mobiles.fin()) {
		s = (Sprite *) list_plateformes_mobiles.info();

		if (s->aDetruire())
			list_plateformes_mobiles.supprimePorc();
		else
			list_plateformes_mobiles.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::updateEvents()
{
	Event *		event;

	// Les évenements de la liste "endormie" sont mis dans la liste "en attente"
	// quand ils sont sur le point d'être activés
	//
	if (!list_event_endormis.estVide()) {
		list_event_endormis.start();
		event = (Event*) list_event_endormis.info();

		while (!list_event_endormis.estVide() && !list_event_endormis.fin() && event->aReveiller()) {
			list_event.ajoute((void*) event);
			list_event_endormis.supprimePorc(); // Porc bcoz l'évenement est transféré, pas détruit

			if (!list_event_endormis.estVide()) {
				list_event_endormis.start();
				event = (Event*) list_event_endormis.info();
			}
		}

	}


	// Si les évenements "en attente" doivent être activés, on les active
	//
	if (!list_event.estVide()) {
		list_event.start();

		while (!list_event.estVide() && !list_event.fin()) {
			event = (Event*) list_event.info();

			if (event->aActiver()) {
				event->doEvent();		// Surtout pas l'ordre inverse!
				list_event.supprime();	// Sinon on activerait un évenement supprimé!
			} else
				list_event.suivant();
		}
	}
}


//-----------------------------------------------------------------------------

void Game::drawEnnemis()
{
	Ennemi *	pl;

	list_ennemis.start();

	while (!list_ennemis.fin()) {
		pl = (Ennemi*) list_ennemis.info();
		pl->affiche();
		list_ennemis.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::updateEnnemis()
{
	Ennemi *	pl;

	list_ennemis.start();

	while (!list_ennemis.fin()) {
		pl = (Ennemi*) list_ennemis.info();
		pl->update();
		list_ennemis.suivant();
	}
}



//-----------------------------------------------------------------------------

void Game::manageCollisions()
{
	Tir *		tir;
	Ennemi *	ennemi;

	// Collisions TirsBB / Ennemis
	//
	list_tirs_bb.start();

	while (!list_tirs_bb.fin()) {
		tir = (Tir*) list_tirs_bb.info();

		list_ennemis.start();

		while (!list_ennemis.fin()) {
			ennemi = (Ennemi*) list_ennemis.info();

			if (tir->collision(ennemi))
				ennemi->estTouche(tir);

			list_ennemis.suivant();
		}

		list_tirs_bb.suivant();
	}

	// Collisions Vaches / Ennemis
	//
	list_cow.start();

	while (!list_cow.fin()) {
		tir = (Tir*) list_cow.info();

		list_ennemis.start();

		while (!list_ennemis.fin()) {
			ennemi = (Ennemi*) list_ennemis.info();

			if (tir->collision(ennemi))
				ennemi->estTouche(tir);

			list_ennemis.suivant();
		}

		list_cow.suivant();
	}

	// Collisions Joueurs / Bonus
	//
	Bonus *		bonus;
	Couille *	joueur;

	list_bonus.start();

	while (!list_bonus.fin()) {
		bonus = (Bonus*) list_bonus.info();

		list_joueurs.start();

		while (!list_joueurs.fin()) {
			joueur = (Couille*) list_joueurs.info();

			if (bonus->collision(joueur))
				bonus->estPris(joueur);

			list_joueurs.suivant();
		}

		list_bonus.suivant();
	}

	if (wait_for_victory <= 0) {
		// Collisions Joueurs / Ennemis
		//
		Ennemi *	ennemis;

		list_ennemis.start();

		while (!list_ennemis.fin()) {
			ennemis = (Ennemi*) list_ennemis.info();

			list_joueurs.start();

			while (!list_joueurs.fin()) {
				joueur = (Couille*) list_joueurs.info();

				if (ennemis->collision(joueur))
					joueur->estTouche(ennemis->degats());

				list_joueurs.suivant();
			}

			list_ennemis.suivant();
		}


		// Collisions Joueurs / tirs ennemis
		//
		list_tirs_ennemis.start();

		while (!list_tirs_ennemis.fin()) {
			tir = (Tir*) list_tirs_ennemis.info();

			list_joueurs.start();

			while (!list_joueurs.fin()) {
				joueur = (Couille*) list_joueurs.info();

				if (tir->collision(joueur))
					joueur->estTouche(tir->degats());

				list_joueurs.suivant();
			}

			list_tirs_ennemis.suivant();
		}
	}
}


//-----------------------------------------------------------------------------

void Game::updateGenEnnemis()
{
	GenEnnemi *	pl;

	list_gen_ennemis.start();

	while (!list_gen_ennemis.fin()) {
		pl = (GenEnnemi*) list_gen_ennemis.info();
		pl->update();
		list_gen_ennemis.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::updateLock()
{
	if (!scroll_locked)
		return;

	if ((cond_end_lock == 0 && list_ennemis.estVide()) ||
	        (cond_end_lock == 1 && list_gen_ennemis.estVide()) ||
	        (cond_end_lock == 2 && game_flag[flag_end_lock] == val_end_lock) ||
	        (cond_end_lock == 3 && game_flag[flag_end_lock] >= val_end_lock)) {
		scroll_locked = false;
		fleche_go = true;
		x_fleche_go = -10;
		nb_rebonds_go = 0;
	}

}



//-----------------------------------------------------------------------------

void Game::updateHoldFire()
{
	if (!hold_fire)
		return;

	if (game_flag[flag_hold_fire] == val_hold_fire)
		hold_fire = false;
}


//-----------------------------------------------------------------------------

void Game::updateBonus()
{
	Bonus *		t;

	list_bonus.start();

	while (!list_bonus.fin()) {
		t = (Bonus*) list_bonus.info();
		t->update();
		list_bonus.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::drawBonus()
{
	Bonus *	pl;

	list_bonus.start();

	while (!list_bonus.fin()) {
		pl = (Bonus*) list_bonus.info();
		pl->affiche();
		list_bonus.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::updateGenBonus()
{
	GenBonus * gb;

	list_gen_bonus.start();

	while (!list_gen_bonus.fin()) {
		gb = (GenBonus*) list_gen_bonus.info();
		gb->update();

		list_gen_bonus.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::drawHUB()
{
	Picture *	pic;
	char		buffer[20];


	if (player1 != NULL && player1->nb_life > 0) {
		drawHUBpv(20, 20, player1->pv);

		sprintf(buffer, "%07d", player1->getScore());

		if (player1->id_couille == ID_BLIP)
			fnt_score_blip.printR(backSurface, 190, 20, buffer);
		else
			fnt_score_blop.printR(backSurface, 190, 20, buffer);

		if (niveau_bonus) {
			fnt_rpg.print(backSurface, 4, 5, "Bonus");
			fnt_rpg.print(backSurface, 4, 20, "Stage");
		} else {
			sprintf(buffer, "%d", player1->nb_life);
			fnt_cool.print(backSurface, 5, 5, buffer);
		}

		switch (player1->id_arme) {
			case ID_M16:
				pic = pbk_misc[14];
				break;
			case ID_PM:
				pic = pbk_misc[8];
				break;
			case ID_LF:
				pic = pbk_misc[11];
				break;
			case ID_FUSIL:
				pic = pbk_misc[9];
				break;
			case ID_LASER:
				pic = pbk_misc[10];
				break;
		}

		pic->BlitTo(backSurface, 135, 50);

		if (player1->id_arme == ID_M16) {
			fnt_ammo.printC(backSurface, 135, 43, "*");
		} else {
			sprintf(buffer, "%d", player1->ammo);

			if (player1->tire && phase)
				fnt_ammo_used.printC(backSurface, 135, 43, buffer);
			else
				fnt_ammo.printC(backSurface, 135, 43, buffer);
		}


		for (int i = 0, dxt = 0; i < player1->nb_cow_bomb; i++, dxt += 23)
			pbk_misc[49]->BlitTo(backSurface, 90 + dxt, 65);
	}

	if (player2 != NULL && player2->nb_life > 0) {
		drawHUBpv(560, 20, player2->pv);

		sprintf(buffer, "%07d", player2->getScore());

		if (player2->id_couille == ID_BLIP)
			fnt_score_blip.print(backSurface, 450, 20, buffer);
		else
			fnt_score_blop.print(backSurface, 450, 20, buffer);

		if (niveau_bonus) {
			fnt_rpg.printR(backSurface, 635, 5, "Bonus");
			fnt_rpg.printR(backSurface, 635, 20, "Stage");
		} else {
			sprintf(buffer, "%d", player2->nb_life);
			fnt_cool.printR(backSurface, 635, 5, buffer);
		}

		switch (player2->id_arme) {
			case ID_M16:
				pic = pbk_misc[14];
				break;
			case ID_PM:
				pic = pbk_misc[8];
				break;
			case ID_LF:
				pic = pbk_misc[11];
				break;
			case ID_FUSIL:
				pic = pbk_misc[9];
				break;
			case ID_LASER:
				pic = pbk_misc[10];
				break;
		}

		pic->BlitTo(backSurface, 510, 50);

		if (player2->id_arme == ID_M16) {
			fnt_ammo.printC(backSurface, 505, 43, "*");
		} else {
			sprintf(buffer, "%d", player2->ammo);

			if (player2->tire && phase)
				fnt_ammo_used.printC(backSurface, 505, 43, buffer);
			else
				fnt_ammo.printC(backSurface, 505, 43, buffer);
		}


		for (int i = 0, dxt = 0; i < player2->nb_cow_bomb; i++, dxt += 23)
			pbk_misc[49]->BlitTo(backSurface, 520 - dxt, 65);
	}

}


//-----------------------------------------------------------------------------

void Game::drawHUBpv(int x, int y, int pv)
{
	static const int x_pv [] = { 3, 0, 13, 44, 31};
	static const int y_pv [] = { 0, 21, 48, 21, 0};

	for (int i = 0; i < pv; i++)
		pbk_bb[201 - i]->BlitTo(backSurface, x + x_pv[i], y + y_pv[i]);

	for (int i = pv; i < 5; i++)
		pbk_bb[196 - i]->BlitTo(backSurface, x + x_pv[i], y + y_pv[i]);
}


//-----------------------------------------------------------------------------

void Game::updateTexteCool()
{
	TexteCool *	txt;

	list_txt_cool.start();

	while (!list_txt_cool.fin()) {
		txt = (TexteCool*) list_txt_cool.info();
		txt->update();

		list_txt_cool.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::drawTexteCool()
{
	TexteCool *	txt;

	list_txt_cool.start();

	while (!list_txt_cool.fin()) {
		txt = (TexteCool*) list_txt_cool.info();
		txt->affiche();

		list_txt_cool.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::updateFondsAnimes()
{
	Sprite *	t;

	list_fonds_animes.start();

	while (!list_fonds_animes.fin()) {
		t = (Sprite*) list_fonds_animes.info();
		t->update();
		list_fonds_animes.suivant();
	}
}



//-----------------------------------------------------------------------------

void Game::drawFondsAnimes()
{
	Sprite *	t;

	list_fonds_animes.start();

	while (!list_fonds_animes.fin()) {
		t = (Sprite*) list_fonds_animes.info();
		t->affiche();
		list_fonds_animes.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::drawDebugInfos()
{
	char	buffer[40];

	if (show_fps) {
		sprintf(buffer, "FPS = %d", fps_count);
		fnt_rpg.print(backSurface, 10, 130, buffer);
	}
	/*
		if ( show_lists)
		{
			sprintf( buffer, "Joueurs = %d", list_joueurs.taille());
			fnt_rpg.print( backSurface, 10, 150, buffer);

			sprintf( buffer, "Tirs joueurs = %d", list_tirs_bb.taille());
			fnt_rpg.print( backSurface, 10, 170, buffer);

			sprintf( buffer, "Ennemis = %d", list_ennemis.taille());
			fnt_rpg.print( backSurface, 10, 190, buffer);

			sprintf( buffer, "Tirs ennemis = %d", list_tirs_ennemis.taille());
			fnt_rpg.print( backSurface, 10, 210, buffer);

			sprintf( buffer, "Gens ennemis = %d", list_gen_ennemis.taille());
			fnt_rpg.print( backSurface, 10, 230, buffer);

			sprintf( buffer, "Nb created = %d", nb_ennemis_created);
			fnt_rpg.print( backSurface, 10, 250, buffer);

			sprintf( buffer, "Fonds animes = %d", list_fonds_animes.taille());
			fnt_rpg.print( backSurface, 10, 270, buffer);

			sprintf( buffer, "Meteo = %d / %d (%d)", list_meteo.taille(), intensite_meteo, type_meteo);
			fnt_rpg.print( backSurface, 10, 290, buffer);

			sprintf( buffer, "Plat. mobile = %d", list_plateformes_mobiles.taille());
			fnt_rpg.print( backSurface, 10, 310, buffer);

			sprintf( buffer, "Giclures = %d", list_giclures.taille());
			fnt_rpg.print( backSurface, 10, 330, buffer);

			sprintf( buffer, "xTex = %d", xTex);
			fnt_rpg.print( backSurface, 10, 350, buffer);

			sprintf( buffer, "next_x = %d", next_x);
			fnt_rpg.print( backSurface, 10, 370, buffer);

			sprintf( buffer, "Offset = %d", offset);
			fnt_rpg.print( backSurface, 10, 390, buffer);

			sprintf( buffer, "n_img = %d", n_img);
			fnt_rpg.print( backSurface, 10, 410, buffer);

			sprintf( buffer, "n_cache = %d", n_cache);
			fnt_rpg.print( backSurface, 10, 430, buffer);

			sprintf( buffer, "glorf = %d", glorf);
			fnt_rpg.print( backSurface, 10, 450, buffer);


			sprintf( buffer, "0-USER0 = %d", game_flag[FLAG_USER0]);
			fnt_rpg.print( backSurface, 440, 165, buffer);

			sprintf( buffer, "1-USER1 = %d", game_flag[FLAG_USER1]);
			fnt_rpg.print( backSurface, 440, 185, buffer);

			sprintf( buffer, "2-USER2 = %d", game_flag[FLAG_USER2]);
			fnt_rpg.print( backSurface, 440, 205, buffer);

			sprintf( buffer, "3-USER3 = %d", game_flag[FLAG_USER3]);
			fnt_rpg.print( backSurface, 440, 225, buffer);

			sprintf( buffer, "4-RESERVED = %d", game_flag[3]);
			fnt_rpg.print( backSurface, 440, 245, buffer);

			sprintf( buffer, "5-BONUS = %d", game_flag[FLAG_BONUS]);
			fnt_rpg.print( backSurface, 440, 265, buffer);

			sprintf( buffer, "6-TIMER = %d", game_flag[FLAG_TIMER]);
			fnt_rpg.print( backSurface, 440, 285, buffer);

			sprintf( buffer, "7-GEN_OFF = %d", game_flag[FLAG_GEN_OFF]);
			fnt_rpg.print( backSurface, 440, 305, buffer);

			sprintf( buffer, "8-NB_KILL = %d", game_flag[FLAG_NB_KILL]);
			fnt_rpg.print( backSurface, 440, 325, buffer);

			sprintf( buffer, "9-NB_ENN = %d", game_flag[FLAG_NB_ENN]);
			fnt_rpg.print( backSurface, 440, 345, buffer);

			sprintf( buffer, "10-NB_GEN = %d", game_flag[FLAG_NB_GEN]);
			fnt_rpg.print( backSurface, 440, 365, buffer);

			sprintf( buffer, "Channels = %d", FSOUND_GetChannelsPlaying());
			fnt_rpg.print( backSurface, 440, 405, buffer);

			sprintf( buffer, "Gore = %d", list_gore.taille());
			fnt_rpg.print( backSurface, 440, 425, buffer);

			sprintf( buffer, "Fonds stat. = %d", list_fonds_statiques.taille());
			fnt_rpg.print( backSurface, 440, 445, buffer);

			sprintf( buffer, "Impacts = %d", list_impacts.taille());
			fnt_rpg.print( backSurface, 440, 465, buffer);

			RECT	r;

			r.top	= 10;
			r.bottom= 150;
			r.left	= 200;
			r.right = 440;

			backSurface->Blt( &r, videoA, NULL, DDBLT_WAIT, 0);
		}
	*/
}

//-----------------------------------------------------------------------------

void Game::updatePremiersPlans()
{
	Sprite *	t;

	list_premiers_plans.start();

	while (!list_premiers_plans.fin()) {
		t = (Sprite*) list_premiers_plans.info();
		t->update();
		list_premiers_plans.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::drawPremiersPlans()
{
	Sprite *	t;

	list_premiers_plans.start();

	while (!list_premiers_plans.fin()) {
		t = (Sprite*) list_premiers_plans.info();
		t->affiche();
		list_premiers_plans.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::updateGiclures()
{
	Sprite *	t;

	list_giclures.start();

	while (!list_giclures.fin()) {
		t = (Sprite*) list_giclures.info();
		t->update();
		list_giclures.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::drawGiclures()
{
	Sprite *	t;

	list_giclures.start();

	while (!list_giclures.fin()) {
		t = (Sprite*) list_giclures.info();
		t->affiche();
		list_giclures.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::updateTeteTurc()
{
	static int	ntete_turc = 0;

	if (list_joueurs.taille() == 0) {
		dummyPlayer.x = offset + 320;
		dummyPlayer.y = y_plat[0][offset + 320];
		tete_turc = &dummyPlayer;
		return;
	}

	ntete_turc += 1;
	ntete_turc %= list_joueurs.taille();


	list_joueurs.start();

	int	i = 0;

	list_joueurs.start();

	while (i < ntete_turc && !list_joueurs.fin()) {
		list_joueurs.suivant();
		i++;
	}

	tete_turc = (Personnage *) list_joueurs.info();
}


//-----------------------------------------------------------------------------

void Game::drawTirsEnnemis()
{
	Sprite *	t;

	list_tirs_ennemis.start();

	while (!list_tirs_ennemis.fin()) {
		t = (Sprite*) list_tirs_ennemis.info();
		t->affiche();
		list_tirs_ennemis.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::updateTirsEnnemis()
{
	Sprite *	t;

	list_tirs_ennemis.start();

	while (!list_tirs_ennemis.fin()) {
		t = (Sprite*) list_tirs_ennemis.info();
		t->update();
		list_tirs_ennemis.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::updateRPG()
{
	if (rpg_to_play == -1)
		return;

	bool	continued = true;

	rpg.startPlay(rpg_to_play);

	while (continued && !app_killed) {
	    in.update();
		manageMsg();
		checkRestore();
		drawAll(false);
		continued = rpg.drawScene(backSurface);
		DDFlipV();
		in.refresh();
	}


	rpg.stopPlay();
	in.waitClean();
	rpg_to_play = -1;
	time = LGetTime();
}

//-----------------------------------------------------------------------------

void Game::updateVictoryAndDefeat()
{
	// Defaite ?
	//
	if (list_joueurs.estVide()) {
		wait_for_death += 1;

		if (wait_for_death >= 200)
			joueurs_morts = true;

		return;
	}

	// Victoire ?
	//
	if (offset >= vic_x &&
	        game_flag[vic_flag1] == vic_val1 &&
	        game_flag[vic_flag2] == vic_val2) {
		hold_fire = true;
		wait_for_victory += 1;

		if (game_flag[1] == 999)
			wait_for_victory = 200;

		if (wait_for_victory >= 200)
			niveau_fini = true;
	} else {
		if (wait_for_victory > 0)
			wait_for_victory = 0;
	}
}


//-----------------------------------------------------------------------------

void Game::updateFlags()
{
	game_flag[FLAG_NB_GEN] = list_gen_ennemis.taille();
	game_flag[FLAG_NB_ENN] = list_ennemis.taille();
	makeb_current_mode = game_flag[FLAG_BONUS];

	// Le TIMER
	//
	if (game_flag[FLAG_TIMER] > 0 && wait_for_victory == -1) {
		etape_timer += 1;
		etape_timer %= 80;

		if (etape_timer == 0) {
			game_flag[FLAG_TIMER] -= 1;

			if (game_flag[FLAG_TIMER] == 0 && niveau_bonus)
				niveau_fini = true;
		}
	}
}


//-----------------------------------------------------------------------------

void Game::drawCow()
{
	Sprite *	t;

	list_cow.start();

	while (!list_cow.fin()) {
		t = (Sprite*) list_cow.info();
		t->affiche();
		list_cow.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::drawTimer()
{
	if (game_flag[FLAG_TIMER] > 0) {
		char	buffer[10];

		fnt_cool.printC(backSurface, 320, 20, txt_data[TXT_TIME]);
		sprintf(buffer, "%d", game_flag[FLAG_TIMER]);
		fnt_cool.printC(backSurface, 320, 50, buffer);
	}
}


//-----------------------------------------------------------------------------

void Game::updatePlateformesMobiles()
{
	Sprite *	pl;

	list_plateformes_mobiles.start();

	while (!list_plateformes_mobiles.fin()) {
		pl = (Sprite*) list_plateformes_mobiles.info();
		pl->update();
		list_plateformes_mobiles.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::drawPlateformesMobiles()
{
	Sprite *	pl;

	list_plateformes_mobiles.start();

	while (!list_plateformes_mobiles.fin()) {
		pl = (Sprite*) list_plateformes_mobiles.info();
		pl->affiche();
		list_plateformes_mobiles.suivant();
	}
}


//-----------------------------------------------------------------------------
#define aa 0.333333
#define bb 0.666666
#define cc 0.5

void Game::updateTouch()
{
    static int last_dir = 1;

    if(last_dir == 1)
    in.angle = 0;
    if(last_dir == 2)
    in.angle = 180;

    in.dist = 0;

    if(in.padded == false)
    {
        int indp = in.search_pressing();

        if(indp != -1)
        {
            if(in.finger[indp].x <= 0.5)
            {
                in.padded = true;
                in.pad_x = in.finger[indp].x;
                in.pad_x *= 640;
                in.pad_y = in.finger[indp].y;
                in.pad_y *= 480;
                in.finger[indp].ptr = &in.padded;
            }
        }
    }
    else
    {
        int indp = in.search_ptr(&in.padded);

        if(indp == -1 || (indp != -1 &&  (in.finger[indp].state == TOUCH_UP || in.finger[indp].state == TOUCH_NOTHING)) )
        {
            in.finger[indp].ptr = NULL;
            in.padded = false;
        }
        else
        {
            float angle = calcul_angle(in.pad_x, in.pad_y, in.finger[indp].x*640.f, in.finger[indp].y*480.f);

            float _aa = in.finger[indp].x*640.f;
            float _bb = in.finger[indp].y*480.f;

            if(in.pad_x == _aa && in.pad_y == _bb)
            in.dist = 0;
            else
            {
                _aa = _aa - in.pad_x;
                _bb = _bb - in.pad_y;
                in.dist = sqrt(_bb*_bb+_aa*_aa);
            }

            if(angle <= 22.5 || (angle >= 322&&angle <= 360) )
            in.droit = true;
            if(angle > 22.5 && angle < 68)
            {
                in.droit = true;
                in.haut = true;
            }

            if(angle >= 68 && angle <= 113)
            in.haut = true;
            if(angle > 113 && angle < 158)
            {
                in.haut = true;
                in.gauche = true;
            }

            if(angle >= 158 && angle <= 220)
            in.gauche = true;
            if(angle > 220 && angle < 248)
            {
                in.gauche = true;
                in.bas = true;
            }

            if(angle >= 248 && angle <= 293)
            in.bas = true;
            if(angle > 293 && angle < 322)
            {
                in.bas = true;
                in.droit = true;
            }
            if(angle == 4000)
            angle = 0;
            in.angle = angle;
        }
    }

    if(in.droit)
    last_dir = 1;
    if(in.gauche)
    last_dir = 2;



    if( (box_manager.get_state("shoot") == TOUCH_DOWN || box_manager.get_state("shoot") == TOUCH_PRESSING) )
    {
        in.tirer = true;
    }
    if( (box_manager.get_state("jump")  == TOUCH_DOWN || box_manager.get_state("jump") == TOUCH_PRESSING) )
    {
        in.sauter = true;
    }
    if(box_manager.get_state("ulti") == TOUCH_UP && player1 != NULL && player1->nb_cow_bomb >= 1)
    {
        in.ulti = true;
    }
}

void Game::updateMenu()
{
	// Appelle le menu s'il y a lieu de le faire
	//
	///MODIF touch menu
	//if (in.scanKey(DIK_ESCAPE)) {
	if(box_manager.get_state("pause") == TOUCH_UP || go_to_menu) {
		MenuGame	menu;
		int			r;
		go_to_menu = false;

		drawAll(false);
		DDFlipV();
		drawAll(false);
		DDFlipV();

		menu.start();
		menu.draw(backSurface);
		DDFlipV();
		//primSurface->Flip(NULL, DDFLIP_WAIT );

		in.waitClean();


		while (!(r = menu.update()) && !app_killed) {///TODO
			manageMsg();
			checkRestore();
			drawAll(false);
			menu.draw(backSurface);

			DDFlipV();
			//primSurface->Flip(NULL, DDFLIP_WAIT );
		}

		if (r == 2)
			skipped = true;

		menu.stop();

		drawAll(false);
		DDFlipV();
		drawAll(false);
		DDFlipV();

		time = LGetTime();
	}
}


//-----------------------------------------------------------------------------

void Game::updateCheat()
{
	if (wait_cheat < 20)
		wait_cheat += 1;

	if (!cheat_on)
		return;

	if (player1 != NULL) {
		if (in.scanKey(DIK_F1))
			player1->ammo += 10;

		if (wait_cheat < 20)
			return;

		if (in.scanKey(DIK_F3)) {
			player1->nb_life++;
			wait_cheat = 0;
		}

		if (in.scanKey(DIK_F2)) {
			player1->nb_cow_bomb += 1;
			wait_cheat = 0;
		}
	}

	if (player2 != NULL) {
		if (in.scanKey(DIK_F5))
			player2->ammo += 10;

		if (wait_cheat < 20)
			return;

		if (in.scanKey(DIK_F7)) {
			player2->nb_life++;
			wait_cheat = 0;
		}

		if (in.scanKey(DIK_F6)) {
			player2->nb_cow_bomb += 1;
			wait_cheat = 0;
		}
	}


	if (in.scanKey(DIK_F9))
		niveau_fini = true;

	if (wait_cheat < 20)
		return;

	if (in.scanKey(DIK_F12)) {
		show_fps = !show_fps;
		wait_cheat = 0;
	}

	if (in.scanKey(DIK_F11)) {
		show_lists = !show_lists;
		wait_cheat = 0;
	}
}


//-----------------------------------------------------------------------------

void Game::showPE(bool bonus, bool fuckOff)
{
	Fonte *	fnt_p1;
	Fonte * fnt_p2;
	char	buffer[20];
	int		killed_p1		= 0;	// % d'ennemis tués par le joueur 1
	int		c_killed_p1		= 0;	// compteur killed_p1
	int		calc_p1			= 0;
	int		c_time_p1		= 0;
	int		total_bonus_p1	= 0;
	int		total_p1		= 0;
	int		obj_p1			= 0;
	int		c_obj_p1		= 0;
	int		perfect_p1		= 0;
	int		c_perfect_p1	= 0;
	int		life_up_p1		= 0;

	int		killed_p2		= 0;	// % d'ennemis tués par le joueur 1
	int		c_killed_p2		= 0;	// compteur killed_p2
	int		calc_p2			= 0;
	int		c_time_p2		= 0;
	int		total_bonus_p2	= 0;
	int		total_p2		= 0;
	int		obj_p2			= 0;
	int		c_obj_p2		= 0;
	int		perfect_p2		= 0;
	int		c_perfect_p2	= 0;
	int		life_up_p2		= 0;

	int		delai			= 0;
	int		xbasep1;
	bool	showp1;
	int		xbasep2;
	bool	showp2;

	systemSurface->BltFast(0, 0, backSurface, NULL, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);

	RECT	r;

	r.top	= 100;
	r.left	= 60;
	r.right	= 580;
	r.bottom = 400;

	LGXpaker.halfTone(systemSurface, &r);

	mbk_inter.play(0);

	if (list_joueurs.taille() == 2) {
		showp1 = showp2 = true;
		xbasep1 = 80;
		xbasep2 = 350;
	} else {
		if (player1 != NULL && player1->nb_life > 0) {
			showp1 = true;
			showp2 = false;
			xbasep1 = 210;
			calc_p2 = 4;
		} else if (player2 != NULL) {
			showp1 = false;
			showp2 = true;
			xbasep2 = 210;
			calc_p1 = 4;
		}

	}

	if (showp1) {
		if (player1->id_couille == ID_BLIP)
			fnt_p1 = &fnt_score_blip;
		else
			fnt_p1 = &fnt_score_blop;
	}

	if (showp2) {
		if (player2->id_couille == ID_BLIP)
			fnt_p2 = &fnt_score_blip;
		else
			fnt_p2 = &fnt_score_blop;
	}

	if (nb_ennemis_created > 0) {
		if (showp1)
			killed_p1 = (100 * player1->getKilled()) / nb_ennemis_created;
		if (showp2)
			killed_p2 = (100 * player2->getKilled()) / nb_ennemis_created;
	}


	if (!bonus || (game_flag[FLAG_TIMER] > 0 && !joueurs_morts)) {
		if (showp1)
			obj_p1 = 50000;
		if (showp2)
			obj_p2 = 50000;
	}


	if (obj_p1 > 0 && player1->perfect)
		perfect_p1 = 50000;

	if (obj_p2 > 0 && player2->perfect)
		perfect_p2 = 50000;

	if (showp1)
		total_p1 = player1->getScore();

	if (showp2)
		total_p2 = player2->getScore();

	if (fuckOff) {
		perfect_p1 = perfect_p2 = obj_p1 = obj_p2 = killed_p1 = killed_p2 = 0;
		game_flag[FLAG_TIMER] = 0;
	}

	while (!app_killed && (calc_p1 < 4 || calc_p2 < 4)) {

		manageMsg();
		checkRestore();

		if (app_killed)
			return;

		in.update();
		LOGI("showPE");///UPDATE du menu des bonus

		delai += 1;
		delai %= 3;

		//if (in.anyKeyPressed())
		//	delai = 0;
		if(in.so_up())
		delai = 0;

		if (delai == 0) {
			// Calculs P1
			//
			if (calc_p1 == 0) {
				// Perfect
				//
				if (c_perfect_p1 >= perfect_p1)
					calc_p1 = 1;
				else {
					c_perfect_p1 += 1000;
					total_bonus_p1 += 1000;
					total_p1 += 1000;
				}
			} else if (calc_p1 == 1) {
				// Bonus objectif atteint
				//
				if (c_obj_p1 >= obj_p1)
					calc_p1 = 2;
				else {
					c_obj_p1 += 1000;
					total_bonus_p1 += 1000;
					total_p1 += 1000;
				}
			}
			if (calc_p1 == 2) {
				// Bonus % d'ennemis tués
				//
				if (c_killed_p1 >= killed_p1)
					calc_p1 = 3; // Passe en TIMER
				else {
					c_killed_p1 += 1;
					total_bonus_p1 += 500;
					total_p1 += 500;
				}
			} else if (calc_p1 == 3) {
				// Bonus temps restant
				//
				if (c_time_p1 >= game_flag[FLAG_TIMER])
					calc_p1 = 4; // Fini le calcul
				else {
					c_time_p1 += 1;
					total_bonus_p1 += 1000;
					total_p1 += 1000;
				}
			}

			// Calculs p2
			//
			if (calc_p2 == 0) {
				// Perfect
				//
				if (c_perfect_p2 >= perfect_p2)
					calc_p2 = 1;
				else {
					c_perfect_p2 += 1000;
					total_bonus_p2 += 1000;
					total_p2 += 1000;
				}
			} else if (calc_p2 == 1) {
				// Bonus objectif atteint
				//
				if (c_obj_p2 >= obj_p2)
					calc_p2 = 2;
				else {
					c_obj_p2 += 1000;
					total_bonus_p2 += 1000;
					total_p2 += 1000;
				}
			}
			if (calc_p2 == 2) {
				// Bonus % d'ennemis tués
				//
				if (c_killed_p2 >= killed_p2)
					calc_p2 = 3; // Passe en TIMER
				else {
					c_killed_p2 += 1;
					total_bonus_p2 += 500;
					total_p2 += 500;
				}
			} else if (calc_p2 == 3) {
				// Bonus temps restant
				//
				if (c_time_p2 >= game_flag[FLAG_TIMER])
					calc_p2 = 4; // Fini le calcul
				else {
					c_time_p2 += 1;
					total_bonus_p2 += 1000;
					total_p2 += 1000;
				}
			}
		}


		// Affichage
		//
		backSurface->BltFast(0, 0, systemSurface, NULL, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);

		if (fuckOff) {
			fnt_cool.printC(backSurface, 320, 120, "BONUS STAGE FAILED!");
		} else {
			fnt_cool.printC(backSurface, 320, 120, "LEVEL COMPLETE!");
		}

		// Affichage	P1
		//

		if (showp1) {
			if (life_up_p1 > 0) {
				fnt_rpg.printC(backSurface, xbasep1 + 105, 270, "LIFE UP");
//				life_up_p1--;
			}

			if (perfect_p1 > 0) {
				strcpy(buffer, "PERFECT");
				fnt_rpg.print(backSurface, xbasep1, 180, buffer);
				sprintf(buffer, "%d", c_perfect_p1);
				fnt_p1->printR(backSurface, xbasep1 + 210, 180, buffer);
			}

			if (obj_p1 > 0) {
				strcpy(buffer, "Objective");
				fnt_rpg.print(backSurface, xbasep1, 200, buffer);
				sprintf(buffer, "%d", c_obj_p1);
				fnt_p1->printR(backSurface, xbasep1 + 210, 200, buffer);
			}

			strcpy(buffer, "Casualties");
			fnt_rpg.print(backSurface, xbasep1, 220, buffer);
			sprintf(buffer, "%d", c_killed_p1);
			fnt_p1->printR(backSurface, xbasep1 + 210, 220, buffer);
			strcpy(buffer, "%");
			fnt_rpg.printR(backSurface, xbasep1 + 220, 220, buffer);

			if (game_flag[FLAG_TIMER] > 0) {
				strcpy(buffer, "Time left");
				fnt_rpg.print(backSurface, xbasep1, 240, buffer);
				sprintf(buffer, "%d", c_time_p1);
				fnt_p1->printR(backSurface, xbasep1 + 210, 240, buffer);
			}

			strcpy(buffer, "BONUS");
			fnt_rpg.print(backSurface, xbasep1, 300, buffer);
			sprintf(buffer, "%d", total_bonus_p1);
			fnt_p1->printR(backSurface, xbasep1 + 210, 300, buffer);

			strcpy(buffer, "SCORE");
			fnt_rpg.print(backSurface, xbasep1, 320, buffer);
			sprintf(buffer, "%d", total_p1);
			fnt_p1->printR(backSurface, xbasep1 + 210, 320, buffer);

			if (total_p1 / 500000 > player1->mod_life) {
				player1->mod_life = total_p1 / 500000;
				player1->nb_life++;
				life_up_p1 = 100;
			}
		}

		// Affichage	P2
		//
		if (showp2) {
			if (life_up_p2 > 0) {
				fnt_rpg.printC(backSurface, xbasep2 + 105, 270, "LIFE UP");
//				life_up_p2--;
			}

			if (perfect_p2 > 0) {
				strcpy(buffer, "PERFECT");
				fnt_rpg.print(backSurface, xbasep2, 180, buffer);
				sprintf(buffer, "%d", c_perfect_p2);
				fnt_p2->printR(backSurface, xbasep2 + 210, 180, buffer);
			}

			if (obj_p2 > 0) {
				strcpy(buffer, "Objective");
				fnt_rpg.print(backSurface, xbasep2, 200, buffer);
				sprintf(buffer, "%d", c_obj_p2);
				fnt_p2->printR(backSurface, xbasep2 + 210, 200, buffer);
			}

			strcpy(buffer, "Casualties");
			fnt_rpg.print(backSurface, xbasep2, 220, buffer);
			sprintf(buffer, "%d", c_killed_p2);
			fnt_p2->printR(backSurface, xbasep2 + 210, 220, buffer);
			strcpy(buffer, "%");
			fnt_rpg.printR(backSurface, xbasep2 + 220, 220, buffer);

			if (game_flag[FLAG_TIMER] > 0) {
				strcpy(buffer, "Time left");
				fnt_rpg.print(backSurface, xbasep2, 240, buffer);
				sprintf(buffer, "%d", c_time_p2);
				fnt_p2->printR(backSurface, xbasep2 + 210, 240, buffer);
			}

			strcpy(buffer, "BONUS");
			fnt_rpg.print(backSurface, xbasep2, 300, buffer);
			sprintf(buffer, "%d", total_bonus_p2);
			fnt_p2->printR(backSurface, xbasep2 + 210, 300, buffer);

			strcpy(buffer, "SCORE");
			fnt_rpg.print(backSurface, xbasep2, 320, buffer);
			sprintf(buffer, "%d", total_p2);
			fnt_p2->printR(backSurface, xbasep2 + 210, 320, buffer);

			if (total_p2 / 500000 > player2->mod_life) {
				player2->mod_life = total_p2 / 500000;
				player2->nb_life++;
				life_up_p2 = 100;
			}
		}

		DDFlipV();
		in.refresh();
	}

	if (!app_killed) {
		//in.waitClean();
		//in.waitKey();
		while(1)
		{
		    in.update();
		    if(in.so_up())
		    break;
		    in.refresh();
		}
	}

	if (showp1)
		player1->setScore(total_p1);
	if (showp2)
		player2->setScore(total_p2);

	mbk_inter.stop();
}

//-----------------------------------------------------------------------------

void Game::updateMeteo()
{
	const static int speed_gouttes[] = { 3, 5, 7, 8, 9, 10 };

	Sprite *	pl;

	list_meteo.start();

	while (!list_meteo.fin()) {
		pl = (Sprite*) list_meteo.info();
		pl->update();
		list_meteo.suivant();
	}


	while (list_meteo.taille() < intensite_meteo) {
		if (type_meteo == METEO_NEIGE) {
//			MeteoNeige * flocon = new MeteoNeige();

			next_flocon = (next_flocon + 1) % NB_FLOCONS;
			MeteoNeige * flocon = &neige[next_flocon];

			int d = rand() % 3;

			flocon->a_detruire = false;
			flocon->xbase = offset + rand() % 800;
			flocon->y = rand() % 480 - 500;

			if (d <= 1)
				flocon->pic = pbk_misc[71];
			else
				flocon->pic = pbk_misc[72];

			flocon->dy = intensite_meteo / 20 + d;
			flocon->phi = rand() % 360;
			flocon->xwide = 10 + d * 4;

			if (mur_opaque(flocon->xbase, 0))
				flocon->y -= 550;

			list_meteo.ajoute((void*) flocon);
		} else if (type_meteo == METEO_PLUIE) {
//			MeteoPluie * goutte = new MeteoPluie();

			next_goutte = (next_goutte + 1) % NB_GOUTTES;
			MeteoPluie * goutte = &pluie[next_goutte];

			int d = rand() % 4;

			goutte->a_detruire = false;
			goutte->x = offset + rand() % 800;
			goutte->y = rand() % 480 - 480;
			goutte->pic = pbk_misc[65 + d];
			goutte->dy = 7 + d * 2;

			if (mur_opaque(goutte->x, 0))
				goutte->y -= 550;

			list_meteo.ajoute((void*) goutte);
		}
	}
}


//-----------------------------------------------------------------------------

void Game::drawMeteo()
{
	Sprite *	pl;

	list_meteo.start();

	while (!list_meteo.fin()) {
		pl = (Sprite*) list_meteo.info();
		pl->affiche();
		list_meteo.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::drawImpacts()
{
	Sprite *	pl;

	list_impacts.start();

	while (!list_impacts.fin()) {
		pl = (Sprite*) list_impacts.info();
		pl->affiche();
		list_impacts.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::updateImpacts()
{
	Sprite *	pl;

	list_impacts.start();

	while (!list_impacts.fin()) {
		pl = (Sprite*) list_impacts.info();
		pl->update();
		list_impacts.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::updateFlecheGo()
{
	if (last_x_go != offset) {
		last_x_go = offset;
		delai_go = 0;
		must_stop_go = true;
	} else if (!fleche_go && !scroll_locked && offset < level_size - 640) {
		delai_go += 1;

		if (delai_go >= 300) {
			fleche_go = true;
			x_fleche_go = -10;
			nb_rebonds_go = 0;
			must_stop_go = false;
		}
	}

	if (fleche_go) {
		ss_etape_fleche_go += 1;
		ss_etape_fleche_go %= 4;

		if (ss_etape_fleche_go == 0) {
			etape_fleche_go += 1;
			etape_fleche_go %= 5;
		}

		teta_go += 3;
		teta_go %= 360;

		if (nb_rebonds_go == 0) {	// La flèche arrive
			x_fleche_go += 10;

			if (x_fleche_go == 640) {
				nb_rebonds_go += 1;
				teta_go = 0;
			}
		} else if (nb_rebonds_go != -1) {
			int	x = (100 * bSin[teta_go]) >> COSINUS;

			if (x < 0) x = -x;

			x_fleche_go = 640 - x;

			if (x == 0) {	// rebond
				nb_rebonds_go += 1;

				if (nb_rebonds_go >= 3 && must_stop_go)
					nb_rebonds_go = -1;
			}
		} else { // La flèche part vers la droite
			x_fleche_go += 10;

			if (x_fleche_go > 800) {
				fleche_go = false;
				delai_go = 0;
			}
		}
	}
}

//-----------------------------------------------------------------------------

void Game::drawFlecheGo()
{
	if (fleche_go)
		pbk_misc[81 + etape_fleche_go]->BlitTo(backSurface, x_fleche_go, 150);
}


//-----------------------------------------------------------------------------

void Game::updateDeformation()
{
	phi_deform += 2;
	phi_deform %= 360;
}


//-----------------------------------------------------------------------------

void Game::drawDeformation()
{
	DDBLTFX         ddfx;
	RECT	r;
	int		pas = 20;
	int		phi = phi_deform;
	int		dphi = 10;
	int		x;
	int		xt;

	ZeroMemory(&ddfx, sizeof(ddfx));
	ddfx.dwSize = sizeof(ddfx);
	ddfx.dwFillColor = 0; // Noir

	pas = 2;
	dphi = 1;

	for (int y = 0; y < 480; y += pas) {
		phi += dphi;
		phi %= 360;

		r.top	= y;
		r.bottom = y + pas;

		x = xt = (5 * bSin[phi]) >> COSINUS;

		if (x < 0) {
			r.left	= -x;
			r.right = 640;
			x = 0;
		} else {
			r.left	= 0;
			r.right = 640 - x;
		}

		backSurface->BltFast(x, y, backSurface, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

		if (xt < 0) {
			r.left	= 640 + xt;
			r.right = 640;
		} else {
			r.left	= 0;
			r.right = xt;
		}

		backSurface->Blt(&r, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddfx);
	}
}

//-----------------------------------------------------------------------------

void Game::updateBulles()
{
	Sprite *	pl;

	// Crée de nouvelles bulles
	//
	list_joueurs.start();

	while (!list_joueurs.fin()) {
		pl = (Sprite*) list_joueurs.info();
		creeBulle(pl);
		list_joueurs.suivant();
	}


	list_ennemis.start();

	while (!list_ennemis.fin() && list_bulles.taille() < 15) {
		pl = (Sprite*) list_ennemis.info();
		creeBulle(pl);
		list_ennemis.suivant();
	}


	// Update les bulles déjà crées
	//
	list_bulles.start();

	while (!list_bulles.fin()) {
		pl = (Sprite*) list_bulles.info();
		pl->update();
		list_bulles.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::drawBulles()
{
	Sprite *	pl;

	list_bulles.start();

	while (!list_bulles.fin()) {
		pl = (Sprite*) list_bulles.info();
		pl->affiche();
		list_bulles.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::creeBulle(Sprite * s)
{
	s->wait_bulle += rand() % 10;

	if (s->wait_bulle > 300) {
		Bulle * b = new Bulle();

		b->xbase = s->x;
		b->y = s->y - 10;
		b->pic = pbk_misc[78 + rand() % 3];
		b->dphi = 5 + rand() % 3;
		b->dy = -(2 + rand() % 2);

		list_bulles.ajoute((void*) b);

		s->wait_bulle = 0;
	}
}


//-----------------------------------------------------------------------------

void Game::updateTremblements()
{
	if (amplitude_tremblement == 0)
		return;


	if (etape_tremblement == 0) {
		dy_tremblement += ddy_tremblement;

		if (dy_tremblement <= -amplitude_tremblement) {
			amplitude_tremblement -= 1;
			ddy_tremblement = (amplitude_tremblement >> 1) + 1;
			dy_tremblement += 1;
		} else if (dy_tremblement >= amplitude_tremblement) {
			amplitude_tremblement -= 1;
			ddy_tremblement = -(amplitude_tremblement >> 1) - 1;
			dy_tremblement -= 1;
		}
	}
}

//-----------------------------------------------------------------------------

void Game::drawTremblements()
{
	if (amplitude_tremblement == 0 || dy_tremblement == 0)
		return;

	int		y;
	RECT	r;
	RECT	r2;

	r2.left = r.left = 0;
	r2.right = r.right = 640;

	if (dy_tremblement < 0) {
		r.top	= -dy_tremblement;
		r.bottom = 480;

		r2.top	 = 480 + dy_tremblement;
		r2.bottom = 480;

		y = 0;
	} else if (dy_tremblement > 0) {
		r.top	= 0;
		r.bottom = 480 - dy_tremblement;

		r2.top	 = 0;
		r2.bottom = dy_tremblement;

		y = dy_tremblement;
	}

	backSurface->BltFast(0, y, backSurface, &r, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);

	DDBLTFX         ddfx;

	ZeroMemory(&ddfx, sizeof(ddfx));
	ddfx.dwSize = sizeof(ddfx);
	ddfx.dwFillColor = 0;

	backSurface->Blt(&r2, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddfx);
}


//-----------------------------------------------------------------------------

bool Game::loadList(const char * fic)
{
    ///MODIF ifstream
	//ifstream	f;
	istringstream f;
	int			n;

	///MODIF open
	//f.open(fic);

	///MODIF is_open
	//if (f.is_open() == 0) {
	if (AAsset_istringstream(fic, f) == false) {
		debug << "Cannot open " << fic << "\n";
		return false;
	}

	nb_part = 0;
	f >> n;


	while (!f.eof()) {
		if (n < 0 || n > 2) {
			debug << "File " << fic << " corrupted!\n";
			///MODIF close
			//f.close();
			f.str("");
			f.clear();

			return false;
		}

		type_part[nb_part] = n;

		if (n == PART_CINE || n == PART_BRIEFING) {
			f.getline(fic_names[nb_part], 200, '*');
			f.getline(fic_names[nb_part], 200);
		} else {
			f >> type_lvl[nb_part];
			f.getline(fic_names[nb_part], 200, '*');
			f.getline(fic_names[nb_part], 200);
		}


		nb_part += 1;
		f >> n;

		if (nb_part > MAX_PART) {
			debug << "File " << fic << " corrupted!\n";
			///MODIF close
			//f.close();
			f.str("");
			f.clear();
			return false;
		}
	}


	///MODIF close
    //f.close();
    f.str("");
    f.clear();
	return true;
}


//-----------------------------------------------------------------------------

void Game::drawLoading()
{
	RECT	r;

	r.left	= 0;
	r.right = 640;
	r.top	= 195;
	r.bottom = 245;

//	LGXpaker.halfTone( backSurface, &r);

//	fnt_menu.printC( backSurface, 320, 205, "LOADING");
	fnt_cool.printC(backSurface, 320, 205, "LOADING");
}


//-----------------------------------------------------------------------------

void Game::updateGore()
{
	Sprite *	t;

	list_gore.start();

	while (!list_gore.fin()) {
		t = (Sprite*) list_gore.info();
		t->update();
		list_gore.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::drawGore()
{
	Sprite *	t;

	list_gore.start();

	while (!list_gore.fin()) {
		t = (Sprite*) list_gore.info();
		t->affiche();
		list_gore.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::getHiscore()
{
	if (player1 != NULL && hi_scores.isGood(player1->getScore()))
		getName(player1, 1);

	if (player2 != NULL && hi_scores.isGood(player2->getScore()))
		getName(player2, 2);
}

//-----------------------------------------------------------------------------

void Game::getName(Joueur * joueur, int ijoueur)
{
	char	buff[30];
	char	name[21];
	char	tmp[20];
	int		i = 0;
	int		key = -1;
	int		x = 640;

	sprintf(buff, "PLAYER %d GOT A HIGH SCORE!", ijoueur);

	name[0] = '\0';

	strcpy(name, "");

	while (!app_killed && x >= 40) {
		manageMsg();
		checkRestore();

		x -= 20;

		pbk_inter[1]->PasteTo(backSurface, 0, 0);

		fnt_menu.printC(backSurface, 320 - x, 160, buff);
		///MODIF
		//fnt_menu.printC(backSurface, 320 + x, 210, "PLEASE ENTER YOUR NAME :");

		DDFlipV();
	}

    ///MODIF
    if(0)
	while (!app_killed && key != DIK_RETURN) {
		manageMsg();
		checkRestore();

		in.waitClean();
		key = in.waitKey();

		DIK_to_string(key, tmp);

		if (key == DIK_SPACE && i < 19) {
			name[i++] = ' ';
			name[i] = '\0';
		}
		if (key == DIK_BACKSPACE && i > 0) {
			name[--i] = '\0';
		} else if (strlen(tmp) == 1 && i < 19) {
			name[i++] = tmp[0];
			name[i] = '\0';
		}

		pbk_inter[1]->PasteTo(backSurface, 0, 0);
		fnt_menu.printC(backSurface, 320 - x, 160, buff);
		fnt_menu.printC(backSurface, 320 + x, 210, "PLEASE ENTER YOUR NAME :");
		fnt_menu.printC(backSurface, 320, 260, name);
		//primSurface->Flip( NULL, 0);
		DDFlipV();
	}
	sprintf(name, "ME");

	while (!app_killed && x < 640) {
		x += 20;

		pbk_inter[1]->PasteTo(backSurface, 0, 0);

		fnt_menu.printC(backSurface, 320 - x, 160, buff);
		///MODIF
		//fnt_menu.printC(backSurface, 320 + x, 210, "PLEASE ENTER YOUR NAME :");
		//fnt_menu.printC(backSurface, 320, 260 + x, name);

		DDFlipV();//primSurface->Flip( NULL, 0);
	}

	hi_scores.add(joueur->getScore(), name);
}

//-----------------------------------------------------------------------------

bool Game::showGameOver()
{
	int				x = 400;

	mbk_inter.play(1);
	bool pressing = false;

	//while (!app_killed && x > 20 && !in.anyKeyPressed()) {
	while (!app_killed && x > 20) {
	    in.update();

	    if(in.so_pressing())
	    pressing = true;
	    if(in.so_up() && pressing)
	    break;

		manageMsg();
		checkRestore();
		LOGI("showGameOver"); ///UPDATE showGameOver

		pbk_inter[0]->PasteTo(backSurface, 0, 0);
		/*
				fnt_menu.printR( backSurface, 320-x, 220, "GAME");
				fnt_menu.print( backSurface, 320+x, 220, "OVER");

				x -= 1;
		*/
		DDFlipV();//primSurface->Flip( NULL, 0);
		in.refresh();
	}
	/*
		if ( !app_killed)
		{
			in.waitClean();
			in.waitKey();
		}

		while ( !app_killed && x < 400)
		{
			manageMsg();
			checkRestore();

			pbk_inter[0]->PasteTo( backSurface, 0, 0);

			fnt_menu.printR( backSurface, 320-x, 220, "GAME");
			fnt_menu.print( backSurface, 320+x, 220, "OVER");

			x += 20;

			DDFlipV();
		}
	*/
	mbk_inter.stop();
}





bool Game::showHighScores()
{
	char	buffer[50];
	int		x[HS_NB_SCORES];

	for (int i = 0; i < HS_NB_SCORES; i++)
		x[i] = 400 + 160 * i;

	DWORD diff = GetTickCount();
	///MODIF touch
	//while (!app_killed && !in.anyKeyPressed() && (GetTickCount() - diff <= 10000)) {
	while (!app_killed &&  (GetTickCount() - diff <= 10000)) {
		manageMsg();
		checkRestore();
		in.update();
		LOGI("showHighScores");///UPDATE showHighScores
		if(in.so_up())
		return true;
		pbk_inter[1]->PasteTo(backSurface, 0, 0);

		for (int i = 0; i < HS_NB_SCORES; i++) {
			if (x[i] > 0)
				x[i] -= 20;

			sprintf(buffer, "%d", hi_scores.getScore(i));
			fnt_cool.printR(backSurface, 300 - x[i], 160 + 30 * i, buffer);

			sprintf(buffer, "%s", hi_scores.getName(i));
			fnt_cool.print(backSurface, 320 + x[i], 160 + 30 * i, buffer);
		}

		DDFlipV();//primSurface->Flip( NULL, 0);
		in.refresh();
	}

	while (!app_killed && x[HS_NB_SCORES - 1] < 350) {
		manageMsg();
		checkRestore();
		in.update();
		LOGI("showHighScores noupdate");
		if(in.so_up())
		return true;

		pbk_inter[1]->PasteTo(backSurface, 0, 0);

		for (int i = 0; i < HS_NB_SCORES; i++) {
			if (i == 0 || x[i - 1] >= 160)
				x[i] += 20;

			sprintf(buffer, "%d", hi_scores.getScore(i));
			fnt_cool.printR(backSurface, 300 - x[i], 160 + 30 * i, buffer);

			sprintf(buffer, "%s", hi_scores.getName(i));
			fnt_cool.print(backSurface, 320 + x[i], 160 + 30 * i, buffer);
		}

		DDFlipV();//primSurface->Flip( NULL, 0);
		in.refresh();
	}

	return false;

	in.waitClean();
}

//-----------------------------------------------------------------------------

float cv(float a)
{
    return (float)a/700.f;
}

void Game::go()
{
	MenuMain	menu;
	int			r;
	static int	zob = 0;

	box_manager.add(0.3442, 0.4028,   0.65,   0.46, "START", 0);
	box_manager.add(0.3957, 0.5017, 0.5971, 0.5614, "OPTS", 0);
	box_manager.add(0.4371,   0.61, 0.5514, 0.6642, "EXIT", 0);

	box_manager.add(0.2185, 0.4028,   0.78, 0.4614, "RET_START_GAME1", 9);
	box_manager.add(0.2071, 0.5085, 0.7914, 0.5642, "RET_START_GAME2", 9);
	box_manager.add(  0.41, 0.6114, 0.5842,   0.67, "RETOUR_START",    9);

	box_manager.add(0.4357, 0.4328, 0.5528, 0.4942, "RET_EXIT",    8);
	box_manager.add(0.4057,   0.54, 0.5842, 0.5971, "RETOUR_EXIT", 8);

	box_manager.add(cv(231), cv(261), cv(467), cv(302), "PAUSE_RESUME", 10);
	box_manager.add(cv(278), cv(335), cv(418), cv(376), "PAUSE_OPTION", 10);
	box_manager.add(cv(253), cv(406), cv(443), cv(446), "PAUSE_EXIT",   10);


    box_manager.add(cv(308), cv(639), cv(388), cv(680), "play",     98);
    box_manager.add(cv(466), cv(340), cv(700), cv(407), "goblop",   98);
	box_manager.add(cv(0),   cv(340), cv(211), cv(407), "goblip",   98);

	///centre (0.1371, 0.8285)
	///min    (0.0328, 0.67)
	///max    (0.2357, 0.9828)
	//box_manager.add(cv(3), cv(407), cv(187), cv(695), "pad",    99);
	p_joystick.LoadPNG("data/pad.png");
	stick.LoadPNG("data/stick.png");
	p_pad0.LoadPNG("data/pad0.png");
	p_pad1.LoadPNG("data/pad1.png");
	p_pad2.LoadPNG("data/pad2.png");
	p_pad3.LoadPNG("data/pad3.png");
	p_pad4.LoadPNG("data/pad4.png");
	p_pad5.LoadPNG("data/pad5.png");
	p_pad6.LoadPNG("data/pad6.png");
	p_pad7.LoadPNG("data/pad7.png");


	box_manager.add(0.92, 0, 1, 0.1085, "pause",    99);
	p_pause.LoadPNG("data/pause.png");

	box_manager.add(0.8957, 0.8571, 0.9885, 0.9885, "ulti",    99);
	p_ulti.LoadPNG("data/ulti.png");
	p_ulti_p.LoadPNG("data/ulti_p.png");

	box_manager.add(0.8742, 0.68, 0.9714, 0.8128, "jump",    99);
    p_jump.LoadPNG("data/jump.png");
    p_jump_p.LoadPNG("data/jump_p.png");

    box_manager.add(0.7714, 0.8442, 0.8657, 0.9785, "shoot",    99);
    p_shoot.LoadPNG("data/shoot.png");
    p_shoot_p.LoadPNG("data/shoot_p.png");




	// Clear l'écran en noir + LOADING
	//
	{
		DDBLTFX		ddfx;

		ZeroMemory(&ddfx, sizeof(ddfx));
		ddfx.dwSize = sizeof(ddfx);
		ddfx.dwFillColor = 0;

		backSurface->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddfx);
		fnt_cool.printC(backSurface, 320, 240, "PLEASE WAIT");
	}

	CINEPlayer	cine;

	cine.loadPBK("data/intro.gfx");
	mbk_interl.play(0);
	cine.playScene("data/intro.cin", primSurface, backSurface);

	menu.start();
	in.waitClean();

	DWORD diff_start = GetTickCount();
//	DWORD diff_time;
    int retour;
    bool cine_played = true;

	do {
		r = RET_CONTINUE;

		while (!r && !app_killed) {
		    retour = -1;
			manageMsg();
			checkRestore();

			in.update();
			LOGI("go");///UPDATE Selection d'ecran principale

			///MODIF touch
			//if (in.anyKeyPressed()) {
			if(in.so_up() || in.so_down()) {
				diff_start = GetTickCount();
			}

			if(GetTickCount() - diff_start >= 20000)
			cine_played = false;


			if (cine_played == false) {/// TEMPS AVANT DE RECHARGER L'INTRO , TODO regler ecran noir
				switch (zob) {
				    ///UPDATE intro
                    case 0:
                    cine.loadPBK("data/intro.gfx");
                    retour = !cine.playScene("data/intro.cin", primSurface, backSurface);
                    break;

                    case 1:
                    retour = showCredits();
                    break;
				}

				///MODIF zob
				//zob = (zob + 1) % 8;

				zob++;
				if(zob == 2)
				zob = 0;
				cine_played = true;


				menu.stop();
				menu.start();
				diff_start = GetTickCount();
			}
			else
			{
				pbk_inter[1]->PasteTo(backSurface, 0, 0);

				r = menu.update();
				menu.draw(backSurface);
				if (menu.up)
                diff_start = GetTickCount();

				DDFlipV();//primSurface->Flip(NULL, DDFLIP_WAIT );
			}

			in.refresh();
		}

		if (r == RET_START_GAME1 || r == RET_START_GAME2) { ///jouer
			if (r == RET_START_GAME1)
			{
			    LOGI("TOUT SEUL");
			    jouePartie(1, selectPlayer());
			}
			else
			{
			    LOGI("A DEUX");
			    jouePartie(2, selectPlayer());
			}

			menu.stop();
			menu.start();
			mbk_interl.play(0);
			diff_start = GetTickCount();
		}

	} while (r != RET_EXIT && !app_killed);

	menu.stop();

	mbk_interl.stop();
}


//-----------------------------------------------------------------------------

void Game::drawVehicules()
{
	Sprite *	pl;

	list_vehicules.start();

	while (!list_vehicules.fin()) {
		pl = (Sprite*) list_vehicules.info();
		pl->affiche();
		list_vehicules.suivant();
	}
}


//-----------------------------------------------------------------------------

void Game::updateVehicules()
{
	Sprite *	pl;

	list_vehicules.start();

	while (!list_vehicules.fin()) {
		pl = (Sprite*) list_vehicules.info();
		pl->update();
		list_vehicules.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::updateFondsStatiques()
{
	Sprite *	pl;

	list_fonds_statiques.start();

	while (!list_fonds_statiques.fin()) {
		pl = (Sprite*) list_fonds_statiques.info();
		pl->update();
		list_fonds_statiques.suivant();
	}
}

//-----------------------------------------------------------------------------

void Game::drawFondsStatiques()
{
	Sprite *	pl;

	list_fonds_statiques.start();

	while (!list_fonds_statiques.fin()) {
		pl = (Sprite*) list_fonds_statiques.info();
		pl->affiche();
		list_fonds_statiques.suivant();
	}
}

//-----------------------------------------------------------------------------

bool Game::showBriefing(char * fn)
{
	pbk_briefing.loadGFX(fn, DDSURF_SYSTEM, false);

	briefing = true;

	DDBLTFX		ddfx;
	RECT		r;

	ZeroMemory(&ddfx, sizeof(ddfx));
	ddfx.dwSize = sizeof(ddfx);
	ddfx.dwFillColor = 0; // Noir

	r.left	= 0;
	r.right = 640;
	r.top	= 0;
	r.bottom = 480;

	backSurface->Blt(&r, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddfx);

	pbk_briefing[0]->PasteTo(backSurface, 0, 0);
	LOGI("LOADING");
	fnt_rpg.printC(backSurface, 320, 460, "Loading...");
	DDFlip();
}

//-----------------------------------------------------------------------------

int Game::selectPlayer()
{
	static const int APPAR_BLIP	= 0;
	static const int FINI_BLIP	= 1;
	static const int APPAR_BLOP	= 2;
	static const int FINI_BLOP	= 3;

	int		etape	 = APPAR_BLIP;
	int		et_phase = 0;
	int		id_perso = 0;
	int		x_perso  = -300;
	int		y_perso	 = 255;
	int		x_nom	 = 1040;
	int		y_nom	 = 255;
	int		y_select = -50;
	int		pic_select;
	int		x_back1	 = 0;
	int		x_back2	 = 640;

	if (lang_type == LANG_UK)
		pic_select = 10;
	else
		pic_select = 11;

    bool play_drawed = false;


	while (!app_killed) {
		manageMsg();
		checkRestore();
		in.update();
		box_manager.manage(98);
		LOGI("selectPlayer");///UPDATE JOUEUR

		et_phase += 1;
		et_phase %= 10;

		if (et_phase == 0)
			phase = !phase;

		// Le fond
		//
		x_back1 -= 20;
		x_back2 -= 20;

		if (x_back1 == -640) x_back1 = 640;
		if (x_back2 == -640) x_back2 = 640;

		pbk_inter[6]->PasteTo(backSurface, x_back1, 0);
		pbk_inter[7]->PasteTo(backSurface, x_back2, 0);


		// Gestion du texte
		//
		if (y_select < 50)
			y_select += 10;

		pbk_inter[pic_select]->BlitTo(backSurface, 320, y_select);

		// Le perso + le nom
		//
		if (etape == APPAR_BLIP) {
			if (x_perso < 240) {
				x_perso += 20;
			//} else if (in.scanKey(DIK_RIGHT) || in.scanAlias(ALIAS_P1_RIGHT)) {
			} else if (box_manager.get_state("goblop") == TOUCH_UP) {
				etape = FINI_BLIP;
			} else if (phase) {
				pbk_inter[4]->BlitTo(backSurface, 620, 257);
			}

			if (x_nom > 500)
				x_nom -= 20;

			pbk_inter[2]->BlitTo(backSurface, x_perso, y_perso);
			pbk_inter[8]->BlitTo(backSurface, x_nom, y_nom);

			//if (x_perso >= 240 && (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE))) {
			if(x_perso >= 240 && box_manager.get_state("play") == TOUCH_UP) {
				drawLoading();
				DDFlipV();//primSurface->Flip( 0, NULL);
				in.refresh();
				return 0;
			}
		} else if (etape == FINI_BLIP) {
			if (x_perso > -300) {
				x_perso -= 20;
			}

			if (x_nom < 1040)
				x_nom += 20;

			pbk_inter[2]->BlitTo(backSurface, x_perso, y_perso);
			pbk_inter[8]->BlitTo(backSurface, x_nom, y_nom);

			if (x_perso <= -300) {
				etape = APPAR_BLOP;
				x_perso = 930;
				x_nom = -500;
				y_perso = 320;
			}
		} else if (etape == APPAR_BLOP) {
			if (x_perso > 310) {
				x_perso -= 20;
			//} else if (in.scanKey(DIK_LEFT) || in.scanAlias(ALIAS_P1_LEFT)) {
			} else if (box_manager.get_state("goblip") == TOUCH_UP) {
				etape = FINI_BLOP;
			} else if (phase) {
				pbk_inter[5]->BlitTo(backSurface, 20, 254);
			}

			if (x_nom < 120)
				x_nom += 20;

			pbk_inter[3]->BlitTo(backSurface, x_perso, y_perso);
			pbk_inter[9]->BlitTo(backSurface, x_nom, y_nom);

			///MODIF touch
			//if (x_perso <= 310 && (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE))) {
			if( x_perso <= 310 && box_manager.get_state("play") == TOUCH_UP) {
				drawLoading();
				DDFlipV();//primSurface->Flip( 0, NULL);

				in.refresh();
				return 1;
			}
		} else {
			if (x_perso < 930) {
				x_perso += 20;
			}

			if (x_nom > -500)
				x_nom -= 20;

			pbk_inter[3]->BlitTo(backSurface, x_perso, y_perso);
			pbk_inter[9]->BlitTo(backSurface, x_nom, y_nom);

			if (x_perso >= 930) {
				etape = APPAR_BLIP;
				x_perso = -300;
				x_nom = 1040;
				y_perso = 255;
			}
		}

		if(x_perso == 240 || x_perso == 310)
        fnt_cool.printC(backSurface, 320,440, "PLAY");

		DDFlipV();//primSurface->Flip( 0, NULL);
		in.refresh();
	}

	return 0;
}

//-----------------------------------------------------------------------------

bool Game::showMainScreen()
{
	DWORD t = GetTickCount();

	///MODIF touch
	//while (!in.anyKeyPressed() && !app_killed && GetTickCount() - t <= 5000) {
	while ( /*!in.so_up()&& */!app_killed && GetTickCount() - t <= 5000) {
		manageMsg();
		checkRestore();

		in.update();
		LOGI("showMainScreen %d", in.so_up());///UPDATE ECRAN PRINCIPALE
		if(in.so_up() )
		return true;

		pbk_inter[1]->PasteTo(backSurface, 0, 0);
		DDFlipV();//primSurface->Flip(NULL, DDFLIP_WAIT );
		in.refresh();
	}
	return false;
}

//-----------------------------------------------------------------------------

bool Game::showCredits(bool theEnd)
{
	static const int GOOD = 118;
	static const int INT_SIZE = 50;
	static const int MARGE = 10;

	static int	marge[INT_SIZE] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	                             };
	static int	im = 0;


	static const int NB_PAGE = 6;
	static const int ILIGNE = 20;
	static const int ITITRE = 40;
	static const int IPARTI = 120;
	static const int SSPEED = 2;

	int		npage = 0;
	DWORD	t = GetTickCount();
	int		y = 480;
	int		ey = 0;
	int		last_y = 100;
	int		xcred = 320;

	PictureBank	pbk_cred;


	if (theEnd) {
		xcred = 510;
		pbk_cred.loadGFX("data/credits.gfx", DDSURF_BEST, false);
	}

	time = LGetTime();

    ///MODIF touch
	//while (!app_killed && (!in.anyKeyPressed() || theEnd) && last_y > 0) {
	while (!app_killed && (!in.so_up() || theEnd) && last_y > 0) {
		dtime += LGetTime() - time;
		time = LGetTime();
		int sum = 0;

		for (int i = 0; i < INT_SIZE; i++) {
			sum += marge[i];
		}

		glorf = sum / INT_SIZE;

		if (glorf >= -MARGE && glorf <= MARGE) {
			ey = (ey + 1) % SSPEED;
			if (ey == 0)
				y--;
			dtime = 0;
		} else {
			while (dtime >= GOOD) {
				ey = (ey + 1) % SSPEED;
				if (ey == 0)
					y--;
				dtime -= GOOD;
			}
		}

		im += 1;
		im %= INT_SIZE;

		manageMsg();
		checkRestore();
		in.update();
		LOGI("showCredits");///UPDATE credit
		if(in.so_up())
		return true;

		if (mustFixGforceBug) {
			RECT	r;

			r.top	= 10;
			r.bottom = 150;
			r.left	= 200;
			r.right = 440;

			backSurface->Blt(&r, videoA, NULL, DDBLT_WAIT, NULL);
		}

		{
			DDBLTFX         ddfx;
			RECT	r;

			ZeroMemory(&ddfx, sizeof(ddfx));
			ddfx.dwSize = sizeof(ddfx);
			ddfx.dwFillColor = 0; // Noir

			r.left	= 0;
			r.right = 640;
			r.top	= 0;
			r.bottom = 480;

			//backSurface->Blt(&r, NULL, NULL, DDBLT_WAIT | DDBLT_COLORFILL, &ddfx);
		}


		if (theEnd) {
			pbk_cred[npage]->PasteTo(backSurface, 0, 0);
		} else {
			pbk_inter[1]->BlitTo(backSurface, 0, 0);
		}

		fnt_rpg.printC(backSurface, xcred, y + ILIGNE, "Credits");

		int y1 = y + ILIGNE + IPARTI;

		fnt_rpg.printC(backSurface, xcred, y1, "CODE");
		fnt_rpg.printC(backSurface, xcred, y1 + ITITRE + ILIGNE * 0, "Benjamin Karaban");
		fnt_rpg.printC(backSurface, xcred, y1 + ITITRE + ILIGNE * 1, "Sylvain Bugat");
//		fnt_rpg.printC( backSurface, xcred, y1+ITITRE+ILIGNE*2, "Didier Colin");

		int y2 = y1 + 2 * ILIGNE + IPARTI + ITITRE;

		fnt_rpg.printC(backSurface, xcred, y2, "MUSIC AND SOUND");
		fnt_rpg.printC(backSurface, xcred, y2 + ILIGNE, "DESIGN");
		fnt_rpg.printC(backSurface, xcred, y2 + ITITRE + ILIGNE, "Gerard Kelly");

		int y3 = y2 + 2 * ILIGNE + IPARTI + ITITRE;

		fnt_rpg.printC(backSurface, xcred, y3, "ADDITIONAL MUSIC");
		fnt_rpg.printC(backSurface, xcred, y3 + ITITRE + 0 * ILIGNE, "El Mobo");
		fnt_rpg.printC(backSurface, xcred, y3 + ITITRE + 1 * ILIGNE, "Rik Ede");

		int y4 = y3 + 2 * ILIGNE + IPARTI + ITITRE;

		fnt_rpg.printC(backSurface, xcred, y4, "ARTWORK");
		fnt_rpg.printC(backSurface, xcred, y4 + ITITRE + ILIGNE * 0, "Laurent Schneider");
		fnt_rpg.printC(backSurface, xcred, y4 + ITITRE + ILIGNE * 1, "Jérémie Comarmond");
		fnt_rpg.printC(backSurface, xcred, y4 + ITITRE + ILIGNE * 2, "Jérôme Karaban");
		fnt_rpg.printC(backSurface, xcred, y4 + ITITRE + ILIGNE * 3, "Didier Colin");
		fnt_rpg.printC(backSurface, xcred, y4 + ITITRE + ILIGNE * 4, "Sylvain Bugat");

		int y5 = y4 + 5 * ILIGNE + IPARTI + ITITRE;

		fnt_rpg.printC(backSurface, xcred, y5, "ADDITIONAL SOUND");
		fnt_rpg.printC(backSurface, xcred, y5 + ILIGNE, "AND VOCAL EFFECTS");
		fnt_rpg.printC(backSurface, xcred, y5 + ITITRE + 1 * ILIGNE, "Eric Khodja");
		fnt_rpg.printC(backSurface, xcred, y5 + ITITRE + 2 * ILIGNE, "Jérôme Karaban");
		fnt_rpg.printC(backSurface, xcred, y5 + ITITRE + 3 * ILIGNE, "Benjamin Karaban");
		fnt_rpg.printC(backSurface, xcred, y5 + ITITRE + 4 * ILIGNE, "Vincent Lagarrigue");

		int y6 = y5 + 5 * ILIGNE + IPARTI + ITITRE;

		fnt_rpg.printC(backSurface, xcred, y6, "STORYLINE");
		fnt_rpg.printC(backSurface, xcred, y6 + ITITRE + 0 * ILIGNE, "Benjamin Karaban");
		fnt_rpg.printC(backSurface, xcred, y6 + ITITRE + 1 * ILIGNE, "Eric Khodja");

		int y7 = y6 + 2 * ILIGNE + IPARTI + ITITRE;

		fnt_rpg.printC(backSurface, xcred, y7, "ORIGINAL CONCEPT");
		fnt_rpg.printC(backSurface, xcred, y7 + ITITRE + 0 * ILIGNE, "Laurent Schneider");
		fnt_rpg.printC(backSurface, xcred, y7 + ITITRE + 1 * ILIGNE, "Jérémie Comarmond");
		fnt_rpg.printC(backSurface, xcred, y7 + ITITRE + 2 * ILIGNE, "Didier Colin");
		fnt_rpg.printC(backSurface, xcred, y7 + ITITRE + 3 * ILIGNE, "Sylvain Bugat");
		fnt_rpg.printC(backSurface, xcred, y7 + ITITRE + 4 * ILIGNE, "Benjamin Karaban");

		int y8 = y7 + 5 * ILIGNE + IPARTI + ITITRE;

		fnt_rpg.printC(backSurface, xcred, y8, "BETA TEST");
		fnt_rpg.printC(backSurface, xcred, y8 + ITITRE + 0 * ILIGNE, "Jérémie Khodja");
		fnt_rpg.printC(backSurface, xcred, y8 + ITITRE + 1 * ILIGNE, "Julien Areas");
		fnt_rpg.printC(backSurface, xcred, y8 + ITITRE + 2 * ILIGNE, "Carlos Sédille");
		fnt_rpg.printC(backSurface, xcred, y8 + ITITRE + 3 * ILIGNE, "Juliette Karaban");

		int y9 = y8 + 4 * ILIGNE + IPARTI + ITITRE;
		int y10 = y9;
		int y11 = y10;


		if (theEnd) {
			fnt_rpg.printC(backSurface, xcred, y9, "THANKS TO");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 0 * ILIGNE, "Arnaud Dubois");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 1 * ILIGNE, "Carole Schmitt");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 2 * ILIGNE, "Aasterion staff");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 3 * ILIGNE, "Aurore Anger");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 4 * ILIGNE, "Cécile Baudoncourt");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 5 * ILIGNE, "Nicolas Clément");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 6 * ILIGNE, "Nathalie Morin");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 7 * ILIGNE, "Florent and Thomas");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 8 * ILIGNE, "Bruno Singer");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 9 * ILIGNE, "Francois Deschamps");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 10 * ILIGNE, "Colin Auger");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 11 * ILIGNE, "TP122 students");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 12 * ILIGNE, "Jeff");
			fnt_rpg.printC(backSurface, xcred, y9 + ITITRE + 13 * ILIGNE, "Flavy");

			y10 = y9 + 14 * ILIGNE + IPARTI + ITITRE;

			fnt_rpg.printC(backSurface, xcred, y10, "SPECIAL THANKS TO");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 0 * ILIGNE, "La Guinguette Pirate");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 1 * ILIGNE, "TiPunch power!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 3 * ILIGNE, "La Pirogue");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 4 * ILIGNE, "I love you Séverine!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 6 * ILIGNE, "Le Montbauron");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 7 * ILIGNE, "mind the 8 ball!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 9 * ILIGNE, "La Fleche d'Or");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 10 * ILIGNE, "avoid the toilets!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 12 * ILIGNE, "Hippochine Restaurant");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 13 * ILIGNE, "great music!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 15 * ILIGNE, "Vitigno Pizzeria");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 16 * ILIGNE, "pizza! good!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 18 * ILIGNE, "Max Linder Theatre");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 19 * ILIGNE, "THX rules!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 21 * ILIGNE, "UNEF");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 22 * ILIGNE, "cheap beer 4 all!");


			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 24 * ILIGNE, "Hayao Myazaki");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 25 * ILIGNE, "Totoro! To-to-ro!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 27 * ILIGNE, "Kevin Smith");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 28 * ILIGNE, "thirty seven?");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 30 * ILIGNE, "Peter Jackson");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 31 * ILIGNE, "Bad Taste rules!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 33 * ILIGNE, "Monty Python");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 34 * ILIGNE, "behind the rabbit?");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 36 * ILIGNE, "John Boorman");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 37 * ILIGNE, "Zardoz has spoken!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 39 * ILIGNE, "Luc Besson");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 40 * ILIGNE, "nah... just kidding!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 42 * ILIGNE, "Christopher Lambert");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 43 * ILIGNE, "watch your back!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 45 * ILIGNE, "Jeremy Irons");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 46 * ILIGNE, "lord Profion!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 48 * ILIGNE, "Wayne Scott");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 49 * ILIGNE, "Rambo! Rambo!");


			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 51 * ILIGNE, "Les Joyeux Urbains");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 52 * ILIGNE, "va chez ta mère!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 54 * ILIGNE, "Toss");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 55 * ILIGNE, "da! da! da!");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 57 * ILIGNE, "Le cassoulet");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 58 * ILIGNE, "best served at 4 AM");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 60 * ILIGNE, "Gamedev.net");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 61 * ILIGNE, "DirectX vs hamsters");

			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 64 * ILIGNE, "THANK");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 65 * ILIGNE, "YOU");
			fnt_rpg.printC(backSurface, xcred, y10 + ITITRE + 66 * ILIGNE, "FOR PLAYING");

			y11 = y10 + 72 * ILIGNE + IPARTI + ITITRE;
		}


		fnt_rpg.printC(backSurface, xcred, y11, "LOADED Studio");
		fnt_rpg.printC(backSurface, xcred, y11 + ILIGNE, "May 2002");

		last_y = y11 + 2 * ILIGNE;

		if (GetTickCount() - t >= 12500 && theEnd) {
			npage++;
			npage %= pbk_cred.getSize();
			t = GetTickCount();
		}

		DDFlip();

		DWORD ttotal = LGetTime() - time;

		if (ttotal <= 0)
			ttotal = GOOD;
		else if (ttotal >= 5000)
			ttotal = GOOD;

		marge[im] = ttotal - GOOD;

		in.refresh();
	}

	if (theEnd) {
		pbk_cred.close();
	}

	return false;
}

//-----------------------------------------------------------------------------

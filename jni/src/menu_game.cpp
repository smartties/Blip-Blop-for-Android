#include <cstdio>
#include <cstring>
#include "lgx_packer.h"
#include "input.h"
#include "globals.h"
#include "config.h"
#include "menu_game.h"
#include "txt_data.h"
#include "control_alias.h"
#include "key_translator.h"

#define TXT_RESUME		800
#define TXT_OPTIONS		801

#define TXT_CTRL		803
#define TXT_EXIT_GAME	805
//-------------------------
#define TXT_VSYNC		806

#define TXT_RETURN		808
#define TXT_ON			809
#define TXT_OFF			810

//-------------------------




//-------------------------
#define TXT_LANGUAGE	816
#define TXT_RESET		829
//-------------------------
#define TXT_P1CTRL		817
#define TXT_P2CTRL		818
#define TXT_P1KEYS		819
#define TXT_P2KEYS		820
//-------------------------
#define TXT_UP			821
#define TXT_DOWN		822
#define TXT_LEFT		823
#define TXT_RIGHT		824
#define TXT_FIRE		825
#define TXT_JUMP		826
#define TXT_SPECIAL		827

#define MENU_MAIN	0
#define MENU_OPTS	1


#define MENU_KEY1	5
#define MENU_KEY2	6

#define NB_TXT		10


MenuGame::MenuGame()
{
	redefine = -1;

	menu_txt = new char * [NB_TXT];

	for (int i = 0; i < NB_TXT; i++)
		menu_txt[i] = new char[100];
}

MenuGame::~MenuGame()
{
	if (menu_txt != NULL) {
		for (int i = 0; i < NB_TXT; i++)
			delete [] menu_txt[i];

		delete [] menu_txt;
		menu_txt = NULL;
	}
}

void MenuGame::start()
{
	current_menu = MENU_MAIN;
	nb_focus = 3;
	focus = 0;
	updateName();
}

int MenuGame::update()
{
	in.update();
	box_manager.manage(10+current_menu);
	LOGI("MenuGame %d", current_menu);///UPDATE MENU ///a revoir(plusieurs return)

	updateRedefine();
	updateName();

	/**
	case 0:		// Resume game
						return 1;
						break;

					case 1:		// Options
						current_menu = MENU_OPTS;
						nb_focus = 4;
						focus = 3;
						updateName();
						return 0;
						break;

					case 2:		// Exit
						return 2;
						break;
	**/

	int retour = 0;

	if(current_menu == MENU_MAIN)
	{
	    if(box_manager.get_state("PAUSE_RESUME") == TOUCH_DOWN ||
           box_manager.get_state("PAUSE_RESUME") == TOUCH_PRESSING)
        focus = 0;
	    if(box_manager.get_state("PAUSE_RESUME") == TOUCH_UP)
	    {
	        LOGI("PAUSE_RESUME");
	        retour = 1;
	    }
	    if(box_manager.get_state("PAUSE_OPTION") == TOUCH_DOWN ||
           box_manager.get_state("PAUSE_OPTION") == TOUCH_PRESSING)
        focus = 1;
	    /*if(box_manager.get_state("PAUSE_OPTION") == TOUCH_UP)///TODO
	    {
	        LOGI("PAUSE_OPTION");
	    }*/
	    if(box_manager.get_state("PAUSE_EXIT") == TOUCH_DOWN ||
           box_manager.get_state("PAUSE_EXIT") == TOUCH_PRESSING)
        focus = 2;
	    if(box_manager.get_state("PAUSE_EXIT") == TOUCH_UP)
	    {
	        LOGI("PAUSE_EXIT");
	        retour = 2;
	    }
	}

	in.refresh();
	return retour;

	//////////////////////////////////////////////////
	//	Touche haut
	//////////////////////////////////////////////////

	if (in.scanKey(DIK_UP) || in.scanAlias(ALIAS_P1_UP)) {
		focus -= 1;

		if (focus < 0)
			focus = nb_focus - 1;

		in.waitClean();
	}
	//////////////////////////////////////////////////
	//	Touche bas
	//////////////////////////////////////////////////
	else if (in.scanKey(DIK_DOWN) || in.scanAlias(ALIAS_P1_DOWN)) {
		focus += 1;
		focus %= nb_focus;
		in.waitClean();
	}

	//////////////////////////////////////////////////
	//	Touche entrée
	//////////////////////////////////////////////////

	if (in.scanKey(DIK_RETURN) || in.scanAlias(ALIAS_P1_FIRE)) {
		in.waitClean();

		switch (current_menu) {
			case MENU_MAIN:
				switch (focus) {
					case 0:		// Resume game
						return 1;
						break;

					case 1:		// Options
						current_menu = MENU_OPTS;
						nb_focus = 4;
						focus = 3;
						updateName();
						return 0;
						break;

					case 2:		// Exit
						return 2;
						break;
				}
				break;

			case MENU_OPTS:
				switch (focus) {
					case 0:
						vSyncOn = !vSyncOn;
						updateName();
						return 0;
						break;

					case 1:
						current_menu = MENU_KEY1;
						nb_focus = 8;
						focus = 7;
						updateName();
						return 0;
						break;

					case 2:
						current_menu = MENU_KEY2;
						nb_focus = 8;
						focus = 7;
						updateName();
						return 0;
						break;

					case 3:		// Return
						current_menu = MENU_MAIN;
						nb_focus = 3;
						focus = 1;
						updateName();
						return 0;
						break;
				}
				break;

			case MENU_KEY1:		// Redefinition
				switch (focus) {
					case 7:
						current_menu = MENU_OPTS;
						nb_focus = 4;
						focus = 3;
						updateName();
						return 0;
						break;

					default:
						redefine = focus;
						updateName();
						return 0;
						break;
				}
				break;

			case MENU_KEY2:		// Redefinition 2
				switch (focus) {
					case 7:
						current_menu = MENU_OPTS;
						nb_focus = 4;
						focus = 3;
						updateName();
						return 0;
						break;

					default:
						redefine = focus;
						updateName();
						return 0;
						break;
				}
				break;
		}
	}

	//////////////////////////////////////////////////
	//	Touche droite
	//////////////////////////////////////////////////

	if (in.scanKey(DIK_RIGHT) || in.scanAlias(ALIAS_P1_RIGHT)) {
		in.waitClean();

		switch (current_menu) {
			case MENU_OPTS:
				switch (focus) {
					case 0:
						vSyncOn = !vSyncOn;
						updateName();
						return 0;
						break;
						/*
									case 1:	// Language
										lang_type += 1;
										lang_type %= 2;

										freeTxtData();

										if ( lang_type == LANG_UK)
											loadTxtData( "data\\uk.dat");
										else
											loadTxtData( "data\\fr.dat");
										break;
						*/
				}
				break;
		}
	}
	//////////////////////////////////////////////////
	//	Touche gauche
	//////////////////////////////////////////////////
	if (in.scanKey(DIK_LEFT) || in.scanAlias(ALIAS_P1_LEFT)) {
		in.waitClean();

		switch (current_menu) {
			case MENU_OPTS:
				switch (focus) {
					case 0:
						vSyncOn = !vSyncOn;
						updateName();
						return 0;
						break;
						/*
									case 1:	// Language
										lang_type += 1;
										lang_type %= 2;

										freeTxtData();

										if ( lang_type == LANG_UK)
											loadTxtData( "data\\uk.dat");
										else
											loadTxtData( "data\\fr.dat");
										break;
						*/
				}
				break;
		}
	}

	if (in.scanKey(DIK_ESCAPE)) {
		in.waitClean();
		return 1;
	} else
		return 0;
}

void MenuGame::draw(SDL::Surface * surf)
{

	int		ys = nb_focus * 20;
	int		y  = 240 - ys;
	int		tmp;

	// Trouve la taille du schnuff à assombrir
	//
	int largeur = 0;

	for (int i = 0; i < nb_focus; i++) {
		tmp = fnt_menu.width(menu_txt[i]);

		if (tmp > largeur)
			largeur = tmp;
	}

	largeur += 60;
	largeur /= 2;

	if (largeur < 200)
		largeur = 200;
	else if (largeur > 320)
		largeur = 320;

	// Réinitialise le cache systeme si le menu a changé
	// ou si on dépasse sur les cotés
	//
	tmp = (320 - largeur) - rec.left; // tmp = différence de largeur


	if (current_menu != old_menu || tmp > 20 || tmp < -20) {
		// Copie le schnuff en cache SYSTEME
		//
		systemSurface->BltFast(0, 0, surf, NULL, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);

		rec.top		= 220 - ys;
		rec.left	= 320 - largeur;
		rec.bottom	= 260 + ys;
		rec.right	= 320 + largeur;

		LGXpaker.halfTone(systemSurface, &rec);

		old_menu = current_menu;
	}

	// Copie la surface déjà colorisée
	//
	surf->BltFast(0, 0, systemSurface, NULL, DDBLTFAST_NOCOLORKEY | DDBLTFAST_WAIT);


	for (int i = 0; i < nb_focus; i++) {
		if (focus == i)
			fnt_menus.printC(surf, 320, y, menu_txt[i]);
		else
			fnt_menu.printC(surf, 320, y, menu_txt[i]);

		y += 50;
	}
}


void MenuGame::updateName()
{
	char	buffer[200];

	switch (current_menu) {
		case MENU_MAIN:
			strcpy(menu_txt[0], txt_data[TXT_RESUME]);
			strcpy(menu_txt[1], txt_data[TXT_OPTIONS]);
			strcpy(menu_txt[2], txt_data[TXT_EXIT_GAME]);
			break;

		case MENU_OPTS:

			if (vSyncOn)
				sprintf(menu_txt[0], "%s %s", txt_data[TXT_VSYNC], txt_data[TXT_ON]);
			else
				sprintf(menu_txt[0], "%s %s", txt_data[TXT_VSYNC], txt_data[TXT_OFF]);

//		strcpy( menu_txt[1], txt_data[TXT_LANGUAGE]);
			strcpy(menu_txt[1], txt_data[TXT_P1KEYS]);
			strcpy(menu_txt[2], txt_data[TXT_P2KEYS]);
			strcpy(menu_txt[3], txt_data[TXT_RETURN]);
			break;

		case MENU_KEY1:
			if (redefine == 0)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P1_UP), buffer);
			sprintf(menu_txt[0], "%s = %s", txt_data[TXT_UP], buffer);

			if (redefine == 1)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P1_DOWN), buffer);
			sprintf(menu_txt[1], "%s = %s", txt_data[TXT_DOWN], buffer);

			if (redefine == 2)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P1_LEFT), buffer);
			sprintf(menu_txt[2], "%s = %s", txt_data[TXT_LEFT], buffer);

			if (redefine == 3)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P1_RIGHT), buffer);
			sprintf(menu_txt[3], "%s = %s", txt_data[TXT_RIGHT], buffer);

			if (redefine == 4)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P1_FIRE), buffer);
			sprintf(menu_txt[4], "%s = %s", txt_data[TXT_FIRE], buffer);

			if (redefine == 5)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P1_JUMP), buffer);
			sprintf(menu_txt[5], "%s = %s", txt_data[TXT_JUMP], buffer);

			if (redefine == 6)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P1_SUPER), buffer);
			sprintf(menu_txt[6], "%s = %s", txt_data[TXT_SPECIAL], buffer);

			strcpy(menu_txt[7], txt_data[TXT_RETURN]);
			break;

		case MENU_KEY2:
			if (redefine == 0)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P2_UP), buffer);
			sprintf(menu_txt[0], "%s = %s", txt_data[TXT_UP], buffer);

			if (redefine == 1)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P2_DOWN), buffer);
			sprintf(menu_txt[1], "%s = %s", txt_data[TXT_DOWN], buffer);

			if (redefine == 2)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P2_LEFT), buffer);
			sprintf(menu_txt[2], "%s = %s", txt_data[TXT_LEFT], buffer);

			if (redefine == 3)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P2_RIGHT), buffer);
			sprintf(menu_txt[3], "%s = %s", txt_data[TXT_RIGHT], buffer);

			if (redefine == 4)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P2_FIRE), buffer);
			sprintf(menu_txt[4], "%s = %s", txt_data[TXT_FIRE], buffer);

			if (redefine == 5)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P2_JUMP), buffer);
			sprintf(menu_txt[5], "%s = %s", txt_data[TXT_JUMP], buffer);

			if (redefine == 6)
				strcpy(buffer, "...");
			else
				DIK_to_string(in.getAlias(ALIAS_P2_SUPER), buffer);
			sprintf(menu_txt[6], "%s = %s", txt_data[TXT_SPECIAL], buffer);

			strcpy(menu_txt[7], txt_data[TXT_RETURN]);
			break;
	}
}

void MenuGame::stop()
{
	old_menu = -1;
}

void MenuGame::updateRedefine()
{
	if (redefine == -1)
		return;


	int n = in.waitKey();

	if (current_menu == MENU_KEY1) {
		switch (redefine) {
			case 0:
				in.setAlias(ALIAS_P1_UP, n);
				break;
			case 1:
				in.setAlias(ALIAS_P1_DOWN, n);
				break;
			case 2:
				in.setAlias(ALIAS_P1_LEFT, n);
				break;
			case 3:
				in.setAlias(ALIAS_P1_RIGHT, n);
				break;
			case 4:
				in.setAlias(ALIAS_P1_FIRE, n);
				break;
			case 5:
				in.setAlias(ALIAS_P1_JUMP, n);
				break;
			case 6:
				in.setAlias(ALIAS_P1_SUPER, n);
				break;
		}
	} else {
		switch (redefine) {
			case 0:
				in.setAlias(ALIAS_P2_UP, n);
				break;
			case 1:
				in.setAlias(ALIAS_P2_DOWN, n);
				break;
			case 2:
				in.setAlias(ALIAS_P2_LEFT, n);
				break;
			case 3:
				in.setAlias(ALIAS_P2_RIGHT, n);
				break;
			case 4:
				in.setAlias(ALIAS_P2_FIRE, n);
				break;
			case 5:
				in.setAlias(ALIAS_P2_JUMP, n);
				break;
			case 6:
				in.setAlias(ALIAS_P2_SUPER, n);
				break;
		}
	}

	in.waitClean();
	redefine = -1;
}

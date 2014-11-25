#include <cstdio>
#include <cstring>
#include "lgx_packer.h"
#include "input.h"
#include "globals.h"
#include "config.h"
#include "menu_main.h"
#include "txt_data.h"
#include "control_alias.h"
#include "key_translator.h"

#define TXT_RESUME		800
#define TXT_VIDEO		801
#define TXT_SOUND		802
#define TXT_CTRL		803
#define TXT_MISC		804
#define TXT_EXIT_GAME	805
#define TXT_ON			809
#define TXT_OFF			810
#define TXT_VSYNC		806

#define TXT_SYNCHRO		806
#define TXT_DETAIL		807
#define TXT_RETURN		808
#define TXT_DHIGH		809
#define TXT_DMED		810
#define TXT_DLOW		811

#define TXT_MUSICVOL	812
#define TXT_SOUNDVOL	813
#define TXT_MUSICON		814
#define TXT_SOUNDON		815

#define TXT_LANGUAGE	816
#define TXT_RESET		829

#define TXT_P1CTRL		817
#define TXT_P2CTRL		818
#define TXT_P1KEYS		819
#define TXT_P2KEYS		820

#define TXT_UP			821
#define TXT_DOWN		822
#define TXT_LEFT		823
#define TXT_RIGHT		824
#define TXT_FIRE		825
#define TXT_JUMP		826
#define TXT_SPECIAL		827

#define TXT_START_GAME	830
#define TXT_EXIT		833

#define TXT_START_GAME1	831
#define TXT_START_GAME2	832

#define TXT_CANCEL		834

#define MENU_MAIN		0




#define MENU_KEY1		5
#define MENU_KEY2		6
#define MENU_OPTS		7
#define MENU_EXIT		8
#define MENU_START		9

#define NB_TXT		10


MenuMain::MenuMain()
{
	redefine = -1;

	menu_txt = new char * [NB_TXT];

	for (int i = 0; i < NB_TXT; i++)
		menu_txt[i] = new char[100];
}


MenuMain::~MenuMain()
{
	if (menu_txt != NULL) {
		for (int i = 0; i < NB_TXT; i++)
			delete [] menu_txt[i];

		delete [] menu_txt;
		menu_txt = NULL;
	}
}

void MenuMain::start()
{
	current_menu = MENU_MAIN;
	nb_focus = 3;
	focus = 0;
	updateName();

	start_music_on = music_on;
	start_sound_on = sound_on;
}

int MenuMain::update()
{
	in.update();

	box_manager.manage(current_menu);
	LOGI("MenuMain %d ", current_menu); ///UPDATE MenuMain /// a revoir (plusieurs return)

	//up = in.anyKeyPressed();

	updateRedefine();
	updateName();

	bool retour = RET_CONTINUE;

	if(current_menu == MENU_MAIN)
	{
	    if(box_manager.get_state("START") == TOUCH_DOWN ||
           box_manager.get_state("START") == TOUCH_PRESSING)
	    focus = 0;
	    if(box_manager.get_state("START") == TOUCH_UP)
	    {
	        LOGI("START");
	        current_menu = MENU_START;
            nb_focus = 3;
            focus = 0;
            updateName();
	    }
	    if(box_manager.get_state("OPTS") == TOUCH_DOWN ||
           box_manager.get_state("OPTS") == TOUCH_PRESSING)
	    focus = 1;
	    /*if(box_manager.get_state("OPTS") == TOUCH_UP)
	    {
	        current_menu = MENU_OPTS;
            nb_focus = 4;
            focus = 3;
            updateName();
	    }*/
	    if(box_manager.get_state("EXIT") == TOUCH_DOWN ||
           box_manager.get_state("EXIT") == TOUCH_PRESSING)
	    focus = 2;
	    if(box_manager.get_state("EXIT") == TOUCH_UP)
	    {
	        LOGI("EXIT");
	        current_menu = MENU_EXIT;
            nb_focus = 2;
            focus = 0;
            updateName();
	    }
	}
	else if(current_menu == MENU_START)
	{
	    if(box_manager.get_state("RET_START_GAME1") == TOUCH_DOWN ||
           box_manager.get_state("RET_START_GAME1") == TOUCH_PRESSING)
	    focus = 0;
	    if(box_manager.get_state("RET_START_GAME1") == TOUCH_UP)
	    {
	        LOGI("RET_START_GAME1");
	        retour = RET_START_GAME1;
	    }

	    if(box_manager.get_state("RET_START_GAME2") == TOUCH_DOWN ||
           box_manager.get_state("RET_START_GAME2") == TOUCH_PRESSING)
	    focus = 1;
	    if(box_manager.get_state("RET_START_GAME2") == TOUCH_UP)
	    {
	        LOGI("RET_START_GAME2");
	        retour = RET_CONTINUE;
	        int starting_time = GetTickCount();

	        fnt_rpg.printC(backSurface, 370, 350, "If Blip'n Blop reaches 100k downloads");
	        DDFlipV();
	        Sleep(3200);
	    }

	    if(box_manager.get_state("RETOUR_START") == TOUCH_DOWN ||
           box_manager.get_state("RETOUR_START") == TOUCH_PRESSING)
	    focus = 2;
	    if(box_manager.get_state("RETOUR_START") == TOUCH_UP)
	    {
	        LOGI("RETOUR_START");
	        current_menu = MENU_MAIN;
            nb_focus = 3;
            focus = 0;
            updateName();
	    }
	}
	else if(current_menu == MENU_OPTS)
	{

	    /// TODO
	}
	else if(current_menu == MENU_EXIT)
	{
	    if(box_manager.get_state("RET_EXIT") == TOUCH_DOWN ||
           box_manager.get_state("RET_EXIT") == TOUCH_PRESSING)
	    focus = 0;
	    if(box_manager.get_state("RET_EXIT") == TOUCH_UP)
	    {
	        LOGI("RET_EXIT");
	        retour = RET_EXIT;
	        exit(0);
	    }

	    if(box_manager.get_state("RETOUR_EXIT") == TOUCH_DOWN ||
           box_manager.get_state("RETOUR_EXIT") == TOUCH_PRESSING)
	    focus = 1;
	    if(box_manager.get_state("RETOUR_EXIT") == TOUCH_UP)
	    {
	        LOGI("RETOUR_EXIT");
	        current_menu = MENU_MAIN;
            nb_focus = 3;
            focus = 2;
            updateName();
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
					case 0:
						current_menu = MENU_START;
						nb_focus = 3;
						focus = 0;
						updateName();
						return RET_CONTINUE;
						break;

					case 1:
						current_menu = MENU_OPTS;
						nb_focus = 4;
						focus = 3;
						updateName();
						return RET_CONTINUE;
						break;

					case 2:
						current_menu = MENU_EXIT;
						nb_focus = 2;
						focus = 0;
						updateName();
						return RET_CONTINUE;
						break;
				}
				break;

			case MENU_START:
				switch (focus) {
					case 0:
						return RET_START_GAME1;
						break;

					case 1:
						return RET_START_GAME2;
						break;

					case 2:
						current_menu = MENU_MAIN;
						nb_focus = 3;
						focus = 0;
						updateName();
						break;
				}
				break;

			case MENU_EXIT:
				switch (focus) {
					case 0:
						return RET_EXIT;
						break;

					case 1:
						current_menu = MENU_MAIN;
						nb_focus = 3;
						focus = 2;
						updateName();
						break;
				}
				break;


			case MENU_OPTS:
				switch (focus) {
					case 0:
						vSyncOn = !vSyncOn;
						updateName();
						return RET_CONTINUE;
						break;

					case 1:
						current_menu = MENU_KEY1;
						nb_focus = 8;
						focus = 7;
						updateName();
						return RET_CONTINUE;
						break;

					case 2:
						current_menu = MENU_KEY2;
						nb_focus = 8;
						focus = 7;
						updateName();
						return RET_CONTINUE;
						break;

					case 3:		// Return
						current_menu = MENU_MAIN;
						nb_focus = 3;
						focus = 1;
						updateName();
						return RET_CONTINUE;
						break;
				}
				break;

			case MENU_KEY1:		// Redefinition
				switch (focus) {
					case 7:
						current_menu = MENU_OPTS;
						nb_focus = 4;
						focus = 1;
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
						focus = 2;
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
						return RET_CONTINUE;
						break;
				}
				break;
		}
	}
	//////////////////////////////////////////////////
	//	Touche gauche
	//////////////////////////////////////////////////
	else if (in.scanKey(DIK_LEFT) || in.scanAlias(ALIAS_P1_LEFT)) {
		in.waitClean();

		switch (current_menu) {
			case MENU_OPTS:
				switch (focus) {
					case 0:
						vSyncOn = !vSyncOn;
						updateName();
						return RET_CONTINUE;
						break;
				}
				break;
		}
	}

	return RET_CONTINUE;
}

void MenuMain::stop()
{

	if (sound_on != start_sound_on) {
		if (sound_on) {
			sbk_bb.loadSFX("data\\bb.sfx");
		} else {
			sbk_bb.close();
		}
	}

	if (music_on != start_music_on) {
		if (music_on) {
			if (strlen(current_mbk) > 0) {
				if (!mbk_niveau.open(current_mbk))
					music_on = false;
				else {
					if (current_zik >= 0) {
						mbk_niveau.play(current_zik);
					}
				}
			}
		} else {
			mbk_niveau.stop();
			mbk_niveau.close();
		}
	}

	old_menu = -1;
}

void MenuMain::draw(SDL::Surface * surf)
{

	int		ys = nb_focus * 15;
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


	if(current_menu == MENU_MAIN || current_menu == MENU_EXIT || current_menu == MENU_START)
	{
	for (int i = 0; i < nb_focus; i++) {
		if (focus == i)
			fnt_menus.printC(surf, 320, y, menu_txt[i]);
		else
			fnt_menu.printC(surf, 320, y, menu_txt[i]);

		y += 50;
	}
	fnt_rpg.printC(surf, 500, 450, "Ported by Martin JULES");
	fnt_rpg.printC(surf, 30, 450, "2002");

	}
	else
	for (int i = 0; i < nb_focus; i++) {
		if (focus == i)
			fnt_menus.printC(surf, 320, y, menu_txt[i]);
		else
			fnt_menu.printC(surf, 320, y, menu_txt[i]);

		y += 30;
	}
}


void MenuMain::updateRedefine()
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

void MenuMain::updateName()
{
	char	buffer[200];

	switch (current_menu) {
		case MENU_MAIN:
			strcpy(menu_txt[0], txt_data[TXT_START_GAME]);
			strcpy(menu_txt[1], "OPTIONS"); //txt_data[TXT_VIDEO]);
//		strcpy( menu_txt[2], "HIGH SCORES");//txt_data[TXT_SOUND]);
//		strcpy( menu_txt[3], "CREDITS");//txt_data[TXT_CTRL]);
			strcpy(menu_txt[2], txt_data[TXT_EXIT]);
			break;

		case MENU_START:
			strcpy(menu_txt[0], txt_data[TXT_START_GAME1]);
			strcpy(menu_txt[1], txt_data[TXT_START_GAME2]);
			strcpy(menu_txt[2], txt_data[TXT_RETURN]);
			break;

		case MENU_EXIT:
			strcpy(menu_txt[0], txt_data[TXT_EXIT]);
			strcpy(menu_txt[1], txt_data[TXT_CANCEL]);
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

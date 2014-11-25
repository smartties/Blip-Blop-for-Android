/******************************************************************
*
*
*		-----------------
*		   RPGPlayer.h
*		-----------------
*
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#include <fstream>
#include <cstdio>
#include <cstring>
#include "lgx_packer.h"
#include "rpg_player.h"
#include "globals.h"
#include "txt_data.h"
#include "couille.h"
#include "scroll.h"


#define	BUFFER_LENGTH	200

RPGPlayer::RPGPlayer() : fic_name(NULL), focus(0), wait_goal(0), key_released(false), skiped(false)
{
	pic_tab[0] = NULL;
	pic_tab[1] = NULL;

	nimage[0] = 0;
	nimage[1] = 0;

	ntxt[0] = 0;
	ntxt[1] = 0;

	buffer1 = new char[BUFFER_LENGTH];
	buffer2 = new char[BUFFER_LENGTH];
}


RPGPlayer::~RPGPlayer()
{
	if (buffer1 != NULL)
		delete [] buffer1;

	if (buffer2 != NULL)
		delete [] buffer2;

	if (fic_name != NULL)
		delete [] fic_name;
}


void RPGPlayer::attachFile(const char * f)
{
	if (fic_name != NULL)
		delete [] fic_name;

	fic_name = new char[strlen(f) + 1];

	strcpy(fic_name, f);
}


bool RPGPlayer::startPlay(int n)
{
    ///MODIF open
	//fic.open(fic_name);

	///MODIF is_open
	//if (fic.is_open() == 0) {
	if (AAsset_istringstream(fic_name, fic) == false) {

		return false;
	}

	sprintf(buffer1, "rpg=%d", n);

	fic.getline(buffer2, BUFFER_LENGTH);removeline(buffer2);


	while (!fic.eof() && strcmp(buffer1, buffer2) != 0)
	{
	    fic.getline(buffer2, BUFFER_LENGTH);removeline(buffer2);

	}


	if (fic.eof()) {

		return false;
	}

	nimage[0]		= -1;
	nimage[1]		= -1;
	ntxt[0]			= -1;
	ntxt[1]			= -1;

	nbjoueurs		= list_joueurs.taille();
	key_released	= false;
	skiped			= false;
	focus			= 0;
	cur_joueur		= 0;
	wait_goal		= 0;

	Couille *	c;
	int			i = 0;

	list_joueurs.start();

	while (!list_joueurs.fin()) {
		c = (Couille *) list_joueurs.info();

		if (c->id_couille == ID_BLIP)
			base_joueur[i] = 0;
		else
			base_joueur[i] = 6;

		list_joueurs.suivant();
		i += 1;
	}


	return true;
}


void RPGPlayer::stopPlay()
{
    ///MODIF close
	//fic.close();
	fic.str("");
	fic.clear();
}

bool RPGPlayer::drawScene(SDL::Surface * surf)
{
	bool	not_finished = true;

	LOGI("drawScene rpg");///UPDATE drawScene rpg /// a revoir plusieurs return

	///MODIF touch
	//if (in.anyKeyPressed()) {
	if(in.so_up()) {
		/*if (in.scanKey(DIK_ESCAPE)) {
			in.waitClean();

			while (updateScene());

			return false;
		}*/

		if (key_released && ((timeGetTime() - initial_time) >= 750)) {
			wait_goal = 0;
			key_released = false;
		}
	} else {
		key_released = true;
	}


	if (timeGetTime() > wait_goal)
		not_finished = updateScene();

	// Assombrissement
	//
	RECT	r;

	if (nimage[0] >= 0) {
		r.left	= 100;
		r.top	= 120;
		r.right = 640;
		r.bottom = 220;

		LGXpaker.halfTone(surf, &r);
	}

	if (nimage[1] >= 0) {
		r.left	= 0;
		r.top	= 300;
		r.right	= 540;
		r.bottom = 400;

		LGXpaker.halfTone(surf, &r);
	}

	// Affiche les têtes de con
	//
	if (pic_tab[0] != NULL &&  nimage[0] >= 0 && nimage[0] < (*pic_tab[0]).getSize())
		(*pic_tab[0])[nimage[0]]->PasteTo(surf, 0, 120);


	if (vbuffer_wide > 640) {
		if (pic_tab[1] != NULL &&  nimage[1] >= 0 && nimage[1] < (*pic_tab[1]).getSize())
			(*pic_tab[1])[nimage[1]]->PasteTo(surf, 540, 300);
	} else {
		if (pic_tab[1] != NULL &&  nimage[1] >= 0 && nimage[1] < (*pic_tab[1]).getSize())
			(*pic_tab[1])[nimage[1]]->PasteTo(surf, 538, 300);
	}

	// Ecrit le texte
	//
	if (ntxt[0] != -1 && txt_data[ntxt[0]] != NULL)
		fnt_rpg.printMW(surf, 120, 135, txt_data[ntxt[0]], 640);

	if (ntxt[1] != -1 && txt_data[ntxt[1]] != NULL)
		fnt_rpg.printMW(surf, 20, 315, txt_data[ntxt[1]], 535);

	return not_finished;
}

bool RPGPlayer::updateScene()
{
	bool	ready_to_draw = false;
	char *	pos;

	while (!ready_to_draw && read() && strcmp(buffer1, "stop") != 0) {

		// D'abord, on analyse les cas ou on n'a pas besoin de couper
		//
		if (strcmp(buffer1, "endif") == 0) {
//			debug<<"endif\n";
		} else if (strcmp(buffer1, "bbswap") == 0) {
			cur_joueur += 1;
			cur_joueur %= nbjoueurs;
		} else {
			// Coupe le schnuff en 2 buffer1:txt1 et buffer2:txt2
			// tel que dans le fichier il y a "txt1=txt2"
			//
			pos = strchr(buffer1, '=');
			strcpy(buffer2, pos + 1);
			pos[0] = '\0';

			if (strcmp(buffer1, "ifnbj") == 0) {
				if (nbjoueurs != atoi(buffer2)) {
					// Si la condition est fausse on skipe le tout
					while (read() && strcmp(buffer1, "endif") != 0);
				}
			} else if (strcmp(buffer1, "focus") == 0) {
				// Gère le focus

				if (strcmp(buffer2, "haut") == 0)
					focus = 0;
				else if (strcmp(buffer2, "bas") == 0)
					focus = 1;
				else
					error(buffer2);
			} else if (strcmp(buffer1, "id") == 0) {
				// Gère l'identité de la PBK de la case

				if (strcmp(buffer2, "joueur") == 0) {
					pic_tab[focus] = &pbk_rpg_bb;
					id[focus] = ID_JOUEUR;
				} else if (strcmp(buffer2, "ennemi") == 0) {
					pic_tab[focus] = &pbk_rpg;
					id[focus] = ID_ENNEMI;
				} else
					error(buffer2);
			} else if (strcmp(buffer1, "img") == 0) {
				// Change l'image

				if (id[focus] == ID_JOUEUR)
					nimage[focus] = atoi(buffer2) + base_joueur[cur_joueur];
				else
					nimage[focus] = atoi(buffer2);
			} else if (strcmp(buffer1, "txt") == 0) {
				// Change le texte

				ntxt[focus] = atoi(buffer2);
			} else if (strcmp(buffer1, "affiche") == 0) {
				// Près pour l'affichage

				initial_time = timeGetTime();
				wait_goal = timeGetTime() + atoi(buffer2);
				ready_to_draw = true;
			} else if (strcmp(buffer1, "flag") == 0) {
				// Flag

				pos = strchr(buffer2, '.');
				int val = atoi(pos + 1);
				pos[0] = '\0';

				game_flag[atoi(buffer2)] = val;
//				debug<<"Flag "<<atoi(buffer2)<<"="<<val<<"\n";
			} else {
				error(buffer1);
			}
		}
	}

	return ready_to_draw;
}


bool RPGPlayer::read()
{
	fic.getline(buffer1, BUFFER_LENGTH);removeline(buffer1);

	// Skip les commentaires
	//
	while (!fic.eof() && buffer1[0] == ';')
	{
	    fic.getline(buffer1, BUFFER_LENGTH);removeline(buffer1);
	}

	if (fic.eof())
		return false;
	else
		return true;
}



void RPGPlayer::error(const char * err_msg)
{
	debug << "RPGPlayer::updateScene() -> Erreur de syntaxe :'" << err_msg << "'\n";
}










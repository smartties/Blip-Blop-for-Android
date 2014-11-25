
#ifndef _MenuGame_
#define _MenuGame_

#include "graphics.h"
#include "box.h"


class MenuGame
{
public:
	int		current_menu;		// Numéro du menu courant
	int		focus;				// Numéro du menu EN ROUGE
	int		nb_focus;			// Nombre de choix du menu actuel
	char ** menu_txt;
	int		redefine;			// Numéro du schnuff à redéfinir
	int		old_menu;

	RECT	rec;


	MenuGame();
	void start();
	int update();	// Retour 0=toujours menu  1=retour jeu  2=quitter
	void stop();
	void updateName();
	void updateRedefine();
	void draw(SDL::Surface * surf);
	~MenuGame();
};

#endif

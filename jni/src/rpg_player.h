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


#ifndef _RPGPlayer_
#define _RPGPlayer_

#include <fstream>
#include "graphics.h"
#include "picture_bank.h"
///MODIF include
#include "asset.h"

using namespace std;

#define	ID_JOUEUR	0
#define ID_ENNEMI	1

class RPGPlayer
{
public:
    ///MODIF ifstream
	//ifstream	fic;
	istringstream	fic;
	char *		fic_name;
	char *		buffer1;
	string buff1;
	char *		buffer2;
	string buff2;

	PictureBank *	pic_tab[2];
	int				nimage[2];
	int				ntxt[2];
	int				id[2];
	int				focus;

	unsigned int	wait_goal;
	unsigned int	initial_time;
	bool			key_released;
	bool			skiped;

	int				nbjoueurs;
	int				cur_joueur;	// Joueur pris en compte à cet instant (0 ou 1)
	int				base_joueur[2]; // Représente l'image de base du joueur selon qu'il soit Blip ou Blop

	RPGPlayer();
	~RPGPlayer();

	void attachFile(const char * f);
	bool startPlay(int n);
	bool drawScene(SDL::Surface * surf);
	bool updateScene();
	void stopPlay();
	bool read();
	void error(const char * err_msg);
};

#endif


#ifndef _CINEPlayer_
#define _CINEPlayer_

#include <fstream>
#include "music_bank.h"
#include "picture_bank.h"
#include "fonte.h"
#include "alpha_blend.h"
///MODIF include
#include "asset.h"

using namespace std;

#define OBJ_SPRITE	0
#define OBJ_SCROLL	1
#define OBJ_TEXTE	2


#define NB_OBJ		20
#define NB_ARG		20
#define STR_LENGTH	40
#define BUFFER_SIZE	200
#define CMD_SIZE	20


struct OBJECT {
	int			id;
	bool		show;

	Picture *	pic;
	int			x;
	int			y;

	int			dx;
	int			dy;
	int			time_mov;

	int			nb_anim;
	int			anim[20];
	int			speed_anim;
	int			wait_anim;
	bool		loop_anim;
	int			etape;

	bool		x_warp;
	int			x_warp1;
	int			x_warp2;

	bool		y_warp;
	int			y_warp1;
	int			y_warp2;

	int			txt;
};


class CINEPlayer
{
protected:
	int		tupdate;
	int		tdraw;
	int		dtime;
	int		glorf;

	/*SDL::Surface * first_surf;*/
	SDL::Surface * back_surf;
	/*
		SDL::Surface * surf1;
		SDL::Surface * surf2;
	*/
	RGBFORMAT		rgb;

	///MODIF ifstream
	//ifstream		fic;
	istringstream   fic;

	char			buffer[BUFFER_SIZE + 1];
	char			buffer2[BUFFER_SIZE + 1];

	PictureBank		pbk;
	MusicBank		mbk;

	OBJECT			obj[NB_OBJ];

	char	cmd_name[CMD_SIZE];
	int		nb_args;
	int		int_arg[NB_ARG];
	char	str_arg[NB_ARG][STR_LENGTH];

	int		num_ligne;
	bool	fini;
	int		frame_to_draw;
	int		time;

	int		clip_x1;
	int		clip_x2;
	int		clip_y1;
	int		clip_y2;

	int		alpha;
	int		delta_alpha;
	int		color[2];
	int		clip_color[2];

	int		delta_vol;
	int		back_vol;


	// Méthodes
	//
	bool getCommand();
	void initPlayer();
	void closePlayer();
	bool error();
	bool error(const char * er);

	// Execute toutes les commandes jusqu'à un affichage
	//
	void updateState();

	void drawScene();
	void drawSprite(int n);
	void drawText(int n);
	void renderLoop();
	void updateScene();

public:

	void loadPBK(const char * f);
	bool playScene(const char * file, SDL::Surface * s1, SDL::Surface * s2);

};

#endif

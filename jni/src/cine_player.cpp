#include <cctype>
#include <cstring>
//#include <fcntl.h>
#include "cine_player.h"
#include "ben_divers.h"
#include "ben_debug.h"
#include "input.h"
#include "txt_data.h"
#include "l_timer.h"
//#include "alphablend.h"
#include "globals.h"
#include "config.h"
#include "precache.h"

#define ISCOM( _cmd) (strcmp( cmd_name, _cmd)==0)

//---------------------------------------------------------------------------

void CINEPlayer::initPlayer()
{
	for (int i = 0; i < NB_OBJ; i++) {
		obj[i].show = false;
		obj[i].time_mov = 0;
		obj[i].nb_anim = 0;
		obj[i].x_warp = false;
		obj[i].y_warp = false;
	}

	num_ligne = 0;
	frame_to_draw = 0;
	fini = false;
	clip_x1 = 0;
	clip_y1 = 0;
	clip_x2 = 640;
	clip_y2 = 480;
	alpha = 0;
	delta_alpha = 0;
	color[0] = color[1] = 0;
	clip_color[0] = clip_color[1] = 0;
	delta_vol = 0;
}


//---------------------------------------------------------------------------


bool CINEPlayer::playScene(const char * file, SDL::Surface * s1, SDL::Surface * s2)
{
	bool	skiped = false;
	/*
		debug<<"---------------------------------------------------------------\n";
		debug<<"Playing cine file "<<file<<"\n";
		debug<<"---------------------------------------------------------------\n";
	*/
	initPlayer();

	/*first_surf = s1;*/
	back_surf = s2;

	Precache(file);

	///MODIF open
	//fic.open(file);

	///MODIF is_open
	//if (fic.is_open() == 0) {
	if (AAsset_istringstream(file, fic) == false) {
		debug << "CINEPlayer -> Cannot open file " << file << "\n";
		return false;
	}


	manageMsg();

	bool pressing = false;
	while (!fini) {
		updateState();
		time = LGetTime();
		dtime = 0;

		while (frame_to_draw > 0 && !fini) {
			manageMsg();

			if (checkRestore())
				time = LGetTime();

			in.update();
			LOGI("playScene");///UPDATE cinematique

			renderLoop();

			///MODIF touch
			//if (in.scanKey(DIK_ESCAPE)) {
			if(in.so_pressing())
			pressing = true;
			if(in.so_up() && pressing) {
				fini = true;
				skiped = true;
			}
			in.refresh();
		}
	}

	closePlayer();
	in.reset();

	return !skiped;

}

//---------------------------------------------------------------------------


void CINEPlayer::updateScene()
{
	tupdate = LGetTime();

	// Gére le volume
	//
	int vol = delta_vol;

	if (vol < 0)
		vol = 0;

	if (vol > back_vol)
		vol = back_vol;

	// Gére l'alpha blending
	//
	alpha += delta_alpha;

	if (alpha > 255)
		alpha = 255;
	else if (alpha < 0)
		alpha = 0;

	// Gére les objets
	//
	for (int i = 0; i < NB_OBJ; i++) {
		if (obj[i].show) {
			if (obj[i].time_mov > 0) {
				obj[i].x += obj[i].dx;
				obj[i].y += obj[i].dy;
				obj[i].time_mov -= 1;
			}

			if (obj[i].nb_anim > 0) {
				obj[i].wait_anim += 1;
				obj[i].wait_anim %= obj[i].speed_anim;

				obj[i].pic = pbk[obj[i].anim[obj[i].etape]];

				if (obj[i].wait_anim == 0) {
					obj[i].etape += 1;

					if (obj[i].etape >= obj[i].nb_anim) {
						if (obj[i].loop_anim) {
							obj[i].etape = 0;
							obj[i].pic = pbk[obj[i].anim[0]];
						} else {
							obj[i].nb_anim = 0;
						}
					}
				}
			}

			if (obj[i].x_warp) {
				if (obj[i].x == obj[i].x_warp1)
					obj[i].x = obj[i].x_warp2;
			}

			if (obj[i].y_warp) {
				if (obj[i].y == obj[i].y_warp1)
					obj[i].y = obj[i].y_warp2;
			}
		}
	}

	tupdate = LGetTime() - tupdate;
	frame_to_draw -= 1;
}

//---------------------------------------------------------------------------


void CINEPlayer::renderLoop()
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

	if (glorf >= -MARGE && glorf <= MARGE) {
		updateScene();
		dtime = 0;
	} else {
		while (dtime >= GOOD) {
			updateScene();
			dtime -= GOOD;
		}
	}

	im += 1;
	im %= INT_SIZE;

	drawScene();

	DWORD ttotal = tupdate + tdraw;

	if (ttotal <= 0)
		ttotal = GOOD;
	else if (ttotal >= 5000)
		ttotal = GOOD;

	marge[im] = ttotal - GOOD;
}


//---------------------------------------------------------------------------


void CINEPlayer::updateState()
{
	bool	to_draw = false;
	int		n;
	int		n2;
	int		i;

	while (!fini && !to_draw && getCommand()) {
		if (ISCOM("endscene")) {
			pbk.close();
			fini = true;
		} else if (ISCOM("loadgfx")) {
			pbk.close();
			if (!pbk.loadGFX(str_arg[0], DDSURF_BEST))
				error("ne peut pas charger le fichier GFX");
		} else if (ISCOM("loadmbk")) {
			mbk.close();
			if (!mbk.open(str_arg[0]))
				error("ne peut pas charger la MBK");
		} else if (ISCOM("playmusic")) {
			mbk.play(int_arg[0]);
		} else if (ISCOM("stopmusic")) {
			mbk.stop();
		} else if (ISCOM("setpos")) {
			n = int_arg[0];

			if (n < 0 || n >= NB_OBJ)
				error("numéro d'objet invalide");
			else {
				obj[n].x = int_arg[1];
				obj[n].y = int_arg[2];
			}
		} else if (ISCOM("setpic")) {
			n = int_arg[0];

			if (n < 0 || n >= NB_OBJ)
				error("numéro d'objet invalide");
			else {
				n2 = int_arg[1];

				if (n2 < 0 || n2 >= pbk.getSize())
					error("numéro d'image invalide");
				else {
					obj[n].id = OBJ_SPRITE;
					obj[n].pic = pbk[n2];
					obj[n].show = true;
				}
			}
		} else if (ISCOM("setmove")) {
			n = int_arg[0];

			if (n < 0 || n >= NB_OBJ)
				error("numéro d'objet invalide");
			else {
				obj[n].dx = int_arg[1];
				obj[n].dy = int_arg[2];
				obj[n].time_mov = int_arg[3];
			}
		} else if (ISCOM("settext")) {
			n = int_arg[0];

			if (n < 0 || n >= NB_OBJ)
				error("numéro d'objet invalide");
			else {
				obj[n].id = OBJ_TEXTE;
				obj[n].txt = int_arg[1];
				obj[n].show = true;
			}
		} else if (ISCOM("reset")) {
			n = int_arg[0];

			if (n < 0 || n >= NB_OBJ)
				error("numéro d'objet invalide");
			else {
				obj[n].show = false;
				obj[n].dx = 0;
				obj[n].dy = 0;
				obj[n].nb_anim = 0;
				obj[n].x_warp = false;
				obj[n].y_warp = false;
			}
		} else if (ISCOM("resetall")) {
			for (i = 0; i < NB_OBJ; i++) {

				obj[i].show = false;
				obj[i].dx = 0;
				obj[i].dy = 0;
				obj[i].nb_anim = 0;
				obj[i].x_warp = false;
				obj[i].y_warp = false;
			}
		} else if (ISCOM("setclip")) {
			clip_x1 = int_arg[0];
			clip_y1 = int_arg[1];
			clip_x2 = int_arg[2];
			clip_y2 = int_arg[3];
		} else if (ISCOM("noclip")) {
			clip_x1 = 0;
			clip_y1 = 0;
			clip_x2 = 640;
			clip_y2 = 480;
		} else if (ISCOM("setanim")) {
			n = int_arg[0];

			if (n < 0 || n >= NB_OBJ)
				error("numéro d'objet invalide");
			else {
				obj[n].speed_anim = int_arg[1];
				if (int_arg[2])
					obj[n].loop_anim = true;
				else
					obj[n].loop_anim = false;

				obj[n].id = OBJ_SPRITE;
				obj[n].pic = pbk[int_arg[3]];
				obj[n].wait_anim = 0;
				obj[n].etape = 0;
				obj[n].nb_anim = nb_args - 3;

				for (i = 3; i < nb_args; i++) {
					obj[n].anim[i - 3] = int_arg[i];
				}

			}
		} else if (ISCOM("setxwarp")) {
			n = int_arg[0];

			if (n < 0 || n >= NB_OBJ)
				error("numéro d'objet invalide");
			else {
				obj[n].x_warp = true;
				obj[n].x_warp1 = int_arg[1];
				obj[n].x_warp2 = int_arg[2];
			}
		} else if (ISCOM("setywarp")) {
			n = int_arg[0];

			if (n < 0 || n >= NB_OBJ)
				error("numéro d'objet invalide");
			else {
				obj[n].y_warp = true;
				obj[n].y_warp1 = int_arg[1];
				obj[n].y_warp2 = int_arg[2];
			}
		} else if (ISCOM("stopanim")) {
			n = int_arg[0];

			if (n < 0 || n >= NB_OBJ)
				error("numéro d'objet invalide");
			else {
				obj[n].nb_anim = false;
			}
		} else if (ISCOM("setalpha")) {
			alpha = int_arg[0];
			delta_alpha = 0;
		} else if (ISCOM("setdeltaalpha")) {
			delta_alpha = int_arg[0];
		} else if (ISCOM("setbackcolor")) {
			if (int_arg[0] < 0 || int_arg[0] > 1)
				error("mauvais numéro de calque");
			else {
				if (int_arg[1] == 0) {
					color[int_arg[0]] = 0;
				} else {
					color[int_arg[0]] = 0xFFFF;
				}
			}
		} else if (ISCOM("setclipcolor")) {
			if (int_arg[0] < 0 || int_arg[0] > 1)
				error("mauvais numéro de calque");
			else {
				if (int_arg[1] == 0) {
					clip_color[int_arg[0]] = 0;
				} else {
					clip_color[int_arg[0]] = 0xFFFF;
				}
			}
		} else if (ISCOM("setvolume")) {
			delta_vol = 0;
		} else if (ISCOM("setdeltavolume")) {
			delta_vol = int_arg[0];
		} else if (ISCOM("renderscene")) {
			frame_to_draw = int_arg[0];
			to_draw = true;
		} else {
			error();

		}
	}
}

//---------------------------------------------------------------------------


void CINEPlayer::drawScene()
{
	RenderRect ddfx;
	tdraw = LGetTime();

	RECT		r;

	back_surf->FillRect(0, 0xFF000000);


	// Affiche tous les sprites/scrolls
	//
	for (int i = 0; i < NB_OBJ; i++) {
		if (obj[i].show) {
			switch (obj[i].id) {
				case OBJ_SPRITE:
					drawSprite(i);
					break;
			}
		}
	}

	// Clippe le tout
	//
	ddfx.dwFillColor = clip_color[0];

	r.left	= 0;
	r.right = clip_x1;
	r.top	= 0;
	r.bottom = 480;
	//graphicInstance->Clear(ddfx);
	back_surf->FillRect(&r,0);

	r.left	= clip_x2;
	r.right = 640;
	r.top	= 0;
	r.bottom = 480;
	//graphicInstance->Clear(ddfx);
	back_surf->FillRect(&r, 0);

	r.left	= 0;
	r.right = 640;
	r.top	= 0;
	r.bottom = clip_y1;
	//graphicInstance->Clear(ddfx);
	back_surf->FillRect(&r, 0);

	r.left	= 0;
	r.right = 640;
	r.top	= clip_y2;
	r.bottom = 480;
	//graphicInstance->Clear(ddfx);
	back_surf->FillRect(&r, 0);

	// Affiche tous les textes
	//
	for (int i = 0; i < NB_OBJ; i++) {
		if (obj[i].show && obj[i].id == OBJ_TEXTE)
			drawText(i);
	}


	/*
		// Alpha blending
		//

		if ( alpha > 0)
		{
			if ( alpha == 255) // 100% surface 2
			{
				back_surf->BltFast( 0, 0, back_surf, NULL, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
			}
			else // Mélange
			{
				r.top	= 0;
				r.left	= 0;
				r.bottom= 480;
				r.right = 640;

				TransAlphaImproved( back_surf, back_surf, 0, 0, r, alpha, rgb.bpp);

				back_surf->BltFast( 0, 0, back_surf, NULL, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
			}
		}
		else // 100% surface 1
		{
			back_surf->BltFast( 0, 0, back_surf, NULL, DDBLTFAST_WAIT | DDBLTFAST_NOCOLORKEY);
		}
	*/


//	first_surf->Flip(NULL, DDFLIP_WAIT);
	DDFlip();

	tdraw = LGetTime() - tdraw;
}


//---------------------------------------------------------------------------

void CINEPlayer::drawSprite(int n)
{
	if (n < NB_OBJ)
		obj[n].pic->BlitTo(back_surf, obj[n].x, obj[n].y);
}

//---------------------------------------------------------------------------

void CINEPlayer::drawText(int n)
{
	if (n < NB_OBJ)
		fnt_rpg.printC(back_surf, obj[n].x, obj[n].y, txt_data[obj[n].txt]);
}


//---------------------------------------------------------------------------


bool CINEPlayer::getCommand()
{
	static const char seps [] = ",)\n";

	int		i = 0;
	int		j = 0;
	char	c;
	char *	arg;
	char *	pos;


	// Retourne faux si EOF
	//
	if (fic.eof())
		return false;


	// Esquive les lignes commentées et les lignes vides
	//
	fic.getline(buffer, BUFFER_SIZE);
	num_ligne += 1;

	while (!fic.eof() && (buffer[0] == ';' || buffer[0] == '\0')) {
		fic.getline(buffer, BUFFER_SIZE);
		num_ligne += 1;
	}

	if (fic.eof() && strlen(buffer) == 0)
		return false;


	// Vire les espaces et met tout en minuscule -----------------
	// Vire aussi les "
	//
	do {
		c = buffer[i++];// Pour éviter 10.000 fois l'indirections

		// Si on arrive à la fin de ligne on s'arrête
		//
		if (c == ';') {
			buffer2[j] = '\0';
		} else if (c != ' ' && c != '\"') {	// Ignore les espaces
			buffer2[j++] = tolower(c);
		}

	} while (c != '\0' && c != ';');

	buffer2[j] = '\0';



	// Recherche le nom de la commande ---------------------------
	//
	pos = strchr(buffer2, '(');

	if (pos == NULL)
		return error();


	pos[0] = '\0';
	strcpy(cmd_name, buffer2);
	arg = pos + 1;


	if (cmd_name[0] == '\0')
		return error();



	// Recherche les arguments de la commande ---------------------
	//
	nb_args = 0;

	arg = strtok(arg, seps);

	while (arg != NULL) {
		strcpy(str_arg[nb_args], arg);
		int_arg[nb_args] = atoi(arg);

		arg = strtok(NULL, seps);
		nb_args += 1;
	}


	return true;
}

void CINEPlayer::loadPBK(const char * f)
{
	pbk.loadGFX(f);
}

//---------------------------------------------------------------------------

void CINEPlayer::closePlayer()
{
	mbk.close();
	pbk.close();
	///MODIF close
	//fic.close();
	fic.str("");
	fic.clear();
}

//---------------------------------------------------------------------------


bool CINEPlayer::error()
{
	debug << "CINEPlayer -> Syntax error line " << num_ligne << "\n";
	fini = true;
	return false;
}


//---------------------------------------------------------------------------

bool CINEPlayer::error(const char * er)
{
	debug << "CINEPlayer -> Error line  " << num_ligne << " : " << er << "\n";
	fini = true;
	return false;
}

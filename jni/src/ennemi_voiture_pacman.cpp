#include "ennemi_voiture_pacman.h"
#include "ennemi_pacman.h"


EnnemiVoiturePacman::EnnemiVoiturePacman(): invoc_pacman(false)
{
	pv = 1000;
	pic = pbk_ennemis[216];
	wait_end = 0;
}

void EnnemiVoiturePacman::update()
{
	if ((game_flag[2] == 1) || (game_flag[2] == 2)) {
		etape ++;
		if (etape > 160) {
			tombeVoiture();
			if (x < 1350) {
				x += 5;
			} else if (x < 1450) {
				x += 4;
			} else if (x < 1550) {
				x += 3;
			} else if (x < 1600) {
				x += 2;
			} else if (plat2(x, y + dy) == 1) {
				y = plat(x, y + dy);

				game_flag[2] = 3;

				etape = 0;
				ss_etape = 0;
			}
		}
	} else if (game_flag[2] == 3) {
		wait_end++;

		if (wait_end >= 250 && game_flag[0] < 6) {
			game_flag[0] = 6;
		}
		/*
			etape ++;
			if (etape >= 120)
			{
				etape = 0;
				ss_etape = 0;
				game_flag[2] = 4;
			}
		}
		else if (game_flag[2] == 4)
		{
			ss_etape ++;
			ss_etape %= 8;

			if (ss_etape == 0)
			{
				etape ++;
				if (etape > 4)
				{
					game_flag[2] = 5;
					etape --;
				}
			}
		}
		else if (game_flag[2] >=5)
		{
			if (!invoc_pacman)
			{
				Ennemi * pacman = new EnnemiPacman();

				pacman->x = x - 30;
				pacman->y = y - 40;
				pacman->dir = SENS_DROITE;
				list_ennemis.ajoute( (void*) pacman);

				invoc_pacman = true;
			}*/
	} else {
		x = 1400;
		y = -10;
	}
}

void EnnemiVoiturePacman::tombeVoiture()
{
	lat_grav += 1;
	lat_grav %= LATENCE_GRAVITE_VOITURE;

	if (lat_grav == 0 && dy < GRAVITE_MAX_VOITURE)
		dy += 1;

	if (dy < 0 && mur_opaque(x, y + dy))
		dy = GRAVITE_MAX;

	int ny = plat(x, y + dy);

	if (ny != 0 && dy > 0 && plat(x, y) == 0)
		y = ny;
	else
		y += dy;
}

int EnnemiVoiturePacman::degats()
{
	return 0;
};

void EnnemiVoiturePacman::affiche()
{
	if (game_flag[2] >= 4) {
		draw(x + 48, y - 82, pbk_ennemis[217 + etape]);
	}
	Sprite::affiche();
}

void EnnemiVoiturePacman::estTouche(Tir * tir)
{
}
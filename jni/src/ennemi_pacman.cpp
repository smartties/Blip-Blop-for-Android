#include "ennemi_pacman.h"


EnnemiPacman::EnnemiPacman(): ss_etape_tir(0), etape_tir(0), tir(false), dx(-2)
{
	pv = 1000;
	pic = pbk_ennemis[223];
	col_on = false;
	dy = -8;
}

void EnnemiPacman::update()
{
	if (game_flag[2] == 5) {
		x += dx;
		tombe();
		ss_etape ++;
		ss_etape %= 5;
		if (ss_etape == 0) {
			etape ++;
			etape %= 7;
		}

		pic = pbk_ennemis[223 + etape];

		if (tir) {
			ss_etape_tir ++;
			ss_etape_tir %= 4;
			if (ss_etape_tir == 0) {
				etape_tir ++;
				if (etape_tir >= 3) {
					tir = false;
					ss_etape_tir = 0;
					etape_tir = 0;
				}
			}
		} else {
			ss_etape_tir ++;
			if (ss_etape_tir >= 13) {
				tir = true;
				ss_etape_tir = 0;
				etape_tir = 0;
			}
		}

		if (plat2(x, y) == 3) {
			etape = 0;
			ss_etape = 0;
			game_flag[2] = 6;
		}
	} else if (game_flag[2] == 6) {
		pic = pbk_ennemis[230];
		etape ++;
		if (etape > 40) {
			game_flag[2] = 7;
			dy = 0;
		}
	} else if (game_flag[2] == 7) {
		pic = pbk_ennemis[223];
		tombe2();
		if (y + 2 * dy > y_plat[0][x]) {
			y = y_plat[0][x];
			game_flag[2] = 8;
			etape = 0;
			ss_etape = 0;
		}
	} else if (game_flag[2] == 8) {
		ss_etape ++;
		ss_etape %= 40;
		if (ss_etape == 0) {
			etape ++;
		}

		if (etape >= 2) {
			game_flag[2] = 9;
			etape = 0;
			ss_etape = 0;
		} else {
			pic = pbk_ennemis[230 + etape];
		}
	} else if (game_flag[2] == 9) {
		pic = pbk_ennemis[230];
	}
}

int EnnemiPacman::degats()
{
	return 0;
};

void EnnemiPacman::affiche()
{
	if (tir) {
		draw(x + 30, y - 20, pbk_ennemis[232 + etape_tir]);
	}

	Sprite::affiche();
}

void EnnemiPacman::estTouche(Tir * tir)
{
}
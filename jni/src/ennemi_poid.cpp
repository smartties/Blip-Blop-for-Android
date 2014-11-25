#include "ennemi_poid.h"
#include "gore_giclure.h"


EnnemiPoid::EnnemiPoid(): nb_colision(0)
{
	pv = 1000;
	pic = pbk_ennemis[169];
	//col_on = false;
}

void EnnemiPoid::update()
{
	if (etat == ETAT_MEURE) {
		onMeure();
	} else {
		pic = pbk_ennemis[169];
		if (game_flag[0] < 3) {
			y = -100;
			x = 565;
		}
		if ((game_flag[0] == 3) || (game_flag[0] == 4)) {
			//col_on = false;
			if (y < 100) {
				tombe2();
			} else {
				dy = 0;
			}
			if (x > 950) {
				etat = ETAT_MEURE;
			}
		}
		/*else if(game_flag[0] == 5)
		{
			//a_detruire = true;
			if (x > 1000)
			{
				pv = 0;
			}
		}*/

//		debug <<"nb_colision: "<<nb_colision <<"\n";
		if (nb_colision >= LATENCE_BOUGE) {
			x += 3;
			nb_colision -= LATENCE_BOUGE;
		}
		colFromPic();
	}
}

void EnnemiPoid::onMeure()
{
	if ((mur_opaque(x, y + dy))) {
		game_flag[0] = 7;
		ss_etape ++;
		ss_etape %= 15;
		if ((etape == 0) && (ss_etape == 1)) {
			tremblement(8);
		}
		if (ss_etape == 0) {
			etape ++;
			if (etape >= 3) {
				grave(x, y, pic);
				a_detruire = true;
			}
		}
		if (etape < 3) {
			pic = pbk_ennemis[202 + etape];
		}
	} else {
		tombe2();
		if (mur_opaque(x, y + dy * 10)) {
			pic = pbk_ennemis[201];
			int i;
			Sprite * s;
			for (i = 0; i < 8 ; i++) {
				s = new GoreGiclure(rand() % 15 - 7, -1 - rand() % 10);
				s->x = x + rand() % 80 - 40;
				s->y = y - rand() % 30 - 10;
				list_giclures.ajoute((void*) s);
			}
		} else if (mur_opaque(x, y + dy * 15)) {
			pic = pbk_ennemis[200];
			int i;
			Sprite * s;
			for (i = 0; i < 6 ; i++) {
				s = new GoreGiclure(rand() % 15 - 7, -1 - rand() % 10);
				s->x = x + rand() % 80 - 40;
				s->y = y - rand() % 30 - 10;
				list_giclures.ajoute((void*) s);
			}
		} else if (mur_opaque(x, y + dy * 20)) {
			pic = pbk_ennemis[200];
			int i;
			Sprite * s;
			for (i = 0; i < 5 ; i++) {
				s = new GoreGiclure(rand() % 15 - 7, -1 - rand() % 10);
				s->x = x + rand() % 80 - 40;
				s->y = y - rand() % 30 - 10;
				list_giclures.ajoute((void*) s);
			}
		} else if (mur_opaque(x, y + dy * 25)) {
			game_flag[0] = 6;
			pic = pbk_ennemis[199];
			int i;
			Sprite * s;
			for (i = 0; i < 4 ; i++) {
				s = new GoreGiclure(rand() % 15 - 7, -1 - rand() % 10);
				s->x = x + rand() % 80 - 40;
				s->y = y - rand() % 30 - 10;
				list_giclures.ajoute((void*) s);
			}
		} else if (mur_opaque(x, y + dy * 30)) {
			pic = pbk_ennemis[199];
			int i;
			Sprite * s;
			for (i = 0; i < 3 ; i++) {
				s = new GoreGiclure(rand() % 15 - 7, -1 - rand() % 10);
				s->x = x + rand() % 80 - 40;
				s->y = y - rand() % 30 - 10;
				list_giclures.ajoute((void*) s);
			}
		} else {
			pic = pbk_ennemis[170];
		}
	}
}

int EnnemiPoid::degats()
{
	return 0;
};

void EnnemiPoid::estTouche(Tir * tir)
{
	if ((tir->dir >= 2) && (tir->dir <= 6)) {
		//debug <<"tir direction: "<<tir->dir <<"\n";
		nb_colision ++;
	}

//	tir->a_detruire = true;
	tir->aTouche(0);

	//Ennemi::estTouche( tir);
}

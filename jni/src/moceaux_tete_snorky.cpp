/******************************************************************
*
*
*		---------------------------
*		    MorceauxTeteSnorky.cpp
*		---------------------------
*
*		Les bouts de tete qui giclent...
*
*
*		Mephisto / LOADED -   V 0.1 - 12 Decembre 2000
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "morceaux_tete_snorky.h"
#include "enemy.h"


//-----------------------------------------------------------------------------
//		Implementation de la classe MorceauSnorkyBaseTeteEntiere
//-----------------------------------------------------------------------------



MorceauSnorkyBaseTeteEntiere::MorceauSnorkyBaseTeteEntiere()
{
	dy = 0;
}

void MorceauSnorkyBaseTeteEntiere::update()
{
	ss_etape++;
	ss_etape %= 5;
	if (ss_etape == 0) {
		etape++;
	}

	if (etape == 2 && ss_etape == 0) {
		Sprite * s;
		if (dir == SENS_DROITE) {
			s = new MorceauSnorkyBaseTrompe(1 + rand() % 2, -1 + rand() % 2);
			s->x = x + 19;
		} else {
			s = new MorceauSnorkyBaseTrompe(- 1 - rand() % 2, -1 - rand() % 2);
			s->x = x - 19;
		}


		s->dir = dir;
		s->y = y - 26;


		list_giclures.ajoute((void*) s);
	}

	if (etape == 3 && ss_etape == 0) {
		Sprite * s;
		if (dir == SENS_DROITE) {
			s = new MorceauSnorkyBaseTetePartieArriere(1, 0);
			s->x = x + 0;
		} else {
			s = new MorceauSnorkyBaseTetePartieArriere(-1 , 0);
			s->x = x - 0;
		}


		s->dir = dir;
		s->y = y + 10;


		list_giclures.ajoute((void*) s);
	}

	if (etape == 6) {
		grave(x, y, pic);
		a_detruire = true;
	} else {
		tombe();
		if (dir == SENS_DROITE) {
			x += 1;
			pic = pbk_ennemis[52 + etape];
			if (etape >= 3) {
				tombe();
				x += 1;
			}
			if ((plat(x, y) != 0) && (x > 0)) {
				x -= 6 - etape;
			}
		} else {
			x -= 1;
			pic = pbk_ennemis[85 + etape];
			if (etape >= 3) {
				tombe();
				x -= 1;
			}
			if ((plat(x, y) != 0) && (x < 0)) {
				x += 6 - etape;
			}
		}
	}

	/*if (etape>=3)
	{
		tombe();

	}*/
}



//-----------------------------------------------------------------------------
//		Implementation de la classe MorceauSnorkyHyporidercorp
//-----------------------------------------------------------------------------



MorceauSnorkyHyporidercorp::MorceauSnorkyHyporidercorp(int vx)
{
	dx = vx;
	dy = -1;
}

void MorceauSnorkyHyporidercorp::update()
{
	tombe();
	x += dx;
	ss_etape++;
	ss_etape %= 6;
	if ((ss_etape == 0) && (etape < 3)) {
		etape++;
	}

	if (etape < 3) {
		if (dir == SENS_DROITE) {
			pic =  pbk_ennemis[307 + etape];
		} else {
			pic =  pbk_ennemis[320 + etape];
		}
	} else if (plat(x, y) != 0) {
		if (ss_etape == 0) {
			etape++;
		}
		if (etape < 5) {
			if (dir == SENS_DROITE) {
				pic =  pbk_ennemis[307 + etape];
			} else {
				pic =  pbk_ennemis[320 + etape];
			}
		} else {
			grave(x, y, pic);
			a_detruire = true;
//			sbk_niveau.play( 9);
		}
	}
}



//-----------------------------------------------------------------------------
//		implementation de la classe MorceauSnorkyBaseTetePartieArriere
//-----------------------------------------------------------------------------


MorceauSnorkyBaseTetePartieArriere::MorceauSnorkyBaseTetePartieArriere(int vx, int vy)
{
	dx = vx;
	dy = vy;
}

void MorceauSnorkyBaseTetePartieArriere::update()
{
	tombe();
	x += dx;
	ss_etape++;
	ss_etape %= 6;
	if ((ss_etape == 0) && (etape < 3)) {
		etape++;
	}

	if (dir == SENS_DROITE) {
		pic =  pbk_ennemis[59 + etape];
	} else {
		pic =  pbk_ennemis[92 + etape];
	}

	if (etape  == 3 && (plat(x, y) != 0)) {
		grave(x, y, pic);
		a_detruire = true;
	}
}



//-----------------------------------------------------------------------------
//		Implementation de la classe MorceauSnorkyBaseTetePartieArriere
//-----------------------------------------------------------------------------

MorceauSnorkyBaseTrompe::MorceauSnorkyBaseTrompe(int vx, int vy)
{
	dx = vx;
	dy = vy;
}

void MorceauSnorkyBaseTrompe::update()
{
	tombe();
	x += dx;
	ss_etape++;
	ss_etape %= 3;
	if (ss_etape == 0) {
		etape++;
		etape %= 8;
	}

	pic =  pbk_ennemis[63 + etape];

	if (plat(x, y) != 0) {
		grave(x, y, pic);
		a_detruire = true;
	}

}



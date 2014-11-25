/******************************************************************
*
*
*		--------------------
*		EnnemiSmurfSauvage.cpp
*		--------------------
*
*		Le schtroumph brujah
*
*
*		Mortimus / LOADED -   V 0.1 - 23 Octobre 2000
*
*
*
******************************************************************/

const int tir_position_depart_x[] = { -15, -8, 6, 1, 8, 17 } ;
const int tir_position_depart_y[] = { 55, 62, 65, 65, 62, 55 } ;

const int tir_dx[] = { -4, -1, 0, 0, 1, 4 } ;
const int tir_dy[] = { 4, 5, 6, 6, 5, 4 } ;

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "ennemi_smurf_sauvage.h"
#include "tir_smurf_sauvage.h"


int	EnnemiSmurfSauvage::wait_shoot;
int	EnnemiSmurfSauvage::etape_wait;

EnnemiSmurfSauvage::EnnemiSmurfSauvage() : etape_shoot(0), position(false)
{
	first_loop = true;
	pv = 150 ;
	etape = 1 ;
	nb_shoot = 0 ;
	mort = false ;
	cible = tete_turc;
	ss_etape_angle = angle = 0;
	sensAngle = true;

	wait_shoot = 100 + rand() % 100;
	etape_wait = 0;
	etat = ETAT_ATTENDS;

	switch (dir) {
		case SENS_DROITE :
			num_pic = 139 ;
			pic = pbk_ennemis[140] ;
			shoot_direction = BAS_DROITE ;
			break ;
		case SENS_GAUCHE :
			num_pic = 141 ;
			pic = pbk_ennemis[142] ;
			shoot_direction = BAS_GAUCHE ;
			break ;
	}
}

void EnnemiSmurfSauvage::update()
{
	if (x > 5850)
		x = 5850;

	shooting = false;

	if (first_loop) {
		y = -100;
		first_loop = false;
	}

	if (cible == NULL || cible->aDetruire()) {
		cible = tete_turc;
	}

	if (etat != ETAT_MEURE) {
		if (cible != NULL && x != cible->x)
			pente = (abs(cible->y - y) * 10) / (x - cible->x) ;
		else
			pente = 3 ;
	}

	if (pente > 0) {
		dir = SENS_GAUCHE ;
		num_pic = 141 ;

		if (pente <= 15)
			shoot_direction = DIAGONALE_GAUCHE ;
		else if (pente <= 25)
			shoot_direction = DIAGONALE_BAS_GAUCHE ;
		else
			shoot_direction = BAS_GAUCHE ;
	} else if (pente < 0) {
		dir = SENS_DROITE ;
		num_pic = 139 ;

		if (pente >= - 15)
			shoot_direction = DIAGONALE_DROITE ;
		else if (pente >= -25)
			shoot_direction = DIAGONALE_BAS_DROITE ;
		else
			shoot_direction = BAS_DROITE ;
	}


	if (etat != ETAT_MEURE)
		pic = pbk_ennemis[num_pic + etape ] ;

	if (blood != 0)
		blood -= 1;

	if (!mort && pv < 0) {
		mort = true ;
		etape = 0 ;
		etat = 0 ;
	}

	switch (etat) {
		case ETAT_ATTENDS:
			if (++etape_wait >= wait_shoot) {
				etat = ETAT_TOMBE;

//				if ( rand() % 10 == 0)
				sbk_niveau.play(17);

				if (rand() % 2 == 0)
					x = offset + 320 - rand() % 150;
				else
					x = offset + 320 + rand() % 150;

				int j = 100 + rand() % 140;

				while (mur_opaque(x, j))
					j = 100 + rand() % 140;

				nb_shoot = 0;
				hauteur = j;
			}
			break ;
		case ETAT_TOMBE :
			onTombe();
			break ;

		case ETAT_TIRE:
			onTire();
			break;

		case ETAT_MONTE:
			etape_wait = 0;

			if (y <= -100) {
				wait_shoot = 100 + rand() % 100;
				etat = ETAT_ATTENDS;
				a_detruire = true;
				cible = NULL;
			} else {
				y -= 2;
			}
			colFromPic();

			break;

		case ETAT_MEURE :
			onMeure() ;
			break ;
		case ETAT_CARBONISE :
			onCarbonise() ;
			break ;
	}
	updateADetruire() ;
}

void EnnemiSmurfSauvage::onTombe()
{
	if (y < hauteur) {
		y += 3;
	} else {
		etat = ETAT_TIRE;
	}

	etape_wait = 0;
	/*
		if ( y > hauteur - 50)
			onTire();
	*/
	colFromPic() ;
}

void EnnemiSmurfSauvage::onTire()
{
	shooting = true;

	ss_etape += 1 ;
	ss_etape %= 4 ;

	if (ss_etape == 0)
		etape += 1 ;

	if (etape > 2)
		etape = 1 ;

	etape_shoot += 1 ;
	etape_shoot %= 10;

	if (etape_shoot == 0) {
//		if(nb_shoot < 5)
//		{
		TirSmurfSauvage * tir = new TirSmurfSauvage() ;
		tir->x = x + tir_position_depart_x[shoot_direction] ;
		tir->y = y + tir_position_depart_y[shoot_direction] ;
		tir->dx = tir_dx[shoot_direction] ;
		tir->dy = tir_dy[shoot_direction] ;
		list_tirs_ennemis.ajoute((void*) tir);

		if (nb_shoot == 0)
			sbk_niveau.play(18);
//		}
		nb_shoot += 1 ;
	}

	if (nb_shoot >= 5)
		etat = ETAT_MONTE;

	colFromPic() ;
}

void EnnemiSmurfSauvage::estTouche(Tir * tir)
{
	static const int dx_giclure_smurf_sauvage [] = { 0, 0, 6, 0, 0, 0, -6, 0 };
	static const int dy_giclure_smurf_sauvage [] = { -15, -15, -15, -15, -15, -15, -15, -15 };


	Ennemi::estTouche(tir);
//	gicle( tir, dx_giclure_smurf_sauvage, dy_giclure_smurf_sauvage);
	/*
		if ( etat == ETAT_MEURE)
			sbk_bb.play( 10+rand()%5);
	*/
	if (etat == ETAT_MEURE)
		sbk_niveau.play(4 + rand() % 10);
}

void EnnemiSmurfSauvage::onMeure()
{
	if (etape >= 5) {
		Sprite * s;
		list_fonds_statiques.start();
		bool ok = true;

		colFromPic();
		y1 = 0;

		while (!list_fonds_statiques.fin()) {
			s = (Sprite *) list_fonds_statiques.info();
			ok = ok && !collision(s);
			list_fonds_statiques.suivant();
		}

		col_on = false;

		if (ok) {
			grave(x, y - 50, pbk_ennemis[117]) ;
			grave(x, y - 100, pbk_ennemis[117]) ;
			grave(x, y - 150, pbk_ennemis[117]) ;
			grave(x, y - 200, pbk_ennemis[117]) ;
			grave(x, y - 250, pbk_ennemis[117]) ;
			grave(x, y, pic);
			a_detruire = true;
		}
	} else {
		ss_etape += 1 ;
		ss_etape %= 4;

		if (ss_etape == 0) {
			etape += 1 ;
			if (dir == SENS_DROITE)
				pic = pbk_ennemis[117 + etape] ;
			else
				pic = pbk_ennemis[122 + etape] ;
		}
	}
}

void EnnemiSmurfSauvage::onCarbonise()
{
	y = hauteur + 50 - etape ;
	ss_etape += 1;
	ss_etape %= 6;

	if (ss_etape == 0)
		etape += 1;

	if (etape == 6) {
		a_detruire = true;
	} else {
		if (dir == SENS_GAUCHE)
			pic = pbk_ennemis[34 + etape];
		else
			pic = pbk_ennemis[40 + etape];
	}
}
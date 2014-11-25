
#include "ennemi_luigi.h"
#include "tir_debouche_chiote.h"
#include "gore_giclure.h"
#include "ennemi_sonic.h"
#include "ennemi_voiture_pacman.h"
#include "event_hold_fire.h"


const int anim_luigi_marche_droite[] = { 0, 1, 2, 1};
const int anim_luigi_marche_gauche[] = { 3, 4, 5, 4};
const int anim_luigi_attaque_droite[] = { 10, 11, 12, 11};
const int anim_luigi_attaque_gauche[] = { 13, 14, 15, 14};
const int anim_luigi_marche_mort_droite[] = {205, 206, 207, 206};
const int anim_luigi_marche_mort_gauche[] = {213, 214, 215, 214};
const int anim_luigi_mort[] = {208, 209, 210, 211, 212, 211, 210, 209};

EnnemiLuigi::EnnemiLuigi(): speed(1), etape_speed(0), attack_delay(50 + rand() % 250), wait_for_attack(0), encaissement(0)
{
	pv = 10000;
	//pv = 1;
	xmin = offset + 20;
}

void EnnemiLuigi::update()
{
	if (game_flag[0] == 7)
		a_detruire = true;

	//debug<<"u\n";

	if (blood > 0)
		blood -= 1;

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_CARBONISE:
		case ETAT_MEURE:
			onMeure();
			break;


		case ETAT_SAUTE:
		case ETAT_TOMBE:
			onSaute();
			break;

		case ETAT_TIRE:
			switch (attack_type) {
				case 0:
					//onCharge();
					break;
				case 1:
					onAttack();
					break;
			}
			break;
	}

	//updateADetruire();
}

void EnnemiLuigi::onAvance()
{
	//debug<<"a\n";
	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		onSaute();
	}

	//pour marcher

	if (x - speed < (xmin + 20) || mur_opaque(x - speed, y)) {
		dir = SENS_DROITE;
		speed = 1;
	} else if (x + speed > offset + 600 || mur_opaque(x + speed, y)) {
		dir = SENS_GAUCHE;
		speed = 1;
	}

	if (game_flag[0] >= 3) {
		wait_for_attack++;
	} else if (x < offset + 600) {
		game_flag[0] = 2;
	}

	if ((wait_for_attack >= attack_delay) && (tete_turc != NULL)) {

		/*if ((plat2(tete_turc->x,tete_turc->y)==plat2(x,y))&&
			(((dir == SENS_DROITE)&&(x<tete_turc->x))||
			((dir == SENS_GAUCHE)&&(x>tete_turc->x))))
		{
			etape=0;
			ss_etape=0;
			attack_type=0;
			attack_etape=0;
			speed=0;
			dy=0;
			etat = ETAT_TIRE;
			onCharge();
			return;
		}*/
		//else
		//{
		int dif_y = tete_turc->y - y;
		int dif_x = tete_turc->x - x;

		if (dif_y == 0) {
			dif_y = 1;
		}
		int coef_direct = dif_x / dif_y;
		//if (dif_x!=0)
		//	//debug<<"dif_x: "<<dif_x<<" dif_y: "<<dif_y<<" dif: "<<dif_y/dif_x<<"\n";
		if ((dir == SENS_DROITE) && (dif_y < 0) && (dif_x > 0) && (dif_y + dif_x < 0)) {
			wait_for_attack = 0;
			attack_delay = 10 + rand() % 50;
			speed = (int)((dif_x * -9) / dif_y);
			dy = (int)(-9 + speed * 0.25);
			etape = 0;
			ss_etape = 0;
			////debug<<"dy: "<<dy<<" speed: "<<speed<<" dif_x: "<<dif_x<<" dif_y: "<<dif_y<<"\n";
			etat = ETAT_SAUTE;
			lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur
			onSaute();
			return;

		} else if ((dir == SENS_GAUCHE) && (dif_y < 0) && (dif_x < 0) && (dif_y - dif_x < 0)) {
			wait_for_attack = 0;
			attack_delay = 10 + rand() % 50;
			speed = (int)((dif_x * 9) / dif_y);
			dy = (int)(-9 + speed * 0.25);
			etape = 0;
			ss_etape = 0;
			////debug<<"dy: "<<dy<<" speed: "<<speed<<" dif_x: "<<dif_x<<" dif_y: "<<dif_y<<"\n";
			etat = ETAT_SAUTE;
			lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur
			onSaute();
			return;
		} else if (pv >= 1000) {
			if ((dir == SENS_DROITE) && (dif_x > 0) && ((coef_direct <= -2) || (coef_direct >= 2))) {
				////debug<<"dif_x: "<<dif_x<<" dif_y: "<<dif_y<<" dif: "<<dif_x/dif_y<<"\n";
				wait_for_attack = 0;
				attack_delay = 50 + rand() % 250;
				attack_type = 1;
				ss_etape = 0;
				etape = 0;
				speed = 0;
				ss_etape_attack = 0;
				etape_attack = 0;
				etat = ETAT_TIRE;
				nb_tir = 0;
				sbk_niveau.play(9);
				onAttack();
				return;
			} else if ((dir == SENS_GAUCHE) && (dif_x < 0) && ((coef_direct <= -2) || (coef_direct >= 2))) {
				////debug<<"dif_x: "<<dif_x<<" dif_y: "<<dif_y<<" dif: "<<dif_x/dif_y<<"\n";
				wait_for_attack = 0;
				attack_delay = 50 + rand() % 250;
				attack_type = 1;
				ss_etape = 0;
				etape = 0;
				speed = 0;
				ss_etape_attack = 0;
				etape_attack = 0;
				etat = ETAT_TIRE;
				nb_tir = 0;
				sbk_niveau.play(9);
				onAttack();
				return;
			}
		}

		//else
		//{
		//	wait_for_attack--;
		//}
		//}
	}
	if (dir == SENS_DROITE) {
		if (speed > 6)
			speed = 6;
		else if (speed < -6)
			speed = -6;

		marche(speed);
		pic = pbk_ennemis[anime(anim_luigi_marche_droite, 4, 14 - (2 * speed))];

		if (encaissement < 0) {
			if (speed > - encaissement / MULTIPLACATEUR_VITESSE_AU_SOL) {
				speed += encaissement / MULTIPLACATEUR_VITESSE_AU_SOL;
			} else {
				speed = 0;
			}
		} else {
			if (speed + encaissement / MULTIPLACATEUR_VITESSE_AU_SOL < LUIGI_SPEED) {
				speed += encaissement / MULTIPLACATEUR_VITESSE_AU_SOL;
			} else {
				speed = LUIGI_SPEED;
			}
		}
	} else {
		if (speed > 6)
			speed = 6;
		else if (speed < -6)
			speed = -6;

		marche(-speed);
		pic = pbk_ennemis[anime(anim_luigi_marche_gauche, 4, 14 - (2 * speed))];

		if (encaissement > 0) {
			if (speed > encaissement / MULTIPLACATEUR_VITESSE_AU_SOL) {
				speed -= encaissement / MULTIPLACATEUR_VITESSE_AU_SOL;
			} else {
				speed = 0;
			}
		} else {
			if (speed - encaissement / MULTIPLACATEUR_VITESSE_AU_SOL < LUIGI_SPEED) {
				speed -= encaissement / MULTIPLACATEUR_VITESSE_AU_SOL;
			} else {
				speed = LUIGI_SPEED;
			}
		}
	}

	if (encaissement >= MULTIPLICATEUR_RECUL_SOL) {
		if (x + encaissement / MULTIPLICATEUR_RECUL_SOL < offset + 620) {
			x += encaissement / MULTIPLICATEUR_RECUL_SOL;
		}
		/*else
		{
			encaissement = 0;
		}*/
	} else if (encaissement <= -MULTIPLICATEUR_RECUL_SOL) {
		if (x + encaissement / MULTIPLICATEUR_RECUL_SOL > xmin) {
			x += encaissement / MULTIPLICATEUR_RECUL_SOL;
		}
		/*else
		{
			encaissement = 0;
		}*/
	}
	/*	if (dir == SENS_DROITE)
		{
			if (encaissement/100 <= speed)
			{
				marche(- encaissement/100);
			}
			else
			{
				if (x - encaissement/100 > xmin)
				{
					marche(- encaissement/100);
				}
				else
				{
					encaissement = 0;
				}
			}
		}
		else
		{
			if (encaissement/100 <= speed)
			{
				marche(encaissement/100);
			}
			else
			{
				if (x + encaissement/100 < offset + 640)
				{
					marche(encaissement/100);
				}
				else
				{
					encaissement = 0;
				}
			}
		}
	}*/

	/*if (encaissement > MARIO_ENDURANCE)
	{
		encaissement -= MARIO_ENDURANCE;
	}
	else if (encaissement < -MARIO_ENDURANCE)
	{
		encaissement += MARIO_ENDURANCE;
	}
	else
	{*/
	encaissement = 0;
	//}

	if (speed < LUIGI_SPEED) {
		etape_speed ++;
		if (etape_speed >= 20) {
			etape_speed = 0;
			speed ++;
		}
	}
	colFromPic();
}

void EnnemiLuigi::onMeure()
{
	if (game_flag[1] == 0) {
		tombe();
		if (x - 3 < xmin || mur_opaque(x - 3, y)) {
			dir = SENS_DROITE;
		} else if (x + 3 > offset + 640 || mur_opaque(x + 3, y)) {
			dir = SENS_GAUCHE;
		}
		if (dir == SENS_DROITE) {
			marche(3);
			pic = pbk_ennemis[anime(anim_luigi_marche_mort_droite, 4, 8)];
		} else {
			marche(-3);
			pic = pbk_ennemis[anime(anim_luigi_marche_mort_gauche, 4, 8)];
		}
		if ((plat2(x, y) == 0) && (x > 1500) && (x < 1550)) {
			dir = SENS_GAUCHE;
			game_flag[1] = 1;
			attack_delay = 0;
		}
	} else if (game_flag[1] == 1) {
		attack_delay ++;
		if (attack_delay >= EXPLOSE_DELAY) {
			game_flag[1] = 2;
			dir = SENS_DROITE;
		} else {
			pic = pbk_ennemis[anime(anim_luigi_mort, 8, 6)];
		}
	} else if (game_flag[1] == 2) {
		marche(3);
		pic = pbk_ennemis[anime(anim_luigi_marche_mort_droite, 4, 8)];
		if (x > offset + 680) {
			game_flag[1] = 3;
			attack_delay = 0;
		}
	} else if (game_flag[1] == 3) {
		attack_delay ++;
		if (attack_delay >= NOMBRE_GICLURES) {
			Ennemi * sonic = new EnnemiVoiturePacman();

			sonic->x = 1960;
			sonic->y = y;
			sonic->dir = SENS_GAUCHE;
			list_ennemis.ajoute((void*) sonic);

			nb_ennemis_created++;


			sonic = new EnnemiSonic();

			sonic->x = 1960;
			sonic->y = y;
			sonic->dir = SENS_GAUCHE;
			list_ennemis.ajoute((void*) sonic);
			a_detruire = true;

		} else {
			Sprite * s;
			int i;
			for (i = 0; i < 16 ; i++) {
				s = new GoreGiclure(-rand() % 10 - 2, -1 - rand() % 10);
				s->x = x + rand() % 20 - 10;
				s->y = y - rand() % 60 - 10;
				list_giclures.ajoute((void*) s);
			}
		}
	}
}

void EnnemiLuigi::onAttack()
{
	//debug<<"b\n";
	nb_tir++;
	if (nb_tir > 275) {
		etape = 0;
		ss_etape = 0;
		etat = ETAT_AVANCE;
		onAvance();
		return;
	}

	if (nb_tir < 50) {
		if (dir == SENS_DROITE)
			pic = pbk_ennemis[10];
		else
			pic = pbk_ennemis[13];

		colFromPic();
		return;
	}

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[anime(anim_luigi_attaque_droite, 4, 2)];
		ss_etape_attack += 1;
		ss_etape_attack %= 4;
		if (ss_etape_attack == 0) {
			etape_attack += 1;
			etape_attack %= 6;
			TirDebouchechiote *	tir1;
			TirDebouchechiote *	tir2;

			switch (etape_attack) {
				case 0:
					tir1 = new TirDebouchechiote(19, 12, 0);
					tir2 = new TirDebouchechiote(19, 12, 0);

					tir1->setDir(dir);
					tir1->x = x + 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x + 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);

					break;
				case 1:
					tir1 = new TirDebouchechiote(18, 11, 1);
					tir2 = new TirDebouchechiote(20, 11, -1);

					tir1->setDir(dir);
					tir1->x = x + 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x + 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);
					break;
				case 2:
					tir1 = new TirDebouchechiote(17, 10, 2);
					tir2 = new TirDebouchechiote(21, 10, -2);

					tir1->setDir(dir);
					tir1->x = x + 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x + 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);
					break;
				case 3:
					tir1 = new TirDebouchechiote(16, 9, 3);
					tir2 = new TirDebouchechiote(22, 9, -3);

					tir1->setDir(dir);
					tir1->x = x + 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x + 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);
					break;
				case 4:
					tir1 = new TirDebouchechiote(17, 10, 2);
					tir2 = new TirDebouchechiote(21, 10, -2);

					tir1->setDir(dir);
					tir1->x = x + 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x + 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);
					break;
				case 5:
					tir1 = new TirDebouchechiote(18, 11, 1);
					tir2 = new TirDebouchechiote(20, 11, -1);

					tir1->setDir(dir);
					tir1->x = x + 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x + 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);
					break;
			}

			//recul
			if (x > offset + 30) {
				x -= 1;
			}
		}
	} else {
		pic = pbk_ennemis[anime(anim_luigi_attaque_gauche, 4, 2)];
		ss_etape_attack += 1;
		ss_etape_attack %= 4;
		if (ss_etape_attack == 0) {
			etape_attack += 1;
			etape_attack %= 6;
			TirDebouchechiote *	tir1;
			TirDebouchechiote *	tir2;

			switch (etape_attack) {
				case 0:
					tir1 = new TirDebouchechiote(26, -12, 0);
					tir2 = new TirDebouchechiote(26, -12, 0);

					tir1->setDir(dir);
					tir1->x = x - 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x - 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);

					break;
				case 1:
					tir1 = new TirDebouchechiote(25, -11, 1);
					tir2 = new TirDebouchechiote(27, -11, -1);

					tir1->setDir(dir);
					tir1->x = x - 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x - 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);
					break;
				case 2:
					tir1 = new TirDebouchechiote(24, -10, 2);
					tir2 = new TirDebouchechiote(28, -10, -2);

					tir1->setDir(dir);
					tir1->x = x - 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x - 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);
					break;
				case 3:
					tir1 = new TirDebouchechiote(23, -9, 3);
					tir2 = new TirDebouchechiote(29, -9, -3);

					tir1->setDir(dir);
					tir1->x = x - 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x - 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);
					break;
				case 4:
					tir1 = new TirDebouchechiote(24, -10, 2);
					tir2 = new TirDebouchechiote(28, -10, -2);

					tir1->setDir(dir);
					tir1->x = x - 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x - 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);
					break;
				case 5:
					tir1 = new TirDebouchechiote(25, -11, 1);
					tir2 = new TirDebouchechiote(27, -11, -1);

					tir1->setDir(dir);
					tir1->x = x - 23;
					tir1->y = y - 13;

					tir2->setDir(dir);
					tir2->x = x - 23;
					tir2->y = y - 33;

					list_tirs_ennemis.ajoute((void*) tir1);
					list_tirs_ennemis.ajoute((void*) tir2);
					break;
			}

			//recul
			if (x < offset + 610) {
				x += 1;
			}
		}
	}
	colFromPic();
}

/*void EnnemiLuigi::onCharge()
{
	speed=LUIGI_CHARGE_SPEED;
	if ( x - speed < xmin || mur_opaque( x-speed, y))
	{
		etape=0;
		ss_etape=0;
		dir = SENS_DROITE;
		speed=1;
		etat=ETAT_AVANCE;
		wait_for_attack=0;
		attack_delay=50 + rand() % 250;
		onAvance();
		return;
	}
	else if ( x + speed > offset + 640 || mur_opaque( x+speed, y))
	{
		etape=0;
		ss_etape=0;
		dir = SENS_GAUCHE;
		speed=1;
		etat=ETAT_AVANCE;
		wait_for_attack=0;
		attack_delay=50 + rand() % 250;
		onAvance();
		return;
	}
	attack_etape+=1;
	if (attack_etape<40)
	{
		if ( dir == SENS_DROITE)
		{
			pic = pbk_ennemis[anime( anim_luigi_marche_droite, 4, 3)];
		}
		else
		{
			pic = pbk_ennemis[anime( anim_luigi_marche_gauche, 4, 3)];
		}
	}
	else
	{
		if ( dir == SENS_DROITE)
		{
			marche(speed);
			pic = pbk_ennemis[anime( anim_luigi_marche_droite, 4, 2)];
		}
		else
		{
			marche( -speed);
			pic = pbk_ennemis[anime( anim_luigi_marche_gauche, 4, 2)];
		}
	}


	colFromPic();
}*/

void EnnemiLuigi::onSaute()
{
	//debug<<"s\n";
	int		yp;

	if (dy < 0) {
		tombe_luigi();
	} else {
		tombe();
	}

	//pour pas que le luigi se tire en dehors de l'ecran...
	if (/*(dir==SENS_GAUCHE)&&*/(x - speed < xmin || mur_opaque(x - speed, y))) {
		dir = SENS_DROITE;
		speed = 1;
	}

	else if (/*(dir==SENS_DROITE)&&*/(x + speed > offset + 600 || mur_opaque(x + speed, y))) {
		dir = SENS_GAUCHE;
		speed = 1;
	}

	// Et si on arrêtait de tomber ?
	//
	if (dy > 0 && (yp = plat(x, y + dy)) != 0) {
		etat = ETAT_NORMAL;
		dy = 0;
		y = yp;
		onAvance();
		return;
	}


	if (dir == SENS_DROITE) {
		if (x + speed < offset + 620)
			x += speed;

		if (dy < 0) {
			pic = pbk_ennemis[6];
		} else {
			pic = pbk_ennemis[7];
		}

		if (encaissement != 0) {
			x += encaissement /  MULTIPLICATEUR_RECUL_AERIEN;
		}

		if (encaissement < 0) {
			if (speed + encaissement / MULTIPLICATEUR_VITESSE_AERIEN < 0) {
				//speed -= encaissement /MULTIPLICATEUR_VITESSE_AERIEN;
				if (speed + encaissement / MULTIPLICATEUR_VITESSE_AERIEN < -2 * LUIGI_SPEED) {
					speed = - 2 * LUIGI_SPEED;
				} else {
					speed += encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
				}
			} else {
				speed += encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
			}
			/*if (speed > - encaissement / MULTIPLICATEUR_VITESSE_AERIEN)
			{
				speed += encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
			}
			else
			{
				speed = 0;
			}*/

		} else {
			if (speed + encaissement / MULTIPLICATEUR_VITESSE_AERIEN < 2 * LUIGI_SPEED) {
				speed += encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
			} else {
				speed = 2 * LUIGI_SPEED;
			}
		}
	} else {
		if (x - speed > xmin)
			x -= speed;

		if (dy < 0) {
			pic = pbk_ennemis[8];
		} else {
			pic = pbk_ennemis[9];
		}

		if (encaissement != 0) {
			x += encaissement / MULTIPLICATEUR_RECUL_AERIEN;
		}

		if (encaissement > 0) {

			if (speed - encaissement / MULTIPLICATEUR_VITESSE_AERIEN < 0) {

				if (speed - encaissement / MULTIPLICATEUR_VITESSE_AERIEN < -2 * LUIGI_SPEED) {
					speed = - 2 * LUIGI_SPEED;
				} else {
					speed -= encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
				}
			} else {
				speed -= encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
			}

		} else {
			if (speed - encaissement / MULTIPLICATEUR_VITESSE_AERIEN < 2 * LUIGI_SPEED) {
				speed -= encaissement / MULTIPLICATEUR_VITESSE_AERIEN;
			} else {
				speed = 2 * LUIGI_SPEED;
			}
		}
	}

	encaissement = 0;

	colFromPic();

}

void EnnemiLuigi::onCarbonise()
{
	a_detruire = true;
	/*ss_etape += 1;
	ss_etape %= 5;

	if ( ss_etape == 0)
		etape += 1;

	if ( etape >= 14)
		a_detruire = true;
	else
	{
		if ( dir == SENS_DROITE)
			pic = pbk_ennemis[100+etape];
		else
			pic = pbk_ennemis[114+etape];
	}*/
}

void EnnemiLuigi::tombe_luigi()
{
	//debug<<"tl\n";

	lat_grav += 1;
	lat_grav %= LATENCE_LUIGI_GRAVITE;

	if (lat_grav == 0 && dy < GRAVITE_MAX)
		dy += 1;

	if (dy < 0 && mur_opaque(x, y + dy))
		dy = GRAVITE_MAX;

	int ny = plat(x, y + dy);

	if (ny != 0 && dy > 0)
		y = ny;
	else
		y += dy;
}

/*void EnnemiLuigi::estTouche( Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche( tir);
	gicle( tir, dx_giclure, dy_giclure);
}*/

void EnnemiLuigi::estTouche(Tir * tir)
{
	Sprite * s;

	for (int i = 0; i < 4 ; i++) {
		if ((tir->dir >= 2) && (tir->dir <= 6)) {
			s = new GoreGiclure(rand() % 6 , -2 - rand() % 6);
		} else if ((tir->dir >= 10) && (tir->dir <= 14)) {
			s = new GoreGiclure(-rand() % 5 - 1, -2 - rand() % 6);
		} else {
			s = new GoreGiclure(rand() % 11 - 5, -2 - rand() % 6);
		}
		s->x = x + rand() % 11 - 5;
		s->y = y - rand() % 30 - 10;

		list_giclures.ajoute((void*) s);
	}

	if ((tir->dir >= 2) && (tir->dir <= 6)) {
		encaissement += tir->degats();
	} else if ((tir->dir >= 10) && (tir->dir <= 14)) {
		encaissement -= tir->degats();
	}


	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);

	if (pv <= 0) {
		EventHoldFire e;

		e.x_activation = 0;
		e.flag = 0;
		e.val = 5;
		e.doEvent();
	}
}

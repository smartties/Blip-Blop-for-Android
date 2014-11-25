
#include "ennemi_mario.h"
#include "tir_mario_fireball.h"
#include "tir_mario_fireball_vertical.h"
#include "ennemi_mario_hologramme.h"


const int anim_mario_marche_droite[] = { 0, 1, 2, 1};
const int anim_mario_marche_gauche[] = { 3, 4, 5, 4};
const int recul_mario[] = { 4, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

EnnemiMario::EnnemiMario(): speed(1), etape_speed(0), attack_delay(50 + rand() % 50), wait_for_attack(0), fireball(0), hologramme(1), nb_pluie(0)
{
	pv = 50000;
	pic = pbk_ennemis[3];
}

void EnnemiMario::update()
{
	xmin = offset + 40;

	if (game_flag[0] == 0) {
		tombe();
		return;
	}

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
					onTirehorizontale();
					break;

				case 1:
					onTireverticale();
					break;

				case 2:
					onRafalehorizontale();
					break;

				case 3:
					onRafaleverticale();
					break;

				case 4:
					onRafaleverticaleinverser();
					break;

				case 5:
					onRafalehorizontaledouble();
					break;

				case 6:
					onRafaleverticaledouble();
					break;

				case 7:
					onTirecross();
					break;

				case 8:
					onRafalehorizontaleconstante();
					break;

				case 9:
					onRafaleverticaleconstante();
					break;

				case 10:
					onRafalecross();
					break;

				case 11:
					onPluiedefeu();
					break;

				case 12:
					onRafaleverticalechercheuse();
					break;

				case 13:
					onRafalehorizontalechercheuse();
					break;

				case 14:
					onRafalecrosschercheuse();
					break;

				case 15:
					onRafaleberserker();
					break;
			}
			break;
	}

	//updateADetruire();
}

void EnnemiMario::onAvance()
{
	// Si plus de plateformes on passe dans l'etat TOMBE
	//
	if (plat(x, y) == 0) {
		etat = ETAT_TOMBE;
		dy = 0;
		lat_grav = 0;
		onSaute();
	}

	//pour marcher

	if (x - speed < xmin || mur_opaque(x - speed, y)) {
		dir = SENS_DROITE;
		speed = 1;
	} else if (x + speed > offset + 600 || mur_opaque(x + speed, y)) {
		dir = SENS_GAUCHE;
		speed = 1;
	}
	/*
		if ((pv < 12500)&&(hologramme))
		{
			EnnemiMarioHologramme * holo = new EnnemiMarioHologramme();

			holo->x = x;
			holo->y = y;
			if (dir == SENS_DROITE)
			{
				holo->dir = SENS_GAUCHE;
			}
			else
			{
				holo->dir = SENS_DROITE;
			}
			list_ennemis.ajoute( (void*) holo);

			hologramme = 0;
		}
	*/
	wait_for_attack++;
	if ((wait_for_attack >= attack_delay) && (tete_turc != NULL)) {
		if (((dir == SENS_DROITE) && (tete_turc->x > x)) || ((dir == SENS_GAUCHE) && (tete_turc->x < x))) {
			etape = 0;
			ss_etape = 0;
			speed = 0;
			dy = -6;
			wait_for_attack = 0;
			etat = ETAT_TIRE;
			y_cible = tete_turc->y;
			x_cible = tete_turc->x;
			attack_etape = 0;
			attack_ss_etape = 0;
			attack_phase = 0;

			if (pv < MARIO_PV_SUR_CRITIQUE) {
				attack_type = rand() % 5 + 11;
				attack_delay = 30 + rand() % 30;
			} else if (pv < MARIO_PV_CRITIQUE) {
				attack_type = rand() % 6 + 5;
				attack_delay = 50 + rand() % 50;
			} else if (pv < MARIO_PV_SOUS_CRITIQUE) {
				attack_type = rand() % 5 + 2;
				attack_delay = 100 + rand() % 50;
			} else {
				attack_type = rand() % 5;
				attack_delay = 150 + rand() % 50;
			}
			//debug<<attack_type<<"\n";
			//onTire();
			switch (attack_type) {
				case 0:
					fireball = true;
					onTirehorizontale();
					break;

				case 1:
					fireball = true;
					onTireverticale();
					break;

				case 2:
					fireball = true;
					onRafalehorizontale();
					break;

				case 3:
					fireball = true;
					onRafaleverticale();
					break;

				case 4:
					if (dir == SENS_DROITE) {
						attack_etape = 1 + (offset + 640 - x) / 100;
					} else {
						attack_etape = 1 + (x - offset) / 100;
					}
					fireball = true;
					onRafaleverticaleinverser();
					break;

				case 5:
					fireball = true;
					onRafalehorizontaledouble();
					break;

				case 6:
					fireball = true;
					onRafaleverticaledouble();
					break;

				case 7:
					fireball = true;
					onTirecross();
					break;

				case 8:
					nb_pluie = 4 + rand() % 7;
					fireball = true;
					onRafalehorizontaleconstante();
					break;

				case 9:
					fireball = true;
					nb_pluie = 3 + rand() % 5;
					onRafaleverticaleconstante();
					break;

				case 10:
					fireball = true;
					nb_pluie = 4 + rand() % 5;
					onRafalecross();
					break;

				case 11:
					speed = 5;
					nb_pluie = 3 + rand() % 4;
					onPluiedefeu();
					break;

				case 12:
					fireball = true;
					nb_pluie = 3 + rand() % 3;
					onRafaleverticalechercheuse();
					break;

				case 13:
					fireball = true;
					nb_pluie = 3 + rand() % 3;
					onRafalehorizontalechercheuse();
					break;

				case 14:
					fireball = true;
					nb_pluie = 3 + rand() % 4;
					onRafalecrosschercheuse();
					break;

				case 15:
					speed = 5;
					fireball = false;
					onRafaleberserker();
					break;
			}
			return;
		}
		/*if ((plat2(tete_turc->x,tete_turc->y)==plat2(x,y))&&
			(((dir == SENS_DROITE)&&(x<tete_turc->x))||
			((dir == SENS_GAUCHE)&&(x>tete_turc->x))))
		{
			etape=0;
			ss_etape=0;
			attack_etape=0;
			speed=0;
			dy=0;
			etat = ETAT_TIRE;
			onCharge();
			return;
		}
		else
		{
			int dif_y=tete_turc->y-y;
			int dif_x=tete_turc->x-x;

			if ((dir==SENS_DROITE)&&(dif_y<0)&&(dif_x>0)&&(dif_y+dif_x<0))
			{
				etape=0;
				ss_etape=0;
				wait_for_attack=0;
				attack_delay = 50 + rand() % 250;
				speed=((dif_x*-9)/dif_y);
				dy=-9+speed*0.25;
				//debug<<"dy: "<<dy<<" speed: "<<speed<<" dif_x: "<<dif_x<<" dif_y: "<<dif_y<<"\n";
				etat = ETAT_SAUTE;
				lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur
				onSaute();
				return;

			}
			else if((dir==SENS_GAUCHE)&&(dif_y<0)&&(dif_x<0)&&(dif_y-dif_x<0))
			{
				etape=0;
				ss_etape=0;
				wait_for_attack=0;
				attack_delay = 50 + rand() % 250;
				speed=((dif_x*9)/dif_y);
				dy=-9+speed*0.25;
				//debug<<"dy: "<<dy<<" speed: "<<speed<<" dif_x: "<<dif_x<<" dif_y: "<<dif_y<<"\n";
				etat = ETAT_SAUTE;
				lat_grav = 0;	// Sinon les sauts diffèrent par leur hauteur
				onSaute();
				return;
			}
		}*/
	}
	if (dir == SENS_DROITE) {
		marche(speed);
		pic = pbk_ennemis[anime(anim_mario_marche_droite, 4, 16 - (3 * speed))];
	} else {
		marche(-speed);
		pic = pbk_ennemis[anime(anim_mario_marche_gauche, 4, 16 - (3 * speed))];
	}
	if (speed < MARIO_SPEED) {
		etape_speed++;
		if (etape_speed >= 20) {
			etape_speed = 0;
			speed++;
		}
	}
	colFromPic();
}

void EnnemiMario::onMeure()
{
	game_flag[0] = 7;
}

void EnnemiMario::onCharge()
{
	/*speed=MARIO_CHARGE_SPEED;
	if ( x - speed < xmin || mur_opaque( x-speed, y))
	{
		dir = SENS_DROITE;
		speed=1;
		etape=0;
		ss_etape=0;
		etat=ETAT_AVANCE;
		wait_for_attack=0;
		attack_delay=50 + rand() % 250;
		onAvance();
		return;
	}
	else if ( x + speed > offset + 640 || mur_opaque( x+speed, y))
	{
		dir = SENS_GAUCHE;
		speed=1;
		etape=0;
		ss_etape=0;
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
			pic = pbk_ennemis[anime( anim_mario_marche_droite, 4, 3)];
		}
		else
		{
			pic = pbk_ennemis[anime( anim_mario_marche_gauche, 4, 3)];
		}
	}
	else
	{
		if ( dir == SENS_DROITE)
		{
			marche(speed);
			pic = pbk_ennemis[anime( anim_mario_marche_droite, 4, 2)];
		}
		else
		{
			marche( -speed);
			pic = pbk_ennemis[anime( anim_mario_marche_gauche, 4, 2)];
		}
	}
	colFromPic();*/
}

void EnnemiMario::onSaute()
{
	int		yp;

	if (dy < 0) {
		tombe_mario();
	} else {
		tombe();
	}

	//pour pas que le mario se tire en dehors de l'ecran...
	if ((dir == SENS_GAUCHE) && (x - speed < xmin || mur_opaque(x - speed, y))) {
		dir = SENS_DROITE;
		speed = 1;
	}

	else if ((dir == SENS_DROITE) && (x + speed > offset + 640 || mur_opaque(x + speed, y))) {
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
		x += speed;
		if (dy < 0) {
			pic = pbk_ennemis[6];
		} else {
			pic = pbk_ennemis[7];
		}
	} else {
		x -= speed;
		if (dy < 0) {
			pic = pbk_ennemis[8];
		} else {
			pic = pbk_ennemis[9];
		}
	}

	colFromPic();

}

void EnnemiMario::onCarbonise()
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

void EnnemiMario::affiche()
{


	Sprite::affiche();
	if ((fireball) && (etape < 3)) {
		if (dir == SENS_DROITE) {
			draw(x + 29, y - 33, pbk_ennemis[48 + etape]);
		} else {
			draw(x - 29, y - 33, pbk_ennemis[51 + etape]);
		}

	}
}

void EnnemiMario::onTirehorizontale()
{
	if (dir == SENS_DROITE)
		pic = pbk_ennemis[10];

	else
		pic = pbk_ennemis[11];



	if ((y - 25 < y_cible) && (y < 444)) {
		if (y > y_cible - 60) {
			dy = 2;
		} else if (y > y_cible - 120) {
			dy = 3;
		} else if (y > y_cible - 180) {
			dy = 4;
		} else if (y > y_cible - 240) {
			dy = 5;
		} else {
			dy = 6;
		}
		if (y + dy > 444) {
			y = 444;
			dy = 0;
		} else {
			y += dy;
		}
	} else if ((y - 30 > y_cible) && (y <= 444)) {
		if (y < y_cible + 60) {
			dy = -2;
		} else if (y < y_cible + 120) {
			dy = -3;
		} else if (y < y_cible + 180) {
			dy = -4;
		} else if (y < y_cible + 240) {
			dy = -5;
		} else {
			dy = -6;
		}

		y += dy;
	} else {

		//y+=dy;
		ss_etape++;
		ss_etape %= 4;
		if (ss_etape == 0) {
			etape++;
			etape %= 3;
		}

		attack_etape++;
		if (attack_etape == 60) {
			etat = ETAT_AVANCE;
			etape = 0;
			ss_etape = 0;
			speed = 1;
			onAvance();
			return;
		} else if (attack_etape >= 40) {
			if (attack_etape == 40) {
				fireball = 0;
				boule_de_feu(4);
			}
			if ((dir == SENS_DROITE) && (x > offset + 10)) {
				x -= recul_mario[attack_etape - 40];
			} else if ((dir == SENS_GAUCHE) && (x < offset + 630)) {
				x += recul_mario[attack_etape - 40];
			}
		}
	}
	colFromPic();
}

void EnnemiMario::onTireverticale()
{
	if (dir == SENS_DROITE)
		pic = pbk_ennemis[10];

	else
		pic = pbk_ennemis[11];


	ss_etape++;
	ss_etape %= 4;
	if (ss_etape == 0) {
		etape++;
		etape %= 3;
	}

	attack_etape++;
	if (attack_etape == 40) {
		fireball = 0;
		TirMarioFireballVertical *	tir = new TirMarioFireballVertical(0, x_cible);

		tir->setDir(dir);
		if (dir == SENS_DROITE) {
			tir->x = x + 38;
		} else {
			tir->x = x - 38;
		}
		tir->y = y - 38;

		list_tirs_ennemis.ajoute((void*) tir);
	} else if (attack_etape == 60) {
		etat = ETAT_AVANCE;
		etape = 0;
		ss_etape = 0;
		speed = 1;
		onAvance();
		return;
	}
	colFromPic();
}

void EnnemiMario::onTirecross()
{
	switch (attack_phase) {
		case 0:
			onTirehorizontale();
			if (attack_etape > 0) {
				attack_phase = 1;
				attack_etape = 20;
				attack_ss_etape = 0;
				fireball = true;
			}
			break;

		case 1:
			onTireverticale();
			if (attack_etape > 40) {
				attack_phase = 2;
				attack_etape = 0;
				attack_ss_etape = 0;
				fireball = true;
				//y_cible = y;
			}
			break;

		case 2:
			onTirehorizontale();
			break;
	}
}


void EnnemiMario::onRafalehorizontale()
{
	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[10];
	} else {
		pic = pbk_ennemis[11];
	}

	ss_etape++;
	ss_etape %= 4;
	if (ss_etape == 0) {
		etape++;
		etape %= 3;
	}

	if ((y >= 140) && (y <= 145)) {
		boule_de_feu(1);
	} else if ((y >= 240) && (y <= 245)) {
		boule_de_feu(1);
	} else if ((y >= 340) && (y <= 345)) {
		boule_de_feu(1);
	} else if ((y >= 440) && (y <= 455)) {
		boule_de_feu(1);
	}

	if (((dy < 0) && (y < 100)) || ((dy > 0) && (y > 435))) {
		etape = 0;
		ss_etape = 0;
		etat = ETAT_TOMBE;
		fireball = false;
		onSaute();

		if (dy > 3) {
			dy = 3;
		}
		return;
	}
	y += dy;
	colFromPic();
}

void EnnemiMario::onRafalehorizontaledouble()
{
	switch (attack_phase) {
		case 0:
			if (y + dy < 100) {
				attack_phase = 1;
				fireball = false;
			} else {
				onRafalehorizontale();
			}
			break;

		case 1:
			tombe();
			if ((dy > 0) && (y < 0)) {
				attack_phase = 2;
				fireball = true;
				dy = 6;
			}
			colFromPic();
			break;

		case 2:
			onRafalehorizontale();
			break;
	}
}

void EnnemiMario::onRafalehorizontaleconstante()
{
	onTirehorizontale();
	if ((nb_pluie >	attack_phase) && (attack_etape > 50)) {
		attack_phase++;
		attack_etape = 30;
		attack_ss_etape = 0;
	} else if ((nb_pluie > attack_phase) && (attack_etape == 40)) {
		fireball = true;
	}
}

void EnnemiMario::onRafalehorizontalechercheuse()
{
	onTirehorizontale();
	if ((nb_pluie >	attack_phase) && (attack_etape > 50)) {
		if ((tete_turc != NULL) && ((tete_turc->x > x && dir == SENS_DROITE) || (tete_turc->x < x && dir == SENS_GAUCHE))) {
			attack_phase++;
			attack_etape = 30;
			attack_ss_etape = 0;
			y_cible = tete_turc->y;
		} else {
			fireball = false;
		}
	} else if ((nb_pluie > attack_phase) && (attack_etape == 40)) {
		fireball = true;
	}
}

void EnnemiMario::onRafaleverticale()
{
	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[10];
	} else {
		pic = pbk_ennemis[11];
	}

	ss_etape++;
	ss_etape %= 4;
	if (ss_etape == 0) {
		etape++;
		etape %= 3;
	}

	attack_ss_etape++;
	attack_ss_etape %= 6;
	if (attack_ss_etape == 0) {
		attack_etape++;
		if (dir == SENS_DROITE) {
			x_cible = x + attack_etape * 100 + rand() % 20;
			if (x_cible > offset + 720) {
				etape = 0;
				ss_etape = 0;
				speed = 0;
				etat = ETAT_AVANCE;
				fireball = false;
				onAvance();
				return;
			}
			TirMarioFireballVertical *	tir = new TirMarioFireballVertical(attack_etape, x_cible);

			tir->setDir(dir);
			tir->x = x + 38;
			tir->y = y - 38;

			list_tirs_ennemis.ajoute((void*) tir);
		} else {
			int x_cible = x - attack_etape * 100 - rand() % 20;
			if (x_cible < offset - 100) {
				etape = 0;
				ss_etape = 0;
				speed = 0;
				etat = ETAT_AVANCE;
				fireball = false;
				onAvance();
				return;
			}
			TirMarioFireballVertical *	tir = new TirMarioFireballVertical(-attack_etape, x_cible);

			tir->setDir(dir);
			tir->x = x - 38;
			tir->y = y - 38;

			list_tirs_ennemis.ajoute((void*) tir);
		}
	}
	colFromPic();
}

void EnnemiMario::onRafaleverticalechercheuse()
{
	onTireverticale();
	if ((nb_pluie > attack_phase) && (attack_etape == 40) && (tete_turc != NULL)) {
		attack_etape = 10;
		attack_ss_etape = 0;
		fireball = true;
		attack_phase ++;
		x_cible = tete_turc->x;
	}
}

void EnnemiMario::onRafaleverticaleconstante()
{
	onTireverticale();
	if ((nb_pluie > attack_phase) && (attack_etape == 40)) {
		attack_etape = 25;
		attack_ss_etape = 0;
		fireball = true;
		attack_phase ++;
	}
}

void EnnemiMario::onRafaleverticaledouble()
{
	switch (attack_phase) {
		case 0:
			if ((dir == SENS_DROITE) && (x + (attack_etape + 1) * 100 + 20 > offset + 620)) {
				attack_phase = 1;
				attack_ss_etape = 0;
				attack_etape = 1 + (offset + 640 - x) / 100;
			} else if ((dir == SENS_GAUCHE) && (x - (attack_etape + 1) * 100 - 20 < offset + 20)) {
				attack_phase = 1;
				attack_ss_etape = 0;
				attack_etape = 1 + (x - offset) / 100;
			} else {
				onRafaleverticale();
			}
			break;

		case 1:
			onRafaleverticaleinverser();
			break;

	}
}

void EnnemiMario::onRafaleverticaleinverser()
{
	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[10];
	} else {
		pic = pbk_ennemis[11];
	}

	ss_etape++;
	ss_etape %= 4;
	if (ss_etape == 0) {
		etape++;
		etape %= 3;
	}

	attack_ss_etape++;
	attack_ss_etape %= 6;
	if (attack_ss_etape == 0) {
		attack_etape--;
		if (dir == SENS_DROITE) {
			x_cible = offset + attack_etape * 100 + rand() % 20;
			if (x_cible < x + 20) {
				etape = 0;
				ss_etape = 0;
				speed = 0;
				etat = ETAT_AVANCE;
				fireball = false;
				onAvance();
				return;
			}
			TirMarioFireballVertical *	tir = new TirMarioFireballVertical(attack_etape, x_cible);

			tir->setDir(dir);
			tir->x = x + 38;
			tir->y = y - 38;

			list_tirs_ennemis.ajoute((void*) tir);
		} else {
			int x_cible = offset + 640 - attack_etape * 100 - rand() % 20;
			if (x_cible > x - 20) {
				etape = 0;
				ss_etape = 0;
				speed = 0;
				etat = ETAT_AVANCE;
				fireball = false;
				onAvance();
				return;
			}
			TirMarioFireballVertical *	tir = new TirMarioFireballVertical(-attack_etape, x_cible);

			tir->setDir(dir);
			tir->x = x - 38;
			tir->y = y - 38;

			list_tirs_ennemis.ajoute((void*) tir);
		}
	}
	colFromPic();
}

void EnnemiMario::onRafalecrosschercheuse()
{
	if (attack_phase % 2 == 0) {
		onTireverticale();
		if ((nb_pluie > attack_phase) && (attack_etape == 40) && (tete_turc != NULL)) {
			attack_etape = 30;
			attack_ss_etape = 0;
			fireball = true;
			attack_phase ++;
			y_cible = tete_turc->y;
		}
	} else {
		onTirehorizontale();
		if ((nb_pluie >	attack_phase) && (attack_etape > 50)) {
			if ((tete_turc != NULL) && ((tete_turc->x > x && dir == SENS_DROITE) || (tete_turc->x < x && dir == SENS_GAUCHE))) {
				attack_phase++;
				attack_etape = 30;
				attack_ss_etape = 0;
				x_cible = tete_turc->x;
			} else {
				fireball = false;
			}
		} else if ((nb_pluie > attack_phase) && (attack_etape == 40)) {
			fireball = true;
		}
	}
}

void EnnemiMario::onRafalecross()
{
	if (attack_phase % 2 == 0) {
		onTireverticale();
		if ((nb_pluie > attack_phase) && (attack_etape == 40)) {
			attack_etape = 35;
			attack_ss_etape = 0;
			fireball = true;
			attack_phase ++;
		}
	} else {
		onTirehorizontale();
		if ((nb_pluie >	attack_phase) && (attack_etape > 50)) {

			attack_phase++;
			attack_etape = 35;
			attack_ss_etape = 0;
		} else if ((nb_pluie > attack_phase) && (attack_etape == 40)) {
			fireball = true;
		}
	}
}

void EnnemiMario::onRafaleberserker()
{
	switch (attack_phase) {
		case 0:
			if (dir == SENS_DROITE) {
				marche(speed);
				pic = pbk_ennemis[anime(anim_mario_marche_droite, 4, 16 - (3 * speed))];
				if (x > offset + 600) {
					fireball = true;
					attack_phase = 1;
					speed = 1;
					dir = SENS_GAUCHE;
				}
			} else {
				marche(-speed);
				pic = pbk_ennemis[anime(anim_mario_marche_gauche, 4, 16 - (3 * speed))];
				if (x < offset + 40) {
					fireball = true;
					attack_phase = 1;
					speed = 1;
					dir = SENS_DROITE;
				}
			}
			colFromPic();
			break;

		case 1:
			if ((dir == SENS_DROITE) && (x + (attack_etape + 1) * 100 + 20 > offset + 620)) {
				attack_phase = 2;
			} else if ((dir == SENS_GAUCHE) && (x - (attack_etape + 1) * 100 - 20 < offset + 20)) {
				attack_phase = 2;
			} else {
				onRafaleverticale();
			}

			break;

		case 2:
			if (y + dy < 100) {
				attack_phase = 3;
				fireball = false;
			} else {
				onRafalehorizontale();
			}
			break;

		case 3:
			tombe();
			if (y < 0) {
				if (dir == SENS_DROITE) {
					dir = SENS_GAUCHE;
					x = offset + 600;
				} else {
					dir = SENS_DROITE;
					x = offset + 40;
				}
				dy = 6;
				attack_phase = 4;
				fireball = true;
			}
			colFromPic();
			break;

		case 4:
			if ((y + dy) > 435) {
				attack_phase = 5;
				if (dir == SENS_DROITE) {
					attack_etape = 1 + (640 - x) / 100;
				} else {
					attack_etape = 1 + x / 100;
				}
				attack_ss_etape = 0;
				etape = 0;
				ss_etape = 0;
				dy = 0;
			} else {
				onRafalehorizontale();
			}
			break;

		case 5:
			if ((dir == SENS_DROITE) && (x + (attack_etape - 1) * 100 - 20 < x)) {
				attack_phase = 6;
				attack_etape = 0;
				fireball = false;
			} else if ((dir == SENS_GAUCHE) && (x - (attack_etape - 1) * 100 + 20 > x)) {
				attack_phase = 6;
				attack_etape = 0;
				fireball = false;
			} else {
				onRafaleverticaleinverser();
			}
			break;

		case 6:
			attack_etape++;
			if (attack_etape >= 160) {
				etat = ETAT_AVANCE;
				etape = 0;
				ss_etape = 0;
				speed = 1;
				onAvance();
				return;
			}
			break;
	}
}

void EnnemiMario::onPluiedefeu()
{

	if (attack_phase == 0) {
		if (dir == SENS_DROITE) {
			marche(speed);
			pic = pbk_ennemis[anime(anim_mario_marche_droite, 4, 16 - (3 * speed))];
			if (x > offset + 600) {
				fireball = true;
				attack_phase = 1;
				speed = 1;
				dir = SENS_GAUCHE;
			}
		} else {
			marche(-speed);
			pic = pbk_ennemis[anime(anim_mario_marche_gauche, 4, 16 - (3 * speed))];
			if (x < offset + 40) {
				fireball = true;
				attack_phase = 1;
				speed = 1;
				dir = SENS_DROITE;
			}
		}
		colFromPic();
	} else {
		if (attack_phase < nb_pluie) {
			if (attack_phase % 2 == 0) {
				//rafale inverser
				if ((dir == SENS_DROITE) && (x + (attack_etape - 1) * 100 - 20 < x)) {
					attack_phase ++;
					attack_ss_etape = 0;
					attack_etape = 0;
				} else if ((dir == SENS_GAUCHE) && (x - (attack_etape - 1) * 100 + 20 > x)) {
					attack_phase ++;
					attack_ss_etape = 0;
					attack_etape = 0;
				} else {
					onRafaleverticaleinverser();
				}
			} else {
				//rafale normale
				if ((dir == SENS_DROITE) && (x + (attack_etape + 1) * 100 + 20 > 620)) {
					attack_phase ++;
					attack_ss_etape = 0;
					attack_etape = 1 + (offset + 640 - x) / 100;
				} else if ((dir == SENS_GAUCHE) && (x - (attack_etape + 1) * 100 - 20 < 20)) {
					attack_phase ++;
					attack_ss_etape = 0;
					attack_etape = 1 + (x - offset) / 100;
				} else {
					onRafaleverticale();
				}
			}
		} else {
			etape++;
			fireball = false;
			if (etape >= 60 + nb_pluie * 30) {
				etape = 0;
				ss_etape = 0;
				speed = 0;
				etat = ETAT_AVANCE;
				onAvance();
				return;
			}
		}
	}
}

inline void EnnemiMario::boule_de_feu(int vitesse)
{
	if (dir == SENS_DROITE) {
		TirMarioFireball *	tir = new TirMarioFireball(vitesse);

		tir->setDir(dir);
		tir->x = x + 38;
		tir->y = y - 31;

		list_tirs_ennemis.ajoute((void*) tir);
	} else {
		TirMarioFireball *	tir = new TirMarioFireball(-vitesse);

		tir->setDir(dir);
		tir->x = x - 38;
		tir->y = y - 31;

		list_tirs_ennemis.ajoute((void*) tir);
	}
}

void EnnemiMario::tombe_mario()
{
	lat_grav += 1;
	lat_grav %= LATENCE_MARIO_GRAVITE;

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

void EnnemiMario::estTouche(Tir * tir)
{
	static const int dx_giclure [] = { 0, 10, 15, 10, 0, -10, -15, -10 };
	static const int dy_giclure [] = { -15, -25, -25, -25, -35, -25, -25, -25 };

	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure, dy_giclure);
}
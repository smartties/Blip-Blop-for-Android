/******************************************************************
*
*
*		----------------------------
*		  EnnemiSnorkInBlackBoss.cpp
*		-----------------------------
*
*
*		Mephisto / LOADED -   V 0.1 - 23 Avril 2001
*
*
*
******************************************************************/

#include "ennemi_snork_in_black_boss.h"
#include "tir_epine.h"
#include "ben_debug.h"

const int anim_snork_in_black_boss_saute_droite[] = { 414, 415, 416, 415};
const int anim_snork_in_black_boss_saute_gauche[] = { 417, 418, 419, 418};

const int snork_in_black_position_x[] = { 5904, 6351, 5831, 6319}; //144,591,71,559
const int snork_in_black_position_y[] = { 175, 189, 342, 328};

EnnemiSnorkInBlackBoss::EnnemiSnorkInBlackBoss(): position(1), type_attack(0), attack(false), x_shark(5604), y_shark(100), shark(false), saut(false)
{
	pv = 15000;
	dy = 0;
	dir = SENS_GAUCHE;
	pic = pbk_ennemis[380];
}


void EnnemiSnorkInBlackBoss::update()
{
	if (blood > 0)
		blood -= 1;

	switch (etat) {
		case ETAT_AVANCE:
		case ETAT_NORMAL:
			onAvance();
			break;

		case ETAT_TOMBE:
		case ETAT_SAUTE:
			onTombe();
			break;

		case ETAT_CARBONISE:
		case ETAT_MEURE:
			onMeure();
			break;

		case ETAT_TIRE:
			onTire();
			break;
	}

	if (x > offset + 1000)
		a_detruire = true;

	//updateADetruire();

}

void EnnemiSnorkInBlackBoss::onAvance()
{
	if (game_flag[0] == 1) {
		if (ss_etape == 0 && etape == 0) {
			sbk_niveau.play(0);
		}

		ss_etape ++;
		ss_etape %= 8;

		if (ss_etape == 0) {
			etape ++;
		}

		if (etape >= 18) {
			game_flag[0] = 2;
			etape = 0;
			ss_etape = 0;
			mbk_niveau.play(1);
			game_flag[FLAG_TIMER] = 50;
		} else {
			pic = pbk_ennemis[383 + etape];
		}
	} else if (game_flag[0] == 2) {
		etape ++;
		if (etape > 20) {
			if (attack) {
				attack = false;
				ss_etape = 0;

				int destination = rand() % 4;

				if (tete_turc->x > 6200 && tete_turc->y > 200) {
					destination = 2;
				} else if (tete_turc->x < 5950 && tete_turc->y > 200) {
					destination = 3;
				} else if (tete_turc->x > 6200 && tete_turc->y < 200) {
					destination = 0;
				} else if (tete_turc->x < 5950 && tete_turc->y < 200) {
					destination = 1;
				}

				/*if (tete_turc->y < 200)
				{
					destination = rand() % 2 + 2;
				}
				else if(tete_turc->y > 200)
				{
					destination = rand() % 2;
				}*/

				if (destination == position) {
					etape = 15;
				} else {
					switch (position) {
						case 0:
							dir = SENS_DROITE;
							switch (destination) {
								case 1:
									dx = 4;
									dy = -7;
									break;

								case 2:
									dx = -1;
									dy = -2;
									break;

								case 3:
									dx = 5;
									dy = -3;

									break;
							}
							break;

						case 1:
							dir = SENS_GAUCHE;
							switch (destination) {
								case 0:
									dx = -6;
									dy = -5;
									break;

								case 2:
									dx = -6;
									dy = -3;
									break;

								case 3:
									dx = -1;
									dy = 3;
									break;
							}
							break;

						case 2:
							dir = SENS_DROITE;
							switch (destination) {
								case 0:
									dx = 1;
									dy = -7;
									break;

								case 1:
									dx = 5;
									dy = -9;
									break;

								case 3:
									dx = 7;
									dy = -5;
									break;
							}
							break;

						case 3:
							dir = SENS_GAUCHE;
							switch (destination) {
								case 0:
									dx = -6;
									dy = -7;
									break;

								case 1:
									dx = 1;
									dy = -6;
									break;

								case 2:
									dx = -5;
									dy = -6;
									break;
							}
							break;


					}
					position = destination;
					etape = 0;
					etat = ETAT_TOMBE;

					/*if (snork_in_black_position_x[position] > x)
					{
						dir = SENS_DROITE;
					}
					else
					{
						dir = SENS_GAUCHE;
					}*/

					//dx = 0;
					//dy = 0;

					//debug <<"destination : " << snork_in_black_position_x[position]<< "   "<<snork_in_black_position_y[position]<<"\n";
					//tirEnCloche( x, y, snork_in_black_position_x[position], snork_in_black_position_y[position], dx, dy);
					lat_grav = 0;
					saut = true;
					onTombe();
					return;
				}
			} else {
				etat = ETAT_TIRE;
				etape = 0;
				ss_etape = 0;

				if (tete_turc != NULL) {
					switch (position) {
						case 0:
							if (tete_turc->x > x && (y < tete_turc->y) && (y > tete_turc->y - 50)) {
								type_attack = 1;
							} else {
								type_attack = 0;
							}
							break;

						case 1:
							if (tete_turc->x < x && (y < tete_turc->y) && (y > tete_turc->y - 50)) {
								type_attack = 1;
							} else {
								type_attack = 0;
							}
							break;

						case 2:
							if (tete_turc->x > x && (y < tete_turc->y) && (y > tete_turc->y - 50)) {
								type_attack = 1;
							} else {
								type_attack = 0;
							}
							break;

						case 3:
							if (tete_turc->x < x && (y < tete_turc->y) && (y > tete_turc->y - 50)) {
								type_attack = 1;
							} else {
								type_attack = 0;
							}
							break;
					}
				}

				if (type_attack == 0) {
					sbk_niveau.play(2);
				} else {
					sbk_niveau.play(3);
				}

				attack = true;
				onTire();
				return;
			}
		}

		if (position == 0 || position == 2) {
			dir = SENS_DROITE;
			pic = pbk_ennemis[401];
		} else {
			dir = SENS_GAUCHE;
			pic = pbk_ennemis[400];
		}
	}

	colFromPic();
}

void EnnemiSnorkInBlackBoss::onTombe()
{
	lat_grav += 1;
	lat_grav %= LATENCE_GRAVITE;

	if (lat_grav == 0 && dy < GRAVITE_MAX)
		dy += 1;

	y += dy;

	if ((dx > 0 && (x + dx) >= snork_in_black_position_x[position]) || (dx < 0 && (x + dx) <= snork_in_black_position_x[position])) {
		dx = 0;
		x = snork_in_black_position_x[position];
	}
	/*else if
	{
		dx =0;
		x = snork_in_black_position_x[position];
	}*/
	x += dx;

	/*if (dx >= 0)
	{
		if ((x <= snork_in_black_position_x[position]) && (x + dx > snork_in_black_position_x[position]))
		{
			if (dy >= 0)
			{
				if ((y <= snork_in_black_position_y[position]) && (y + dy > snork_in_black_position_y[position]))
				{
					etat = ETAT_AVANCE;
					etape = 0;
					ss_etape = 0;
					x = snork_in_black_position_x[position];
					y = snork_in_black_position_y[position];
					onAvance();
					return;
				}
			}
			else
			{
				if ((y >= snork_in_black_position_y[position]) && (y + dy < snork_in_black_position_y[position]))
				{
					etat = ETAT_AVANCE;
					etape = 0;
					ss_etape = 0;
					x = snork_in_black_position_x[position];
					y = snork_in_black_position_y[position];
					onAvance();
					return;
				}
			}

		}
	}
	else
	{
		if ((x >= snork_in_black_position_x[position]) && (x + dx < snork_in_black_position_x[position]))
		{
			if (dy >= 0)
			{
				if ((y <= snork_in_black_position_y[position]) && (y + dy > snork_in_black_position_y[position]))
				{
					etat = ETAT_AVANCE;
					etape = 0;
					ss_etape = 0;
					x = snork_in_black_position_x[position];
					y = snork_in_black_position_y[position];
					onAvance();
					return;
				}
			}
			else
			{
				if ((y >= snork_in_black_position_y[position]) && (y + dy < snork_in_black_position_y[position]))
				{
					etat = ETAT_AVANCE;
					etape = 0;
					ss_etape = 0;
					x = snork_in_black_position_x[position];
					y = snork_in_black_position_y[position];
					onAvance();
					return;
				}
			}
		}
	}*/

	//debug <<"x: "<<x <<" y: "<< y <<"\n";


	if ((x > (snork_in_black_position_x[position] - tolerance)) && (x < (snork_in_black_position_x[position] + tolerance)) && (y > (snork_in_black_position_y[position] - tolerance)) && (y < (snork_in_black_position_y[position] + tolerance))) {
		etat = ETAT_AVANCE;
		etape = 0;
		ss_etape = 0;
		x = snork_in_black_position_x[position];
		y = snork_in_black_position_y[position];
		saut = false;
		onAvance();
		return;
	}

	/*	if (plat2(x + dx , y + dy) == plat2(snork_in_black_position_x[position],snork_in_black_position_y[position]))
		{

			etat = ETAT_AVANCE;
			etape = 0;
			ss_etape = 0;
			onAvance();
			return;
		}*/

	if (dir == SENS_DROITE) {
		pic = pbk_ennemis[anime(anim_snork_in_black_boss_saute_droite, 4, 6)];
	} else {
		pic = pbk_ennemis[anime(anim_snork_in_black_boss_saute_gauche, 4, 6)];
	}

	colFromPic();
}

void EnnemiSnorkInBlackBoss::onMeure()
{
	col_on = false;
	if (game_flag[0] == 2 && !saut) {
		int destination = 0;

		if (destination == position) {
			game_flag[0] = 3;

			if (position == 0 || position == 2) {
				dir = SENS_DROITE;
				pic = pbk_ennemis[401];
			} else {
				dir = SENS_GAUCHE;
				pic = pbk_ennemis[400];
			}
		} else {
			switch (position) {
				case 0:
					dir = SENS_DROITE;
					switch (destination) {
						case 1:
							dx = 4;
							dy = -7;
							break;

						case 2:
							dx = -1;
							dy = -2;
							break;

						case 3:
							dx = 5;
							dy = -3;

							break;
					}
					break;

				case 1:
					dir = SENS_GAUCHE;
					switch (destination) {
						case 0:
							dx = -6;
							dy = -5;
							break;

						case 2:
							dx = -6;
							dy = -3;
							break;

						case 3:
							dx = -1;
							dy = 3;
							break;
					}
					break;

				case 2:
					dir = SENS_DROITE;
					switch (destination) {
						case 0:
							dx = 1;
							dy = -7;
							break;

						case 1:
							dx = 5;
							dy = -9;
							break;

						case 3:
							dx = 7;
							dy = -5;
							break;
					}
					break;

				case 3:
					dir = SENS_GAUCHE;
					switch (destination) {
						case 0:
							dx = -6;
							dy = -7;
							break;

						case 1:
							dx = 1;
							dy = -6;
							break;

						case 2:
							dx = -5;
							dy = -6;
							break;
					}
					break;


			}
			position = destination;
			etape = 0;
			saut = true;
			//etat = ETAT_TOMBE;

			lat_grav = 0;
			return;
		}
	} else if (game_flag[0] == 2 && saut) {
		lat_grav += 1;
		lat_grav %= LATENCE_GRAVITE;

		if (lat_grav == 0 && dy < GRAVITE_MAX)
			dy += 1;

		y += dy;

		if ((dx > 0 && (x + dx) >= snork_in_black_position_x[position]) || (dx < 0 && (x + dx) <= snork_in_black_position_x[position])) {
			dx = 0;
			x = snork_in_black_position_x[position];
		}

		x += dx;

		if ((x > (snork_in_black_position_x[position] - tolerance)) && (x < (snork_in_black_position_x[position] + tolerance)) && (y > (snork_in_black_position_y[position] - tolerance)) && (y < (snork_in_black_position_y[position] + tolerance))) {
			//etat = ETAT_MEURE;
			etape = 0;
			ss_etape = 0;
			x = snork_in_black_position_x[position];
			y = snork_in_black_position_y[position];
			saut = false;
			//onAvance();
			return;
		}

		if (dir == SENS_DROITE) {
			pic = pbk_ennemis[anime(anim_snork_in_black_boss_saute_droite, 4, 6)];
		} else {
			pic = pbk_ennemis[anime(anim_snork_in_black_boss_saute_gauche, 4, 6)];
		}
	} else if (game_flag[0] == 3) {
		shark = true;
		x_shark += 5;

		if (x_shark < 5800) {
			y_shark ++;
		} else if (x_shark > 6004) {
			y_shark --;
		}

		if (x_shark > 6800) {
			game_flag[0] = 4;
		}
	} else if (game_flag[0] == 4) {
		x_shark += 5;
	}
}

void EnnemiSnorkInBlackBoss::onTire()
{
	if (type_attack == 0) {
		ss_etape ++;
		ss_etape %= 6;
		if (ss_etape == 0) {
			etape ++;
		}

		if (etape > 5) {
			etat = ETAT_NORMAL;
			etape = 0;
			ss_etape = 0;
			onAvance();
			return;
		} else if (ss_etape == 1) {
			if (dir == SENS_DROITE) {
				TirEpine * tir;
				switch (etape) {
					case 0:
						tir = new TirEpine(425, 4 , -6);
						tir->setDir(dir);
						tir->x = x + 36;
						tir->y = y - 51;

						list_tirs_ennemis.ajoute((void*) tir);

						break;

					case 1:
						tir = new TirEpine(426, 5 , -5);
						tir->setDir(dir);
						tir->x = x + 36;
						tir->y = y - 51;

						list_tirs_ennemis.ajoute((void*) tir);

						break;

					case 2:
						tir = new TirEpine(427, 6 , -4);
						tir->setDir(dir);
						tir->x = x + 52;
						tir->y = y - 16;

						list_tirs_ennemis.ajoute((void*) tir);
						break;

					case 3:
						tir = new TirEpine(428, 7 , 0);
						tir->setDir(dir);
						tir->x = x + 52;
						tir->y = y - 16;

						list_tirs_ennemis.ajoute((void*) tir);
						break;

					case 4:
						tir = new TirEpine(429, 6 , 4);
						tir->setDir(dir);
						tir->x = x + 35;
						tir->y = y + 25;

						list_tirs_ennemis.ajoute((void*) tir);
						break;

					case 5:
						tir = new TirEpine(430, 5 , 5);
						tir->setDir(dir);
						tir->x = x + 35;
						tir->y = y + 25;

						list_tirs_ennemis.ajoute((void*) tir);
						break;

				}
			} else {
				TirEpine * tir;

				switch (etape) {
					case 0:
						tir = new TirEpine(439, -4 , -6);
						tir->setDir(dir);
						tir->x = x - 36;
						tir->y = y - 51;

						list_tirs_ennemis.ajoute((void*) tir);

						break;

					case 1:
						tir = new TirEpine(438, -5 , -5);
						tir->setDir(dir);
						tir->x = x - 36;
						tir->y = y - 51;

						list_tirs_ennemis.ajoute((void*) tir);

						break;

					case 2:
						tir = new TirEpine(437, -6 , -4);
						tir->setDir(dir);
						tir->x = x - 52;
						tir->y = y - 16;

						list_tirs_ennemis.ajoute((void*) tir);
						break;

					case 3:
						tir = new TirEpine(436, -7 , 0);
						tir->setDir(dir);
						tir->x = x - 52;
						tir->y = y - 16;

						list_tirs_ennemis.ajoute((void*) tir);
						break;

					case 4:
						tir = new TirEpine(435, -6 , 4);
						tir->setDir(dir);
						tir->x = x - 35;
						tir->y = y + 25;

						list_tirs_ennemis.ajoute((void*) tir);
						break;

					case 5:
						tir = new TirEpine(434, -5 , 5);
						tir->setDir(dir);
						tir->x = x - 35;
						tir->y = y + 25;

						list_tirs_ennemis.ajoute((void*) tir);
						break;

				}

			}
		}

		if (dir == SENS_DROITE) {
			pic = pbk_ennemis[402 + 2 * (etape / 2) + ss_etape / 3];
		} else {
			pic = pbk_ennemis[408 + 2 * (etape / 2) + ss_etape / 3];
		}
	} else {
		ss_etape ++;
		ss_etape %= 5;

		if (ss_etape == 0) {
			etape ++;
		}

		if (etape >= 1) {
			if (dir == SENS_DROITE) {
				TirEpine * tir = new TirEpine(422, 14 , 0);

				tir->setDir(dir);
				tir->x = x + 77;
				tir->y = y - 2;

				list_tirs_ennemis.ajoute((void*) tir);
			} else {
				TirEpine * tir = new TirEpine(423, -14 , 0);

				tir->setDir(dir);
				tir->x = x - 77;
				tir->y = y - 2;

				list_tirs_ennemis.ajoute((void*) tir);
			}

			etat = ETAT_NORMAL;
			etape = 0;
			ss_etape = 0;
			onAvance();
			return;
		} else {
			if (dir == SENS_DROITE) {
				pic = pbk_ennemis[421];
			} else {
				pic = pbk_ennemis[420];
			}
		}
	}
	/*ss_etape ++;
	if (etape == 0)
	{
		ss_etape %= 20;
	}
	else
	{
		ss_etape %= 4;
	}

	if(ss_etape == 0)
	{
		etape ++;
	}

	if ((etape == 1) && (ss_etape == 0))
	{
		if (dir == SENS_DROITE)
		{
			int vx = 5 + rand() % 2;
			int vy = rand() % 5 - 2;

			TirEpine * tir = new TirEpine(364, vx , vy);

			tir->setDir( dir);
			tir->x = x + 49;
			tir->y = y - 15;

			list_tirs_ennemis.ajoute( (void*) tir);
		}
		else
		{
			int vx = -5 - rand() % 2;
			int vy = rand() % 5 - 2;

			TirEpine * tir = new TirEpine(365, vx , vy);

			tir->setDir( dir);
			tir->x = x - 49;
			tir->y = y - 15;

			list_tirs_ennemis.ajoute( (void*) tir);
		}
	}

	if (etape == 3)
	{
		nb_tir ++;
		etape = 0;
		if (nb_tir >= SNORK_IN_BLACK_MAX_TIR)
		{
			ss_etape = 0;
			etape = 0;
			etat = ETAT_AVANCE;
			onAvance();
			return;
		}
	}

	if (dir == SENS_DROITE)
	{
		if (etape == 0)
		{
			pic = pbk_ennemis[344];
		}
		else
		{
			pic = pbk_ennemis[350 + etape - 1];
		}
	}
	else
	{
		if (etape == 0)
		{
			pic = pbk_ennemis[347 ];
		}
		else
		{
			pic = pbk_ennemis[352 + etape - 1];
		}
	}*/
	colFromPic();
}


void EnnemiSnorkInBlackBoss::estTouche(Tir * tir)
{
	static const int dx_giclure_snorkbase1 [] = { 0, 0, 4, 0, 0, 0, -4, 0 };
	static const int dy_giclure_snorkbase1 [] = { -15, -15, -15, -15, -25, -15, -15, -15 };


	Ennemi::estTouche(tir);
	gicle(tir, dx_giclure_snorkbase1, dy_giclure_snorkbase1);
}

void EnnemiSnorkInBlackBoss::affiche()
{
	if (x_shark < 5904) {
		Sprite::affiche();
	}
	if (shark) {
		if (x_shark < 5904) {
			draw(x_shark, y_shark, pbk_ennemis[441]);
		} else {
			draw(x_shark, y_shark, pbk_ennemis[440]);
		}
	}
}


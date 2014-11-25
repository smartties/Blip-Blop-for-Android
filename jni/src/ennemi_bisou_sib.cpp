
#include "ennemi_bisou_sib.h"


#define ETAT_ATTENDS_MAL	100
#define ETAT_ATTENDS		101
#define ETAT_COURS_FOREST	102
#define ETAT_RENTRE_MAL		103

static const int anim_cours [] = { 640, 641, 642, 641 };

EnnemiBisouSIB::EnnemiBisouSIB()
{
	if (game_flag[FLAG_USER1] != 0) {
		etat = ETAT_ATTENDS_MAL;
		game_flag[FLAG_USER1] = 0;
	} else {
		etat = ETAT_ATTENDS;
	}

	ss_etape = etape = 0;
	encaisse = 0;
}


void EnnemiBisouSIB::update()
{
	tombe();

	switch (etat) {
		case ETAT_ATTENDS_MAL:
			pic = pbk_ennemis[635];
			colFromPic();

			if (x < offset + 440 || game_flag[1] == 0)
				etat = ETAT_RENTRE_MAL;

			break;

		case ETAT_ATTENDS:
			pic = pbk_ennemis[639];
			colFromPic();

			if (x - tete_turc->x < 200)
				etat = ETAT_COURS_FOREST;

			break;

		case ETAT_RENTRE_MAL:
			ss_etape += 1;
			ss_etape %= 9;

			if (ss_etape == 0) {
				etape += 1;

				if (etape == 5) {
					etape = ss_etape = 0;
					etat = ETAT_COURS_FOREST;
				} else {
					pic = pbk_ennemis[635 + etape];
				}
			}

			noCol();
			break;


		case ETAT_COURS_FOREST:
			pic = pbk_ennemis[anime(anim_cours, 4, 5)];
			marche(3);
			noCol();
			break;

	}


	updateADetruire();
}


void EnnemiBisouSIB::estTouche(Tir * tir)
{
	if (++encaisse > 300) {
		if (etat == ETAT_ATTENDS_MAL)
			etat = ETAT_RENTRE_MAL;
		else if (etat == ETAT_ATTENDS)
			etat = ETAT_COURS_FOREST;

		noCol();
	}
}
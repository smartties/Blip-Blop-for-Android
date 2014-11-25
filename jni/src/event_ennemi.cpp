/******************************************************************
*
*
*		-----------------
*		  EventEnnemi.h
*		-----------------
*
*		Classe Evenement Ennemi
*
*		La classe evenement qui crée un ennemi
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

#include "event_ennemi.h"
#include "enemy.h"

#include "ennemi_smurf.h"
#include "ennemi_smurf_gourmand.h"
#include "ennemi_smurf_farceur.h"
#include "ennemi_smurf_sauvage.h"
#include "ennemi_smurf_a_lunettes.h"
#include "ennemi_smurf_paresseux.h"
#include "ennemi_smurf_coquet.h"
#include "ennemi_smurf_frileux.h"
#include "ennemi_smurf_peon.h"
#include "ennemi_smurf_paysan.h"
#include "ennemi_smurf_costaud.h"
#include "ennemi_smurfette.h"
#include "ennemi_grand_smurf.h"
#include "ennemi_smurf_cigogne.h"

#include "ennemi_pikachu.h"
#include "ennemi_bulbizarre.h"
#include "ennemi_flameche.h"
#include "ennemi_com.h"
#include "ennemi_com_volant.h"

#include "ennemi_lemmings.h"
#include "ennemi_lemmings_volant.h"

#include "ennemi_bisou_ciel.h"
#include "ennemi_bisou_etoile.h"
#include "ennemi_bisou_boom.h"
#include "ennemi_bisou_nuage.h"
#include "ennemi_bisou_zombi.h"
#include "ennemi_bisou_chaman.h"
#include "ennemi_bisou_coeur.h"
#include "ennemi_bisou_jedi.h"
#include "ennemi_bisou_sib.h"

#include "ennemi_snorky_base_1.h"
#include "ennemi_snorky_base_2.h"
#include "ennemi_snorky_gouverneur.h"
#include "ennemi_snorky_mage.h"
#include "ennemi_snorky_hyporider.h"
#include "ennemi_snork_in_black.h"
#include "ennemi_snork_in_black_boss.h"
#include "ennemi_diabolo.h"

#include "ennemi_toad.h"
#include "ennemi_yoshi.h"
#include "ennemi_yoshi_dca.h"
#include "ennemi_princesseguard.h"
#include "ennemi_princesse.h"
#include "ennemi_tails.h"
#include "ennemi_tailsvolant.h"
#include "ennemi_knukles.h"
#include "ennemi_rayman.h"

#include "ennemi_luigi.h"
#include "ennemi_sonic.h"
#include "ennemi_mariotapette.h"
#include "ennemi_lara.h"
#include "ennemi_pic.h"
#include "ennemi_poid.h"

#include "ennemi_mario.h"

#define	IDENNEMI_SMURF				0
#define	IDENNEMI_SMURF_GOURMAND		1
#define IDENNEMI_SMURF_FARCEUR		2
#define IDENNEMI_SMURF_SAUVAGE		3
#define IDENNEMI_SMURF_PAYSAN		4
#define IDENNEMI_SMURCOSTAUD		5
#define IDENNEMI_SMURFETTE			6
#define IDENNEMI_CIGOGNE			7
#define IDENNEMI_GRANDSMURF			8

#define IDENNEMI_PIKACHU			100
#define IDENNEMI_BULBIZARRE			101
#define IDENNEMI_FLAMECHE			102
#define IDENNEMI_COM				103
#define IDENNEMI_COM_VOLANT			104

#define IDENNEMI_BISOUCIEL			200
#define IDENNEMI_BISOUETOILE		201
#define IDENNEMI_BISOUBOOM			202
#define IDENNEMI_BISOUNUAGE			203
#define IDENNEMI_BISOUZOMBI			204
#define IDENNEMI_BISOUCHAMAN		205
#define IDENNEMI_BISOUCOEUR			206
#define IDENNEMI_BISOUJEDI			207
#define IDENNEMI_BISOUJEDIHEROS		208
#define IDENNEMI_BISOUSIB			209

#define IDENNEMI_LEMMINGS			400
#define IDENNEMI_LEMMINGS_VOLANT	401

#define IDENNEMI_SNORKY_BASE_1      300
#define IDENNEMI_SNORKY_BASE_2      301
#define IDENNEMI_SNORKY_GOUVERNEUR  302
#define IDENNEMI_SNORKY_MAGE        303
#define IDENNEMI_SNORKY_RIDER       304
#define IDENNEMI_SNORK_IN_BLACK		305
#define IDENNEMI_DIABOLO			306
#define IDENNEMI_SNORK_IN_BLACK_BOSS 307

#define IDENNEMI_TOAD               500
#define IDENNEMI_YOSHI              501
#define IDENNEMI_PRINCESSE_GUARD    502
#define IDENNEMI_PRINCESSE          503
#define IDENNEMI_TAILS              504
#define IDENNEMI_YOSHI_DCA          505
#define IDENNEMI_KNUKLES            506
#define IDENNEMI_RAYMAN             507
#define IDENNEMI_TAILSVOLANT        508

#define IDENNEMI_LUIGI              600
#define IDENNEMI_SONIC              601
#define IDENNEMI_MARIO_TAPETTE      602
#define IDENNEMI_LARA               603
#define IDENNEMI_PIC				604
#define IDENNEMI_POID				605

#define IDENNEMI_MARIO              700


void EventEnnemi::doEvent()
{
	Ennemi *	enn = NULL;

	switch (id_ennemi) {
		case IDENNEMI_SMURF:
			switch (rand() % 6) {
				case 0 :
					enn = new EnnemiSmurf();
					break;
				case 1 :
					enn = new EnnemiSmurfALunettes();
					break;
				case 2 :
					enn = new EnnemiSmurfCoquet();
					break;
				case 3 :
					enn = new EnnemiSmurfFrileux();
					break;
				case 4 :
					enn = new EnnemiSmurfParesseux();
					break;
				case 5 :
					enn = new EnnemiSmurfPeon();
					break ;
			}
			break ;

		case IDENNEMI_SMURF_GOURMAND:
			enn = new EnnemiSmurfGourmand();
			break;

		case IDENNEMI_SMURF_FARCEUR:
			enn = new EnnemiSmurfFarceur();
			break;

		case IDENNEMI_SMURF_SAUVAGE:
			enn = new EnnemiSmurfSauvage();
			break;

		case IDENNEMI_SMURF_PAYSAN:
			enn = new EnnemiSmurfPaysan();
			break;

		case IDENNEMI_SMURCOSTAUD:
			enn = new EnnemiSmurfCostaud();
			break;

		case IDENNEMI_SMURFETTE:
			enn = new EnnemiSmurfette();
			break;

		case IDENNEMI_GRANDSMURF:
			enn = new EnnemiGrandSmurf();
			break;

		case IDENNEMI_CIGOGNE:
			enn = new EnnemiSmurfCigogne();
			break;

		case IDENNEMI_PIKACHU:
			enn = new EnnemiPikachu();
			break;

		case IDENNEMI_BULBIZARRE:
			enn = new EnnemiBulbizarre();
			break;

		case IDENNEMI_FLAMECHE:
			enn = new EnnemiFlameche();
			break;

		case IDENNEMI_COM:
			enn = new EnnemiCOM();
			break;

		case IDENNEMI_BISOUCIEL:
			enn = new EnnemiBisouCiel();
			break;

		case IDENNEMI_BISOUETOILE:
			enn = new EnnemiBisouEtoile();
			break;

		case IDENNEMI_BISOUBOOM:
			enn = new EnnemiBisouBoom();
			break;

		case IDENNEMI_BISOUNUAGE:
			enn = new EnnemiBisouNuage();
			break;

		case IDENNEMI_BISOUZOMBI:
			enn = new EnnemiBisouZombi();
			break;

		case IDENNEMI_BISOUCHAMAN:
			enn = new EnnemiBisouChaman();
			break;

		case IDENNEMI_BISOUCOEUR:
			enn = new EnnemiBisouCoeur();
			break;

		case IDENNEMI_BISOUJEDI:
			enn = new EnnemiBisouJedi();
			break;

		case IDENNEMI_BISOUJEDIHEROS:
			enn = new EnnemiBisouJediHeros();
			break;

		case IDENNEMI_BISOUSIB:
			enn = new EnnemiBisouSIB();
			break;

		case IDENNEMI_LEMMINGS:
			enn = new EnnemiLemmings();
			break;

		case IDENNEMI_LEMMINGS_VOLANT:
			enn = new EnnemiLemmingsVolant();
			break;

		case IDENNEMI_COM_VOLANT:
			enn = new EnnemiCOMVolant();
			break;

		case IDENNEMI_SNORKY_BASE_1:
			enn = new EnnemiSnorkyBase1();
			break;

		case IDENNEMI_SNORKY_BASE_2:
			enn = new EnnemiSnorkyBase2();
			break;

		case IDENNEMI_SNORKY_GOUVERNEUR:
			enn = new EnnemiSnorkyGouverneur();
			break;

		case IDENNEMI_SNORKY_MAGE:
			enn = new EnnemiSnorkyMage();
			break;

		case IDENNEMI_SNORKY_RIDER:
			enn = new EnnemiSnorkyHyporider();
			break;

		case IDENNEMI_DIABOLO:
			enn = new EnnemiDiabolo();
			break;

		case IDENNEMI_SNORK_IN_BLACK:
			enn = new EnnemiSnorkInBlack();
			break;

		case IDENNEMI_SNORK_IN_BLACK_BOSS:
			enn = new EnnemiSnorkInBlackBoss();
			break;

		case IDENNEMI_TOAD:
			enn = new EnnemiToad();
			break;

		case IDENNEMI_YOSHI:
			enn = new EnnemiYoshi();
			break;

		case IDENNEMI_YOSHI_DCA:
			enn = new EnnemiYoshiDCA();
			break;

		case IDENNEMI_PRINCESSE:
			enn = new EnnemiPrincesse();
			break;

		case IDENNEMI_TAILS:
			enn = new EnnemiTails();
			break;

		case IDENNEMI_KNUKLES:
			enn = new EnnemiKnukles();
			break;

		case IDENNEMI_RAYMAN:
			enn  = new EnnemiRayman();
			break;

		case IDENNEMI_TAILSVOLANT:
			enn = new EnnemiTailsvolant();
			break;

		case IDENNEMI_LUIGI:
			enn = new EnnemiLuigi();
			break;

		case IDENNEMI_SONIC:
			enn = new EnnemiSonic();
			break;

		case IDENNEMI_MARIO_TAPETTE:
			enn = new EnnemiMariotapette();
			break;

		case IDENNEMI_LARA:
			enn = new EnnemiLara();
			break;

		case IDENNEMI_PIC:
			enn = new EnnemiPic();
			break;

		case IDENNEMI_POID:
			enn = new EnnemiPoid();
			break;

		case IDENNEMI_MARIO:
			enn = new EnnemiMario();
			break;
	}

	if (enn != NULL) {
		enn->x = x;
		enn->y = y;
		enn->dir = sens;

		list_ennemis.ajoute((void*) enn);

		if (enn->count())
			nb_ennemis_created += 1;
	} else {
		debug << "Erreur : identité d'ennemi inconnue (" << id_ennemi << ")\n";
	}
}

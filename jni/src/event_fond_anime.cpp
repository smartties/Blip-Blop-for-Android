/******************************************************************
*
*
*		----------------------
*		  EventFondAnime.cpp
*		----------------------
*
*
*
*		Prosper / LOADED -   2 Aout 2000
*
*
*
******************************************************************/

// Configuration
//
#include "config.h"

// Header classe
//
#include "event_fond_anime.h"

// Fonds pokemons
//
#include "fond_bombe.h"
#include "fond_poke_alarme_1.h"
#include "fond_poke_fleche.h"
#include "fond_poke_ciel.h"
#include "fond_poke_ascenceur.h"
#include "fond_poke_interupteur.h"
#include "fond_poke_caisse_tombante.h"
#include "fond_poke_ascenseur_2.h"
#include "fond_poke_level_2.h"
#include "fond_poke_level_3.h"

// Fonds Snorkys
//
#include "fond_snork_sas.h"
#include "fond_poissons.h"

// Fonds lemmings
//
#include "fond_ventilo.h"
#include "fond_lumiere.h"
#include "fond_lampe_2.h"
#include "fond_eau.h"

//Fonds Jeux Vidéos
//
#include "fond_cube.h"
#include "fond_piece.h"
#include "fond_ring.h"
#include "fond_tournesol_1.h"
#include "fond_tournesol_2.h"
#include "fond_tournesol_3.h"
#include "fond_tournesol_4.h"
#include "fond_drapeau.h"

#include "fond_lcd.h"
#include "fond_worldmap.h"
#include "fond_electronics.h"
#include "fond_ecraneige.h"
#include "fond_ecrancamera.h"
#include "fond_assembleur.h"
#include "fond_windows.h"
#include "fond_dos.h"
#include "fond_bossventilo.h"

#include "fond_battle_cruiser.h"
#include "fond_etoile.h"
#include "fond_monolite.h"
#include "fond_rocher_1.h"
#include "fond_rocher_2.h"
#include "fond_rocher_hyperspace.h"


#define IDFOND_POKEALARME1	100
#define IDFOND_POKEALARME2	101
#define IDFOND_POKEALARME3	102
#define IDFOND_POKEFLECHE	103
#define IDFOND_POKECIEL		104
#define IDFOND_POKEASCENC	105
#define IDFOND_INTERRUPTEUR 106
#define IDFOND_CAISSETOMBANTE 107
#define IDFOND_POKEASCENC2  108
#define IDFOND_BOMBE        109
#define IDFOND_LEVEL2       110
#define IDFOND_LEVEL3		111

#define IDFOND_SAS1         300
#define IDFOND_SAS2         301
#define IDFOND_POISSONROUGE 302
#define IDFOND_POISSONVIOLET			303
#define IDFOND_POISSONROUGECAMOUFLE		304
#define IDFOND_POISSONVIOLETCAMOUFLE	305

#define IDFOND_VENTILO		400
#define IDFOND_LUMIERE		401
#define IDFOND_EAU			402
#define IDFOND_LUMIERE2		403

#define IDFOND_CUBE         500
#define IDFOND_PIECE        501
#define IDFOND_RING         502
#define IDFOND_TOURNESOL1   503
#define IDFOND_TOURNESOL2   504
#define IDFOND_TOURNESOL3   505
#define IDFOND_TOURNESOL4   506
#define IDFOND_DRAPEAU		507

#define IDFOND_LCD          600
#define IDFOND_WORLDMAP     601
#define IDFOND_ELECTRONIC1  602
#define IDFOND_ELECTRONIC2  603
#define IDFOND_ELECTRONIC3  604
#define IDFOND_ELECTRONIC4  605
#define IDFOND_ECRANNEIGE   606
#define IDFOND_ECRANCAMERA  607
#define IDFOND_ASSEMBLEUR   608
#define IDFOND_WINDOWS      609
#define IDFOND_DOS          610
#define IDFOND_BOSSVENTILO  611

#define IDFOND_BATTLECRUISER 700
#define IDFOND_ROCHER_HYPERSPACE 701
#define IDFOND_MONOLITE		 702
#define IDFOND_ROCHER1		 703
#define IDFOND_ROCHER2       704
#define IDFOND_ETOILE		 705

void EventFondAnime::doEvent()
{
	Sprite * s = NULL;
	bool	plat_mobile = false;

	switch (id_fond) {
		case IDFOND_VENTILO:
			s = new FondVentilo();
			break;

		case IDFOND_LUMIERE:
			s = new FondLumiere();
			break;

		case IDFOND_EAU:
			s = new FondEau();
			break;

		case IDFOND_LUMIERE2:
			s = new FondLumiere2();
			break;

		case IDFOND_POKEALARME1:
			s = new FondPokeAlarme1();
			break;

		case IDFOND_POKEALARME2:
			s = new FondPokeAlarme2();
			break;

		case IDFOND_POKEALARME3:
			s = new FondPokeAlarme3();
			break;

		case IDFOND_POKEFLECHE:
			s = new FondPokeFleche();
			break;

		case IDFOND_POKECIEL:
			s = new FondPokeCiel();
			break;

		case IDFOND_POKEASCENC:
			s = new FondPokeAscenceur();
			plat_mobile = true;
			break;

		case IDFOND_INTERRUPTEUR:
			s = new FondPokeInterupteur();
			plat_mobile = true;
			break;

		case IDFOND_CAISSETOMBANTE:
			s = new FondPokeCaisseTombante();
			plat_mobile = true;
			break;

		case IDFOND_POKEASCENC2:
			s = new FondPokeAscenceur2();
			plat_mobile = true;
			break;

		case IDFOND_BOMBE:
			s = new FondBombe();
			plat_mobile = true;
			break;

		case IDFOND_LEVEL2:
			s = new FondPokeLevel2();
			break;

		case IDFOND_LEVEL3:
			s = new FondPokeLevel3();
			break;

		case IDFOND_SAS1:
			s = new FondSnorkSas1();
			plat_mobile = true;
			break;

		case IDFOND_SAS2:
			s = new FondSnorkSas2();
			plat_mobile = true;
			break;

		case IDFOND_POISSONROUGE:
			s = new FondPoissonRouge();
			break;

		case IDFOND_POISSONVIOLET:
			s = new FondPoissonViolet();
			break;

		case IDFOND_POISSONROUGECAMOUFLE:
			s = new FondPoissonRougeCamoufle();
			break;

		case IDFOND_POISSONVIOLETCAMOUFLE:
			s = new FondPoissonVioletCamoufle();
			break;

		case IDFOND_CUBE:
			s = new FondCube();
			break;

		case IDFOND_PIECE:
			s = new FondPiece();
			break;

		case IDFOND_RING:
			s = new FondRing();
			break;

		case IDFOND_TOURNESOL1:
			s = new FondTournesol1();
			break;

		case IDFOND_TOURNESOL2:
			s = new FondTournesol2();
			break;

		case IDFOND_TOURNESOL3:
			s = new FondTournesol3();
			break;

		case IDFOND_TOURNESOL4:
			s = new FondTournesol4();
			break;

		case IDFOND_DRAPEAU:
			s = new FondDrapeau();
			break;

		case IDFOND_LCD:
			s = new FondLCD();
			break;

		case IDFOND_WORLDMAP:
			s = new FondWorldmap();
			break;

		case IDFOND_ELECTRONIC1:
			s = new FondElectronic1();
			break;

		case IDFOND_ELECTRONIC2:
			s = new FondElectronic2();
			break;

		case IDFOND_ELECTRONIC3:
			s = new FondElectronic3();
			break;

		case IDFOND_ELECTRONIC4:
			s = new FondElectronic4();
			break;

		case IDFOND_ECRANNEIGE:
			s = new FondEcranneige();
			break;

		case IDFOND_ECRANCAMERA:
			s = new FondEcrancamera();
			break;

		case IDFOND_ASSEMBLEUR:
			s = new FondAssembleur();
			break;

		case IDFOND_WINDOWS:
			s = new FondWindows();
			break;

		case IDFOND_DOS:
			s = new FondDos();
			break;

		case IDFOND_BOSSVENTILO:
			s = new FondBossventilo();
			break;

		case IDFOND_BATTLECRUISER:
			s = new FondBattlecruiser();
			break;

		case IDFOND_ROCHER_HYPERSPACE:
			s = new FondRocherHyperspace();
			break;

		case IDFOND_MONOLITE:
			s = new FondMonolite();
			plat_mobile	= true;
			break;

		case IDFOND_ROCHER1:
			s = new FondRocher1();
			plat_mobile = true;
			break;

		case IDFOND_ROCHER2:
			s = new FondRocher2();
			plat_mobile = true;
			break;

		case IDFOND_ETOILE:
			s = new FondEtoile();
			break;

		case 900:
			s = new FondBombe();
			break;

	}

	if (s != NULL) {
		s->x = x;
		s->y = y;

		if (plat_mobile)
			list_plateformes_mobiles.ajoute((void*) s);
		else
			list_fonds_animes.ajoute((void*) s);
	} else {
		debug << "Erreur : identité de fond animé inconnue (" << id_fond << ")\n";
	}

}

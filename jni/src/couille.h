/******************************************************************
*
*
*		-----------------
*		    Couille.h
*		-----------------
*
*		Pour Blip et Blop
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _Couille_
#define _Couille_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "controlor.h"
#include "personnage.h"
#include "joueur.h"
#include "tir.h"

#include "tir_bbm16.h"
#include "tir_bbpm.h"
#include "tir_bb_fusil.h"
#include "tir_bb_laser.h"
#include "tir_bblf.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define NB_TIRS_M16			16
#define NB_TIRS_PM			20
#define NB_TIRS_FUSIL		40
#define NB_TIRS_LASER		2
#define NB_TIRS_LF			300

#ifndef _BBCONST_
#define _BBCONST_

#define BBDIR_BAS_B_D		0
#define BBDIR_BAS_D			1
#define BBDIR_BAS_DROITE	2
#define BBDIR_DROITE_B		3
#define BBDIR_DROITE		4
#define BBDIR_DROITE_H		5
#define BBDIR_HAUT_DROITE	6
#define BBDIR_HAUT_D		7
#define BBDIR_HAUT_H_D		8
#define BBDIR_HAUT_H_G		9
#define BBDIR_HAUT_G		10
#define BBDIR_HAUT_GAUCHE	11
#define BBDIR_GAUCHE_H		12
#define BBDIR_GAUCHE		13
#define BBDIR_GAUCHE_B		14
#define BBDIR_BAS_GAUCHE	15
#define BBDIR_BAS_G			16
#define BBDIR_BAS_B_G		17

#define BBLIM_DROITE		8

#define ID_M16		0
#define ID_FUSIL	1
#define ID_PM		2
#define ID_LF		3
#define ID_LASER	4

#define ID_BLIP		0
#define ID_BLOP		1

#endif

//-----------------------------------------------------------------------------
//		Définition de la classe Couille
//-----------------------------------------------------------------------------

class Couille : public Personnage, public Joueur
{
public:
	Picture **	pbk_own;
	int			id_couille;
	bool		perfect;

	Controlor *	ctrl;
	int			sauti;

	int			id_arme;
	int			dir_arme;
	int			ammo;

	int			etape_arme;		// Pour la détonation
	int			ss_etape_arme;
	int			nb_etape_arme;
	int			latence_arme;

	int			cadence_arme;	// Latence tir
	int			pruno;			// Etape tir

	int			poid_arme;		// Latence tourne arme
	int			etape_bouge_arme;

	bool		tire;			// Est en train de tirer

	int			dx_saut;		// Pour l'inertie
	int			dx_glisse;
	int			latence_glisse;
	int			etape_recul;

	int			invincible;
	bool		inv_cow;
	int			a_mal;
	int			etape_cli;

	int			y_to_go;

	int			nb_life;
	int			nb_cow_bomb;
	int			wait_cow_bomb;
	bool		jump_released;	// Le bouton saut a été relaché
	int			time_down;		// Temps ecoulé depuis la dernière fois
								// que bas a été pressé

	bool		locked_fire;
	bool		locked_dir;

	bool		fire_lf;
	bool		fire_laser;

	TirBBM16	tirs_m16[NB_TIRS_M16];
	int			next_m16;

	TirBBPM		tirs_pm[NB_TIRS_PM];
	int			next_pm;

	TirBBFusil	tirs_fusil[NB_TIRS_FUSIL];
	int			next_fusil;

	TirBBLaser	tirs_laser[NB_TIRS_LASER];
	int			next_laser;

	TirBBLF		tirs_lf[NB_TIRS_LF];
	int			next_lf;

public:

	int			mod_life;

	Couille();

	virtual void rearme() = 0;

	virtual void affiche();
	virtual void afficheNormal();
	virtual void afficheSaute();
	virtual void afficheMeure();
	virtual void afficheVehicule();
	virtual void afficheArme( int xtmp, int ytmp);
	virtual void afficheOeil( int xtmp, int ytmp);
	virtual void update();
	virtual void onNormal();
	virtual void onSaute();
	virtual void onAvance();
	virtual void onMeure();
	virtual void onComeBack();
	virtual void onSaleto();
	virtual void onVehicule();
	virtual void updateArme();
	virtual void estTouche( const Tir * tir);
	virtual void estTouche( int degats);
	virtual void colFromPic();

	virtual void lockVehicule( bool can_fire, bool can_dir);
	virtual void unlockVehicule();

	virtual void manageDirection();
	virtual bool okBonus();
	virtual void setSuperWeapon();
	virtual void endLevel()
	{
		sbk_bb.stop( 2);
		sbk_bb.stop( 4);
	};

};

#endif

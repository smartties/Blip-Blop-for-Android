/******************************************************************
*
*
*		--------------------
*		EnnemiSmurfSauvage.h
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

#ifndef _EnnemiSmurfSauvage_
#define _EnnemiSmurfSauvage_

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "enemy.h"

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#define DIAGONALE_GAUCHE		0
#define DIAGONALE_BAS_GAUCHE	1
#define BAS_GAUCHE				2
#define BAS_DROITE				3
#define DIAGONALE_BAS_DROITE	4
#define DIAGONALE_DROITE		5

#define ETAT_ATTENDS			100
#define ETAT_MONTE				102

//-----------------------------------------------------------------------------
//		Définition de la classe EnnemiSmurfSauvage
//-----------------------------------------------------------------------------

class EnnemiSmurfSauvage : public Ennemi
{
public:
	int shoot_direction ; // direction dans laquelle on pointe l'arme
	int hauteur ;
	int pente ;		  // coefficient directeur de la droite
	// passant par tete_turc et le smurfSauvage
	int num_pic ;
	int etape_shoot ;
	int nb_shoot ;

	static int	wait_shoot;
	static int	etape_wait;

	bool first_loop;
	bool mort ;
	bool position;

	int ss_etape_angle;
	int angle;
	bool sensAngle;

	bool shooting;

	Sprite *	cible;

	EnnemiSmurfSauvage();

	inline virtual void affiche()
	{
		draw(x, y - 50, pbk_ennemis[117]) ;
		draw(x, y - 100, pbk_ennemis[117]) ;
		draw(x, y - 150, pbk_ennemis[117]) ;
		draw(x, y - 200, pbk_ennemis[117]) ;
		draw(x, y - 250, pbk_ennemis[117]) ;

		Ennemi::affiche() ;

		// Si on est pas mort, on affiche l'arme suivant la direction du tir
		if (pv > 0) {
			if (shooting) {
				switch (shoot_direction) {
					case DIAGONALE_GAUCHE :
						draw(x + 8, y + 38, pbk_ennemis[137 + etape]) ;
						break ;
					case DIAGONALE_BAS_GAUCHE :
						draw(x + 8, y + 38, pbk_ennemis[133 + etape]) ;
						break ;
					case BAS_GAUCHE :
						draw(x + 8, y + 38, pbk_ennemis[129 + etape]) ;
						break ;
					case BAS_DROITE :
						draw(x - 5, y + 38, pbk_ennemis[127 + etape]) ;
						break ;
					case DIAGONALE_BAS_DROITE :
						draw(x - 5, y + 38, pbk_ennemis[131 + etape]) ;
						break ;
					case DIAGONALE_DROITE :
						draw(x - 5, y + 38, pbk_ennemis[135 + etape]) ;
						break ;
				}
			} else {
				switch (shoot_direction) {
					case DIAGONALE_GAUCHE :
						draw(x + 8, y + 38, pbk_ennemis[352]) ;
						break ;
					case DIAGONALE_BAS_GAUCHE :
						draw(x + 8, y + 38, pbk_ennemis[350]) ;
						break ;
					case BAS_GAUCHE :
						draw(x + 8, y + 38, pbk_ennemis[354]) ;
						break ;
					case BAS_DROITE :
						draw(x - 5, y + 38, pbk_ennemis[353]) ;
						break ;
					case DIAGONALE_BAS_DROITE :
						draw(x - 5, y + 38, pbk_ennemis[349]) ;
						break ;
					case DIAGONALE_DROITE :
						draw(x - 5, y + 38, pbk_ennemis[351]) ;
						break ;
				}
			}
		}
	}

	virtual void update();
	virtual void onTombe() ;
	virtual void onTire() ;
	virtual void onMeure();
	virtual void onCarbonise();
	virtual void estTouche(Tir * tir);
};

#endif
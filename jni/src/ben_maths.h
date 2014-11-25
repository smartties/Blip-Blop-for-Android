/******************************************************************
*
*
*		----------------
*		   BenMaths.h
*		----------------
*
*
*		Fonctions mathématiques précalculée
*		Gain approximatif : 2000 à 2500%
*
*		Cf. BenMaths.cpp pour plus d'infos
*
*		Prosper / LOADED -   V 0.1
*
*
*
******************************************************************/


#ifndef _BenMaths_
#define _BenMaths_

//-----------------------------------------------------------------------------
//		Constantes
//-----------------------------------------------------------------------------

#ifndef PI
#define	PI			3.141592654	// C'est PI, utilisé pour la conversion
#endif								// depgrés<->radians
#ifndef NULL
#define	NULL		0			// Well...
#endif

#define		COSINUS		10			// Pour l'utilisation de bCos[] et bSin[]
#define		PREC_COS	1			// Demande le précalcul des cosinus
#define		PREC_SIN	2			// Demande le précalcul des sinus
#define		PREC_ROOT	4			// Demande le précalcul des racines carrées
#define		PREC_ALL	0xFFFFFFFF	// Demande le précalcul de toutes les fonctions

//-----------------------------------------------------------------------------
//		Déclaration externe des tableaux
//-----------------------------------------------------------------------------

#ifndef BENMATHS_CPP_FILE
extern int *	bCos;
extern int *	bSin;
extern char *	bSqr;
#endif

//-----------------------------------------------------------------------------
//		Prototypes
//-----------------------------------------------------------------------------

void preCalcMathsFunctions();
void preCalcMathsFunctions(int f);
void preCalcMathsFunctions(int f, int nb);
void freeMathsFunctions();

#endif

/******************************************************************
*
*
*		----------------
*		  Fonte.h
*		----------------
*
*		Classe Fonte
*
*		Affiche du joli texte
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include "graphics.h"
#include <string.h>
#include <fstream>

///MODIF INCLUDE ENGINE
#include "Engine/io.h"

#include <fcntl.h>
#include <stdio.h>
#include "lgx_packer.h"
#include "ben_debug.h"
#include "fonte.h"


//-----------------------------------------------------------------------------

Fonte::Fonte() : pictab(NULL), nom_fic(NULL)
{
}


//-----------------------------------------------------------------------------

Fonte::~Fonte()
{
	if (pictab != NULL)
		debug << "Fonte non fermée!\n";
}


//-----------------------------------------------------------------------------

bool Fonte::load(const char * fic, int flags)
{
	SDL::Surface *	surf = NULL;

	int			taille;
	int			fhh;
	void *		ptr;

	if (pictab != NULL) {
		debug << "Fonte::load->Objet déjà ouvert!\n";
		return false;
	}

	LOGI("OPENING %s", fic);
	///MODIF read
	//fhh = _open(fic, _O_RDONLY | _O_BINARY);
	Parseur parseur;

	///MODIF fhh
	//if (fhh == -1) {
	if(parseur.open(fic) == false) {
		debug << "Fonte::load->Ne peut pas ouvrir " << fic << "\n";
		LOGI("fhh == -1");
		return false;
	}

	pictab = new Picture * [256];
	if (pictab == NULL) {
		debug << "Fonte::load->Pas assez de mémoire pour " << fic << "\n";
		///MODIF close fhh
		//_close(fhh);
		parseur.close();

		return false;
	}

	for (int i = 0; i < 256; i++)
		pictab[i] = NULL;

    ///MODIF read
	//_read(fhh, &h, sizeof(h));
	//_read(fhh, &spc, sizeof(spc));
	parseur.read(&h, sizeof(h));
	parseur.read(&spc, sizeof(spc));


	for (int i = 1; i < 256; i++) {

	    ///MODIF read
		//_read(fhh, &taille, sizeof(taille));
		parseur.read(&taille, sizeof(taille));

		if (taille == 0) {
			continue;
		}
		ptr = malloc(taille);

		if (ptr == NULL) {
			debug << "Fonte::load() - Impossible d'allouer " << taille << " octets \n";
			///MODIF close fhh
		    //_close(fhh);
		    parseur.close();

			for (int j = 0; j < i; j++)
				delete pictab[j];
			delete [] pictab;
			pictab = NULL;
			return false;
		}

        ///MODIF read
		//_read(fhh, ptr, taille);
		parseur.read(ptr, taille);

		surf = LGXpaker.loadLGX(ptr, flags);

		free(ptr);

		if (surf == NULL) {
			debug << "Pas assez de mémoire pour le " << i << " de " << fic << "\n";

			///MODIF close fhh
		    //_close(fhh);
		    parseur.close();
		    LOGI("NO MORE ERRETRETER %s", fic);

			for (int j = 0; j < i; j++)
				delete pictab[j];
			delete [] pictab;
			pictab = NULL;
			return false;
		}

		pictab[i] = new Picture;
		pictab[i]->SetSurface(surf);
		pictab[i]->SetSpot(0, 0);
//		pictab[i]->SetColorKey( RGB( 250, 212, 152));
		pictab[i]->SetColorKey(RGB( 246, 205, 148));
		//pictab[i]->SetColorKey(RGB(250, 206, 152));

		/*static int test_i = 1;
		char buf[128];
		sprintf(buf, "test/%d.bmp", test_i);
		SDL_SaveBMP(surf->Get(), buf);
		test_i++;*/

	}

	nom_fic = new char[strlen(fic) + 1];
	strcpy(nom_fic, fic);
	flag_fic = flags;

	///MODIF close fhh
    //_close(fhh);
    parseur.close();

	return true;
}

//-----------------------------------------------------------------------------

void Fonte::print(SDL::Surface * surf, int x, int y, const char * txt)
{
	if (txt == NULL)
		return;

	int		curx;	// X courant
	int		c;

	curx = x;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = (unsigned char) txt[i];
		if (c == ' ') {
			curx += spc;
		} else if (pictab[c] != NULL) {
			pictab[c]->BlitTo(surf, curx, y);
			curx += pictab[c]->xSize();
		}
	}
}


//-----------------------------------------------------------------------------

void Fonte::printM(SDL::Surface * surf, int x, int y, const char * txt, int ym)
{
	if (txt == NULL)
		return;

	int		curx;	// X courant
	int		cury;	// Y courant
	int		nx;		// Next x (pour ne pas le calculer 2 fois)
	unsigned int		c;

	curx = x;
	cury = y;


	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = (unsigned char) txt[i];

		if (c == ' ') {
			curx += spc;
		} else if (pictab[c] != NULL) {
			// Calcul du X suivant
			nx = curx + pictab[c]->xSize();

			// Ligne suivante ?
			if (nx >= ym) {
				cury += h;
				pictab[c]->BlitTo(surf, x, cury);
				curx = x + pictab[c]->xSize();
			} else {	// Non, on continue..
				pictab[c]->BlitTo(surf, curx, cury);
				curx = nx;
			}
		}
	}
}


//-----------------------------------------------------------------------------

void Fonte::printR(SDL::Surface * surf, int x, int y, const char * txt)
{
	if (txt == NULL)
		return;

	int		l = 0;	// Longueur en pixels de la chaîne
	int		c;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = (unsigned char) txt[i];

		if (c == ' ')
			l += spc;
		else if (pictab[c] != NULL)
			l += pictab[c]->xSize();
	}

	print(surf, x - l, y, txt);
}


//-----------------------------------------------------------------------------

void Fonte::printC(SDL::Surface * surf, int xtaille, int y, const char * txt)
{
	debug << "Fonte::printC("<<txt<<")" <<"\n";
	if (txt == NULL)
		return;

	int		l = 0;	// Longueur en pixels de la chaîne
	int		c;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = (unsigned char) txt[i];

		if (c == ' ')
			l += spc;
		else if (pictab[c] != NULL)
			l += pictab[c]->xSize();
	}
	//LOGI("printc %d, %s", xtaille - (l >> 1), txt);
	print(surf, xtaille - (l >> 1), y, txt);
}


//-----------------------------------------------------------------------------

void Fonte::close()
{
	if (pictab == NULL)
		return;

	// Ferme les PICs et détruit les trucs dynamiques...
	for (int i = 0; i < 256; i++) {
		if (pictab[i] != 0) {
			pictab[i]->Close();
			delete pictab[i];
			pictab[i] = NULL;
		}
	}

	if (pictab != NULL) {
		delete [] pictab;
		pictab = NULL;
	}

	if (nom_fic != NULL) {
		delete [] nom_fic;
		nom_fic = NULL;
	}
}



//-----------------------------------------------------------------------------

void Fonte::printMW(SDL::Surface * surf, int x, int y, const char * srctxt, int ym)
{
	static const char delim [] = " ";

	if (srctxt == NULL)
		return;

	int		curx;	// X courant
	int		cury;	// Y courant
	int		nx;		// Next x (pour ne pas le calculer 2 fois)

	curx = x;
	cury = y;

	char * txt = new char[strlen(srctxt) + 1];
	char * token;

	strcpy(txt, srctxt);
	token = strtok(txt, delim);

	while (token != NULL) {
		nx = width(token);

		if (curx + nx > ym) {
			cury += h;
			print(surf, x, cury, token);
			curx = x + nx;
		} else {
			print(surf, curx, cury, token);
			curx += nx;
		}

		curx += spc;

		token = strtok(NULL, delim);
	}
}


//-----------------------------------------------------------------------------

int Fonte::width(const char * txt)
{
	if (txt == NULL)
		return 0;

	int		l = 0;	// Longueur en pixels de la chaîne
	int		c;

	for (unsigned int i = 0; i < strlen(txt); i++) {
		c = (unsigned char) txt[i];

		if (c == ' ')
			l += spc;
		else if (pictab[c] != NULL)
			l += pictab[c]->xSize();
	}

	return l;
}

//-----------------------------------------------------------------------------

bool Fonte::restoreAll()
{
	if (nom_fic == NULL)
		return true;

	SDL::Surface *	surf;

	int			taille;
	int			fhh;
	void *		ptr;
	Parseur parseur;

    ///MODIF open
	//fhh = _open(nom_fic, _O_RDONLY | _O_BINARY);

    ///MODIF open
	//if (fhh == -1) {
	if(parseur.open(nom_fic) == false) {
		debug << "Fonte::restoreAll()->Ne peut pas ouvrir " << nom_fic << "\n";
		return false;
	}

    ///MODIF read
	//_read(fhh, &h, sizeof(h));
	//_read(fhh, &spc, sizeof(spc));
	parseur.read(&h, sizeof(h));
	parseur.read(&spc, sizeof(spc));


	for (int i = 1; i < 256; i++) {
	    ///MODIF read
		//_read(fhh, &taille, sizeof(taille));
		parseur.read(&taille, sizeof(taille));

		if (taille == 0) {
			continue;
		}

		ptr = malloc(taille);

		if (ptr == NULL) {
			debug << "Fonte::restoreAll() - Impossible d'allouer " << taille << " octets \n";
			///MODIF close
			//_close(fhh);
			parseur.close();
			for (int j = 0; j < i; j++)
				delete pictab[j];
			delete [] pictab;
			pictab = NULL;
			return false;
		}

		///MODIF read
		//_read(fhh, ptr, taille);
		parseur.read(ptr, taille);


		surf = LGXpaker.loadLGX(ptr, flag_fic);

		free(ptr);

		if (surf == NULL) {
			debug << "Pas assez de mémoire pour le " << i << " de " << nom_fic << "\n";
			///MODIF close
			//_close(fhh);
			parseur.close();
			for (int j = 0; j < i; j++)
				delete pictab[j];
			delete [] pictab;
			pictab = NULL;
			return false;
		}

		pictab[i]->SetSurface(surf);
		pictab[i]->SetSpot(0, 0);
		pictab[i]->SetColorKey(RGB(250, 206, 152));
	}

	///MODIF close
	//_close(fhh);
	parseur.close();
	return true;
}

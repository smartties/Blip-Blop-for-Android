/******************************************************************
*
*
*		------------------
*		  PictureBank.cpp
*		------------------
*
*		Classe PictureBank
*
*		Représente un tableau/une banque d'images.
*
*
*		Prosper / LOADED -   V 0.2 - 13 Juillet 2000
*
*
*
******************************************************************/


//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
///MODIF INCLUDE ENGINE
#include "Engine/io.h"
#include <fcntl.h>
#include "dd_gfx.h"
#include "picture_bank.h"
#include "lgx_packer.h"
#include "ben_debug.h"


//-----------------------------------------------------------------------------
//		PictureBank::PictureBank() - met le pointeur à NULL et NB à 0
//-----------------------------------------------------------------------------

PictureBank::PictureBank() : tab(NULL), nb_pic(0), nom_fic(NULL), flag_fic(0)
{
}

//-----------------------------------------------------------------------------
//		PictureBank::~PictureBank()
//-----------------------------------------------------------------------------

PictureBank::~PictureBank()
{
	if (tab != NULL)
		debug << "PictureBank non désallouée\n";

	if (nom_fic != NULL) {
		delete [] nom_fic;
		nom_fic = NULL;
	}
}

//-----------------------------------------------------------------------------
//		PictureBank::loadGFX() - charge un fichier GFX pour créer la banque
//-----------------------------------------------------------------------------

bool PictureBank::loadGFX(const char * file, int flag, bool trans)
{
	SDL::Surface *	surf;
	int			fic;
	int			xspot;
	int			yspot;
	int			taille;
	int			version;
	void *		ptr;

    ///MODIF open
	//fic = _open(file, _O_BINARY | _O_RDONLY);
	Parseur parseur;

	///MODIF open
	//if (fic == -1) {
	if( parseur.open(file) == false ) {

	    LOGI("no such file : %s", file);
		debug << "PictureBank::loadGFX() - Impossible de charger le fichier " << file << "\n";
		return false;
	}

    ///MODIF read
	//_read(fic, &nb_pic, sizeof(nb_pic));
	parseur.read(&nb_pic, sizeof(nb_pic));

	tab = new Picture * [nb_pic];
	LOGI("nb pic %d", nb_pic);
	if (tab == NULL) {
		debug << "PictureBank::loadGFX() - Nani? Pas assez de mémoire ???\n";
		LOGI("Pas assez de mémoire");
		///MODIF close
		//_close(fic);
		parseur.close();
		return false;
	}

	for (int i = 0; i < nb_pic; i++) {

	    ///MODIF read
		//_read(fic, &xspot, sizeof(xspot));	// Coordonnées du point chaud
		//_read(fic, &yspot, sizeof(yspot));
		//_read(fic, &taille, sizeof(taille));
		parseur.read(&xspot, sizeof(xspot));
		parseur.read(&yspot, sizeof(yspot));
		parseur.read(&taille, sizeof(taille));

		ptr = malloc(taille);

		if (ptr == NULL) {
			debug << "PictureBank::loadGFX() - Impossible d'allouer " << taille << " octets \n";
			///MODIF close
			//_close(fic);
			parseur.close();
			for (int j = 0; j < i; j++)
				delete tab[j];
			delete [] tab;
			tab = NULL;
			return false;
		}

        ///MODIF read
		//_read(fic, ptr, taille);
		parseur.read(ptr, taille);
		surf = LGXpaker.loadLGX(ptr, flag, &version);


		free(ptr);


		if (surf == NULL) {
			debug << "PictureBank::loadGFX() - surface à NULL\n";
			LOGI("no surface");
			return false;
		}

		tab[i] = new Picture();

		tab[i]->SetSpot(xspot, yspot);
		tab[i]->SetSurface(surf);

		if (trans) {
			if (version == 1)
			{
				tab[i]->SetColorKey(RGB(246, 205, 148));
			}
			else
			{
				tab[i]->SetColorKey(RGB(246, 210, 148));
			}
		}
	}

	if (nom_fic != NULL)
		delete [] nom_fic;

	nom_fic = new char[strlen(file) + 1];

	strcpy(nom_fic, file);
	flag_fic = flag;
	trans_fic = trans;
	///MODIF close
	//_close(fic);
	parseur.close();
	LOGI("succes");
	return true;
}

void PictureBank::close()
{
	if (nb_pic != 0 && tab != NULL) {
		for (int i = 0; i < nb_pic; i++) {
			tab[i]->Close();
			delete tab[i];
		}

		delete [] tab;
		tab = NULL;
		nb_pic = 0;
	}

	if (nom_fic != NULL) {
		delete [] nom_fic;
		nom_fic = NULL;
	}
}




bool PictureBank::restoreAll()
{
	if (nom_fic != NULL) {
		SDL::Surface *	surf;
		int			fic;
		int			xspot;
		int			yspot;
		int			taille;
		int			version;
		void *		ptr;

        ///MODIF open
		//fic = _open(nom_fic, _O_BINARY | _O_RDONLY);
		Parseur parseur;

		///MODIF open
		//if (fic == -1) {
		if( parseur.open(nom_fic) == false ) {
			debug << "PictureBank::restoreAll() - Impossible de charger le fichier " << nom_fic << "\n";
			return false;
		}

		///MODIF read
		//_read(fic, &nb_pic, sizeof(nb_pic));
		parseur.read(&nb_pic, sizeof(nb_pic));

		for (int i = 0; i < nb_pic; i++) {
			// Libère l'ancienne surface
			//
			surf = tab[i]->Surf();
			surf->Release();

			///MODIF read
			//_read(fic, &xspot, sizeof(xspot));	// Coordonnées du point chaud
			//_read(fic, &yspot, sizeof(yspot));
			//_read(fic, &taille, sizeof(taille));
			parseur.read(&xspot, sizeof(xspot));
			parseur.read(&yspot, sizeof(yspot));
			parseur.read(&taille, sizeof(taille));

			ptr = malloc(taille);

			if (ptr == NULL) {
				debug << "PictureBank::restoreAll() - Impossible d'allouer " << taille << " octets \n";
				///MODIF close
				//_close(fic);
				parseur.close();
				for (int j = 0; j < i; j++)
					delete tab[j];
				delete [] tab;
				tab = NULL;
				return false;
			}

            ///MODIF read
			//_read(fic, ptr, taille);
			parseur.read(ptr, taille);
			surf = LGXpaker.loadLGX(ptr, flag_fic, &version);


			free(ptr);


			if (surf == NULL) {
				debug << "PictureBank::restoreAll() - surface à NULL\n";
				///MODIF close
				//_close(fic);
				parseur.close();
				return false;
			}

			tab[i]->SetSpot(xspot, yspot);
			tab[i]->SetSurface(surf);

			if (trans_fic) {
				if (version == 1)
					tab[i]->SetColorKey(RGB(250, 206, 152));
				else
					tab[i]->SetColorKey(RGB(250, 214, 152));
			}
		}

		///MODIF close
		//_close(fic);
		parseur.close();
	}

	return true;
}

/******************************************************************
*
*
*		----------------
*		  LGXpacker.cpp
*		----------------
*
*		Classe LGXpacker
*
*		La classe LGXpacker permet de charger
*		et de lire des images LGX.
*
*		! ATTENTION !
*		Le LGX ne fonctionne qu'en mode 16 bits!!!
*
*
*
*		Prosper / LOADED -   V 0.1 - 23 Juin 2000
*
*
*
******************************************************************/

//-----------------------------------------------------------------------------
//		Protection pour ne pas déclarer 'ddraw' 2 fois (une fois dans le .h)
//-----------------------------------------------------------------------------

#define LGXPACKER_CPP_FILE

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <fcntl.h>
///MODIF INCLUDE ENGINE
#include "Engine/io.h"

#include <stdio.h>
#include "ben_debug.h"
#include "dd_gfx.h"
#include "lgx_packer.h"

//-----------------------------------------------------------------------------
//		Objet 'LGXpaker' global REEL
//-----------------------------------------------------------------------------

LGXpacker	LGXpaker;

//-----------------------------------------------------------------------------
//		LGXpacker::LGXpacker() - met les pointeurs à NULL
//-----------------------------------------------------------------------------

LGXpacker::LGXpacker() : tab_0(NULL), tab_1(NULL), half_tone(NULL)
{
}

//-----------------------------------------------------------------------------
//		LGXpacker::~LGXpacker()
//-----------------------------------------------------------------------------

LGXpacker::~LGXpacker()
{
	if (tab_0 != NULL || tab_1 != NULL || half_tone != NULL) {
		debug << "LGXpacker non désaloué\n";
		closePaker();
	}
}

//-----------------------------------------------------------------------------
//		LGXpacker::init() - récupère les capacités de la carte graphique
//-----------------------------------------------------------------------------

bool LGXpacker::init(SDL::Surface * surf)
{
	int		mask;
	int		cpt;

	// On vérifie qu'on nous envoit pas n'importe quoi

	if (surf == NULL) {
		debug << "LGXpacker::init() / Surface nulle!\n";
		return false;
	}

	// On veut le format des pixels de la surface

	SDL::PixelFormat pf;

	if (surf->GetPixelFormat(&pf) == false) {
		debug << "LGXpacker::init() / ne peut pas obtenir le PIXELFORMAT\n";
		return false;
	}

	// Maintenant, on va décortiquer tout ça pour avoir des infos pratiques

	if (pf.dwRBitMask == 0 || pf.dwGBitMask == 0 || pf.dwBBitMask == 0) {
		debug << "LGXpacker::init() / Masques RGB à 0\n";
		return false;
	}


	// D'abord le rouge (R)

	mask = rMask = pf.dwRBitMask;
	cpt = 0;

	while ((mask & 1) == 0) {
		mask = mask >> 1;
		cpt++;
	}

	rDecal = cpt;
	rMax = mask;


	// Now le vert (G)

	mask = gMask = pf.dwGBitMask;
	cpt = 0;

	while ((mask & 1) == 0) {
		mask = mask >> 1;
		cpt++;
	}

	gDecal = cpt;
	gMax = mask;


	// Enfin le bleu (B)

	mask = bMask = pf.dwBBitMask;
	cpt = 0;

	while ((mask & 1) == 0) {
		mask = mask >> 1;
		cpt++;
	}

	bDecal = cpt;
	bMax = mask;


	// On précalcule les conversions des 65536 valeurs possibles
	// pour accélerer la décompression (putain ça c'est de l'optimisation! :)

	//
	// ************************ VERSION 0 ****************************
	//

	tab_0 = new unsigned long[0x10000];
	if (tab_0 == NULL) {
		debug << "Impossible d'allouer la mémoire de décompression\n";
		return false;
	}



	for (int r = 0; r <= LGX_RMAX_0; r++)
		for (int g = 0; g <= LGX_GMAX_0; g++)
			for (int b = 0; b <= LGX_BMAX_0; b++) {
				cpt = (r << LGX_RDECAL_0) | (g << LGX_GDECAL_0) | (b << LGX_BDECAL_0);

				tab_0[cpt] = (((r * rMax) / LGX_RMAX_0) << rDecal) |
				             (((g * gMax) / LGX_GMAX_0) << gDecal) |
				             (((b * bMax) / LGX_BMAX_0) << bDecal) |
							 pf.dwABitMask;	//Alpha fix
			}


	//
	// ************************ VERSION 1 ****************************
	//

	tab_1 = new unsigned long[0x8000];
	if (tab_1 == NULL) {
		debug << "Impossible d'allouer la mémoire de décompression\n";
		delete [] tab_0;
		tab_0 = NULL;
		return false;
	}



	for (int r = 0; r <= LGX_RMAX_1; r++)
		for (int g = 0; g <= LGX_GMAX_1; g++)
			for (int b = 0; b <= LGX_BMAX_1; b++) {
				cpt = (r << LGX_RDECAL_1) | (g << LGX_GDECAL_1) | (b << LGX_BDECAL_1);

				tab_1[cpt] = (((r * rMax) / LGX_RMAX_1) << rDecal) |
				             (((g * gMax) / LGX_GMAX_1) << gDecal) |
							 (((b * bMax) / LGX_BMAX_1) << bDecal) |
							 pf.dwABitMask;	//Alpha fix;
			}

	//
	// ************************ HALF TONE ****************************
	//
	half_tone = new unsigned short[0x10000];
	if (half_tone == NULL) {
		debug << "Impossible d'allouer la mémoire HALF TONE\n";
		delete [] tab_0;
		tab_0 = NULL;
		delete [] tab_1;
		tab_1 = NULL;
		return false;
	}

	int		r;
	int		g;
	int		b;

	for (int i = 0; i <= 0xFFFF; i++) {
		r = i & rMask;
		g = i & gMask;
		b = i & bMask;

		r = (r >> 1) & rMask;
		g = (g >> 1) & gMask;
		b = (b >> 1) & bMask;

		half_tone[i] = r | g | b;
	}

	return true;
}

//-----------------------------------------------------------------------------
//		LGXpacker::closePaker() - libère la mémoire utilisée
//-----------------------------------------------------------------------------

void LGXpacker::closePaker()
{
	if (tab_0 != NULL) {
		delete [] tab_0;
		tab_0 = NULL;
	}

	if (tab_1 != NULL) {
		delete [] tab_1;
		tab_1 = NULL;
	}

	if (half_tone != NULL) {
		delete [] half_tone;
		half_tone = NULL;
	}
}

//-----------------------------------------------------------------------------
// LGXpaker::createLGX_0()
//-----------------------------------------------------------------------------

bool LGXpacker::createLGX_0(HDC hdc, const char * fic, int xs, int ys)
{
	void *	ptr;
	FILE *	f;
	int		taille;

	LOGI("LGXPacker");

	if ((taille = createLGX_0(hdc, xs, ys, ptr)) == 0 || ptr == NULL)
		return false;

	if ((f = fopen(fic, "wb")) == NULL) {
		return false;
	}

	fwrite(ptr, 1, taille, f);
	fclose(f);

	free(ptr);

	return true;
}

//-----------------------------------------------------------------------------
// LGXpaker::createLGX_1()
//-----------------------------------------------------------------------------

bool LGXpacker::createLGX_1(HDC hdc, const char * fic, int xs, int ys)
{
	void *	ptr;
	FILE *	f;
	int		taille;

	LOGI("LGXPacker");

	if ((taille = createLGX_1(hdc, xs, ys, ptr)) == 0 || ptr == NULL)
		return false;

	if ((f = fopen(fic, "wb")) == NULL) {
		return false;
	}

	fwrite(ptr, 1, taille, f);
	fclose(f);

	free(ptr);

	return true;
}


//-----------------------------------------------------------------------------
// LGXpaker::createLGX_0()
//-----------------------------------------------------------------------------

int LGXpacker::createLGX_0(HDC hdc, int xs, int ys, void * & ptr)
{
	unsigned int	pixval;
	int				rval;
	int				gval;
	int				bval;

	unsigned char*	ptrd;	// Pointeur sur les données
	LGX_HEADER *	lh;
	int				taille = xs * ys * 2 + sizeof(LGX_HEADER);

	ptr = malloc(taille);
	if (ptr == NULL) {
		return 0;
	}

	lh = (LGX_HEADER *) ptr;

	lh->id[0] = 'L';
	lh->id[1] = 'G';
	lh->id[2] = 'X';
	lh->version = 0;
	lh->xsize = xs;
	lh->ysize = ys;
	lh->depth = 16;

	ptrd = (unsigned char*)ptr + sizeof(LGX_HEADER);

	// Remarque : bizarrement, les couleurs sont données dans l'ordre BGR
	// et pas RGB, bien que ce ne soit pas le cas de D3D (???)

	int		x = 0;
	int		y = 0;

	taille = 0; // Now, taille va valoir la taille effective du fichier

	while (y < ys) {
		pixval = GetPixel(hdc, x, y);


		// On convertit la valeur RGB au format LGX

		rval = ((pixval & 0xFF) * LGX_RMAX_0) / 0xFF;
		gval = (((pixval >> 8) & 0xFF) * LGX_GMAX_0) / 0xFF;
		bval = (((pixval >> 16) & 0xFF) * LGX_BMAX_0) / 0xFF;


		taille++;		// 1 mot inscrit


		*((unsigned short*)ptrd) = (unsigned short)((rval << LGX_RDECAL_0) | (gval << LGX_GDECAL_0) | (bval << LGX_BDECAL_0));
		ptrd += 2;

		x++;

		if (x == xs) {
			x = 0;
			y++;
		}

	}

	return ((taille << 1) + sizeof(LGX_HEADER)); // Il faut * taille par 2 car on a compté les mots
}

//-----------------------------------------------------------------------------
// LGXpaker::createLGX_1()
//-----------------------------------------------------------------------------

int LGXpacker::createLGX_1(HDC hdc, int xs, int ys, void * & ptr)
{
	unsigned int	pixval;
	unsigned short	LGXpixval;
	unsigned short	LGXpixval2;
	int				rval;
	int				gval;
	int				bval;

	unsigned char*	ptrd;	// Pointeur sur les données
	LGX_HEADER *	lh;
	int				taille = xs * ys * 2 + sizeof(LGX_HEADER);

	ptr = malloc(taille);
	if (ptr == NULL) {
		return 0;
	}

	lh = (LGX_HEADER *) ptr;

	lh->id[0] = 'L';
	lh->id[1] = 'G';
	lh->id[2] = 'X';
	lh->version = 1;
	lh->xsize = xs;
	lh->ysize = ys;
	lh->depth = 16;

	ptrd = (unsigned char*)ptr + sizeof(LGX_HEADER);

	// Remarque : bizarrement, les couleurs sont données dans l'ordre BGR
	// et pas RGB, bien que ce ne soit pas le cas de D3D (???)

	int		x = 0;
	int		y = 0;
	unsigned short		cpt;

	taille = 0; // Now, taille va valoir la taille effective du fichier

	while (y < ys) {
		pixval = GetPixel(hdc, x, y);

		rval = ((pixval & 0xFF) * LGX_RMAX_1) / 0xFF;
		gval = (((pixval >> 8) & 0xFF) * LGX_GMAX_1) / 0xFF;
		bval = (((pixval >> 16) & 0xFF) * LGX_BMAX_1) / 0xFF;

		LGXpixval = (unsigned short)((rval << LGX_RDECAL_1) | (gval << LGX_GDECAL_1) | (bval << LGX_BDECAL_1));

		cpt = 0;

		do {

			x++;

			if (x == xs) {
				x = 0;
				y++;
			}

			cpt++;

			pixval = GetPixel(hdc, x, y);

			rval = ((pixval & 0xFF) * LGX_RMAX_1) / 0xFF;
			gval = (((pixval >> 8) & 0xFF) * LGX_GMAX_1) / 0xFF;
			bval = (((pixval >> 16) & 0xFF) * LGX_BMAX_1) / 0xFF;

			LGXpixval2 = (unsigned short)((rval << LGX_RDECAL_1) | (gval << LGX_GDECAL_1) | (bval << LGX_BDECAL_1));


		} while (y < ys && LGXpixval == LGXpixval2 && cpt < 0x7FFF);




		if (cpt >= 2) {
			*((unsigned short*)ptrd) = (unsigned short)((unsigned short)0x8000 | cpt);
			ptrd += 2;
			taille += 2;	// 2 mots inscrits
		} else {
			taille++;		// 1 mot inscrit
		}


		// Dans tous les cas on fait ça...
		*((unsigned short*)ptrd) = LGXpixval;
		ptrd += 2;


	}

	return ((taille << 1) + sizeof(LGX_HEADER)); // Il faut * taille par 2 car on a compté les mots
}



//-----------------------------------------------------------------------------
//		LGXpacker::loadLGX() - charge un fichier LGX à partir de l'emplacement
//							   mémoire précisé
//-----------------------------------------------------------------------------

SDL::Surface * LGXpacker::loadLGX(void * ptr, int flags, int * version)
{
	if (tab_0 == NULL || tab_1 == NULL) {
		debug << "LGXpaker::loadLGX() - LGXpaker non initialisé!\n";
		return NULL;
	}

	SDL::Surface *	surf;

	LGX_HEADER *	lh = (LGX_HEADER *) ptr;


	// On vérifie qu'il s'agit bien d'un fichier LGX

	if (lh->id[0] != 'L' || lh->id[1] != 'G' || lh->id[2] != 'X') {
		debug << "LGXpacker::LoadLGX() / Format de fichier erroné!\n";
		return NULL;
	}

	int		xs = lh->xsize;
	int		ys = lh->ysize;

	// On crée la surface correspondante

	surf = DDCreateSurface(xs, ys, flags);
	if (surf == NULL) {
		debug << "LGXpacker::LoadLGX() / Ne peut pas créer la surface\n";
		return NULL;
	}


	// Maintenant on veut l'adresse de la surface

	SDL::SurfaceInfo	ddsd;

	if (surf->Lock(NULL, &ddsd, DDLOCK_WAIT | DDLOCK_WRITEONLY | DDLOCK_SURFACEMEMORYPTR, NULL) != DD_OK) {
		debug << "LGXpacker::LoadLGX() / Impossible d'obtenir l'adresse de la surface\n";
		return surf;
	}


	// data pointe sur les données du fichier (après le header)
	unsigned short * data = (unsigned short *)((char *) ptr + sizeof(LGX_HEADER));

	int				i;
	unsigned long	col;
	unsigned short	d;

	int				dpitch = ddsd.lPitch - 2 * xs;

	if (version != NULL)
		*version = lh->version;

	//
	// ************************ VERSION 0 ****************************
	//
	if (lh->version == 0) {
		if (dpitch != 0) {
			unsigned char * surfPtr = (unsigned char*) ddsd.lpSurface;

			int				x = 0;
			int				y = 0;

			while (y < ys) {
				d = *(data++);

				*((unsigned long*)surfPtr) = tab_0[d];

				surfPtr += 4;
				x++;

				if (x == xs) {
					x = 0;
					y++;
					//surfPtr += dpitch;
				}
			}
		} else { // dpitch=0! cool! :)
			unsigned short * surfPtr = (unsigned short*) ddsd.lpSurface;

			int		t = xs * ys;
			int		delta = 0;

			while (delta < t) {
				d = *(data++);
				surfPtr[delta++] = tab_0[d];
			}
		}
	}
	//
	// ************************ VERSION 1 ****************************
	//
	else if (lh->version == 1) {
		if (dpitch != 0) {
			unsigned char * surfPtr = (unsigned char*) ddsd.lpSurface;

			int				x = 0;
			int				y = 0;

			while (y < ys) {
				d = *(data++);


				if (d & 0x8000) {
					col = tab_1[*(data++)];


					for (i = 0; i < (d & 0x7FFF); i++) {
						*((unsigned long*)surfPtr) = col;

						surfPtr += 4;
						x++;

						if (x == xs) {
							x = 0;
							y++;
							//surfPtr += dpitch;
						}
					}
				} else {
					*((unsigned long*)surfPtr) = tab_1[d];

					surfPtr += 4;
					x++;

					if (x == xs) {
						x = 0;
						y++;
						//surfPtr += dpitch;
					}
				}
			}
		} else { // dptich=0! cool! :)
			unsigned long * surfPtr = (unsigned long*) ddsd.lpSurface;

			int		t = xs * ys;
			int		delta = 0;

			while (delta < t) {
				d = *(data++);

				if (d & 0x8000) {
					col = tab_1[*(data++)];

					for (i = 0; i < (d & 0x7FFF); i++)
						surfPtr[delta++] = col;
				} else
					surfPtr[delta++] = tab_1[d];

			}
		}
	}
	surf->Unlock(NULL);


	static int counter = 0;
	char buf[128];
	sprintf(buf, "test/%d.bmp",counter);
	/*if (counter >200&&counter<250)
		SDL_SaveBMP(surf->Get(), buf);*/

	counter++;

	return surf;


}


//-----------------------------------------------------------------------------
//		LGXpacker::loadLGX() - charge une image LGX à partir d'un fichier
//-----------------------------------------------------------------------------

SDL::Surface * LGXpacker::loadLGX(const char * fic, int flags)
{
	if (tab_0 == NULL || tab_1 == NULL) {
		debug << "LGXpaker::loadLGX() - LGXpaker non initialisé!\n";
		return NULL;
	}

	SDL::Surface *	surf;
	int		fhh;
	int		taille;
	Parseur parseur;

	///MODIF open fhh
	//if ((fhh = _open(fic, _O_BINARY | _O_RDONLY)) == -1) {
	if(parseur.open(fic) == false) {
		debug << "LGXpacker::loadLGX() / Ne peut pas ouvrir le fichier " << fic << "\n";
		return NULL;
	}
	///MODIF taille
	//taille = _filelength(fhh);
	taille = parseur.length;


	void * ptr = malloc(taille);

	if (ptr == NULL) {
		debug << "LGXpaker::loadLGX() -> Mémoire insuffisante - (" << taille << ")\n";
		///MODIF fhh
		//_close(fhh);
		parseur.close();
		return NULL;
	}

	///MODIF read
	//_read(fhh, ptr, taille);
	//_close(fhh);
	parseur.read(ptr, taille);
	parseur.close();

	surf = loadLGX(ptr, flags);

	return surf;

}

//-----------------------------------------------------------------------------
// LGXpaker::fincColor()
//-----------------------------------------------------------------------------

int LGXpacker::findColor(COLORREF rgb)
{
	int red =  rgb & 0x000000FF;
	int gre = (rgb & 0x0000FF00) >> 8;
	int ble = (rgb & 0x00FF0000) >> 16;

//	debug<<red<<" "<<gre<<" "<<ble<<"\n";

	red = ((float(red) * float(rMax)) / float(0xFF));
	gre = (gre * gMax) / 0xFF;
	ble = (ble * bMax) / 0xFF;

//	debug<<red<<" "<<gre<<" "<<ble<<"\n";

//	char buff[29];

	int end = (red << rDecal) | (gre << gDecal) | (ble << bDecal);
	/*
		sprintf( buff, "%X", end);
		debug<<buff<<"\n";
	*/
	return (end);
}


//-----------------------------------------------------------------------------
// LGXpaker::halfTone()
//-----------------------------------------------------------------------------

void LGXpacker::halfTone(SDL::Surface * surf, RECT * r)
{
	SDL::SurfaceInfo ddsd;

	if (surf->Lock(r, &ddsd, DDLOCK_SURFACEMEMORYPTR, NULL) == false)
		return;

	unsigned long * ptr = (unsigned long*)ddsd.lpSurface;
	for (int i = 0; i < (surf->Get()->w*surf->Get()->h); i++)
	{
		(*ptr) = 0xFF000000 | ((*ptr) & 0xFF) >> 1 | ((((*ptr) & 0xFF00) >> 1) & 0xFF00) | ((((*ptr) & 0xFF0000) >> 1) & 0xFF0000);
		ptr++;
	}


	surf->Unlock(r);
}

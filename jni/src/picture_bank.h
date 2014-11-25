/******************************************************************
*
*
*		------------------
*		  PictureBank.h
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
#ifndef _PictureBank_
#define _PictureBank_

#include "picture.h"
#include "asset.h"

//-----------------------------------------------------------------------------
//		Définition de la classe PictureBank
//-----------------------------------------------------------------------------

class PictureBank
{
private:
	Picture **	tab;
	int			nb_pic;
	char *		nom_fic;
	int			flag_fic;
	bool		trans_fic;

public:
	inline Picture * operator [](int n) const
	{
		return tab[n];
	};
	inline Picture ** getPix() const
	{
		return tab;
	};
	inline int getSize() const
	{
		return nb_pic;
	};


	PictureBank();
	~PictureBank();
	bool loadGFX(const char * file, int flag = DDSURF_BEST, bool trans = true);
	bool restoreAll();
	void close();
};


#endif

/******************************************************************
*
*
*		-----------------
*		   TexteCool.h
*		-----------------
*
*		Pour les textes "tetra tuerie"
*
*
*		Prosper / LOADED -   V 0.1 - 17 Aout 2000
*
*
*
******************************************************************/

#ifndef _TexteCool_
#define _TexteCool_

#ifndef TEXTE_COOL_CPP
extern bool txt_cool_free[];
#endif

class TexteCool
{
public:
	int		y;
	int		nn;
	int		ntxt;
	int		x;
	int		t;

	TexteCool();

	void update();
	void affiche();

	bool aDetruire()
	{
		return x <= -320;
	};
};

void clearTexteCool();

#endif



/******************************************************************
*
*
*		---------------
*		  GenEnnemi.h
*		---------------
*
*		Classe Générateur ennemi
*
*
*		Prosper / LOADED -   5 Aout 2000
*
*
*
******************************************************************/

#ifndef _GenEnnemi_
#define _GenEnnemi_


class GenEnnemi
{
public:
	int		id_ennemi;
	int		sens;
	int		x;
	int		y;
	int		periode;
	int		capacite;
	int		t;
	bool	a_detruire;

	GenEnnemi();

	virtual void update();

	inline virtual bool aDetruire()
	{
		return a_detruire;
	};
};

#endif
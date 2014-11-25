/******************************************************************
*
*
*		---------------
*		  GenBonus.h
*		---------------
*
*
*		Prosper / LOADED -   5 Aout 2000
*
*
*
******************************************************************/

#ifndef _GenBonus_
#define _GenBonus_


class GenBonus
{
public:
	int		x;
	int		periode;
	int		t;
	int		type;
	bool	a_detruire;

	GenBonus();

	virtual void update();

	inline virtual bool aDetruire()
	{
		return a_detruire;
	};
};

#endif
/******************************************************************
*
*
*		----------------
*		  Controlor.h
*		----------------
*
*		Classe Controlor
*
*		Sert d'intermédiaire entre Blip/Blop et les interfaces
*
*
*		Prosper / LOADED -   V 0.2
*
*
*
******************************************************************/

#ifndef _Controlor_
#define _Controlor_

//-----------------------------------------------------------------------------
//		Définition de la classe Controlor (ABSTRAITE)
//-----------------------------------------------------------------------------

class Controlor
{
protected:
	bool inertia_on;

public:

	Controlor() : inertia_on(true) {};

	virtual int gauche() const = 0;
	virtual int haut() const = 0;
	virtual int droite() const = 0;
	virtual int bas() const = 0;
	virtual int fire() const = 0;
	virtual int saut() const = 0;
	virtual int super() const = 0;

	virtual bool inertia() const
	{
		return inertia_on;
	};

	virtual void setInertia(bool i)
	{
		inertia_on = i;
	};
};


#endif


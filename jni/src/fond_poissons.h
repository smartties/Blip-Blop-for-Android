/******************************************************************
*
*
*		-----------------------
*		    FondPoissons.h
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 18 Janvier 2001
*
*
*
******************************************************************/

#ifndef _FondPoissons_
#define _FondPoissons_

#define POISSON_SPEED 1

class FondPoissonRouge : public Sprite
{
private:
	int dir;

public:
	FondPoissonRouge();
	virtual void update();

};

class FondPoissonViolet : public Sprite
{
private:
	int dir;

public:
	FondPoissonViolet();
	virtual void update();

};

class FondPoissonRougeCamoufle : public Sprite
{
private:
	int dir;

public:
	FondPoissonRougeCamoufle();
	virtual void update();

};

class FondPoissonVioletCamoufle : public Sprite
{
private:
	int dir;

public:
	FondPoissonVioletCamoufle();
	virtual void update();

};

#endif
/******************************************************************
*
*
*		-----------------------
*		    FondPoissons.cpp
*		-----------------------
*
*
*
*		Mephisto / LOADED -   V 0.1 - 18 Janvier 2001
*
*
*
******************************************************************/

#include "sprite.h"
#include "fond_poissons.h"


FondPoissonRouge::FondPoissonRouge()
{
	dir = rand() % 2;
}

void FondPoissonRouge::update()
{
	ss_etape ++;
	ss_etape %= 9;

	if (ss_etape == 0) {
		etape ++;
		etape %= 3;
	}

	if (dir) {
		x += POISSON_SPEED;
		pic = pbk_niveau[2 + etape];
	} else {
		x -= POISSON_SPEED;
		pic = pbk_niveau[5 + etape];
	}


	if ((x < offset - 100) || (x > offset + 740)) {
		a_detruire = true;
	}

}


FondPoissonViolet::FondPoissonViolet()
{
	dir = rand() % 2;
}

void FondPoissonViolet::update()
{
	ss_etape ++;
	ss_etape %= 9;

	if (ss_etape == 0) {
		etape ++;
		etape %= 3;
	}

	if (dir) {
		x += POISSON_SPEED;
		pic = pbk_niveau[14 + etape];
	} else {
		x -= POISSON_SPEED;
		pic = pbk_niveau[17 + etape];
	}


	if ((x < offset - 100) || (x > offset + 740)) {
		a_detruire = true;
	}

};

FondPoissonRougeCamoufle::FondPoissonRougeCamoufle()
{
	dir = rand() % 2;
}

void FondPoissonRougeCamoufle::update()
{
	ss_etape ++;
	ss_etape %= 9;

	if (ss_etape == 0) {
		etape ++;
		etape %= 3;
	}

	if (dir) {
		x += POISSON_SPEED;
		pic = pbk_niveau[8 + etape];
	} else {
		x -= POISSON_SPEED;
		pic = pbk_niveau[11 + etape];
	}


	if ((x < offset - 100) || (x > offset + 740)) {
		a_detruire = true;
	}

}


FondPoissonVioletCamoufle::FondPoissonVioletCamoufle()
{
	dir = rand() % 2;
}

void FondPoissonVioletCamoufle::update()
{
	ss_etape ++;
	ss_etape %= 9;

	if (ss_etape == 0) {
		etape ++;
		etape %= 3;
	}

	if (dir) {
		x += POISSON_SPEED;
		pic = pbk_niveau[20 + etape];
	} else {
		x -= POISSON_SPEED;
		pic = pbk_niveau[23 + etape];
	}


	if ((x < offset - 100) || (x > offset + 740)) {
		a_detruire = true;
	}

}


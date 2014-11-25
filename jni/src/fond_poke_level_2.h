/******************************************************************
*
*
*		---------------------------
*		    FondPokeLevel2.h
*		---------------------------
*
*
*
*		Mephisto / LOADED -   V 0.2 - 17 Fevrier 2001
*
*
*
******************************************************************/

#ifndef _FondPokeLevel2_
#define _FondPokeLevel2_

#include "sprite.h"

#define PBK_2		130
#define PBK_L		136
#define PBK_E		133
#define PBK_V		139

class FondPokeLevel2 : public Sprite
{
private:
	int etape_L1;
	int etape_E1;
	int etape_V;
	int etape_E2;
	int etape_L2;

public:

	FondPokeLevel2();

	virtual void update();
	virtual void affiche();

};

#endif
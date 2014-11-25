
#ifndef _FondPokeAlarme1_
#define _FondPokeAlarme1_

#include "sprite.h"

class FondPokeAlarme1 : public Sprite
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 3;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 14;
		}

		pic = pbk_niveau[etape];
		updateADetruire();
	};

};

class FondPokeAlarme2 : public Sprite
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 3;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 14;
		}

		pic = pbk_niveau[14 + etape];
		updateADetruire();
	};
};

class FondPokeAlarme3 : public Sprite
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 3;

		if (ss_etape == 0) {
			etape += 1;
			etape %= 14;
		}

		pic = pbk_niveau[28 + etape];
		updateADetruire();
	};
};

#endif
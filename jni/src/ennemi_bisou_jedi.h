
#ifndef _EnnemiBisouJedi_
#define _EnnemiBisouJedi_

#include "enemy.h"

class EnnemiBisouJedi : public Ennemi
{
public:
	int		wait_shoot;
	int		etape_shoot;
	bool	a_epee;

	EnnemiBisouJedi();
	virtual void onAvance();
	virtual void onMeure();
	virtual void estTouche(Tir * tir);
	virtual void update();
	virtual void onCarbonise();
	virtual void affiche();
};

class EnnemiBisouJediHeros : public EnnemiBisouJedi
{
public:

	bool	intro;

	EnnemiBisouJediHeros() : intro(true)
	{
		pv = 6000;
	};

	virtual void update()
	{
		if (intro) {
			if (x > offset + 450) {
				EnnemiBisouJedi::onAvance();
				col_on = false;
			} else {
				intro = false;
				game_flag[FLAG_USER1] = 1;
				game_flag[FLAG_GEN_OFF] = 0;
			}
		} else {
			EnnemiBisouJedi::update();
		}
	};

	virtual void estTouche(Tir * tir)
	{
		EnnemiBisouJedi::estTouche(tir);

		if (pv <= 0) {
			game_flag[FLAG_USER1] = 2;
			game_flag[FLAG_GEN_OFF] = 1;
		}
	}
};

#endif
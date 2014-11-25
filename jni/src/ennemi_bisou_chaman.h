
#ifndef _EnnemiBisouChaman_
#define _EnnemiBisouChaman_

#include "enemy.h"

class EnnemiBisouChaman : public Ennemi
{
public:
	int		wait_shoot;
	int		etape_shoot;
	int		nb_lueurs;
	int		nb_touch;
	int		n_pos;

	EnnemiBisouChaman();
	virtual void onAvance();
	virtual void onLeveBaton();
	virtual void onBaisseBaton();
	virtual void onTire();
	virtual void onMeure();
	virtual void onCarbonise();
	virtual void estTouche(Tir * tir);
	virtual void update();
	virtual void affiche();
	virtual void onTele();
};

#endif

#include "ennemi_com.h"

EnnemiCOM::EnnemiCOM()
{
	pv = 100;
}


void EnnemiCOM::update()
{

	switch (etat) {
		case ETAT_NORMAL:
		case ETAT_AVANCE:
			onAvance();
			break;

		case ETAT_MEURE:
		case ETAT_CARBONISE:
			onMeure();
			break;
	}

	updateADetruire();
}


void EnnemiCOM::onAvance()
{
	ss_etape += 1;
	ss_etape %= 8;

	if (ss_etape == 0) {
		etape += 1;
		etape %= 2;
	}

	// vole
	//
	if (x - 1 < offset || mur_opaque(x - 1, y))
		dir = SENS_DROITE;
	else if (x + 1 > offset + 640 || mur_opaque(x + 1, y))
		dir = SENS_GAUCHE;

	if (dir == SENS_DROITE)
		x += 1;
	else
		x -= 1;

	pic = pbk_ennemis[98 + etape];

	colFromPic();
}


void EnnemiCOM::onMeure()
{
	if (ss_etape == 0 && etape == 0) {
		sbk_niveau.play(6);
	}

	ss_etape += 1;
	ss_etape %= 3;

	if (ss_etape == 0 && etape < 22)
		etape += 1;

	if (etape >= 22) {
		a_detruire = true;
	} else {
		pic = pbk_ennemis[76 + etape];
	}
}

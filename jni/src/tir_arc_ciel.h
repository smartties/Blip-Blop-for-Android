
#ifndef _TirArcCiel_
#define _TirArcCiel

class TirArcCiel : public Tir
{
public:
	virtual void update()
	{
		ss_etape += 1;
		ss_etape %= 3;

		if (ss_etape == 0)
			etape += 1;

		if (etape >= 15) {
			a_detruire = true;
		} else {
			if (dir == SENS_DROITE)
				pic = pbk_ennemis[48 + etape];
			else
				pic = pbk_ennemis[63 + etape];

			colFromPic();
		}
	};
};

#endif
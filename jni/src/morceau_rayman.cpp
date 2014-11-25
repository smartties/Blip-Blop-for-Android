
/******************************************************************
*
*
*		-----------------------
*		   MorceauRayman.cpp
*		-----------------------
*
*		Poing1 & 2 qui giclent + jambes qui giclent..
*
*		Mephisto / LOADED -   V 0.1 - 20 Decembre 2000
*
*
*
******************************************************************/

#include "morceau_rayman.h"

//implementation de la classe MorceauxRayman

MorceauRayman::MorceauRayman(int m_pic, int vx, int vy): dx(vx)
{
	pic = pbk_ennemis[m_pic];
	dy  = vy;
	n_pic = m_pic;
}

void MorceauRayman::update()
{
	x += dx;
	tombe();

	if (plat(x, y) != 0) {
		switch (n_pic) {
			case  230:
				game_flag[0] = 2;
				game_flag[2] = 1;
				grave(x, y, pic);
				a_detruire = true;
				break;

			case 231:
				game_flag[0] = 2;
				game_flag[2] = 2;
				grave(x, y, pic);
				a_detruire = true;
				break;

			case 270:
			case 271:
				game_flag[0] = 2;
				game_flag[2] = 3;
				grave(x, y, pic);
				a_detruire = true;
				break;
		}
	}
}
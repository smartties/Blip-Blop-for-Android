
#include "ennemi_smurf_cigogne.h"
#include "ben_maths.h"

EnnemiSmurfCigogne::EnnemiSmurfCigogne()
{
	pic = pbk_ennemis[355];
	noCol();
	first = true;
}

void EnnemiSmurfCigogne::update()
{
	if (first) {
		base_y = y;
		x -= 100;
		base_x = x;
		first = false;
	}

	if (game_flag[1] < 5)
		return;

	x += 4;

	y = base_y + ((100 * bSin[((x - base_x) / 4) % 360]) >> COSINUS);

	if (x > offset + 750 && game_flag[0] < 3) {
		game_flag[0] = 3;
	}
}

#include "globals.h"
#include "event_bonus.h"

#define BONUS_SEED	20

int makeb_current_mode = 0;

int bonus_list[][BONUS_SEED] = {

	// Num 0 : 10 PM, 10 fusils (idéal pour niveaux bonus)
	{ BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL },

	// Num 1 : 10 PM, 10 fusils (idem num 0)
	{ BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL, BPM, BFUSIL },

	// Num 2 :  que LF
	{ BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF, BLF },

	// Num 3 :  que LASER
	{ BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER, BLASER },

	// Num 4 : que PM
	{ BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM, BPM },

	// Num 5 : que FUSIL
	{ BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL, BFUSIL },

	// Num 6 : 4 Lance flammes, 8 fusils, 8 PMs
	{ BPM, BFUSIL, BPM, BFUSIL, BLF, BPM, BFUSIL, BFUSIL, BFUSIL, BLF, BPM, BFUSIL, BFUSIL, BFUSIL, BLF, BPM, BFUSIL, BPM, BFUSIL, BLF },

	// Num 7 : 4 Lasers, 8 fusils, 8 PMs
	{ BPM, BFUSIL, BPM, BFUSIL, BLASER, BPM, BFUSIL, BFUSIL, BFUSIL, BLASER, BPM, BFUSIL, BFUSIL, BFUSIL, BLASER, BPM, BFUSIL, BPM, BFUSIL, BLASER },

	// Num 8 : 9 PM, 8 FUSILs, 1 bières, 1 tonneau, 1 invincibilité
	{ BPM, BFUSIL, BPM, BPM, BFUSIL, BBEER, BPM, BFUSIL, BFUSIL, BPM, BFUSIL, BPM, BTONNO, BPM, BFUSIL, BPM, BFUSIL, BINV, BFUSIL, BPM },
};

void MakeBonus(int x, int y)
{
	static int seed = 0;

	seed += 1;
	seed %= BONUS_SEED;

	int	n = bonus_list[makeb_current_mode][seed];

	EventBonus eb;

	eb.x = x;
	eb.y = y;
	eb.type = n;
	eb.doEvent();
}

void MakeBonusWeapon(int x, int y)
{
	static int seed = 0;

	seed += 1;
	seed %= BONUS_SEED;

	int	n = bonus_list[1][seed];

	EventBonus eb;

	eb.x = x;
	eb.y = y;
	eb.type = n;
	eb.doEvent();
}


#include "event_bonus.h"
#include "bonus_pm.h"
#include "bonus_fusil.h"
#include "bonus_laser.h"
#include "bonus_beer.h"
#include "bonus_invincible.h"
#include "bonus_tonneau.h"
#include "bonus_vache.h"
#include "bonus_lf.h"

void EventBonus::doEvent()
{
	Bonus * bonus;

	switch (type) {
		case BPM:
			bonus = new BonusPM();
			break;

		case BFUSIL:
			bonus = new BonusFusil();
			break;

		case BLF:
			bonus = new BonusLF();
			break;

		case BLASER:
			bonus = new BonusLaser();
			break;

		case BBEER:
			bonus = new BonusBeer();
			break;

		case BINV:
			bonus = new BonusInvincible();
			break;

		case BTONNO:
			bonus = new BonusTonneau();
			break;

		case BCOW:
			bonus = new BonusVache();
			break;

		default:
			bonus = NULL;
			debug << "Unknown bonus type\n";
			break;
	}

	if (bonus != NULL) {
		bonus->x = x;
		bonus->y = y;

		list_bonus.ajoute((void*) bonus);
	}
}

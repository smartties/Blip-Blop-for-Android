
#ifndef _FICEVENT_
#define _FICEVENT_

//--------------------------------------------------------------------------
//	Constantes d'identification des événements
//--------------------------------------------------------------------------

#define EVENTID_ENNEMI				0
#define EVENTID_ENNEMI_GENERATOR	1
#define EVENTID_FOND_ANIME			2
#define EVENTID_MIFOND				3
#define EVENTID_PREMIER_PLAN		4
#define EVENTID_LOCK				5
#define EVENTID_HOLD_FIRE			6
#define EVENTID_FORCE_SCROLL		7
#define EVENTID_RPG					8
#define EVENTID_FLAG				9
#define EVENTID_TEXT				10
#define EVENTID_SON					11
#define EVENTID_METEO				12
#define EVENTID_OVERKILL			13
#define EVENTID_DYNAMIC_LOAD		14
#define EVENTID_MUSIC				15
#define EVENTID_BONUS_GENERATOR		16
#define EVENTID_TURRET				17
#define EVENTID_BONUS				18


struct FICEVENT {
	int		event_id;		// Identificateur de l'événement
	int		x_activation;	// Abscisse d'activation

	int		id;
	int		x;

	union {
		int		n_pbk;
		int		n_sbk;
		int		n_txt;
	};

	union {
		int		y;
		int		cond;
		int		speed;
		int		intensite;
		int		play;
	};

	union {
		int		capacite;
		int		flag;
		int		duree;
	};

	union {
		int		val;
		int		sens;
		int		dir;
	};

	int		periode;
	bool	tmp;
	char	fic[20];

};

#endif
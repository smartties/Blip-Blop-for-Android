
#ifndef _HiScores_
#define _HiScores_

#ifndef NULL
#define NULL	0
#endif

#include "log.h"

const int HS_NB_SCORES		= 10;
const int HS_NAME_LENGTH	= 20;

class HiScores
{
protected:

	char *	names[HS_NB_SCORES];
	int		scores[HS_NB_SCORES];

	/*
		Le premier appel à cette fonction crypte les données. Le
		deuxième les décryptes, etc...

		ATTENTION : il ne faut surtout pas lire les données cryptées!
		(risque de chaîne sans '\0')
	*/

public:
	void	crypte();

	HiScores()
	{
		for (int i = 0; i < HS_NB_SCORES; i++)
			names[i] = new char[HS_NAME_LENGTH];

		init();
	};

	~HiScores()
	{
		for (int i = 0; i < HS_NB_SCORES; i++)
			if (names[i] != NULL)
				delete [] names[i];
	};


	/*
		Retourne le nom du joueur de rang N (0 étant le meilleur)
	*/
	char *	getName(int n) const
	{
		if (n >= 0 && n < HS_NB_SCORES)
			return names[n];
		else
			return NULL;
	};

	/*
		Retourne le score du joueur de rang N (0 étant le meilleur)
	*/
	int		getScore(int n) const
	{
		if (n >= 0 && n < HS_NB_SCORES)
			return scores[n];
		else
			return 0;
	};

	/*
		Retourne vrai si le score passé en paramètre est assez
		élevé pour rentrer dans le HiScore
	*/
	bool	isGood(int scr)
	{
		return (scores[HS_NB_SCORES - 1] < scr);
	};


	/*
		Initialise la table des scores avec des scores bidons
		et des "LOADED" partout
	*/
	void	init();


	/*
		Ajoute le score (et le nom) passé en
		paramètre à la table
	*/
	void	add(int scr, const char * name);


	/*
		Sauvegarde les scores dans un fichier crypté!
	*/
	bool	save(const char * file);

	/*
		Charge les scores dans un fichier crypté!
	*/
	bool	load(const char * file);
};

#endif

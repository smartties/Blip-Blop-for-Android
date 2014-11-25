/******************************************************************
*
*
*		-------------------
*		    Joueur.h
*		-------------------
*
*		Pour gérer le coté "joueur" (points) de BB
*
*
*		Prosper / LOADED -   V 0.1 - 17 Juillet 2000
*
*
*
******************************************************************/

#ifndef _Joueur_
#define _Joueur_

class Joueur
{
protected:
	int		score;
	int		nb_killed;

public:

	Joueur() : score(0)
	{
	};

	inline void setKilled(int n)
	{
		nb_killed = n;
	};

	inline void addKilled()
	{
		nb_killed += 1;
	};

	inline virtual int getScore()
	{
		return score;
	};

	inline virtual int getKilled()
	{
		return nb_killed;
	};

	inline virtual void setScore(int ns)
	{
		score = ns;
	};

	inline virtual void addPoints(int p)
	{
		score += p;
	};
};

#endif
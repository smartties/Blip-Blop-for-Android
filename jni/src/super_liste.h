/******************************************************************
*
*
*		----------------
*		   SuperListe.h
*		----------------
*
*
*		Liste de pointeurs (void*) doublement chaînée
*		MAIS à sens unique
*
*
*		Prosper / LOADED -   V 1.0 - 28 Juin 2000
*
*
*
******************************************************************/


#ifndef _SuperListe_
#define _SuperListe_

//-----------------------------------------------------------------------------
//		Structure CELLULE pour rendre la liste plus jolie
//-----------------------------------------------------------------------------

struct CELLULE {
	CELLULE *	prev;
	void *		data;
	CELLULE *	next;
};

//-----------------------------------------------------------------------------
//		La classe SuperListe en personne
//-----------------------------------------------------------------------------

class SuperListe
{
protected:
	CELLULE *	tete;		// Tete de la liste
	CELLULE *	obs;		// Observateur
	int			nb_elem;	// Nombre d'élements
public:
	static CELLULE *trash;
	static int		nb_lists;

public:

	// Constructeur normal
	//
	SuperListe();

	// Destructeur
	~SuperListe();


	// Met l'observateur sur la tête
	//
	inline void 	start()
	{
		obs = tete;
	};


	// Avance l'observateur
	//
	inline void 	suivant()
	{
		if (obs != NULL) obs = obs->next;
	};


	// Rajoute une cellule en tête de liste
	//
	void	ajoute(void * nouvo);


	// Supprime la cellule observée
	//
	// ! ATTENTION !
	//
	// La suppression avance l'observateur !!!
	//
	void	supprime();


	// Supprime la cellule observée, mais pas la valeur contenue
	//
	void *	supprimePorc();


	// Vide la liste
	//
	void	vide();
	void	vide_porc();


	// Renvoit le nombre d'éléments contenus
	//
	inline int	taille() const
	{
		return nb_elem;
	};


	// Indique si la fin de la liste a été atteinte
	//
	inline bool	fin() const
	{
		return (obs == NULL);
	};


	// Indique VRAI si la liste est vide (ne contient aucune cellule)
	//
	inline bool	estVide() const
	{
		return (tete == NULL);
	};


	// Renvoit la valeur de la cellule observée
	//
	inline void *	info() const
	{
		if (obs != NULL)
			return (obs->data);
		else
			return NULL;
	};


	// Trie la liste selon la fonction donnée en paramètre
	//
	void	(trier(int (*fonc)(const void *, const void*)));
};

#endif

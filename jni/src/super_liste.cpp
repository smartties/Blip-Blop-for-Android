/******************************************************************
*
*
*		-------------------
*		   SuperListe.cpp
*		-------------------
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

#ifndef NULL
#define NULL	0
#endif

//-----------------------------------------------------------------------------
//		Headers
//-----------------------------------------------------------------------------

#include <cstdlib>
#include "super_liste.h"
#include "ben_debug.h"

CELLULE * SuperListe::trash		= NULL;
int		  SuperListe::nb_lists	= 0;

//-----------------------------------------------------------------------------

SuperListe::SuperListe() : tete(NULL), obs(NULL), nb_elem(0)
{
	nb_lists += 1;
}


//-----------------------------------------------------------------------------

SuperListe::~SuperListe()
{
	if (nb_elem != 0) {
		debug << "SuperListe non désallouée (taille " << nb_elem << ")\n";
		vide();
	}

	nb_lists -= 1;

	if (nb_lists == 0) {
		CELLULE *	cel;

		while (trash != NULL) {
			cel = trash;
			trash = trash->next;
			delete cel;
		}
	}
}


//-----------------------------------------------------------------------------

void SuperListe::ajoute(void * nouvo)
{
	CELLULE *	ptr;

	if (trash == NULL)
		ptr = new CELLULE();
	else {
		ptr = trash;
		trash = trash->next;
	}

	ptr->data = nouvo;
	ptr->prev = NULL;
	ptr->next = tete;

	if (tete != NULL)
		tete->prev = ptr;

	tete = ptr;

	nb_elem++;
}


//-----------------------------------------------------------------------------

void * SuperListe::supprimePorc()
{
	void *	dat;

	if (obs == NULL)
		return NULL;


	if (obs == tete) {
		CELLULE *	ptr;

		ptr = tete->next;

		dat = tete->data;

		//delete tete;
		tete->next = trash;
		trash = tete;

		tete = obs = ptr;

		if (tete != NULL)
			tete->prev = NULL;
	} else {
		CELLULE *	ptr_p;
		CELLULE *	ptr_n;

		ptr_p = obs->prev;
		ptr_n = obs->next;

		ptr_p->next = ptr_n;

		if (ptr_n != NULL)
			ptr_n->prev = ptr_p;

		dat = obs->data;

		obs->next = trash;
		trash = obs;

		obs = ptr_n;
	}

	nb_elem--;

	return dat;
}

//-----------------------------------------------------------------------------

void SuperListe::supprime()
{
	if (obs == NULL)
		return;


	if (obs == tete) {
		CELLULE *	ptr;

		ptr = tete->next;

		free(tete->data);

		tete->next = trash;
		trash = tete;

		tete = obs = ptr;

		if (tete != NULL)
			tete->prev = NULL;
	} else {
		CELLULE *	ptr_p;
		CELLULE *	ptr_n;

		ptr_p = obs->prev;
		ptr_n = obs->next;

		ptr_p->next = ptr_n;

		if (ptr_n != NULL)
			ptr_n->prev = ptr_p;

		free(obs->data);

		obs->next = trash;
		trash = obs;

		obs = ptr_n;
	}

	nb_elem--;
}




//-----------------------------------------------------------------------------

void SuperListe::vide()
{
	CELLULE * ptr;

	ptr = tete;

	while (ptr != NULL) {
		tete = ptr->next;

		//free(ptr->data);
		delete ptr;

		ptr = tete;
	}

	tete = NULL;
	nb_elem = 0;
}

//-----------------------------------------------------------------------------

void SuperListe::vide_porc()
{
	CELLULE * ptr;

	ptr = tete;

	while (ptr != NULL) {
		tete = ptr->next;

		delete ptr;

		ptr = tete;
	}

	tete = NULL;
	nb_elem = 0;
}



//-----------------------------------------------------------------------------

void (SuperListe::trier(int (*fonc)(const void *, const void*)))
{
	if (tete == NULL || tete->next == NULL)
		return;

	CELLULE *	p1;
	CELLULE *	p2;

	p1 = tete;
	p2 = p1->next;


	while (p2 != NULL) {
		if (fonc(p1->data, p2->data) > 0) {
			if (p1->prev != NULL)
				(p1->prev)->next = p2;
			else
				tete = p2;

			if (p2->next != NULL)
				(p2->next)->prev = p1;

			p1->next = p2->next;
			p2->prev = p1->prev;

			p2->next = p1;
			p1->prev = p2;

			if (p2->prev != NULL)
				p1 = p2->prev;
		} else {
			p1 = p2;
		}

		p2 = p1->next;
	}

}

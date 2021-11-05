#pragma once
#include "Item.h"
class Grille
{
private :
	int hauteur;
	int largeur;
	Item **elements;

public :
	Grille();
	Grille(int, int);
	Grille(Grille*);

	int getHauteur();
	int getLargeur();
	void afficher();
	void setTab(Item**);
};


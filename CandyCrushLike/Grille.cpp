#include "Grille.h"
#include <stdio.h>
#include <iostream>

Grille::Grille() {
	this->hauteur = 10;
	this->largeur = 10;
}

Grille::Grille(int h, int l) {
	this->hauteur = h;
	this->largeur = l;
}

Grille::Grille(Grille* g) {
	this->hauteur = g->getHauteur();
	this->largeur = g->getLargeur();
}

int Grille::getHauteur() {
	return this->hauteur;
}

int Grille::getLargeur() {
	return this->largeur;
}

void Grille::afficher() {
	for (int i = 0; i < hauteur; i++) {
		for (int j = 0; j < largeur; j++) {
			std::cout << elements[i][j].getName() << "(" << i << ", " << j << ") ";
		}
		std::cout << std::endl;
	}
}

void Grille::setTab(Item** elements) {
	this->elements = elements;
}
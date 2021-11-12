#include "../headers/Grille.h"
#include <stdio.h>
#include "../headers/Item.h"
#include <iostream>

Grille::Grille() {
    this->hauteur = 10;
    this->largeur = 10;
    this->array = new Item[this->hauteur * this->largeur];
}

Grille::Grille(int h, int l) {
    this->hauteur = h;
    this->largeur = l;
    this->array = new Item[h * l];
}

Grille::Grille(Grille *g) {
    this->hauteur = g->getHauteur();
    this->largeur = g->getLargeur();
    this->array = g->getArray();

}

int Grille::getHauteur() const  {
    return this->hauteur;
}

int Grille::getLargeur() const {
    return this->largeur;
}

Item* Grille::getArray() {
    return this->array;
}

void Grille::setArray(Item *arr) {
    this->array = arr;
}

Item Grille::getArrItem(int h, int l) {
    return this->array[(h * this->hauteur) + l];
}

void Grille::setArrItem(int h, int l, Item val) {
    this->array[(h * this->hauteur) + l] = val;
}


void Grille::afficher() {
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            std::cout << this->array[i * hauteur+j].getName() << " ; ";
        }
        std::cout << std::endl;
    }
}



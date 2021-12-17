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



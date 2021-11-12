#pragma once

#include "Item.h"
#include <stdio.h>
#include <iostream>

class Grille {
private :
    int hauteur;
    int largeur;
    Item *array;

public :
    Grille();

    Grille(int, int);

    Grille(Grille *);

    int getHauteur() const;

    int getLargeur() const;

    Item *getArray();

    Item getArrItem(int h, int l);

    //void setArrItem(int h, int l, std::string val);
    void setArrItem(int h, int l, Item val);

    void afficher();

    void setArray(Item *arr);
};


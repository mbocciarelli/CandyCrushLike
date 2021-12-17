#pragma once

#include "Item.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include "../headers/Bonbon.h"

class Grille {
private :
    int hauteur;
    int largeur;
    Item *array;
    std::map<Bonbon, sf::Texture*> mapTexture;

public :
    Grille();

    Grille(int, int);

    int getHauteur() const {
        return this->hauteur;
    };

    int getLargeur() const {
        return this->largeur;
    };

    Item* getArray() const {
        return this->array;
    };

    Item* getArrItem(int h, int l) const {
        return &this->array[(h * this->hauteur) + l];
    };

    void setArrItem(int h, int l, Item val) {
        this->array[(h * this->hauteur) + l] = val;
    };

    void setArray(Item *arr) {
        this->array = arr;
    };

    void loadTexture(Bonbon name, std::string path) {
        createNewTexture(name);
        mapTexture.at(name)->loadFromFile(path);
    };

    void createNewTexture(Bonbon name) {
        mapTexture.insert(std::pair<Bonbon, sf::Texture*>(name, new sf::Texture()));
    }

    sf::Texture* getTexture(Bonbon name) const {
        return mapTexture.at(name);
    }
};


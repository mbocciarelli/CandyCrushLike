#pragma once

#include "Item.h"
#include <stdio.h>
#include <iostream>
#include <map>
#include <SFML/Graphics/Texture.hpp>
#include "../headers/Bonbon.h"

struct Cell {
    int h;
    int l;

    Cell() : h(0), l(0) {};
    Cell(int h, int l) : h(h), l(l) {}
};

class Grille {
private:
    int hauteur;
    int largeur;
    std::vector<Item*> array;
    std::vector<Cell> arrayToDestruct;
    std::map<Bonbon, int> bonbonToDestroy;
    std::map<Bonbon, sf::Texture*> mapTexture;

    struct offset
    {
        int hauteur;
        int largeur;

        offset(int h, int l) {
            hauteur = h;
            largeur = l;
        };
    };

    bool IsSameBonbon(int hauteur, int largeur, offset item1, offset item2, offset item3);

public:
    Grille();

    Grille(int, int);

    int getHauteur() const {
        return this->hauteur;
    };

    int getLargeur() const {
        return this->largeur;
    };

    std::vector<Item*> getArray() const {
        return this->array;
    };

    Item* getArrItem(int h, int l) const {
        int temp = (h * this->hauteur) + l;
        return this->array[temp];
    };

    void setArrItem(Item* val) {
        this->array.push_back(val);
    };

    void setArray(std::vector<Item*> arr) {
        this->array = arr;
    };

    std::map<Bonbon, int> getBonbonToDestroy() const {
        return bonbonToDestroy;
    }

    void clearBonbonToDestroy() {
        for (const auto& kv : bonbonToDestroy) {
            bonbonToDestroy.at(kv.first) = 0;
        }
    }

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

    bool checkIfPlayable();

    void testLineColumn(Bonbon& previousCandy, int* nb, std::vector<Cell>* tempPositions, int l, int h);

    bool CheckMatch();

    void DestroyCells();

    void ReorganizeCells();

    void RegenerateCells();

    void SwapCell(Cell from, Cell to);

    void ReplaceCells();

};
//
// Created by Daniel Chiquet on 12/11/2021.
//
#ifndef HELLOSFML_SFML_TEST_H
#define HELLOSFML_SFML_TEST_H

#include "Grille.h"
#include "../SFML/Graphics.hpp"
#include "Click.h"


int sfml_test();

Grille* load(int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, float sizeSprite);

void loadTexture(Grille* grille);

void loadSprite(Grille* grille, int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, float sizeSprite);

void dessinerJeu(Grille* grille);

Bonbon generateItem(int min, int max);

bool eventClickLeft(sf::Event event);

Click* TestClick(sf::Event event, Click* tabClick, Grille grille);

#endif //HELLOSFML_SFML_TEST_H

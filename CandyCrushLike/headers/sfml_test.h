//
// Created by Daniel Chiquet on 12/11/2021.
//

#ifndef HELLOSFML_SFML_TEST_H
#define HELLOSFML_SFML_TEST_H


#include "Grille.h"
#include "../SFML/Graphics.hpp"
#include "Click.h"

int sfml_test(Grille grille);
bool eventClickLeft(sf::Event event);
void CreateGrille(sf::RenderWindow& window, Grille grille);
Click* TestClick(sf::Event event, Click* tabClick, Grille grille);
#endif //HELLOSFML_SFML_TEST_H

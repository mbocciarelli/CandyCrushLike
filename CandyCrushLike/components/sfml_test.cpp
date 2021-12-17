//
// Created by Daniel Chiquet on 12/11/2021.
//


#include <iostream>
#include "../headers/sfml_test.h"
#include "../SFML/Graphics.hpp"
#include "../headers/Grille.h"
#include "../SFML/Graphics/Sprite.hpp"


int wWidth = 1920;
int wHeight = 1080;
sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");

int sfml_test() {
    int widthGrille = 10;
    int heightGrille = 10;
    auto *tabClick = new Click[2];

    int widthMarge = (wWidth * 400) / 1920;
    int heightMarge = (wHeight * 240) / 1080;
    tabClick[0] = Click(0, 0, 0);
    tabClick[1] = Click(0, 0, 0);

    int xFirstPoint = widthMarge / 2;
    int yFirstPoint = heightMarge / 2;
    int sizeCell = (((float)wWidth / (float)wHeight) * 75) / (1920.0 / 1080.0);
    float sizeSprite = (((float)wWidth / (float)wHeight) * 1.5) / (1920.0 / 1080.0);

    std::cout << window.getSize().x << " " << window.getSize().y << std::endl;
    std::cout << xFirstPoint << " " << yFirstPoint << std::endl;
    std::cout << sizeCell << " " << sizeSprite << std::endl;

    std::srand(std::time(nullptr));
    Grille* grille = load(widthGrille, heightGrille, xFirstPoint, yFirstPoint, sizeCell, sizeSprite);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (eventClickLeft(event)) {
                    tabClick = TestClick(event, tabClick, grille);
                }
            }
        }

                   
        dessinerJeu(grille);
    }
    return 0;
}

Grille* load(int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, float sizeSprite) {

    Grille* grille = new Grille(widthGrille, heightGrille);

    loadTexture(grille);

    loadSprite(grille, widthGrille, heightGrille, xFirstPoint, yFirstPoint, sizeCell, sizeSprite);

    return grille;
}

bool eventClickLeft(sf::Event event) {
    return event.mouseButton.button == sf::Mouse::Left;
}

Click* TestClick(sf::Event event, Click* tabClick, Grille grille){
    std::cout << "the left button was pressed" << std::endl;
    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
    Click lastClick = where_is_clic(event, grille, wWidth, wHeight);
    tabClick[0] = tabClick[1];
    tabClick[1] = lastClick;
    if (tabClick[0].getStatus() != 0) {
        std::cout << compareClick(tabClick) << std::endl;
        tabClick[0] = Click(0, 0, 0);
        tabClick[1] = Click(0, 0, 0);
        std::cout << "------" << std::endl;
    }
    return tabClick;

void loadTexture(Grille* grille) {
    grille->loadTexture(Bonbon::BLUE, "asset/Blue.png");
    grille->loadTexture(Bonbon::GREEN, "asset/Green.png");
    grille->loadTexture(Bonbon::ORANGE, "asset/Orange.png");
    grille->loadTexture(Bonbon::PURPLE, "asset/Purple.png");
    grille->loadTexture(Bonbon::RED, "asset/Red.png");
    grille->loadTexture(Bonbon::YELLOW, "asset/Yellow.png");
}

void loadSprite(Grille* grille, int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, float sizeSprite) {
    for (int i = 0; i < widthGrille; i++) {
        for (int j = 0; j < heightGrille; j++) {

            grille->setArrItem(i, j, Item());

            Bonbon itemName = generateItem(1, 6); // 6 Textures max
            grille->getArrItem(i, j)->setName(itemName);

            grille->getArrItem(i, j)->getSprite()->setTexture(*grille->getTexture(itemName));
            grille->getArrItem(i, j)->getSprite()->setScale(sizeSprite, sizeSprite);
            grille->getArrItem(i, j)->getSprite()->setPosition(j * sizeCell + xFirstPoint, i * sizeCell + yFirstPoint);
        }
    }
}

void dessinerJeu(Grille* grille) {

    window.clear(sf::Color::Black);

    for (int i = 0; i < grille->getHauteur(); i++) {
        for (int j = 0; j < grille->getLargeur(); j++) {
            window.draw(*grille->getArrItem(i, j)->getSprite());
        }
    }

    window.display();
}

//Min et max son inclu dans le rand
Bonbon generateItem(int min, int max) {
    Bonbon b;

    int random = rand() % max + min;

    switch (random) {
    
        case 1 :
            b = Bonbon::BLUE;
            break;

        case 2:
            b = Bonbon::GREEN;
            break;

        case 3:
            b = Bonbon::ORANGE;
            break;

        case 4:
            b = Bonbon::PURPLE;
            break;

        case 5:
            b = Bonbon::RED;
            break;

        case 6:
            b = Bonbon::YELLOW;
            break;
    }

    return b;
}
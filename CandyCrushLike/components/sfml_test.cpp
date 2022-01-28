//
// Created by Daniel Chiquet on 12/11/2021.
//


#include <iostream>
#include "../headers/sfml_test.h"
#include "../SFML/Graphics.hpp"
#include "../headers/Grille.h"
#include "../SFML/Graphics/Sprite.hpp"

#include "../ImGUI/imgui.h"
#include "../ImGUI/imgui-SFML.h"

enum State{
    WaitAction,
    Pause,
    Animation,
};


int wWidth = 1920;
int wHeight = 1080;

int xFirstPoint;
int yFirstPoint;

sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");

ImGui::SFML::Init(window, static_cast<sf::Vector2f>(window.getSize()), true);
int sfml_test() {
    int widthGrille = 3;
    int heightGrille = 3;
    auto *tabClick = new Click[2];

    int widthMarge = (wWidth * 400) / wWidth;
    int heightMarge = (wHeight * 240) / wHeight;
    tabClick[0] = Click(0, 0, 0);
    tabClick[1] = Click(0, 0, 0);

    xFirstPoint = widthMarge / 2;
    yFirstPoint = heightMarge / 2;
    int sizeCell = (((float)wWidth / (float)wHeight) * 75) / (1920.0 / 1080.0);
    
    if (sizeCell > ((wWidth - widthMarge) / widthGrille || sizeCell > ((wHeight - heightMarge) / heightGrille ))) {
        if (((wWidth - widthMarge) / widthGrille) > ((wHeight - heightMarge) / heightGrille)) {
            sizeCell = (wHeight - heightMarge) / heightGrille;
        }
        else {
            sizeCell = (wWidth - widthMarge) / widthGrille;
        }
    }

    float sizeSprite = (((float)wWidth / (float)wHeight) * 1.5) / (1920.0f / 1080.0f);
    
    if ((widthGrille / 10) < (heightGrille / 10)) {
        sizeSprite = sizeSprite / (heightGrille / 10);
    }
    else {
        sizeSprite = sizeSprite / (widthGrille / 10);
    }

    if (sizeSprite > 2) {
        sizeSprite = 2;
    }

    std::cout << window.getSize().x << " " << window.getSize().y << std::endl;
    std::cout << "xFirstPoint : "<< xFirstPoint << " " << " ; yFirstPoint : "<< yFirstPoint << std::endl;
    std::cout << sizeCell << " " << sizeSprite << std::endl;

    std::srand(std::time(nullptr));
    Grille* grille = load(widthGrille, heightGrille, xFirstPoint, yFirstPoint, sizeCell, sizeSprite);

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (eventClickLeft(event)) {
                    tabClick = TestClick(event, tabClick, grille);
                }
            }
        }
        ImGui::SFML::Update(window, deltaClock.restart());

                   
        dessinerJeu(grille);
    }
    ImGui::SFML::Shutdown();
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

Click* TestClick(sf::Event event, Click* tabClick, Grille* grille) {
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
}

void loadTexture(Grille* grille) {
    grille->loadTexture(Bonbon::BLUE, "asset/Blue.png");
    grille->loadTexture(Bonbon::GREEN, "asset/Green.png");
    grille->loadTexture(Bonbon::ORANGE, "asset/Orange.png");
    grille->loadTexture(Bonbon::PURPLE, "asset/Purple.png");
    grille->loadTexture(Bonbon::RED, "asset/Red.png");
    grille->loadTexture(Bonbon::YELLOW, "asset/Yellow.png");
}

void loadSprite(Grille* grille, int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, float sizeSprite) {
    for (int i = 0; i < heightGrille; i++) {
        for (int j = 0; j < widthGrille; j++) {

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

    for (int i = 0; i < grille->getLargeur(); i++) {
        for (int j = 0; j < grille->getHauteur(); j++) {
            window.draw(*grille->getArrItem(i, j)->getSprite());
        }
    }
    ImGui::SFML::Render(window);
    window.display();
}

//Min et max son inclu dans le rand
Bonbon generateItem(int min, int max) {
    Bonbon b;

    int random = rand() % (max-1) + (min-1);

    return (Bonbon)random;
}
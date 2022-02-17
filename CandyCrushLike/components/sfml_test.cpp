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

int widthMarge;
int heightMarge;

int widthGrille = 10;
int heightGrille = 10;

int xFirstPoint;
int yFirstPoint;
int sizeCell;
float sizeSprite;

Cell prevCellClick;
bool checkPrevCell = false;

Grille* grille;

sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!", sf::Style::Close | sf::Style::Titlebar);

int sfml_test() {

    CalculParameters();

    std::cout << window.getSize().x << " " << window.getSize().y << std::endl;
    std::cout << xFirstPoint << " " << yFirstPoint << std::endl;
    std::cout << sizeCell << " " << sizeSprite << std::endl;

    std::srand(std::time(nullptr));
    Grille* grille = load(widthGrille, heightGrille, xFirstPoint, yFirstPoint, sizeCell, sizeSprite);

    while (window.isOpen()) {

        checkMouseEvent();

        dessinerJeu(grille);
    }
    return 0;
}

void CalculParameters() {
    widthMarge = (wWidth * 400) / 1920;
    heightMarge = (wHeight * 240) / 1080;

    xFirstPoint = widthMarge / 2;
    yFirstPoint = heightMarge / 2;

    CalculSizeCell();

    CalculSizeSprite();
}

void CalculSizeCell() {
    int width = wWidth - widthMarge;
    int height = wHeight - heightMarge;

    sizeCell = (((float)wWidth / (float)wHeight) * 75) / (1920.0 / 1080.0);

    if (sizeCell > (width / widthGrille || sizeCell > (height / heightGrille))) {
        if ((width / widthGrille) > (height / heightGrille)) {
            sizeCell = height / heightGrille;
        }
        else {
            sizeCell = width / widthGrille;
        }
    }
}

void CalculSizeSprite() {
    int width = widthGrille / 10;
    int height = heightGrille / 10;

    sizeSprite = (((float)wWidth / (float)wHeight) * 1.5) / (1920.0 / 1080.0);

    if (width < height) {
        sizeSprite = sizeSprite / height;
    }
    else {
        sizeSprite = sizeSprite / width;
    }

    if (sizeSprite > 2) {
        sizeSprite = 2;
    }
}

Grille* load(int widthGrille, int heightGrille, int xFirstPoint, int yFirstPoint, int sizeCell, float sizeSprite) {

    grille = new Grille(widthGrille, heightGrille);

    loadTexture(grille);

    loadSprite(grille, widthGrille, heightGrille, xFirstPoint, yFirstPoint, sizeCell, sizeSprite);

    if (widthGrille > 2 && heightGrille > 2) {
        std::cout << grille->checkIfPlayable();
    }

    return grille;
}

bool eventClickLeft(sf::Event event) {
    return event.mouseButton.button == sf::Mouse::Left;
}

void checkMouseEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {


        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::MouseButtonPressed:

            if (!eventClickLeft(event))
                break;

            if (!IsOnGrid(event.mouseButton.x, event.mouseButton.y))
                break;

            Cell cell = GetCell(event.mouseButton.x, event.mouseButton.y);

            if (!checkPrevCell) {
                prevCellClick = cell;
                checkPrevCell = true;
                break;
            }

            if (!IsAroundPrevCell(cell))
                break;

            grille->SwapCell(prevCellClick, cell);
            checkPrevCell = false;

            bool matchIsOk = grille->CheckMatch();
            if (matchIsOk) {
                grille->DestroyCells();
                dessinerJeu(grille);
                grille->ReorganizeCells();
            }
            else {
                grille->SwapCell(cell, prevCellClick);
            }

            dessinerJeu(grille);

            break;
        }
    }
}

bool IsOnGrid(int xClick, int yClick) {
    xClick -= xFirstPoint;
    yClick -= yFirstPoint;

    return (
        xClick >= 0 && xClick < (sizeCell* widthGrille)
        && yClick >= 0 && yClick < (sizeCell* heightGrille)
        );
}

bool IsAroundPrevCell(Cell cell) {
    return (
        prevCellClick.h == cell.h + 1 && prevCellClick.l == cell.l
        || prevCellClick.h == cell.h - 1 && prevCellClick.l == cell.l
        || prevCellClick.h == cell.h && prevCellClick.l == cell.l + 1
        || prevCellClick.h == cell.h && prevCellClick.l == cell.l - 1
        );
}

Cell GetCell(int xClick, int yClick) {
    xClick -= xFirstPoint;
    yClick -= yFirstPoint;

    int xClickMarge = xClick % sizeCell;
    int yClickMarge = yClick % sizeCell;

    Cell cell;

    int lig = (xClick - xClickMarge) / sizeCell;
    int col = (yClick - yClickMarge) / sizeCell;
    cell.h = col;
    cell.l = lig;

    return cell;
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
    for (int i = 0; i < grille->getHauteur(); i++) {
        for (int j = 0; j < grille->getLargeur(); j++) {

            grille->setArrItem(new Item());

            Bonbon itemName = generateItem(1, 6); // 6 Textures max
            if (i > 1) {
                if (grille->getArrItem(i - 1, j)->getName() == itemName && grille->getArrItem(i - 2, j)->getName() == itemName) {
                    itemName = generateItemWithExcludeItem(1, 6, (int)itemName);
                }
            }

            if (j > 1) {
                if (grille->getArrItem(i, j - 1)->getName() == itemName && grille->getArrItem(i, j - 2)->getName() == itemName) {
                    itemName = generateItemWithExcludeItem(1, 6, (int)itemName);
                }
            }

            grille->getArrItem(i, j)->setName(itemName);

            grille->getArrItem(i, j)->getSprite()->setTexture(*grille->getTexture(itemName));
            UpdateSizeItem(grille->getArrItem(i, j), i, j);
        }
    }
}


void dessinerJeu(Grille* grille) {

    window.clear(sf::Color::Black);

    for (int i = 0; i < grille->getHauteur(); i++) {
        for (int j = 0; j < grille->getLargeur(); j++) {
            if (grille->getArrItem(i, j)->getName() == Bonbon::AUCUN)
                continue;

            window.draw(*grille->getArrItem(i, j)->getSprite());
        }
    }

    window.display();
}

void UpdateGrille() {
    for (int i = 0; i < grille->getHauteur(); i++) {
        for (int j = 0; j < grille->getLargeur(); j++) {

            UpdateSizeItem(grille->getArrItem(i, j), i, j);

        }
    }
}

void UpdateSizeItem(Item* item, int i, int j) {
    item->getSprite()->setScale(sizeSprite, sizeSprite);
    //item->getSprite()->move(0, sizeCell);
    item->getSprite()->setPosition(j * sizeCell + xFirstPoint, i * sizeCell + yFirstPoint);
}

//Min et max son inclu dans le rand
Bonbon generateItem(int min, int max) {
    Bonbon b;

    min -= 1;
    max -= 1;

    int random = rand() % max + min;

    return (Bonbon)random;
}

Bonbon generateItemWithExcludeItem(int min, int max, int valueExclude) {
    Bonbon b;

    min -= 1;
    max -= 1;

    if (valueExclude > max || valueExclude < min) {
        int random = rand() % max + min;

        return (Bonbon)random;
    }

    if (valueExclude == max) {
        int random = rand() % (max - 1) + min;

        return (Bonbon)random;
    }
    else if (valueExclude == min) {
        int random = rand() % max + (min + 1);

        return (Bonbon)random;
    }
    else {
        int random1;
        if (valueExclude == 1) {
            random1 = 0;
        }
        else {
            random1 = rand() % (valueExclude - 1) + min;
        }

        int random2 = rand() % max + (valueExclude + 1);

        if (random1 > max) {
            return (Bonbon)random2;
        }

        if (random2 > max) {
            return (Bonbon)random1;
        }

        int random = rand() % 2;

        if (random == 0)
            return (Bonbon)random1;

        return (Bonbon)random2;
    }
}
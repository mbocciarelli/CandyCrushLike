//
// Created by Daniel Chiquet on 12/11/2021.
//


#include <iostream>
#include "../headers/sfml_test.h"


int wWidth = 1800;
int wHeight = 1200;


int sfml_test(Grille grille) {
    auto *tabClick = new Click[2];

    tabClick[0] = Click(0, 0, 0);
    tabClick[1] = Click(0, 0, 0);

    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");

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

        window.clear(sf::Color::Black);
        CreateGrille(window, grille);
        window.display();
    }
    return 0;
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

}

void CreateGrille(sf::RenderWindow& window, Grille grille){
    int l = grille.getHauteur();
    int c = grille.getLargeur();

    for (unsigned int i = 0; i < (wWidth / 8); i++) {
        sf::Vertex line[] =
                {
                        sf::Vertex(sf::Vector2f(i * (wWidth / c), 0), sf::Color::White),
                        sf::Vertex(sf::Vector2f(i * (wWidth / c), wHeight), sf::Color::White)
                };
        window.draw(line, 2, sf::Lines);
    }
    for (unsigned int i = 0; i < (wHeight / 8); i++) {
        sf::Vertex line[] =
                {
                        sf::Vertex(sf::Vector2f(0, i * (wHeight / l)), sf::Color::White),
                        sf::Vertex(sf::Vector2f(wWidth, i * (wHeight / l)), sf::Color::White)
                };
        window.draw(line, 2, sf::Lines);
    }
}

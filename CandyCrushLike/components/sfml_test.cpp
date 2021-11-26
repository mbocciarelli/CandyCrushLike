//
// Created by Daniel Chiquet on 12/11/2021.
//


#include <iostream>
#include "../headers/sfml_test.h"
#include "../SFML/Graphics.hpp"


int wWidth = 1800;
int wHeight = 1200;


int sfml_test() {
    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "SFML works!");
/*
    sf::CircleShape shape(100.f);
    shape.setPosition(0.f, 0.f);
    shape.setFillColor(sf::Color::Green);

    sf::CircleShape shape2(100.f);
    shape2.setPosition(10.f, 0.f);
    shape2.setFillColor(sf::Color::Red);

    sf::CircleShape shape3(100.f);
    shape3.setPosition(300.f, 100.f);
    shape3.setFillColor(sf::Color::Blue);
*/
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    std::cout << "the left button was released" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
            }


        }


        window.clear(sf::Color::Black);
        for (unsigned int i = 0; i < (wWidth / 8); i++) {
            sf::Vertex line[] =
                    {
                            sf::Vertex(sf::Vector2f(i * (wWidth / 8), 0), sf::Color::White),
                            sf::Vertex(sf::Vector2f(i * (wWidth / 8), wHeight), sf::Color::White)
                    };
            window.draw(line, 2, sf::Lines);
        }
        for (unsigned int i = 0; i < (wHeight / 8); i++) {
            sf::Vertex line[] =
                    {
                            sf::Vertex(sf::Vector2f(0, i * (wHeight / 8)), sf::Color::White),
                            sf::Vertex(sf::Vector2f(wWidth, i * (wHeight / 8)), sf::Color::White)
                    };
            window.draw(line, 2, sf::Lines);
        }
        window.display();
    }
    return 0;
}
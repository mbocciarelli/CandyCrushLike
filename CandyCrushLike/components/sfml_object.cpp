//
// Created by Daniel Chiquet on 12/11/2021.
//

#include "../headers/sfml_object.h"

sfml_object::sfml_object() {}

void sfml_object::createWindow() {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    this->window = &window;
}

void sfml_object::testCircle() {
    sf::RenderWindow *window = this->window;
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear();
        window->draw(shape);
        window->display();
    }
}



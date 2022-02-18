//
// Created by Daniel Chiquet on 12/11/2021.
//
#include "../SFML/Graphics.hpp"

class sfml_object {
private:
    sf::RenderWindow *window;
public:
    sfml_object();

public:
    void createWindow();



    void testCircle();
};

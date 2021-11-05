#include <SFML/Graphics.hpp>
#include "Grille.h"
#include "Item.h"

int main()
{
    /*sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }*/

    Item* tab[2][2];
    
    tab[0][0] = new Item("a");
    tab[1][0] = new Item("b");
    tab[0][1] = new Item("a");
    tab[1][1] = new Item("a");

    Grille grille = new Grille(2, 2);
    grille.setTab(*tab);
    grille.afficher();
    return 0;
}
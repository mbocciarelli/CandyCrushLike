#pragma once

#include <string>
#include <SFML/Graphics/Sprite.hpp>
#include "../headers/Bonbon.h"

class Item {
private:
    sf::Sprite* s;
    Bonbon name;

public:
    Item();

    Item(sf::Sprite*, Bonbon);

    Bonbon regenerateItem(int min, int max);


    /* Getter & Setter*/
    void setSprite(sf::Sprite* sprite) {
        s = sprite;
    };

    sf::Sprite* getSprite() {
        return s;
    };

    void setName(Bonbon name) {
        this->name = name;
    };

    Bonbon getName() const {
        return name;
    };
};


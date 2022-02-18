#include "../headers/Item.h"

Item::Item() {
	s = new sf::Sprite();
}

Item::Item(sf::Sprite* sprite, Bonbon name)
	: s(sprite), name(name) {

}

Bonbon Item::regenerateItem(int min, int max) {
    Bonbon b;

    min -= 1;
    max -= 1;

    int random = rand() % max + min;

    this->name = (Bonbon)random;
    return (Bonbon)random;
}


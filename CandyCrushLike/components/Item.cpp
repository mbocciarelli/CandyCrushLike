#include "../headers/Item.h"

Item::Item() {
    name = Bonbon::AUCUN;
	s = new sf::Sprite();
}

Item::Item(sf::Sprite* sprite, Bonbon name)
	: s(sprite), name(name) {

}

Bonbon Item::regenerateItem(int min, int max) {
    min -= 1;
    max -= 1;

    int random = rand() % max + min;

    this->name = (Bonbon)random;
    return (Bonbon)random;
}


#include "../headers/Item.h"

Item::Item() {
	s = new sf::Sprite();
}

Item::Item(sf::Sprite* sprite, Bonbon name)
	: s(sprite), name(name) {

}


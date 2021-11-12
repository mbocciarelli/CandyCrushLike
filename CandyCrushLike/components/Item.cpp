#include "../headers/Item.h"

Item::Item() {
}
Item::Item(std::string name) {
    this->name = name;
}

std::string Item::getName() {
    return this->name;
}

void Item::setName(std::string name) {
    this->name = name;
}


//
// Created by Daniel Chiquet on 05/11/2021.
//

#include "../headers/candy.h"

Candy::Candy() {}

Candy::Candy(const string &name, int id) : name(name), id(id) {}

const string &Candy::getName() const {
    return name;
}

void Candy::setName(const string &name) {
    Candy::name = name;
}

int Candy::getId() const {
    return id;
}

void Candy::setId(int id) {
    Candy::id = id;
}

Candy::~Candy() {

}



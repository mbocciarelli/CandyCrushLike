//
// Created by Daniel Chiquet on 05/11/2021.
//

#ifndef HELLOSFML_CANDY_H
#define HELLOSFML_CANDY_H

#include <iostream>
#include "main.h"

using namespace std;

class Candy{
private:
    string name;
    int id;

public:
    Candy();

    Candy(const string &name, int id);

    const string &getName() const;

    void setName(const string &name);

    int getId() const;

    void setId(int id);

    virtual ~Candy();

};
#endif //HELLOSFML_CANDY_H

#pragma once

#include <string>

class Item {
private:
    std::string name;

public:
    Item();

    Item(std::string);

    std::string getName();

    void setName(std::string name);
};


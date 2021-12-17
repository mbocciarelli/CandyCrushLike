//
// Created by Daniel Chiquet on 26/11/2021.
//

#include <SFML/Window/Event.hpp>
#include "Grille.h"

class Click {
private:
    int status;
    int col;
    int line;
public:
    Click(int status, int col, int line);

    Click();

    int getStatus() const;

    void setStatus(int status);

    int getCol() const;

    void setCol(int col);

    int getLine() const;

    void setLine(int line);

    void print() const;
};

int compareClick(Click *tabClick);

Click where_is_clic(sf::Event event, Grille grille, int wWidth, int wHeight);

bool LeftOrRightBox(Click c1, Click c2);

bool UpperOrBottomBox(Click c1, Click c2);

bool SameBox(Click c1, Click c2);

//
// Created by Daniel Chiquet on 26/11/2021.
//

#include "../headers/Click.h"

Click::Click() {}

Click::Click(int status, int col, int line) : status(status), col(col), line(line) {}

int Click::getStatus() const {
    return status;
}

void Click::setStatus(int status) {
    Click::status = status;
}

int Click::getCol() const {
    return col;
}

void Click::setCol(int col) {
    Click::col = col;
}

int Click::getLine() const {
    return line;
}

void Click::setLine(int line) {
    Click::line = line;
}

void Click::print() const{
    std::cout << "clic :\ncol : " <<Click::col<< "\nline : " <<Click::line<< std::endl;
}


int compareClick(Click* tabClick) {
    Click c1 = tabClick[0];
    Click c2 = tabClick[1];
    if(UpperOrBottomBox(c1,c2)){
        return 1;
    }
    if(LeftOrRightBox(c1,c2)){
        return 2;
    }
    if(SameBox(c1,c2)){
        return 3;
    }
    else{
        return 0;
    }
}

Click where_is_clic(sf::Event event, Grille grille, int wWidth, int wHeight) {
    int size_col = wWidth / grille.getLargeur();
    int size_line = wHeight / grille.getHauteur();
    int col = (event.mouseButton.x / size_col) + 1;
    int line = (event.mouseButton.y / size_line) + 1;



    Click c(1, col, line);
    c.print();

    return c;

}

bool LeftOrRightBox(Click c1, Click c2) {
    return (c1.getCol() == c2.getCol() - 1 || c1.getCol() == c2.getCol() + 1) && (c1.getLine() == c2.getLine());
}

bool UpperOrBottomBox(Click c1, Click c2) {
    return (c1.getCol() == c2.getCol()) && (c1.getLine() == c2.getLine()+1 || c1.getLine() == c2.getLine()-1);
}

bool SameBox(Click c1, Click c2) {
    return (c1.getCol() == c2.getCol()) && (c1.getLine() == c2.getLine());
}


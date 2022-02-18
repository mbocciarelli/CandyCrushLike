#include "../headers/Grille.h"
#include <stdio.h>
#include "../headers/Item.h"
#include <iostream>

Grille::Grille() {
    this->hauteur = 10;
    this->largeur = 10;
    this->array.reserve(hauteur * largeur);

    for (int i = 0; i < 6; i++) {
        bonbonToDestroy.emplace((Bonbon)i, 0);
    }

}

Grille::Grille(int h, int l) {
    this->hauteur = h;
    this->largeur = l;
    this->array.reserve(hauteur * largeur);

    for (int i = 0; i < 6; i++) {
        bonbonToDestroy.emplace((Bonbon)i, 0);
    }

}

bool Grille::checkIfPlayable() {

    bool gridIsPlayable = false;

    for (int i = 0; i < getHauteur(); i++) {
        for (int j = 0; j < getLargeur(); j++) {
            if (j == 0) {
                if (i == 0) {
                    /*
                    Pattern check ex:
                            Random Rouge Rouge
                            Rouge Random Random
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(0, 1), offset(0, 2), offset(1, 0));

                    /*
                    Pattern check ex:
                            Random Rouge
                            Rouge Random
                            Rouge Random
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(1, 0), offset(2, 0), offset(0, 1));
                }
                else if (i == getHauteur() - 1) {
                    /*
                    Pattern check ex:
                            Rouge Random Random
                            Random Rouge Rouge
                    */

                    gridIsPlayable = IsSameBonbon(i, j, offset(0, 1), offset(0, 2), offset(-1, 0));

                    /*
                    Pattern check ex:
                            Rouge Random
                            Rouge Random
                            Random Rouge
                    */

                    gridIsPlayable = IsSameBonbon(i, j, offset(-1, 0), offset(-2, 0), offset(0, 1));
                }
                else {
                    /*
                    Pattern check ex:
                            Rouge Random Random
                            Random Rouge Rouge
                            Rouge Random Random
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(0, 1), offset(0, 2), offset(1, 0));

                    gridIsPlayable = IsSameBonbon(i, j, offset(0, 1), offset(0, 2), offset(-1, 0));

                    /*
                    Pattern check ex:
                            Rouge Random
                            Random Rouge
                            Rouge Random
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(-1, 0), offset(1, 0), offset(0, 1));

                }
            }
            else if (j == getLargeur() - 1) {
                if (i == 0) {
                    /*
                    Pattern check ex:
                            Rouge Rouge Random
                            Random Random Rouge
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(0, -1), offset(0, -2), offset(1, 0));

                    /*
                    Pattern check ex:
                            Rouge Random
                            Random Rouge
                            Random Rouge
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(1, 0), offset(2, 0), offset(1, 0));
                }
                else if (i == getHauteur() - 1) {
                    /*
                    Pattern check ex:
                            Random Random Rouge
                            Rouge Rouge Random
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(0, -1), offset(0, -2), offset(-1, 0));

                    /*
                    Pattern check ex:
                            Random Rouge
                            Random Rouge
                            Rouge Random
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(-1, 0), offset(-2, 0), offset(0, -1));
                }
                else {
                    /*
                    Pattern check ex:
                            Random Random Rouge
                            Rouge Rouge Random
                            Random Random Rouge
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(0, -1), offset(0, -2), offset(1, 0));

                    gridIsPlayable = IsSameBonbon(i, j, offset(0, -1), offset(0, -2), offset(-1, 0));
                    /*
                    Pattern check ex:
                            Random Rouge
                            Rouge Random
                            Random Rouge
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(0, 1), offset(0, -1), offset(-1, 0));
                }
            }
            else
            {
                if (i == 0) {

                    /*
                    Pattern check ex:
                            Rouge Random Rouge
                            Random Rouge Random
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(0, -1), offset(0, 1), offset(1, 0));

                    /*
                    Pattern check ex:
                            Rouge Random Rouge
                            Random Rouge Random
                            Random Rouge Random
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(1, 0), offset(2, 0), offset(0, 1));

                    gridIsPlayable = IsSameBonbon(i, j, offset(0, 1), offset(2, 0), offset(0, -1));
                }
                else if (i == getHauteur() - 1) {

                    /*
                    Pattern check ex:
                            Random Rouge Random
                            Rouge Random Rouge
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(0, -1), offset(0, 1), offset(-1, 0));

                    /*
                    Pattern check ex:
                            Random Rouge Random
                            Random Rouge Random
                            Rouge Random Rouge
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(-1, 0), offset(-2, 0), offset(0, 1));

                    gridIsPlayable = IsSameBonbon(i, j, offset(-1, 0), offset(-2, 0), offset(0, -1));
                }
                else {
                    /*
                    Pattern check ex:
                            Random Rouge Random
                            Rouge Random Rouge
                            Random Rouge Random
                    */
                    gridIsPlayable = IsSameBonbon(i, j, offset(0, -1), offset(0, 1), offset(1, 0));

                    gridIsPlayable = IsSameBonbon(i, j, offset(0, -1), offset(0, 1), offset(-1, 0));

                    gridIsPlayable = IsSameBonbon(i, j, offset(-1, 0), offset(1, 0), offset(0, 1));

                    gridIsPlayable = IsSameBonbon(i, j, offset(0, 1), offset(0, 1), offset(-1, 0));
                }
            }

            if (gridIsPlayable)
                return true;
        }
    }

    return false;
}

void Grille::testLineColumn(Bonbon& previousCandy, int* nb, std::vector<Cell>* tempPositions, int l, int h) {
    Bonbon candyTest;
    candyTest = getArrItem(h, l)->getName();

    if (previousCandy == candyTest && candyTest != Bonbon::AUCUN) {
        tempPositions->push_back(Cell(h, l));
        *nb = *nb + 1;
    }
    else {
        if (*nb >= 3) {
            for (int i = 0; i < tempPositions->size(); i++)
                arrayToDestruct.push_back(tempPositions->at(i));
        }
        previousCandy = candyTest;
        tempPositions->clear();
        tempPositions->push_back(Cell(h, l));
        *nb = 1;
    }
}

bool Grille::CheckMatch() {
   Bonbon previousCandy = Bonbon::AUCUN;
    int nb = 1;
    std::vector<Cell> tempPositions;
    for (int h = 0; h < this->hauteur; h++) {
        for (int l = 0; l < this->largeur; l++) {
            testLineColumn(previousCandy, &nb, &tempPositions, l, h);
        }
        previousCandy = Bonbon::AUCUN;
    }
    previousCandy = Bonbon::AUCUN;
    for (int l = 0; l < this->largeur; l++) {
        for (int h = 0; h < this->hauteur; h++) {
            testLineColumn(previousCandy, &nb, &tempPositions, l, h);
        }
        previousCandy = Bonbon::AUCUN;
    }
    return (this->arrayToDestruct.size() > 0);
}

bool Grille::IsSameBonbon(int hauteur, int largeur, offset item1, offset item2, offset item3) {

    if (getArrItem(hauteur + item1.hauteur, largeur + item1.largeur)->getName() == getArrItem(hauteur + item2.hauteur, largeur + item2.largeur)->getName()
        && getArrItem(hauteur + item1.hauteur, largeur + item1.largeur)->getName() == getArrItem(hauteur + item3.hauteur, largeur + item3.largeur)->getName()
        && getArrItem(hauteur + item1.hauteur, largeur + item1.largeur)->getName() != getArrItem(hauteur, largeur)->getName())
    {
        return true;
    }

    return false;
}

void Grille::DestroyCells() {
    std::cout << "(new_move)" << std::endl;
    for (int i = 0; i < arrayToDestruct.size(); i++) {
        std::cout << "(" << arrayToDestruct.at(i).h << "," << arrayToDestruct.at(i).l << ")" << std::endl;
        int h = arrayToDestruct.at(i).h;
        int l = arrayToDestruct.at(i).l;

        Bonbon name = getArrItem(h, l)->getName();
        if(name != Bonbon::AUCUN)
            bonbonToDestroy.at(name)++;

        getArrItem(h, l)->setName(Bonbon::AUCUN);
    }

    arrayToDestruct.clear();
}

void Grille::ReorganizeCells() {
    for (int i = getHauteur() - 1; i >= 0; i--) {
        for (int j = getLargeur() - 1; j >= 0; j--) {
            if (getArrItem(i, j)->getName() == Bonbon::AUCUN) {
                int saveHauteur = i;
                do {
                    saveHauteur--;
                } while (saveHauteur > 0 && getArrItem(saveHauteur, j)->getName() == Bonbon::AUCUN);
                
                if (saveHauteur >= 0 && getArrItem(saveHauteur, j)->getName() != Bonbon::AUCUN) {
                    SwapCell(Cell(saveHauteur, j), Cell(i, j));
                }
            }
        }
    }
}

void Grille::RegenerateCells() {
    for (int h = 0; h < getHauteur(); ++h) {
        for (int l = 0; l < getLargeur(); ++l) {
            if (getArrItem(h, l)->getName() == Bonbon::AUCUN) {
                Bonbon name = getArrItem(h, l)->regenerateItem(1, 6);
                getArrItem(h, l)->getSprite()->setTexture(*getTexture(name));
            }
        }
    }
}


void Grille::SwapCell(Cell from, Cell to) {
    Item* fromItem = getArrItem(from.h, from.l);
    Item* toItem = getArrItem(to.h, to.l);

    Bonbon temp = fromItem->getName();
    fromItem->setName(toItem->getName());
    toItem->setName(temp);

    if (fromItem->getName() != Bonbon::AUCUN) {
        fromItem->getSprite()->setTexture(*getTexture(fromItem->getName()));
    }
    if (toItem->getName() != Bonbon::AUCUN) {
        toItem->getSprite()->setTexture(*getTexture(toItem->getName()));
    }
}

#include <iostream>
#include "./headers/main.h"

int main()
{

    /*Grille grille = new Grille(2, 2);
    //Item tab = grille.getArray()

    grille.setArrItem(0, 0,  Item("aa"));
    grille.setArrItem(0, 1, Item("ab"));
    grille.setArrItem(1, 0, Item("ba"));
    grille.setArrItem(1, 1, Item("bb"));

    grille.afficher();

    //std::cout << "coucou" << std::endl;*/
    /*sfml_object o_sfml;
    o_sfml.createWindow();
    o_sfml.testCircle();*/
    Grille grille = new Grille(10, 16);
    sfml_test(grille);

    return 0;
}
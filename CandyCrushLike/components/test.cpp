//
// Created by Daniel Chiquet on 12/11/2021.
//

#include "../headers/test.h"
#include <iostream>

using namespace std;

struct A {
    A() { cout << "A"; }
};

struct B {
    B() { cout << "B"; }
};

struct C {
    C() { cout << "C"; }
};

struct D {
    D() { cout << "D"; }
};

struct E : D {
    E() { cout << "E"; }
};

struct F : A, B {
    C c;
    D d;
    E e;

    F() { cout << "F"; }
};

int test() {
    F object;
    cout << endl << sizeof(F) << endl;
    return 0;
}
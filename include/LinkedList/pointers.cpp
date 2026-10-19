// David Alonso Cantú Delgado
// A00189239
#include <iostream>
#include <memory>
using namespace std;

#include "Fraction.h"

int main() {

    int x = 42;
    int* p = &x;
    
    cout << x << endl;
    cout << &x << endl;
    cout << p << endl;
    cout << *p << endl;

    cout << "valores de q" << endl;
    int* q = new int(5);
    cout << q << endl;
    cout << *q << endl;

    delete q;
    cout << q << endl;
    cout << *q << endl;

    Fraction* f = new Fraction(2, 3);

    f->print();
    cout << f->getDenominator() << "/" << f->getNumerator() << endl;
    delete f;
    f = nullptr;

    std::unique_ptr<Fraction> g = std::make_unique<Fraction>(3, 4);
    g->print();
    cout << g->getDenominator() << "/" << g->getNumerator() << endl;


    return 0;
}
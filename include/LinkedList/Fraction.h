// David Alonso Cantú Delgado
// A00189239
#ifndef Fraction_h
#define Fraction_h
#include <iostream>
// define una clase fracción básica
class Fraction {
private:
    int numerator;
    int denominator;
public:
    Fraction() : numerator(0), denominator(1) {}
    Fraction(int num, int den) : numerator(num), denominator(den) {}

    int getNumerator() const {
        return numerator;
    }

    int getDenominator() const {
        return denominator;
    }

    void setNumerator(int num) {
        numerator = num;
    }

    void setDenominator(int den) {
        denominator = den;
    }

    void print() const {
        std::cout << numerator << "/" << denominator << std::endl;
    }   

    
};



#endif /* Fraction_h */
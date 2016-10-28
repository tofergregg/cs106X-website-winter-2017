#pragma once

#include<ostream>
using namespace std;

class Fraction {
public:
    Fraction();
    Fraction(int num,int denom);

    void add(Fraction f);
    void mult(Fraction f);
    float dec();
    int get_num();
    int get_denom();
    friend ostream& operator<<(ostream& out, Fraction &frac);
private:
    int num;   // the numerator
    int denom; // the denominator
    void reduce(); // reduce the fraction to lowest terms
    int gcd(int u, int v);
};

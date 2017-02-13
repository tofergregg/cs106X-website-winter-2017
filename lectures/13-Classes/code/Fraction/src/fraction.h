#pragma once

#include<ostream>
using namespace std;

class Fraction {
public:
    Fraction();
    Fraction(int num,int denom);

    void add(Fraction f);
    void mult(Fraction f);
    float decimal();
    int getNum();
    int getDenom();
    friend ostream& operator<<(ostream& out, Fraction &frac);
    friend Fraction operator*(const Fraction &first, const Fraction &second);
private:
    int num;   // the numerator
    int denom; // the denominator
    void reduce(); // reduce the fraction to lowest terms
    int gcd(int u, int v);
};

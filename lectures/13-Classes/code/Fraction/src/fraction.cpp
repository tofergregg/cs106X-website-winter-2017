#include <iostream>
#include "fraction.h"

// purpose: the default constructor to create
//          a fraction of 1 / 1
// arguments: none
// return value: none (constructors don't return)
Fraction::Fraction()
{
    num = 1;
    denom = 1;
}

// purpose: an overloaded constructor
//          to create a custom fraction
//	        that immediately gets reduced
// arguments: an int numerator
//            and an int denominator
Fraction::Fraction(int num, int denom)
{
    this->num = num;
    this->denom = denom;

    // reduce in case we were given
    // an unreduced fraction
    reduce();
}

// getters for numerator and denominator
int Fraction::getNum() {
    return num;
}

int Fraction::getDenom() {
    return denom;
}

// purpose: to add another fraction
// with this one with the result being
// stored in this fraction
// arguments: another fraction
// return value: none
void Fraction::add(Fraction other) {
        // calculate the new numerator
        int new_num = num * other.denom + other.num * denom;

        // calculate the new denominator
        int new_denom = denom * other.denom;

        // replace our values with the new values
        num = new_num;
        denom = new_denom;

        // reduce the fraction
        reduce();
}

// purpose: to multiply another fraction
// with this one with the result being
// stored in this fraction
// arguments: another fraction
// return value: none
void Fraction::mult(Fraction other)
{
    // multiplies a Fraction
    // with this Fraction
    num *= other.num;
    denom *= other.denom;

    // reduce the fraction
    reduce();
}

// purpose: To return a decimal
// value of our fraction
// arguments: None
// return value: the decimal
//               value of this fraction
float Fraction::decimal()
{
    // returns the decimal
    // value of our fraction
    return (float)num / denom;
}


// purpose: To reduce the fraction
// arguments: None
// return value: None
void Fraction::reduce() {
    // reduce the fraction to lowest terms
    // find the greatest common divisor
    int frac_gcd = gcd(num,denom);

    // reduce by dividing num and denom
    // by the gcd
    num = num / frac_gcd;
    denom = denom / frac_gcd;
}

// purpose: To recursively find the greatest
// common divisor
// arguments: two integers
// return value: the gcd of the two integers
int Fraction::gcd(int u, int v) {
    if (v != 0) {
        return gcd(v,u%v);
    }
    else {
        return u;
    }
}


// purpose: To overload the << operator
// for use with cout
// arguments: a reference to an outstream and the
//            fraction we are using
// return value: a reference to the outstream
ostream& operator<<(ostream& out, Fraction &frac) {
    out << frac.num << "/" << frac.denom;
    return out;
}

Fraction operator*(const Fraction &first, const Fraction &second) {
    int newNum = first.num * second.num;
    int newDenom = first.denom * second.denom;

    return Fraction(newNum, newDenom); // will be reduced automatically
}


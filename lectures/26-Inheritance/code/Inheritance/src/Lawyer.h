/*
 * CS 106B, Marty Stepp
 * This file declares the Lawyer class, a subclass
 * (child class, derived class) in our inheritance hierarchy.
 */

#pragma once

#include "Employee.h"
#include <string>

// Employee edna("Edna Smith", 5);
// Lawyer lisa("Lisa Fiedler", "Stanford", 7);
// lisa.salary()

class Lawyer : public Employee {
    // I now have an hours, name, salary, etc. method. yay!
public:
    Lawyer(string name, string lawSchool, int years);
    virtual double salary() const;
    void sue(string person);

private:
    string myLawSchool;
};

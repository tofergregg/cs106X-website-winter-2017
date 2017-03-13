/*
 * CS 106B, Marty Stepp
 * This file declares the Employee class, the parent (base) class in
 * our inheritance hierarchy.
 */

#pragma once

#include <string>
using namespace std;

// A class to represent employees in general.
class Employee {
public:
    Employee(string name, int years);
    virtual int hours() const;
    virtual string name() const;
    virtual double salary() const;
    virtual int vacationDays() const;
    virtual string vacationForm() const;
    virtual int years() const;
    // virtual string getFavoritePokemon() = 0;

private:
    string myName;
    int myYears;
};







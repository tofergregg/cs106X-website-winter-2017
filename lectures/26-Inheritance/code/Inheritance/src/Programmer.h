/*
 * CS 106B, Marty Stepp
 * This file declares the Programmer class, a subclass
 * (child class, derived class) in our inheritance hierarchy.
 */

#pragma once

#include "Employee.h"

class Programmer : public Employee {
public:
    Programmer(string name, int years);
    virtual string vacationForm() const;
    virtual void code();
};

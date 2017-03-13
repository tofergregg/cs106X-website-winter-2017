/*
 * CS 106B, Marty Stepp
 * This file declares several classes in an inheritance hierarchy.
 * We write the method implementations in the .h file for brevity
 * rather than separating it into a .h and .cpp.
 */

#pragma once

#include <iostream>
using namespace std;

class Snow {
public:
    virtual void method2() {
        cout << "Snow 2" << endl;
    }

    void method3() {
        cout << "Snow 3" << endl;
    }
};

class Rain : public Snow {
public:
    virtual void method1() {
        cout << "Rain 1" << endl;
    }

    virtual void method2() {
        cout << "Rain 2" << endl;
    }
};

class Sleet : public Snow {
public:
    virtual void method2() {
        cout << "Sleet 2" << endl;
        Snow::method2();
        method3();
    }

    void method3() {
        cout << "Sleet 3" << endl;
    }
};

class Fog : public Sleet {
public:
    virtual void method1() {
        cout << "Fog 1" << endl;
    }

    void method3() {
        cout << "Fog 3" << endl;
    }
};


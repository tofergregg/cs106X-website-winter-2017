
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "ourStack.h"
#include "simpio.h"
using namespace std;

int myMethod(string param);

int main() {
    OurStack stack("hello");
    for (int i = 0; i < 10; i++) {
        stack.push(i);
        cout << "push " << i << endl;
    }

    cout << endl;
    cout << "Top element is " << stack.peek() << endl;
    cout << "popping..." << endl;

    while (!stack.isEmpty()) {
        cout << stack.pop() << " ";
    }
    cout << endl;
    return 0;
}

int myMethod(string param) {
    return 5;
}

// Mystery function -- what is the output?
#include <iostream>
#include "console.h"

using namespace std;

// Function Definition and Code
void mystery(int& b, int c, int& a) {
    a++;
    b--;
    c += a;
}

// main
int main() {
    int a = 5;
    int b = 2;
    int c = 8;
    mystery(c, a, b);
    cout << a << " " << b << " " << c << endl;
    return 0;
}

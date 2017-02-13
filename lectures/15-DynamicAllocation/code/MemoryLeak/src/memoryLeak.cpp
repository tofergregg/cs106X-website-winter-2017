// Note: You probably don't want to run this program as is.
// It will thrash your memory, and you may not be able to quit
// the program and will have to restart your machine.

// The point of hte program is to demonstrate that allocating
// and lots of memory without deleting it is bad for your system.

#include<iostream>
#include "console.h"
using namespace std;

const int INIT_CAPACITY = 10000000;

class Demo {
public:
    Demo(); // constructor
    string at(int i);
private:
    string *bigArray;
};

Demo::Demo()
{
    bigArray = new string[INIT_CAPACITY];
    for (int i=0;i<INIT_CAPACITY;i++) {
        bigArray[i] = "Lalalalalalalalala!";
    }
}

string Demo::at(int i)
{
    return bigArray[i];
}

int main()
{
    for (int i=0;i<10000;i++){
        Demo demo;
        cout << i << ": " << demo.at(1234) << endl;
    }
    return 0;
}

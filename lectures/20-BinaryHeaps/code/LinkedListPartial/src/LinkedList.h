#include <iostream>
#include <string>
#include <ostream>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
using namespace std;

struct Node {
    string key;
    double value;
    Node *link;
};

class LinkedList {
public:
    // constructor
    LinkedList();

    // destructor
    ~LinkedList();

    void insert(string key, double value);
    void clear();
    friend ostream &operator<<(ostream &out, LinkedList &list);
private:
    Node *head;
};

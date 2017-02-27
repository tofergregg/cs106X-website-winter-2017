#include <iostream>
#include <ostream>

using namespace std;

struct Node {
    string str;
    Node *left;
    Node *right;

    // constructor for new Node
    Node(string s) {
        str = s;
        left = NULL;
        right = NULL;
    }
};

class StringSet {
public:
    // constructor
    StringSet();

    // destructor
    ~StringSet();

    // adds a string to the BST
    void add(string s);

    // returns the string earliest  in the alphabet (empty string if not found)
    string findMin();

    // returns the string farthest in the alphabet (empty string if not found)
    string findMax();

    // returns true if the set contains the element
    bool contains(string s);

    // removes string from the set
    void remove(string s);

    // returns number of elements in the set
    int size();

    // returns true if zero elements
    bool isEmpty();

    // overloads << to print set in order
    friend ostream &operator<<(ostream &out, StringSet &set);

private:
    Node *root;
    int count;
    // helper functions
    void add(string s, Node *&node);
    string findMin(Node *node);
    string findMax(Node *node);
    bool contains(string &s, Node *node);
    Node *remove(string &s, Node *node, Node *parent);
    void inOrderTraversal(ostream &out, Node *node, string &max);
    void postOrderClear(Node *node);
};

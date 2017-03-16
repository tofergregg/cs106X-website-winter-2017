// HashMapIntInt.h

#pragma once

const double LOAD_FACTOR_MAX = 0.75;

// linked list Node
struct Node {
    Node() {
        key = 0;
        value = 0;
        next = nullptr;
    }

    Node(int k, int v) {
       key = k;
       value = v;
       next = nullptr;
    }

    int key;
    int value;
    Node *next;
};

class HashMap {
public:
    HashMap(); // constructor
    ~HashMap(); // destructor
    void put(int k, int v);
    bool containsKey(int key);
    void remove(int key);
    void printTable();

    int size();
    int capacity();
    double loadFactor();

private:
    int count;
    int tableCapacity;
    Node **elements;
    int hash(int key);
    void rehash();
};

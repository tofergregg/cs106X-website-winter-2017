// HashMapIntInt.cpp

#include "HashMapIntInt.h"
#include <iostream>

using namespace std;

HashMap::HashMap() {
    // constructor
    count = 0;
    tableCapacity = INIT_CAP;
    elements = new Node *[tableCapacity];
    for (int i=0; i < tableCapacity; i++) {
        elements[i] = nullptr;
    }
}
HashMap::~HashMap() {
    for (int i=0; i < tableCapacity; i++) {
        Node *node = elements[i];
        while (node != nullptr) {
            Node *temp = node->next;
            delete node;
            node = temp;
        }
    }
    delete [] elements;
}
void HashMap::put(int k, int v) {
    int index = hash(k);
    // check if exists
    Node *curr = elements[index];
    while (curr != nullptr) {
        if (curr->key == k) {
            curr->value = v;
            return;
        }
        curr = curr->next;
    }
    // doesn't exist, so insert at head

    Node *newNode = new Node(k, v);
    newNode->next = elements[index];
    elements[index] = newNode;
    count++;

    // check for need to rehash
    if (loadFactor() > LOAD_FACTOR_MAX) {
        rehash();
    }
}

bool HashMap::containsKey(int key) {
    int index = hash(key);
    // attempt to find in bucket
    Node *curr = elements[index];
    while (curr != nullptr) {
        if (curr->key == key) {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

void HashMap::remove(int key) {
    int index = hash(key);
    // find and remove
    Node *curr = elements[index];
    Node *prev = nullptr;
    while (curr != nullptr) {
        if (curr->key == key) {
            if (prev == nullptr) {
                elements[index] = curr->next;
                delete curr;
            } else {
                prev->next = curr->next;
                delete curr;
            }
            count--;
        }
        prev = curr;
        curr = curr->next;
    }
}
void HashMap::printTable() {
    for (int i=0; i < tableCapacity; i++) {
        cout << i << ": {";
        Node *curr = elements[i];
        while (curr != nullptr) {
            cout << "(" << curr->key << "," << curr->value << "), ";
            curr = curr->next;
        }
        cout << "}" << endl;
    }
    cout << endl;
}

int HashMap::size() {
    return count;
}

int HashMap::capacity() {
    return tableCapacity;
}

double HashMap::loadFactor() {
    return count / (double) tableCapacity;
}


int HashMap::hash(int key) {
    //return (2 * key + 1) % tableCapacity;
    return abs(key) % tableCapacity;
}

void HashMap::rehash() {
    // rehash all elements
    // first, save the old elements array
    Node **origElements = elements;
    int origCapacity = tableCapacity;

    // reset count and update capacity
    count = 0;
    tableCapacity *= 2;
    // create a new elements array
    elements = new Node *[tableCapacity];
    for (int i=0; i < tableCapacity; i++) {
        elements[i] = nullptr; // initialize
    }

    // add new elements by putting
    for (int i=0; i < origCapacity; i++) {
        Node *curr = origElements[i];
        while (curr != nullptr) {
            put(curr->key,curr->value);
            curr = curr->next;
        }
    }

    // clean up old elements
    for (int i=0; i < origCapacity; i++) {
        Node *node = origElements[i];
        while (node != nullptr) {
            Node *temp = node->next;
            delete node;
            node = temp;
        }
    }
    delete [] origElements;
}

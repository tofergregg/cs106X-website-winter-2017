#include "LinkedList.h"

// constructor
LinkedList::LinkedList(){
    head = NULL; // empty list
}

// destructor
LinkedList::~LinkedList(){
    clear(); // just call the clear function, because we have one
}

void LinkedList::insert(string key, double value){
    // create a new node
    Node *newNode = new Node;
    newNode->key = key;
    newNode->value = value;

    // special case
    if (head == NULL) {
        head = newNode;
        head->link = NULL; // must end list
    }
    else {
        // insert at the front
        newNode->link = head;
        head = newNode;
    }
}

void LinkedList::clear(){
    // basic idea: traverse the list and delete all nodes
    while (head != NULL) {
        Node *temp = head->link;
        delete head;
        head = temp;
    }
}

ostream &operator<<(ostream &out, LinkedList &list){
    // print all nodes
    Node *curr = list.head;
    while (curr != NULL) {
        out << "(" << curr->key << "," << curr->value << ")->";
        curr = curr->link;
    }
    out << "NULL";
    return out;
}

/*
 * File: Nim.cpp
 * -------------
 * This program simulates a simple variant of the game of Nim.  In this
 * version, the game starts with a pile of 13 coins on a table.  Players
 * then take turns removing 1, 2, or 3 coins from the pile.  The player
 * who takes the last coin loses.
 */

#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "map.h"
#include "gwindow.h"
#include "timer.h"
#include "grid.h"
#include "strlib.h"
using namespace std;

const int SUSPENSE_ITERS = 5;
const int SUSPENSE_DELAY = 1000;

struct Tree {
    string value;
    Tree * left;
    Tree * right;
};

void introduction() {
    cout << "Welcome to the second episode of the CS106B ";
    cout << "Gameshow. Pick a door and maybe you will win ";
    cout << "a prize!"<< endl;
}

void suspense() {
    cout << "Building suspense..." << endl;
    for(int i = 0; i < SUSPENSE_ITERS; i++) {
        cout << "..." << endl;
        pause(SUSPENSE_DELAY);
    }
}

int getUserChoice() {
    while(true) {
        int choice = getInteger("Door? ");
        if(choice >= 1 && choice <= 3) {
            return choice;
        }
        cout << "Illegal door." << endl;
    }
}

Tree * makeTree(string value) {
    Tree * t = new Tree;
    t->value = value;
    t->left = NULL;
    t->right = NULL;
    return t;
}

// Makes the tree thats on the board!
Tree * initTree() {
    Tree * root = new Tree;
    root->value = "you";

    root->left = makeTree("win");
    root->left->left = makeTree("a");
    root->left->right = makeTree("very");

    root->right = makeTree("big");
    root->right->right = makeTree("prize");

    return root;
}

void doorOne(Tree * tree) {
    if(tree == NULL) return;
    cout << tree->value << " ";
    doorOne(tree->left);
    doorOne(tree->right);
}

void doorTwo(Tree * tree) {
    if(tree == NULL) return;
    doorTwo(tree->left);
    cout << tree->value << " ";
    doorTwo(tree->right);
}

void doorThree(Tree * tree) {
    if(tree == NULL) return;
    doorThree(tree->left);
    doorThree(tree->right);
    cout << tree->value << " ";
}

int main() {
    setConsoleFont("courier-32");
    introduction();
    Tree * tree = initTree();
    int choice = getUserChoice();
    suspense();
    switch (choice) {
        case 1: doorOne(tree); break;
        case 2: doorTwo(tree); break;
        case 3: doorThree(tree); break;
    }
    return 0;
}

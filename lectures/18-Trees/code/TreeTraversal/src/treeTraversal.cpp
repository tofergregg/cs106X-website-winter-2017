/*
 * File: treeTraversal.cpp
 * -------------
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "queue.h"
using namespace std;

struct Tree {
    string value;
    Tree * left;
    Tree * right;
};

Tree * makeTree(string value) {
    Tree * t = new Tree;
    t->value = value;
    t->left = NULL;
    t->right = NULL;
    return t;
}

// Makes the tree
Tree * initTree() {
    Tree * root = new Tree;
    root->value = "this";

    root->left = makeTree("is");
    root->left->left = makeTree("a");
    root->left->right = makeTree("correctly");

    root->right = makeTree("written");
    root->right->right = makeTree("sentence.");

    return root;
}

void preOrder(Tree * tree) {
    if(tree == NULL) {
        return;
    }
    cout << tree->value << " ";
    preOrder(tree->left);
    preOrder(tree->right);
}

void inOrder(Tree * tree) {
    if(tree == NULL) {
        return;
    }
    inOrder(tree->left);
    cout << tree->value << " ";
    inOrder(tree->right);
}

void postOrder(Tree * tree) {
    if(tree == NULL) {
        return;
    }
    postOrder(tree->left);
    postOrder(tree->right);
    cout << tree->value << " ";
}

void levelOrder(Tree *tree) {
    Queue<Tree *>treeQueue;
    treeQueue.enqueue(tree);
    while (!treeQueue.isEmpty()) {
        Tree *node = treeQueue.dequeue();
        cout << node->value << " ";

        // enqueue both left and right, if they exist
        if (node->left != NULL) {
            treeQueue.enqueue(node->left);
        }
        if (node->right != NULL) {
            treeQueue.enqueue(node->right);
        }
    }
}

int main() {
    setConsoleFont("courier-32");
    Tree * tree = initTree();
    cout << "1) Pre-order" << endl;
    cout << "2) In-order" << endl;
    cout << "3) Post-order (Yoda?)" << endl;
    cout << "4) Level-order" << endl << endl;
    int choice = -1;
    while (choice != 0) {
        choice = getInteger("Please choose 1-4 (0 to quit): ");
        switch (choice) {
            case 1: preOrder(tree); break;
            case 2: inOrder(tree); break;
            case 3: postOrder(tree); break;
            case 4: levelOrder(tree); break;
        }
        cout << endl << endl;
    }
    cout << "Goodbye!" << endl;
    return 0;
}

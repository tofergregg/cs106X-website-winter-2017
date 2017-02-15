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

struct Tower {
    string name;
    Tower * link;
};

Tower *createTower(string name, Tower *link) {
   Tower *temp = new Tower;
   temp->name = name;
   temp->link = link;
   return temp;
}

void signal(Tower *start) {
   if (start != NULL) {
      cout << "Lighting " << start->name << endl;
      signal(start->link);
   }
}

int main() {
    Tower * head;




    head = createTower("Rohan", NULL);
    // NOW HEAD HAS A NEW VALUE!!!!!
    head = createTower("Halifirien", head);
    head = createTower("Calenhad", head);
    head = createTower("Min-Rimmon", head);
    head = createTower("Erelas", head);
    head = createTower("Nardol", head);
    head = createTower("Eilenach", head);
    head = createTower("Amon Din", head);
    head = createTower("Minas Tirith", head);

    signal(head);



    return 0;
}

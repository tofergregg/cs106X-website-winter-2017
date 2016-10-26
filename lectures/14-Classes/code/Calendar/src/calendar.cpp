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
#include <cmath>
#include "console.h"
#include "error.h"
#include "simpio.h"
#include "map.h"
#include "timer.h"
#include "vector.h"
#include "grid.h"
#include "strlib.h"
#include "date.h"
using namespace std;

int main() {
    Date today(3,2,2016);
    Date midterm(9, 2, 2016);
    Date valentines(14, 2, 2016);
    Date springBreak(19, 3,2016);
    Date election(8,11,2016);
    Date hugeParty(1,1,2100);

    cout << "today: " << today << endl;
    cout << "valentines day: " << valentines << endl;
    cout << "----" << endl;

    cout << "days until midterm: " << today.daysUntil(midterm) << endl;
    cout << "days until valentines: " << today.daysUntil(valentines) << endl;
    cout << "days until spring break: " << today.daysUntil(springBreak) << endl;
    cout << "days until election: " << today.daysUntil(election) << endl;
    cout << "days until 2100: " << today.daysUntil(hugeParty) << endl;
    cout << "----" << endl;

    cout << "Changing to tomorrow..." << endl;
    today.incrementDay();
    cout << "days until spring break: " << today.daysUntil(springBreak) << endl;
    return 0;
}


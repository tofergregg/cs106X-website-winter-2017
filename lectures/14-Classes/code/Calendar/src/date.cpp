#include "date.h"
#include <iostream>
#include <math.h>
#include "gwindow.h"
#include "gobjects.h"
#include "strlib.h"
using namespace std;

Date::Date(int day, int month, int y) {
    this->day = day;
    this->month = month;
    year = y;
    if(month < 1 || month > 12) {
        throw "Day is not legal";
    }
    if(day < 1 || day > daysInMonth()) {
        throw "Month is not legal";
    }
}

Date::~Date() {
    // don't care
}

int Date::getDay(){
    return day;
}

int Date::getMonth(){
    return month;
}

int Date::getYear(){
    return year;
}

int Date::daysUntil(Date future) {
    Date curr(this->day, this->month, this->year);
    if(future < curr) {
        throw "Date is not in the future";
    }
    int counter = 0;
    while(curr != future) {
        curr.incrementDay();
        counter++;
    }
    return counter;
}

void Date::incrementDay(){
    day++;
    if(day > daysInMonth()) {
        month++;
        day = 1;
    }
    if(month > 12) {
        year++;
        month = 1;
    }
}

int Date::daysInMonth() {
    if(month == 2) {
        return isLeapYear() ? 29 : 28;
    }
    if(month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

bool Date::isLeapYear() {
    if (year % 4 != 0) return false;
    if (year % 100 == 0) {
        // centries years are only leap years if they are also
        // divisible by 400
        return year % 400 == 0;
    }
    return true;
}

bool operator ==(const Date & d1, const Date & d2) {
    if(d1.day != d2.day) return false;
    if(d1.month != d2.month) return false;
    if(d1.year != d2.year) return false;
    return true;
}

bool operator !=(const Date & d1, const Date & d2) {
    return !(d1 == d2);
}

bool operator <(const Date & d1, const Date & d2) {
    if(d2.year > d1.year) return true;
    if(d2.year< d1.year) return false;
    if(d2.month > d1.month) return true;
    if(d2.month < d1.month) return false;
    return d2.day > d1.day;
}

bool operator <=(const Date & d1, const Date & d2) {
    return d1 < d2 || d1 == d2;
}

ostream& operator<<(ostream& out, Date& date){
    out << date.day << "/";
    out << date.month << "/";
    out << date.year;
    return out;
}



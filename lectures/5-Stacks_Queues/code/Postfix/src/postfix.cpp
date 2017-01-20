// Postfix arithmetic, implementing +, -, *, /

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "stack.h"

using namespace std;

const string OPERATORS = "+-*x/";
const string SEPARATOR = " ";

// function prototypes
double parsePostfix(string expression);
string getNextToken(string &expression);
void performCalculation(Stack<double> &s, char op);

int main() {
    string expression;
    double answer;
    do {
        expression = getLine("Please enter a postfix expression (blank to quit): ");
        answer = parsePostfix(expression);
        cout << "The answer is: " << answer << endl << endl;
    } while (expression != "");
    return 0;
}

double parsePostfix(string expression) {
    Stack<double> s;
    string nextToken;

    while (expression != "") {
        // gets the next token and removes it from expression
        nextToken = getNextToken(expression);
        if (OPERATORS.find(nextToken) == string::npos) {
            // we have a number
            double operand = stringToDouble(nextToken);
            s.push(operand);
        }
        else {
            // we have an operator
            char op = stringToChar(nextToken);
            performCalculation(s,op);
        }
    }
    return s.pop();
}

void performCalculation(Stack<double> &s, char op) {
    double result;
    double operand2 = s.pop(); // LIFO!
    double operand1 = s.pop();
    switch(op) {
        case '+': result = operand1 + operand2;
                  break;
        case '-': result = operand1 - operand2;
                  break;
        // allow "*" or "x" for times
        case '*':
        case 'x': result = operand1 * operand2;
                  break;
        case '/': result = operand1 / operand2;
                  break;
    }
    s.push(result);
}

string getNextToken(string &expression) {
    // pull out the substring up to the first space
    // and return the token, removing it from the expression
    string token;
    int sepLoc = expression.find(SEPARATOR);
    if (sepLoc != (int) string::npos) {
        token = expression.substr(0,sepLoc);
        expression = expression.substr(sepLoc+1,expression.size()-sepLoc);
        return token;
    }
    else {
        token = expression;
        expression = "";
        return token;
    }
}

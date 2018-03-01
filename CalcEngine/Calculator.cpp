#include "Calculator.h"
#include <stdexcept>
#include <cmath>
#include <cassert>
using namespace std;

Calculator::Calculator() {
    num1 = 0;
    num2 = 0;
    oper = NONE;
}

void Calculator::store(double value) {
    num2 = value;
}

double Calculator::handleOperation(Calculator::opType newOperation) {
    if(newOperation == SQRT) {
        num2 = pow(num2, 0.5);
        return num2;
    }
    else if(oper == ADD) {
        num1 += num2;
    }
    else if(oper == SUBTRACT) {
        num1 -= num2;
    }
    else if(oper == MULTIPLY) {
        num1 *= num2;
    }
    else if(oper == DIVIDE) {
        num1 /= num2;
    }
    else { //NONE
        num1 = num2;
    }

    oper = newOperation;
    return num1;
}

double Calculator::equalsPressed() {
    num1 = handleOperation(oper);
    return num1;
}

void Calculator::clear() {
    num1 = 0;
    num2 = 0;
    oper = NONE;
}

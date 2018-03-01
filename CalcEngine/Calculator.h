#ifndef CALCULATOR_H
#define CALCULATOR_H

class Calculator {
public:
    Calculator();
    enum opType
    {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE,
        SQRT,
        NONE    //no stored operation
    };

    //stores a value to num2
    void store(double value);

    //processes any existing operation, stores new operation
    //  returns result of existing operation (num1)
    double handleOperation(opType newOperation);

    //processes existing operation, sores result to num1 and returns it
    double equalsPressed();

    //clear all state
    void clear();

private:
    double num1;
    double num2;
    opType oper;
};

#endif // CALCULATOR_H

#include "CalDialog.h"
#include <QLabel>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QLineEdit>

CalDialog::CalDialog(QWidget *parent)
    :QDialog(parent)
{
    //Setup stuff to put stuff into
    editScreen = new QLineEdit();
    QGridLayout* numberGrid = new QGridLayout;
    QHBoxLayout* bottomHBox = new QHBoxLayout;
    QVBoxLayout* leftVBox = new QVBoxLayout;
    QVBoxLayout* rightVBox = new QVBoxLayout;

    //Setup and add all of the buttons
    //Grid
    QPushButton* numButton[3][3];
    int currentNum = 1;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            numButton[i][j] = new QPushButton(QString::number(currentNum));
            numberGrid->addWidget(numButton[i][j], i, j);
            connect(numButton[i][j], SIGNAL(clicked()), this, SLOT(pushedNumber()));
            currentNum++;
        }
    }

    //bottomHBox
    QPushButton* btnZero = new QPushButton("0");
    QPushButton* btnPoint = new QPushButton(".");
    bottomHBox->addWidget(btnZero, 1);
    bottomHBox->addWidget(btnPoint, 0);

    //leftVBox
    QPushButton* btnAdd = new QPushButton("+");
    QPushButton* btnSubtract = new QPushButton("-");
    QPushButton* btnMultiply = new QPushButton("x");
    QPushButton* btnDivide = new QPushButton("/");
    leftVBox->addWidget(btnDivide);
    leftVBox->addWidget(btnMultiply);
    leftVBox->addWidget(btnSubtract);
    leftVBox->addWidget(btnAdd);

    //rightVbox
    QPushButton* btnSqrt = new QPushButton("Sqrt");
    QPushButton* btnClear = new QPushButton("Clear");
    QPushButton* btnEqual = new QPushButton("=");
    btnEqual->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    rightVBox->addWidget(btnSqrt, 0);
    rightVBox->addWidget(btnClear, 0);
    rightVBox->addWidget(btnEqual, 1);

    //Setup innerSubLayout
    QVBoxLayout* innerSubLayout = new QVBoxLayout;
    innerSubLayout->addLayout(numberGrid);
    innerSubLayout->addLayout(bottomHBox);

    //Setup subLayout
    QHBoxLayout* subLayout = new QHBoxLayout;
    subLayout->addLayout(innerSubLayout);
    subLayout->addLayout(leftVBox);
    subLayout->addLayout(rightVBox);

    //Setup mainLayout
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(editScreen);
    mainLayout->addLayout(subLayout);

    mainLayout->setSizeConstraint( QLayout::SetFixedSize );
    setLayout(mainLayout);

    //Connect signals
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(pushedOperation()));
    connect(btnSubtract, SIGNAL(clicked()), this, SLOT(pushedOperation()));
    connect(btnMultiply, SIGNAL(clicked()), this, SLOT(pushedOperation()));
    connect(btnDivide, SIGNAL(clicked()), this, SLOT(pushedOperation()));
    connect(btnSqrt, SIGNAL(clicked()), this, SLOT(pushedOperation()));

    connect(btnEqual, SIGNAL(clicked()), this, SLOT(pushedEquals()));

    connect(btnZero, SIGNAL(clicked()), this, SLOT(pushedNumber()));
    connect(btnPoint, SIGNAL(clicked()), this, SLOT(pushedNumber()));

    connect(btnClear, SIGNAL(clicked()), this, SLOT(pushedClear()));

}

void CalDialog::pushedOperation() {
    //Store the value on the screen in the calculator

    //Previously clicking equals means that the calculator must be reset
    //But the calc needs to keep its result from pushing equals
    if(clickedEquals) {
        c.handleOperation(Calculator::NONE);
        QString textNum = editScreen->text();
        bool ok;
        double inputNum = textNum.toDouble(&ok);
        this->pushedClear();
        if(ok) {
            c.store(inputNum);
        }
        clickedEquals = false;
    }
    //If equals was not pushed then the number on the screen just goes
    //Sraight into the calculator.
    else {
        QString numberText = editScreen->text();
        bool ok;
        double numberInput = numberText.toDouble(&ok);
        if(ok) {
            c.store(numberInput);
        }
    }

    QPushButton* operationButton = dynamic_cast<QPushButton*>(sender());
    std::string opSymbol = (operationButton->text()).toStdString();

    //Find the right operation
    double answer = 0;
    if(opSymbol == "+") {
        answer = c.handleOperation(Calculator::ADD);
    }
    else if(opSymbol == "-") {
        answer = c.handleOperation(Calculator::SUBTRACT);
    }
    else if(opSymbol == "x") {
        answer = c.handleOperation(Calculator::MULTIPLY);
    }
    else if(opSymbol == "/") {
        answer = c.handleOperation(Calculator::DIVIDE);
    }
    else { /* if(opSymbol == "Sqrt")*/
        answer = c.handleOperation(Calculator::SQRT);
    }

    //Turn double back into Qsting using QString's static function number
    QString theResult = QString::number(answer);
    editScreen->clear();
    editScreen->insert(theResult);

    clickedOperation = true;

}

void CalDialog::pushedEquals() {
    if(!clickedEquals) {
        QString numberText = editScreen->text();
        bool ok;
        double numberInput = numberText.toDouble(&ok);
        if(ok) {
            c.store(numberInput);
        }
    }
    double answer = c.equalsPressed();
    QString theResult = QString::number(answer);
    editScreen->clear();
    editScreen->insert(theResult);
    clickedEquals = true;
}

void CalDialog::pushedNumber() {
    QPushButton* numberButton = dynamic_cast<QPushButton*>(sender());
    if(clickedOperation) {
        editScreen->clear();
    }
    else if (clickedEquals) {
        this->pushedClear();
    }

    QString screenContents = editScreen->text();
    QChar decimal = '.';
    if(screenContents.contains(decimal) && numberButton->text() == decimal) {
        //Do nothing
    }
    else {
        editScreen->insert(numberButton->text());
        clickedOperation = false;
        clickedEquals = false;
    }
}

void CalDialog::pushedClear() {
    c.clear();
    editScreen->clear();
    clickedOperation = false;
    clickedEquals = false;
}

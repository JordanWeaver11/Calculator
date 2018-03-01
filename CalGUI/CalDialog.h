#ifndef CALDIALOG_H
#define CALDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "Calculator.h"

class CalDialog : public QDialog {
    Q_OBJECT
public:
    explicit CalDialog(QWidget *parent = 0);

signals:


public slots:
    void pushedNumber();
    void pushedOperation();
    void pushedEquals();
    void pushedClear();

private:
    QLineEdit* editScreen;
    bool clickedOperation;
    bool clickedEquals;
    Calculator c;
};

#endif // CALDIALOG_H

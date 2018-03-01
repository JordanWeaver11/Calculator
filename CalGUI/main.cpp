#include <QApplication>
#include "CalDialog.h"


using namespace std;

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    CalDialog dlg;
//    dlg.setFixedSize(400, 200);
    dlg.show();

    return app.exec();
}


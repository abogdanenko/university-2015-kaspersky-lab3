#include "scannermainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScannerMainWindow w;
    w.initLayout();
    w.show();

    return a.exec();
}

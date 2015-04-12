#include "scannermainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScannerMainWindow w;
    w.setLayout();
    w.show();

    return a.exec();
}

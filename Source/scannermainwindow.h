#ifndef SCANNERMAINWINDOW_H
#define SCANNERMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class ScannerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ScannerMainWindow(QWidget *parent = 0);
    ~ScannerMainWindow();
    void setLayout();
};

#endif // SCANNERMAINWINDOW_H

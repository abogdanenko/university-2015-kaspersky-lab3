#include "scannermainwindow.h"

ScannerMainWindow::ScannerMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

ScannerMainWindow::~ScannerMainWindow()
{

}

void ScannerMainWindow::setLayout()
{
    this->setWindowTitle("Simple Antivirus Scanner");
    this->resize(600, 400);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QMenuBar *menuBar = new QMenuBar(centralWidget);
    QMenu *menuHelp = new QMenu(menuBar);
    QAction *actionAbout = new QAction(menuHelp);

    menuBar->addMenu(menuHelp);
    menuHelp->addAction(actionAbout);
    menuHelp->setTitle("Help");
    actionAbout->setText("About...");
}

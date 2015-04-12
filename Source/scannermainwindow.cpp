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

    QWidget *buttonWidget = new QWidget(centralWidget);
    QPushButton *btnChooseFile = new QPushButton(buttonWidget);
    QPushButton *btnChooseDir = new QPushButton(buttonWidget);
    QPushButton *btnStart = new QPushButton(buttonWidget);
    QVBoxLayout *buttonVBox = new QVBoxLayout();
    btnChooseFile->setText("Choose File");
    btnChooseDir->setText("Choose Directory");
    btnStart->setText("Start");
    buttonWidget->setLayout(buttonVBox);
    buttonVBox->addWidget(btnChooseFile);
    buttonVBox->addWidget(btnChooseDir);
    buttonVBox->addWidget(btnStart);
    buttonWidget->move(0, 20);
    buttonWidget->resize(170, 120);

    QGroupBox *groupBox = new QGroupBox(centralWidget);
    groupBox->setTitle("Action");
    QVBoxLayout *radioVBox = new QVBoxLayout();
    groupBox->setLayout(radioVBox);

    QRadioButton *radioAsk = new QRadioButton(groupBox);
    QRadioButton *radioIgnore = new QRadioButton(groupBox);
    QRadioButton *radioDelete = new QRadioButton(groupBox);

    radioAsk->setText("Ask");
    radioIgnore->setText("Ignore");
    radioDelete->setText("Delete");

    radioAsk->setChecked(true);

    radioVBox->addWidget(radioAsk);
    radioVBox->addWidget(radioIgnore);
    radioVBox->addWidget(radioDelete);

    groupBox->move(200, 20);
    groupBox->resize(100, 120);
}

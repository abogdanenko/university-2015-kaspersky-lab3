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
    QMenu *menuHistory = new QMenu(menuBar);
    QMenu *menuRecent = new QMenu(menuHistory);
    QMenu *menuHelp = new QMenu(menuBar);
    QAction *actionAbout = new QAction(menuHelp);
    QAction *actionClearHistory = new QAction(menuHistory);
    QAction *actionClearLog = new QAction(menuHistory);

    menuBar->addMenu(menuHistory);
    menuBar->addMenu(menuHelp);
    menuHelp->addAction(actionAbout);
    menuHistory->addMenu(menuRecent);
    menuHistory->addAction(actionClearHistory);
    menuHistory->addAction(actionClearLog);
    menuHistory->setTitle("History");
    menuRecent->setTitle("Recent");
    menuHelp->setTitle("Help");
    actionAbout->setText("About...");
    actionClearHistory->setText("Clear scan history");
    actionClearLog->setText("Clear scan log");

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

    QGroupBox *scanBox = new QGroupBox(centralWidget);
    QVBoxLayout *scanVBox = new QVBoxLayout();
    QLabel *label = new QLabel(scanBox);
    QLineEdit *lineEdit = new QLineEdit(scanBox);
    QCheckBox *recursiveBox = new QCheckBox(scanBox);

    scanBox->setTitle("Scan Options");
    label->setText("Filter by extension");
    lineEdit->setText("*.*");
    recursiveBox->setText("Scan subdirectories recursively");

    scanBox->setLayout(scanVBox);
    scanVBox->addWidget(label);
    scanVBox->addWidget(lineEdit);
    scanVBox->addWidget(recursiveBox);

    QWidget *topControls = new QWidget(centralWidget);
    QHBoxLayout *topControlsHBox = new QHBoxLayout();
    topControls->setLayout(topControlsHBox);
    topControlsHBox->addWidget(buttonWidget);
    topControlsHBox->addWidget(scanBox);
    topControlsHBox->addWidget(groupBox);
    topControlsHBox->addStretch();
    topControls->setFixedWidth(500);

    QVBoxLayout *centralVBox = new QVBoxLayout();
    QLabel *labelTarget = new QLabel(centralWidget);
    QLabel *labelLog = new QLabel(centralWidget);
    QTextEdit *editLog = new QTextEdit(centralWidget);
    QLineEdit *lineEditTarget = new QLineEdit(centralWidget);
    labelTarget->setText("File / Directory");
    labelLog->setText("Scan log");
    centralWidget->setLayout(centralVBox);
    centralVBox->addWidget(menuBar);
    centralVBox->addWidget(topControls);
    centralVBox->addWidget(labelTarget);
    centralVBox->addWidget(lineEditTarget);
    centralVBox->addWidget(labelLog);
    centralVBox->addWidget(editLog);
}

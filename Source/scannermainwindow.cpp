#include "scannermainwindow.h"

ScannerMainWindow::ScannerMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

ScannerMainWindow::~ScannerMainWindow()
{

}

void ScannerMainWindow::initMenu()
{
    mnuBar = new QMenuBar(centralWidget);
    mnuHistory = new QMenu(centralWidget);
    menuRecent = new QMenu(centralWidget);
    mnuHelp = new QMenu(centralWidget);
    actionClearHistory = new QAction(centralWidget);
    actionClearLog = new QAction(centralWidget);
    actionAbout = new QAction(centralWidget);

    mnuBar->addMenu(mnuHistory);
    mnuBar->addMenu(mnuHelp);
    mnuHistory->addMenu(menuRecent);
    mnuHistory->addAction(actionClearHistory);
    mnuHistory->addAction(actionClearLog);
    mnuHelp->addAction(actionAbout);

    mnuHistory->setTitle("History");
    menuRecent->setTitle("Recent");
    mnuHelp->setTitle("Help");
    actionClearHistory->setText("Clear scan history");
    actionClearLog->setText("Clear scan log");
    actionAbout->setText("About...");
}


void ScannerMainWindow::initButtons()
{
    buttonWidget = new QWidget(topControls);
    btnSelectFile = new QPushButton(buttonWidget);
    btnSelectFolder = new QPushButton(buttonWidget);
    btnCheck = new QPushButton(buttonWidget);
    QVBoxLayout *vbox = new QVBoxLayout();

    btnSelectFile->setText("Select File");
    btnSelectFolder->setText("Select Directory");
    btnCheck->setText("Start");

    buttonWidget->setLayout(vbox);
    vbox->addWidget(btnSelectFile);
    vbox->addWidget(btnSelectFolder);
    vbox->addWidget(btnCheck);
}

void ScannerMainWindow::initOptions()
{
    optionsBox = new QGroupBox(topControls);
    QVBoxLayout *vbox = new QVBoxLayout();
    QLabel *lblExtensions = new QLabel(optionsBox);
    edtExtensions = new QLineEdit(optionsBox);
    chkRecursive = new QCheckBox(optionsBox);

    optionsBox->setTitle("Scan Options");
    lblExtensions->setText("Filter by extension");
    edtExtensions->setText("*.*");
    chkRecursive->setText("Scan subdirectories recursively");

    optionsBox->setLayout(vbox);
    vbox->addWidget(lblExtensions);
    vbox->addWidget(edtExtensions);
    vbox->addWidget(chkRecursive);
}

void ScannerMainWindow::initAction()
{
    actionBox = new QGroupBox(topControls);
    QVBoxLayout *vbox = new QVBoxLayout();
    radioAsk = new QRadioButton(actionBox);
    radioIgnore = new QRadioButton(actionBox);
    radioDelete = new QRadioButton(actionBox);

    actionBox->setTitle("Action");
    radioAsk->setText("Ask");
    radioIgnore->setText("Ignore");
    radioDelete->setText("Delete");

    actionBox->setLayout(vbox);
    vbox->addWidget(radioAsk);
    vbox->addWidget(radioIgnore);
    vbox->addWidget(radioDelete);

    radioAsk->setChecked(true);
}

void ScannerMainWindow::initTopControls()
{
    topControls = new QWidget(centralWidget);

    initButtons();
    initOptions();
    initAction();

    QHBoxLayout *hbox = new QHBoxLayout();
    topControls->setLayout(hbox);
    hbox->addWidget(buttonWidget);
    hbox->addWidget(optionsBox);
    hbox->addWidget(actionBox);
    hbox->addStretch();
    topControls->setFixedWidth(500);
}

void ScannerMainWindow::initBottomWidgets()
{
    lblFileName = new QLabel(centralWidget);
    lblLog = new QLabel(centralWidget);
    edtFileName = new QLineEdit(centralWidget);
    edtLog = new QTextEdit(centralWidget);
    lblFileName->setText("File / Directory");
    lblLog->setText("Scan log");
}

void ScannerMainWindow::initCentralWidget()
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    initMenu();
    initTopControls();
    initBottomWidgets();

    QVBoxLayout *vbox = new QVBoxLayout();
    centralWidget->setLayout(vbox);
    vbox->addWidget(mnuBar);
    vbox->addWidget(topControls);
    vbox->addWidget(lblFileName);
    vbox->addWidget(edtFileName);
    vbox->addWidget(lblLog);
    vbox->addWidget(edtLog);
}

void ScannerMainWindow::initLayout()
{
    setWindowTitle("Simple Antivirus Scanner");
    initCentralWidget();
}

void ScannerMainWindow::Connect()
{
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(mnuAboutTriggered()));
    connect(actionClearLog, SIGNAL(triggered()), edtLog, SLOT(clear()));
    connect(btnSelectFile, SIGNAL(clicked()), this, SLOT(onSelectFile()));
    connect(btnSelectFolder, SIGNAL(clicked()), this, SLOT(onSelectFolder()));
}

void ScannerMainWindow::mnuAboutTriggered()
{
    QMessageBox msg;
    QString s;
    s = "Проект SimpleAntivirusScanner_KL2015 выполнен в рамках спецкурса"
        " Лаборатории Касперского \"Командная разработка кроссплатформенных"
        " приложений\"."
        "\n"
        "\n"
        "Авторы: Богданенко Алексей, Хамитов Камиль"
        "\n"
        "\n"
        "Апрель 2015";

    msg.setText(s);
    msg.exec();
}

void ScannerMainWindow::onSelectFile()
{
    QStringList filters;
    QString ext = edtExtensions->text();

    if (ext != "*.*") {
        filters << QString("User defined (%1)").arg(ext);
    }

    filters << "All files (*.*)";

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setDirectory(QDir::homePath());
    dialog.setNameFilters(filters);

    if (dialog.exec()) {
        QStringList filenames = dialog.selectedFiles();
        QString filename = filenames[0];
        edtFileName->setText(filename);
    }
}

void ScannerMainWindow::onSelectFolder()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QDir::homePath());
    dialog.setOption(QFileDialog::ShowDirsOnly, true);

    if (dialog.exec()) {
        QStringList filenames = dialog.selectedFiles();
        QString filename = filenames[0];
        edtFileName->setText(filename);
    }
}

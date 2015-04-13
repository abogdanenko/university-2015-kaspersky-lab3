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
    mnuRecent = new QMenu(centralWidget);
    mnuHelp = new QMenu(centralWidget);
    actClearHistory = new QAction(centralWidget);
    actClearLog = new QAction(centralWidget);
    actAbout = new QAction(centralWidget);

    mnuBar->addMenu(mnuHistory);
    mnuBar->addMenu(mnuHelp);
    mnuHistory->addMenu(mnuRecent);
    mnuHistory->addAction(actClearHistory);
    mnuHistory->addAction(actClearLog);
    mnuHelp->addAction(actAbout);

    mnuHistory->setTitle("History");
    mnuRecent->setTitle("Recent");
    mnuHelp->setTitle("Help");
    actClearHistory->setText("Clear scan history");
    actClearLog->setText("Clear scan log");
    actAbout->setText("About...");
}


void ScannerMainWindow::initButtons()
{
    wgtButtons = new QWidget(topControls);
    btnSelectFile = new QPushButton(wgtButtons);
    btnSelectFolder = new QPushButton(wgtButtons);
    btnCheck = new QPushButton(wgtButtons);
    QVBoxLayout *vbox = new QVBoxLayout();

    btnSelectFile->setText("Select File");
    btnSelectFolder->setText("Select Directory");
    btnCheck->setText("Start");

    wgtButtons->setLayout(vbox);
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
    gbxActions = new QGroupBox(topControls);
    QVBoxLayout *vbox = new QVBoxLayout();
    rdoAsk = new QRadioButton(gbxActions);
    rdoIgnore = new QRadioButton(gbxActions);
    rdoDelete = new QRadioButton(gbxActions);

    gbxActions->setTitle("Action");
    rdoAsk->setText("Ask");
    rdoIgnore->setText("Ignore");
    rdoDelete->setText("Delete");

    gbxActions->setLayout(vbox);
    vbox->addWidget(rdoAsk);
    vbox->addWidget(rdoIgnore);
    vbox->addWidget(rdoDelete);

    rdoAsk->setChecked(true);
}

void ScannerMainWindow::initTopControls()
{
    topControls = new QWidget(centralWidget);

    initButtons();
    initOptions();
    initAction();

    QHBoxLayout *hbox = new QHBoxLayout();
    topControls->setLayout(hbox);
    hbox->addWidget(wgtButtons);
    hbox->addWidget(optionsBox);
    hbox->addWidget(gbxActions);
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
    connect(actAbout, SIGNAL(triggered()), this, SLOT(mnuAboutTriggered()));
    connect(actClearLog, SIGNAL(triggered()), edtLog, SLOT(clear()));
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

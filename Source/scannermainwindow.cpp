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
    mnuBar = new QMenuBar(wgtCentral);
    mnuHistory = new QMenu(wgtCentral);
    mnuRecent = new QMenu(wgtCentral);
    mnuHelp = new QMenu(wgtCentral);
    actClearHistory = new QAction(wgtCentral);
    actClearLog = new QAction(wgtCentral);
    actAbout = new QAction(wgtCentral);

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
    wgtButtons = new QWidget(wgtTop);
    btnSelectFile = new QPushButton(wgtButtons);
    btnSelectFolder = new QPushButton(wgtButtons);
    btnCheck = new QPushButton(wgtButtons);
    QVBoxLayout *vbox = new QVBoxLayout(wgtButtons);

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
    gbxOptions = new QGroupBox(wgtTop);
    QLabel *lblExtensions = new QLabel(gbxOptions);
    edtExtensions = new QLineEdit(gbxOptions);
    chkRecursive = new QCheckBox(gbxOptions);
    QVBoxLayout *vbox = new QVBoxLayout(gbxOptions);

    gbxOptions->setTitle("Scan Options");
    lblExtensions->setText("Filter by extension");
    edtExtensions->setText("*.*");
    chkRecursive->setText("Scan subdirectories recursively");

    gbxOptions->setLayout(vbox);
    vbox->addWidget(lblExtensions);
    vbox->addWidget(edtExtensions);
    vbox->addWidget(chkRecursive);
}

void ScannerMainWindow::initAction()
{
    gbxActions = new QGroupBox(wgtTop);
    QVBoxLayout *vbox = new QVBoxLayout(gbxActions);
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

void ScannerMainWindow::initTopWidget()
{
    wgtTop = new QWidget(wgtCentral);

    initButtons();
    initOptions();
    initAction();

    QHBoxLayout *hbox = new QHBoxLayout(wgtTop);
    wgtTop->setLayout(hbox);
    hbox->addWidget(wgtButtons);
    hbox->addWidget(gbxOptions);
    hbox->addWidget(gbxActions);
    hbox->addStretch();
    wgtTop->setFixedWidth(500);
}

void ScannerMainWindow::initBottomWidgets()
{
    lblFileName = new QLabel(wgtCentral);
    lblLog = new QLabel(wgtCentral);
    edtFileName = new QLineEdit(wgtCentral);
    edtLog = new QTextEdit(wgtCentral);
    edtLog->setReadOnly(true);
    lblFileName->setText("File / Directory");
    lblLog->setText("Scan log");
}

void ScannerMainWindow::initCentralWidget()
{
    wgtCentral = new QWidget(this);
    setCentralWidget(wgtCentral);

    initMenu();
    initTopWidget();
    initBottomWidgets();

    QVBoxLayout *vbox = new QVBoxLayout(wgtCentral);
    wgtCentral->setLayout(vbox);
    vbox->addWidget(mnuBar);
    vbox->addWidget(wgtTop);
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
    connect(btnCheck, SIGNAL(clicked()), this, SLOT(onCheck()));
    connect(&scanner, SIGNAL(log(QString)), this, SLOT(onLog(QString)));
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

void ScannerMainWindow::onLog(QString aHtmlMessage)
{
    edtLog->moveCursor(QTextCursor::End);
    edtLog->insertHtml(aHtmlMessage);
    QString newline = "<br>\n";
    edtLog->insertHtml(newline);
}

void ScannerMainWindow::onCheck()
{
    QString aTargetName = edtFileName->text();
    bool aIsRecursive = chkRecursive->isChecked();
    QString aExt = edtExtensions->text();

    MalwarePolicy policy = MPOL_SKIP;
    if (rdoDelete->isChecked()) {
        policy = MPOL_REMOVE;
    }

    scanner.setPolicy(policy);
    scanner.check(aTargetName, aIsRecursive, aExt);
}

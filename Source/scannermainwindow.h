#ifndef SCANNERMAINWINDOW_H
#define SCANNERMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "scanner.h"

class ScannerMainWindow : public QMainWindow
{
    Q_OBJECT

    QMenuBar *mnuBar;
    QMenu *mnuHistory;
    QMenu *mnuRecent;
    QMenu *mnuHelp;
    QAction *actAbout;
    QAction *actClearHistory;
    QAction *actClearLog;

    QWidget *wgtButtons;
    QPushButton *btnSelectFile;
    QPushButton *btnSelectFolder;
    QPushButton *btnCheck;

    QGroupBox *gbxActions;
    QRadioButton *rdoAsk;
    QRadioButton *rdoIgnore;
    QRadioButton *rdoDelete;

    QGroupBox *gbxOptions;
    QLineEdit *edtExtensions;
    QCheckBox *chkRecursive;

    QWidget *wgtTop;

    QLabel *lblFileName;
    QLabel *lblLog;
    QLineEdit *edtFileName;
    QTextEdit *edtLog;

    QWidget *wgtCentral;

    Scanner scanner;

    void initMenu();
    void initButtons();
    void initOptions();
    void initAction();
    void initTopWidget();
    void initBottomWidgets();
    void initCentralWidget();

public slots:
    void mnuAboutTriggered();
    void onSelectFile();
    void onSelectFolder();
    void onCheck();
    void onLog(QString aHtmlMessage);

public:
    ScannerMainWindow(QWidget *parent = 0);
    ~ScannerMainWindow();
    void initLayout();
    void Connect();
};

#endif // SCANNERMAINWINDOW_H

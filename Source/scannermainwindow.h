#ifndef SCANNERMAINWINDOW_H
#define SCANNERMAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class ScannerMainWindow : public QMainWindow
{
    Q_OBJECT

    QMenuBar *mnuBar;
    QMenu *menuHistory;
    QMenu *menuRecent;
    QMenu *mnuHelp;
    QAction *actionAbout;
    QAction *actionClearHistory;
    QAction *actionClearLog;

    QWidget *buttonWidget;
    QPushButton *btnSelectFile;
    QPushButton *btnSelectFolder;
    QPushButton *btnStart;

    QGroupBox *actionBox;
    QRadioButton *radioAsk;
    QRadioButton *radioIgnore;
    QRadioButton *radioDelete;

    QGroupBox *optionsBox;
    QLineEdit *edtExtensions;
    QCheckBox *chkRecursive;

    QWidget *topControls;

    QLabel *lblFileName;
    QLabel *lblLog;
    QLineEdit *edtFileName;
    QTextEdit *editLog;

    QWidget *centralWidget;

    void initMenu();
    void initButtons();
    void initOptions();
    void initAction();
    void initTopControls();
    void initBottomWidgets();
    void initCentralWidget();

public slots:
    void mnuAboutTriggered();
    void onSelectFile();
    void onSelectFolder();

public:
    ScannerMainWindow(QWidget *parent = 0);
    ~ScannerMainWindow();
    void initLayout();
    void Connect();
};

#endif // SCANNERMAINWINDOW_H

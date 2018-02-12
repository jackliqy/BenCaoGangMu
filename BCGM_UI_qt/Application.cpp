/**
  \file Application.cpp

  \author Jack Li
*/

#include "Application.h"

#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QThreadPool>
#include <QHostAddress>
#include <QLocalServer>
#include <QLocalSocket>
#include <QTimer>

using namespace std;


Application * theApp;

bool exiting = false;


void MainDialog::closeEvent(QCloseEvent *)
{
    exiting = true;
    theApp->prepareForExit();
    theApp->exit(0);
}


struct Application::Private
{
    Private()
        : dialog_(0)
    {}
    //
    QString ini_file_;
    //
    MainDialog * dialog_;
    QLocalServer * uniqueapp_;
};


Application::Application(int & argc, char ** argv)
    : QApplication(argc, argv), d(new Private)
{
    setOrganizationName("Jack.Li");
    setOrganizationDomain("http://blog.csdn.net/checkylqy");
    setApplicationName("BCGM");
    QThreadPool::globalInstance()->setMaxThreadCount(20);
    QThreadPool::globalInstance()->setExpiryTimeout(60000);
    theApp = this;

    QString const ini_file = (argc > 1)
        ? argv[1] : defaultIni().c_str();
    setIniFile(ini_file);
}


Application::~Application()
{
    if (d->dialog_) {
        delete d->dialog_;
    }
    if (d->uniqueapp_)
        delete d->uniqueapp_;
    delete d;
}


void Application::uniqueApplication()
{
    QString applicationTypeName = QCoreApplication::applicationName();
    QLocalSocket socket;
    socket.connectToServer(applicationTypeName);
    if (socket.waitForConnected(500)) {
        socket.disconnectFromServer();
        QMessageBox::critical(0, tr("Application is already running."),
            tr("Another application is already running, "
            "please close this application and start again."));
        ::exit(10);
    }
    d->uniqueapp_ = new QLocalServer(this);
    d->uniqueapp_->listen(applicationTypeName);
}


void Application::init()
{
    if (dialog()) {
        if (!dialog()->init(iniFile())) {
            exit(-1);
            return;
        }
        dialog()->show();
    }
}


void Application::setIniFile(QString const & ini_file)
{
    d->ini_file_ = ini_file;
}


QString const & Application::iniFile() const
{
    return d->ini_file_;
}


int Application::exec()
{
    QTimer::singleShot(0, this, SLOT(execCommands()));

    return QApplication::exec();
}


void Application::execCommands()
{
    init();
}


void Application::setMainDialog(MainDialog * dialog)
{
    d->dialog_ = dialog;
}


MainDialog * Application::dialog() const
{
    return d->dialog_;
}


void loadStyleSheet(QWidget * w, QString const & sheetName)
{
    static QString styleSheet;
    if (styleSheet.isEmpty()) {
        QFile file(":/qss/" + sheetName.toLower() + ".qss");
        file.open(QFile::ReadOnly);
        styleSheet = QLatin1String(file.readAll());

        QRegExp reg1("Q_WS_MAC:[^\n]*\n");
        QRegExp reg2("Q_WS_X11:[^\n]*\n");
        QRegExp reg3("Q_WS_WIN:");

        styleSheet.replace(reg1, "");
        styleSheet.replace(reg2, "");
        styleSheet.replace(reg3, "");
        file.close();
    }
    w->setStyleSheet(styleSheet);
}


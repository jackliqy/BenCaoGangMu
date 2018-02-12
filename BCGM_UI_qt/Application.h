/**
  \file Application.h

  \author Jack Li
*/

#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QDialog>

class QString;

class MainDialog : public QDialog
{
public:
    MainDialog(QWidget * parent, Qt::WindowFlags f = 0) : QDialog(parent, f) {}
    /// This is a pure virtual class.
    virtual ~MainDialog() {}
    ///
    virtual bool init(QString const & ini_file) = 0;

protected:
    void closeEvent(QCloseEvent *);
};


class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int & argc, char ** argv);
    virtual ~Application();
    ///
    int exec();
    ///
    virtual std::string defaultIni() { return std::string(); }
    ///
    void setIniFile(QString const & ini_file);

    QString const & iniFile() const;
    ///
    virtual void prepareForExit(){}
    ///
    void uniqueApplication();

public:
    ///
    void setMainDialog(MainDialog * dialog);
protected:
    ///
    MainDialog * dialog() const;
    ///
    virtual void init();

private Q_SLOTS:
    ///
    void execCommands();

private:
    struct Private;
    Private * d;
};

// Singleton.
extern Application * theApp;

/// This variable is necessary to work around a thread related crash:
extern bool exiting;

void loadStyleSheet(QWidget * w, QString const & sheetName);

#endif // APPLICATION_H

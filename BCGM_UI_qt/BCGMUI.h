/**
  \file BCGMApp.h

  \author Jack Li
*/

#ifndef BCGMUI_H
#define BCGMUI_H

#include "Application.h"
#include "BCGMApp.h"
#include "BCGMBaseUI.h"

//Camera
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

///
class BCGMUI : public BCGMBaseUI
{
    Q_OBJECT
public:
    BCGMUI(QWidget * parent = 0);
    ~BCGMUI();
    ///
    void initSkin();

protected:
    bool eventFilter(QObject *, QEvent *);

public Q_SLOTS:
    // Override the QDialog::reject() so that the Escape key
    // does not quit the app.
    virtual void reject() {}

private Q_SLOTS:
    bool init(QString const & ini_file);
    void onWindowBlocked();
    void onWindowUnblocked();

    void questionButton_Clicked();
    void on_pushButton_NetWorkList_pressed();

private slots:
    void minimizePressed();
    //void saveImage();

private:
    //non-copyable
    BCGMUI(BCGMUI const &);
    void operator=(BCGMUI const &);

    struct Private;
    Private * const d;
};


#endif // BCGMUI_H


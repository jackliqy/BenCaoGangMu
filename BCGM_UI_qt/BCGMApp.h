/**
  \file BCGMApp.h

  \author Jack Li
*/

#ifndef BCGMAPP_H
#define BCGMAPP_H

#include <QMainWindow>

#include "Application.h"
#include "ApplicationSkin.h"

class BCGMApp : public Application
{
    Q_OBJECT
public:
    ///
    BCGMApp(int argc, char * argv[]);
    ///
    ~BCGMApp();

    void init();

private:
    void installSkin(ApplicationSkin * skin);
    friend ApplicationSkin * theSkin();

public Q_SLOTS:
    //void checkAndUpdate();

private Q_SLOTS:
    //void exit();

private:
    //non-copyable
    BCGMApp(BCGMApp const &);
    void operator=(BCGMApp const &);

    //
    struct Private;
    Private * const d;
};

ApplicationSkin * theSkin();

#endif // BCGMAPP_H


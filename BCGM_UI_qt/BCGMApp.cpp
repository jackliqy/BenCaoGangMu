/**
  \file BCGMApp.cpp

  \author Jack Li
*/

#include "BCGMApp.h"
#include "UiFactory.h"

using namespace std;

inline void initResource() {
    Q_INIT_RESOURCE(BCGM);
}

static BCGMApp * app_;

struct BCGMApp::Private
{
    Private() : skin_(0) {}

    ///
    void installSkin(ApplicationSkin * skin);
    ///
    ApplicationSkin * skin_;

};


void BCGMApp::Private::installSkin(ApplicationSkin * skin)
{
    skin_ = skin;
}


BCGMApp::BCGMApp(int argc, char * argv[])
        : Application(argc, argv),
          d(new BCGMApp::Private)
{
    app_ = this;
    //add resource
    initResource();
    //only can start one application
    uniqueApplication();
    //loading library
    //QApplication::addLibraryPath("../plugins");

    d->installSkin(ApplicationSkinFactory::createSkin());
    //
    setMainDialog(UiFactory::createUi());

}


BCGMApp::~BCGMApp()
{
    delete d;
}


void BCGMApp::init()
{
    // First initialize the dialog
    //if(app_){
        //QApplication::exit(-1);
        //return;
    //}
    Application::init();
}


ApplicationSkin * theSkin()
{
    if (app_)
        return app_->d->skin_;
    // should not happen
    return 0;
}


int main(int argc, char *argv[])
{
    BCGMApp app(argc, argv);
    return app.exec();
}


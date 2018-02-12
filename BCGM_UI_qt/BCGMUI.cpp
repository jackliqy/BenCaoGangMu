/**
  \file BCGMUI.cpp

  \author Jack Li
*/

#include "BCGMUI.h"
#include "BCGMBaseUI.h"
#include "ui_BCGM.h"
#include "NetworkList.h"
#include "PaintClock.h"

#include <QApplication>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>
#include <QToolButton>
#include <QBitmap>

using namespace std;

struct BCGMUI::Private
{
    Private(BCGMUI *)
    {}
    ///
    Ui::BCGM ui;

};


BCGMUI::BCGMUI(QWidget * parent)
    : BCGMBaseUI(parent), d(new BCGMUI::Private(this))
{
    printf("HELLO WORLD!\n");
}


BCGMUI::~BCGMUI()
{
    delete d;
}


bool BCGMUI::eventFilter(QObject *object, QEvent *event)
{
    switch (event->type()) {
    case QEvent::MouseButtonDblClick:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove: {
        QMouseEvent *me = dynamic_cast<QMouseEvent*> (event);
        //if (object == d->ui.header)
            //return onBannerMouseEvent(me);
        onBannerMouseEvent(me);
        break;
    }
    case QEvent::Resize: {
        break;
    }

    case QEvent::Show:{

        break;
    }

    case QEvent::Move: {
        break;
    }

    // used to do the UI changes.
    case QEvent::WindowBlocked:
        QTimer::singleShot(0, this, SLOT(onWindowBlocked()));
        break;
    case QEvent::WindowUnblocked:
        QTimer::singleShot(0, this, SLOT(onWindowUnblocked()));
        break;

    default:
        break;
    }
    return false;
}


void BCGMUI::onWindowBlocked()
{
    //
}


void BCGMUI::onWindowUnblocked()
{    
    //FIXME: This is a workaround for a possible bug in Qt
    //that the sizeGrip is disabled when switching back.
    setSizeGripEnabled(false);
    setSizeGripEnabled(true);
}


bool BCGMUI::init(QString const & ini_file)
{
    BCGMBaseUI::init();

    ///set app stylesheet
    QString const style = theSkin()->styleSheet();
    loadStyleSheet(this, style);

    d->ui.setupUi(this);
    installEventFilter(this);
    this->setWindowOpacity(1);//设置窗体不透明
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);//设置窗体无边框,允许任务栏按钮右键菜单
    //this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    setSizeGripEnabled(true);
    ///
    initSkin();

    return true;
}


void BCGMUI::on_pushButton_NetWorkList_pressed()
{
    qDebug() << "Clicked pushButton";
}


void BCGMUI::questionButton_Clicked()
{
    QString versionString = "1.0";
    QString text = theApp->applicationName();
    text.append(" : ").append(versionString)
            .append("<p><p>")
            .append(tr("Package version : ")).append("1.0")
            .append("<p><p>")
            .append(tr("Developed by: Jack Li"))
            .append("<a href=\"http://blog.csdn.net/checkylqy/\"> http://blog.csdn.net/checkylqy</a>");
    QString title = QString(tr("About ")).append(theApp->applicationName());
    QMessageBox::about(this, title, text);
}


void BCGMUI::minimizePressed()
{
    this->showMinimized();
}


void BCGMUI::initSkin()
{
    //background
    QPixmap pixmap = QPixmap(":/resources/image/a.jpg").scaled(this->size());
    QPalette palette(this->palette());

    palette.setBrush(QPalette::Background, QBrush(pixmap));
    this->setPalette(palette);
    this->setMask(pixmap.mask());
    this->setAutoFillBackground(true);
    //LOGO
    QLabel * background = new QLabel(this);
    background->setPixmap(QPixmap(":/resources/image/logo.png"));
    background->setGeometry(this->geometry().x(),
                            this->geometry().y(), 120, 40);//120 40
    background->setScaledContents(true);//set Pixmap full of label
    //min/maximize
    int width = this->width();
    QToolButton * aboutButton = new QToolButton(this);
    QToolButton * closeButton = new QToolButton(this);
    //QToolButton * minButton = new QToolButton(this);
    QPixmap aboutPix = QPixmap(":/resources/image/help_icon.png");
    //QPixmap minPix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix = QPixmap(":/resources/image/close_icon.png");

    aboutButton->setIcon(aboutPix);
    //minButton->setIcon(minPix);
    closeButton->setIcon(closePix);

    aboutButton->setGeometry(width-70.5, 5, 30, 30);
    //minButton->setGeometry(width-60.5, 5, 30, 30);
    closeButton->setGeometry(width-35.5, 5, 30, 30);

    aboutButton->setToolTip(tr("关于"));
    //minButton->setToolTip(tr("最小化"));
    closeButton->setToolTip(tr("关闭"));
    aboutButton->setStyleSheet("background-color:transparent;");
    //minButton->setStyleSheet("background-color:transparent;");
    closeButton->setStyleSheet("background-color:transparent;");

    connect(aboutButton, SIGNAL(pressed()), SLOT(questionButton_Clicked()));
    //connect(minButton, SIGNAL(pressed()), SLOT(minimizePressed()));
    connect(closeButton, SIGNAL(pressed()), SLOT(close()));
}


/*
void BCGMUI::maximizePressed()
{
    static QPoint prev_pos = QPoint();
    static QSize prev_size = QSize();
    setUpdatesEnabled(false);
    if (isMaximized()) {
        showNormal();
        if (!prev_size.isNull())
            resize(prev_size);
        if (!prev_pos.isNull())
            move(prev_pos);
    } else {
        // FIXME: Maximizing a frameless window overlaps the taskbar:
        // - http://bugreports.qt.nokia.com/browse/QTBUG-4362
        prev_pos = pos();
        prev_size = size();

        QRect const available = QApplication::desktop()->availableGeometry(this);
        move(available.topLeft());
        resize(available.size());
        setWindowState(Qt::WindowMaximized);
    }
    setUpdatesEnabled(true);
    update();
}
*/


/**
  \file PaintClock.cpp

  \author Jack Li
*/

#include "PaintClock.h"

#include <QApplication>
#include <QTimer>
#include <QTime>
#include <QPainter>


struct PaintClock::Private
{
    Private(PaintClock * parent)
    {
    }
    ///
    QTimer * timer_;
};


PaintClock::PaintClock(QWidget * parent)
    : QDialog(parent), d(new PaintClock::Private(this))
{
    setGeometry(parent->geometry().x()+parent->frameGeometry().width()/2.5,
        parent->geometry().y()+parent->frameGeometry().height()/3, 200, 200);
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint);
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);
    //setContentsMargins(0,0,0,0);

    d->timer_ = new QTimer(this);
    connect(d->timer_, SIGNAL(timeout()), this, SLOT(update()));
    d->timer_->start(1000);
}


PaintClock::~PaintClock()
{
    delete d->timer_;
    delete d;
}


void PaintClock::move(int x, int y)
{
    QDialog::move(x, y);
}


void PaintClock::show()
{
    QDialog::show();
}


void PaintClock::paintEvent(QPaintEvent *)
{
    static const QPoint hour[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint min[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -60)
    };
    static const QPoint sec[3] = {
        QPoint(2, 8),
        QPoint(-2, 8),
        QPoint(0, -80)
    };

    QTime time = QTime::currentTime();
    QPainter paint(this);
    /* move to center */
    paint.translate(100, 100);
    //paint.drawLine(0, 0, 100, 100);
    paint.setRenderHint(QPainter::Antialiasing);//set painter antialias
    paint.setBrush(Qt::red);
    paint.setPen(Qt::red);
    paint.save();
    paint.rotate(6.0 * time.second());
    /* paint sec pointer */
    paint.drawConvexPolygon(sec, 4);
    paint.restore();
    paint.setBrush(Qt::blue);
    paint.setPen(Qt::blue);
    paint.save();
    paint.rotate(6.0 * (time.minute() + time.second() /60.0));/* 6(360 / 60) */
    /* paint min pointer */
    paint.drawConvexPolygon(min, 4);
    paint.restore();
    paint.setBrush(Qt::black);
    paint.setPen(Qt::black);
    paint.save();
    paint.rotate(30.0 * (time.hour() + time.minute() / 60.0));/* 30(360 / 12) */
    /* paint hour pointer */
    paint.drawConvexPolygon(hour, 4);
    paint.restore();
    /* paint clock dial plate */
    for (int i = 1; i <= 60; i++) {
        paint.rotate(6);/* 6° */
        if (i == 60) {
            paint.save();
            paint.setBrush(Qt::red);
            paint.setPen(Qt::red);
            paint.drawLine(0, -98, 0, -82); /* -98*cos(30).. */
            paint.restore();
        } else if (i == 30) {
            paint.save();
            paint.setBrush(Qt::red);
            paint.setPen(Qt::red);
            paint.drawLine(0, -98, 0, -83); /* -98*cos(30).. */
            paint.restore();
        } else if (i == 45 || i == 15) {
            paint.save();
            paint.setBrush(Qt::yellow);
            paint.setPen(Qt::yellow);
            paint.drawLine(0, -98, 0, -84); /* -98*cos(30).. */
            paint.restore();
        } else if (i %5 == 0) {
            paint.save();
            paint.setBrush(Qt::yellow);
            paint.setPen(Qt::yellow);
            paint.drawLine(0, -98, 0, -86); /* -98*cos(30).. */
            paint.restore();
        } else {
            paint.drawLine(0, -98, 0, -88); /* -98*cos(30).. */
        }
    }
    /* paint number:12,6,9,3 */
    paint.save();
    paint.setBrush(Qt::black);
    paint.setPen(Qt::black);
    QFont* pFont = new QFont("宋体", 11, 75, false);
    paint.setFont(*pFont);
    paint.drawText(QRectF(-8, -80, 25, 15), "12");
    paint.drawText(QRectF(-4, 70, 25, 15), "6");
    paint.drawText(QRectF(-75, -5, 25, 15), "9");
    paint.drawText(QRectF(70, -5, 25, 15), "3");
    delete pFont;
    paint.restore();
}


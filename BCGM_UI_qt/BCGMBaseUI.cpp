/**
  \file BCGMBaseUI.cpp

  \author Jack Li
*/

#include "BCGMBaseUI.h"
#include "BCGMApp.h"

#include <QMouseEvent>

bool BCGMBaseUI::init()
{
    //theApp->setFont(QFont(theSkin()->applicationFont()));

	return true;
}


bool BCGMBaseUI::onBannerMouseEvent(QMouseEvent * me)
{
	static bool dragging = false;
	static QPoint drag_start;

	switch (me->type()) {
	case QEvent::MouseButtonDblClick:
		if (!(me->button() & Qt::LeftButton))
			break;
		maximizePressed();
		break;

	case QEvent::MouseButtonPress:
		if (!(me->button() & Qt::LeftButton))
			break;
		dragging = !(windowState() & Qt::WindowMaximized);
		if (dragging)
			drag_start = me->pos();
		me->accept();
		break;

	case QEvent::MouseButtonRelease:
		dragging = false;
		break;

	case QEvent::MouseMove:
		if (!dragging)
			break;
		move(this->pos() + me->pos() - drag_start);
		me->accept();
		break;

	default:
		break;
	}
	return false;
}


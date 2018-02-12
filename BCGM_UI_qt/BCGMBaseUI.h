/**
  \file NetworkManagerBaseUI.h

  \author Jack Li
*/

#ifndef BCGM_BASEUI_H
#define BCGM_BASEUI_H

#include "Application.h"

class QMouseEvent;


///
class BCGMBaseUI : public MainDialog
{
	Q_OBJECT
public:
    BCGMBaseUI(QWidget * parent = 0, Qt::WindowFlags f = 0)
		: MainDialog(parent, f)
	{}
    ~BCGMBaseUI() {}

public Q_SLOTS:
	// Override the QDialog::reject() so that the Escape key
	// does not quit the app.
	virtual void reject() {}

protected:
	virtual bool init();

	bool onBannerMouseEvent(QMouseEvent * me);

	virtual void maximizePressed() {}

};


#endif // BCGM_BASEUI_H

/**
  \file BaseDialog.h

  \author Jack Li
*/

#ifndef BASE_DIALOG_H
#define BASE_DIALOG_H

#include <QDialog>

class BaseDialog : public QDialog
{
	Q_OBJECT
public:
	BaseDialog(QWidget * parent) 
		: QDialog(parent, (Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowCloseButtonHint))
	{}

	virtual ~BaseDialog() {}
};


#endif // BASE_DIALOG_H


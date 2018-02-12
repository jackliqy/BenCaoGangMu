/**
  \file NetworkList.h

  \author Jack.Li
*/

#ifndef NETWORK_LIST_H
#define NETWORK_LIST_H

#include "BaseDialog.h"

class LoadInfoImage;

class NetworkList : public BaseDialog
{
	Q_OBJECT
public:
    NetworkList(QWidget * parent = 0);
    ~NetworkList();

	void show();
    void QthreadFirmware();
    void GetFirmware();

Q_SIGNALS:
	void finished();

private Q_SLOTS:
	void showHpavList();
	void copyData();

private:
    NetworkList(NetworkList const &);
    void operator=(NetworkList const &);

	struct Private;
	Private * const d;
};


#endif // NETWORK_LIST_H

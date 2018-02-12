/**
 \file PaintClock.h

 \author Jack Li
*/

#ifndef PAINTCLOCK_H
#define PAINTCLOCK_H

#include <QDialog>
#include <QWidget>


class PaintClock : public QDialog
{
public:
	PaintClock(QWidget *parent);
	~PaintClock();
	
	void show();
	void move(int x, int y);

protected:
	void paintEvent(QPaintEvent * event);

private:
	PaintClock(PaintClock const &);
	void operator=(PaintClock const &);

	struct Private;
	Private * const d; 
};

#endif // PAINTCLOCK_H

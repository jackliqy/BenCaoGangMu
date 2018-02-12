/**
  \file UIFactory.h
  \author Jack Li
*/

#ifndef UIFACTORY_H
#define UIFACTORY_H

class MainDialog;

class UiFactory
{
public:
	UiFactory();

	///
    static MainDialog * createUi();
};


#endif // UIFACTORY_H

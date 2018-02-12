/**
  \file UIFactory.cpp

  \author Jack Li
*/

#include "Application.h"
#include "BCGMUI.h"
#include "BCGMApp.h"
#include "UiFactory.h"

MainDialog * UiFactory::createUi()
{
    return new BCGMUI();
}


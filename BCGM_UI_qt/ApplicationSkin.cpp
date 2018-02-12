/**
  \file ApplicationSkin.cpp

  \author Jack Li
*/

#include "ApplicationSkin.h"
#include "resources/normal/NormalSkin.h"


// Allow to set a compile flag to choose which is the default
#ifdef NMORANGE
    static InspectionCarSkin default_skin = NMOrange;
#else
    // Allow to change the default without recompiling everything
    static InspectionCarSkin default_skin = NMnormal;
#endif


ApplicationSkin * ApplicationSkinFactory::createSkin()
{
    InspectionCarSkin manager_skin = default_skin;

    cleanupNormalResource();

    switch (manager_skin) {
	case NMOrange:
        //return new OrangeSkin;
    case NMnormal:
        return new NormalSkin;
        ;
	}
	return 0;
}


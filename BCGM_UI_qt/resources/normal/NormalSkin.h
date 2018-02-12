/**
\file NormalSkin.h

\author Jack Li
*/

#ifndef NORMAL_SKIN_H
#define NORMAL_SKIN_H

#include "ApplicationSkin.h"

inline void initNormalResource() { Q_INIT_RESOURCE(NormalSkin); }


class NormalSkin : public ApplicationSkin {
	Q_OBJECT
public:
	NormalSkin() {
		initNormalResource();
	}
	QString styleSheet() { return "normal"; }

	int majorVersion() { return 0; }
	int minorVersion() { return 0; }
	int maintVersion() { return 1; }
	bool testVersion() { return true; }

};


#endif // NORMAL_SKIN_H

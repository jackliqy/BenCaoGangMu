/**
  \file ApplicationSkin.h

  \author Jack Li
*/

#ifndef APPLICATION_SKIN_H
#define APPLICATION_SKIN_H

#include <QColor>
#include <QFont>
#include <QObject>


inline void cleanupNormalResource() { Q_CLEANUP_RESOURCE(NormalSkin); }


enum InspectionCarSkin {
    NMnormal = 0,
    NMdark,
    NMOrange
};

class ApplicationSkin;

class ApplicationSkinFactory
{
public:
	static ApplicationSkin * createSkin();
};


// This class is a QObject such that we can use tr(..)
class ApplicationSkin : public QObject {
	Q_OBJECT
public:
	ApplicationSkin() {}
	virtual ~ApplicationSkin() {}

	// The name of the stylesheet used as basis for the UI
    virtual QString styleSheet() = 0;

	// For now, all skins have the same version number
	virtual int majorVersion() = 0;
	virtual int minorVersion() = 0;
    virtual int maintVersion() = 0;
	virtual bool testVersion() = 0;
};


#endif // APPLICATION_SKIN_H

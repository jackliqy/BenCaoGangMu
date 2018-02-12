#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T16:39:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += multimedia
QT += multimediawidgets
QT += network
QT += concurrent
QT += axcontainer

TARGET = BCGM
TEMPLATE = app


HEADERS += \
    Application.h \
    ApplicationSkin.h \
    BaseDialog.h \
    BCGMApp.h \
    BCGMBaseUI.h \
    BCGMUI.h \
    NetworkList.h \
    UiFactory.h \
    ExceptionMessage.h \
    Base.h \
    resources/normal/NormalSkin.h \
    PaintClock.h


SOURCES += \
    Application.cpp \
    ApplicationSkin.cpp \
    BCGMApp.cpp \
    BCGMBaseUI.cpp \
    BCGMUI.cpp \
    UiFactory.cpp \
    Base.cpp \
    NetworkList.cpp \
    PaintClock.cpp


FORMS += \
    BCGM.ui \
    NetworkList.ui


RESOURCES += \
    BCGM.qrc \
    resources/normal/NormalSkin.qrc


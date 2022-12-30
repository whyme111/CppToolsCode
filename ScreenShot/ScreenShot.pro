QT       += core gui
QT += winextras
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Snapper/freesnapdialog.cpp \
    Snapper/freesnapgraphicsview.cpp \
    Snapper/freesnaprect.cpp \
    main.cpp \
    mainwindow.cpp \
    screenshothelper.cpp \
    windowsinfo.cpp

HEADERS += \
    Snapper/freesnapdialog.h \
    Snapper/freesnapgraphicsview.h \
    Snapper/freesnaprect.h \
    mainwindow.h \
    screenshothelper.h \
    windowsinfo.h

FORMS += \
    Snapper/freesnapdialog.ui \

unix|win32: LIBS += \
    -L$$PWD/lib/ -lGDI32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/shot.qrc

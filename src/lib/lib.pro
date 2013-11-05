TEMPLATE=lib

CONFIG += plugin

TARGET=flymodenavigator

DESTDIR = $$OUT_PWD/FlyModeNavigator
QMAKE_POST_LINK += $$QMAKE_COPY $$PWD/qmldir $$PWD/FlyModeNavigator.qml $$DESTDIR;

QT += 3dquick quick

HEADERS += \
    mousemover.h \
    flymodenavigatormodule.h

SOURCES += \
    mousemover.cpp \
    flymodenavigatormodule.cpp

OTHER_FILES += FlyModeNavigator.qml \
            qmldir

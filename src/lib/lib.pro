TEMPLATE=lib

CONFIG += plugin

TARGET=flymodenavigator

DESTDIR = $$OUT_PWD/FlyModeNavigator

copyqml.commands = $$QMAKE_COPY $$PWD/qmldir $$PWD/FlyModeNavigator.qml $$DESTDIR;
first.depends = $(first) copyqml
export(first.depends)
export(copyqml.commands)
QMAKE_EXTRA_TARGETS += first copyqml

QT += 3dquick quick

HEADERS += \
    mousemover.h \
    flymodenavigatormodule.h

SOURCES += \
    mousemover.cpp \
    flymodenavigatormodule.cpp

OTHER_FILES += FlyModeNavigator.qml \
            qmldir

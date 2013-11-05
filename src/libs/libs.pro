TEMPLATE=lib

CONFIG += plugin

TARGET=FlyModeNavigator

DESTDIR = $$OUT_PWD/$$TARGET

qmlplugindump.commands = qmlplugindump -notrelocatable $$TARGET 1.0 . > $$DESTDIR/plugins.qmltypes
copyqml.commands = $(COPY_DIR) $$PWD/qmldir $$PWD/FlyModeNavigator.qml $$DESTDIR
first.depends = $(first) copyqml qmlplugindump
export(first.depends)
export(copyqml.commands)
export(qmlplugindump.commands)
QMAKE_EXTRA_TARGETS += first copyqml qmlplugindump

QT += 3dquick quick

HEADERS += \
    mousemover.h \
    flymodenavigatormodule.h

SOURCES += \
    mousemover.cpp \
    flymodenavigatormodule.cpp

OTHER_FILES += FlyModeNavigator.qml \
            qmldir

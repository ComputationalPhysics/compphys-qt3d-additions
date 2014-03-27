TEMPLATE=lib
TARGET=FlyModeNavigator
QT += qml 3dquick quick

CONFIG += qt plugin

uri = CompPhys.FlyModeNavigator

DESTDIR = $$OUT_PWD/$$TARGET

#qmlplugindump.commands = qmlplugindump -notrelocatable $$TARGET 1.0 . > $$DESTDIR/plugins.qmltypes
copyqml.commands = $(COPY_DIR) $$PWD/qmldir $$PWD/FlyModeNavigator.qml $$DESTDIR
first.depends = $(first) copyqml
export(first.depends)
export(copyqml.commands)
#export(qmlplugindump.commands)
QMAKE_EXTRA_TARGETS += first copyqml

HEADERS += \
    mousemover.h \
    flymodenavigatormodule.h

SOURCES += \
    mousemover.cpp \
    flymodenavigatormodule.cpp

OTHER_FILES += FlyModeNavigator.qml \
            qmldir

# Install instructions
qmldir.files = qmldir
qmlfile.files = FlyModeNavigator.qml
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    qmlfile.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir qmlfile
}

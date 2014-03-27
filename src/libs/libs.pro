QT += 3dquick
TEMPLATE=lib
CONFIG += plugin

TARGET=StereoViewport

DESTDIR = $$OUT_PWD/$$TARGET

qmlplugindump.commands = qmlplugindump -notrelocatable $$TARGET 1.0 . > $$DESTDIR/plugins.qmltypes
copyqml.commands = $(COPY_DIR) $$PWD/qmldir $$DESTDIR
first.depends = $(first) copyqml qmlplugindump
export(first.depends)
export(copyqml.commands)
export(qmlplugindump.commands)
QMAKE_EXTRA_TARGETS += first copyqml qmlplugindump

HEADERS += \
    qglmaskedsurface_p.h \
    qgldrawbuffersurface_p.h \
    stereoviewport.h \
    stereoviewportmodule.h

SOURCES += \
    stereoviewport.cpp \
    qglmaskedsurface.cpp \
    qgldrawbuffersurface.cpp \
    stereoviewportmodule.cpp

OTHER_FILES += \
    qmldir

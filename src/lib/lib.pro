QT += 3dquick
TEMPLATE=lib
CONFIG += plugin

TARGET=stereoviewport

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

DESTDIR = $$OUT_PWD/StereoViewport
QMAKE_POST_LINK += $$QMAKE_COPY $$PWD/qmldir $$DESTDIR/qmldir;

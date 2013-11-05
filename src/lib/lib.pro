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

TEMPLATE=lib
TARGET=MarchingCubes
QT += qml quick 3dquick

CONFIG += qt plugin

#TARGET = $$qtLibraryTarget($$TARGET)
uri = CompPhys.MarchingCubes

HEADERS_OUT_DIR = $$OUT_PWD/include/compphys/marchingcubes

# Create plugin info data for Qt Creator
#QMAKE_POST_LINK += qmlplugindump -notrelocatable CompPhys.$$TARGET 1.0 $$OUT_PWD > $$DESTDIR/plugins.qmltypes

SOURCES += \
    marchingcubesmodule.cpp \
    isosurface.cpp \
    marchingcubes.cpp \
    datasource.cpp

HEADERS += \
    marchingcubesmodule.h \
    isosurface.h \
    marchingcubes.h \
    datasource.h

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    solibs.path = $$[QT_INSTALL_LIBS]
    mac {
        solibs.files = $$OUT_PWD/lib$${TARGET}.dylib
    } else {
        solibs.files = $$OUT_PWD/lib$${TARGET}.so
    }
    system(mkdir -p $$OUT_PWD && touch $$solibs.files) # to ensure the file exists when qmake looks for it
    INSTALLS += target qmldir solibs
}

# Copy the necessary headers as well
!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copyheaders.commands = $$QMAKE_MKDIR $$HEADERS_OUT_DIR && $(COPY_DIR) $$PWD/isosurface.h $$PWD/datasource.h $$HEADERS_OUT_DIR
    first.depends = $(first) copyheaders
    export(first.depends)
    export(copyheaders.commands)
    QMAKE_EXTRA_TARGETS += first copyheaders
}

# Set up installation of headers
target_headers.files = isosurface.h datasource.h
unix {
    headersInstallPath = $$[QT_INSTALL_HEADERS]/compphys/marchingcubes
    target_headers.path = $$headersInstallPath
    INSTALLS += target_headers
}

OTHER_FILES += README.md \
    qmldir

QMAKE_CXXFLAGS += -std=c++0x

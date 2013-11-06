QT += 3dquick

# Add more folders to ship with the application, here
folder_01.source = qml/flymodenavigator
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

# Added for code completion in Qt Creator
QML_IMPORT_PATH = $$OUT_PWD/../libs/

OTHER_FILES +=

TARGET = flymodenavigator-demo

macx {
    LIBS_TARGET_DIR = $$OUT_PWD/$${TARGET}.app/Contents/Resources/

    copydata.commands = echo Balle && $(COPY_DIR) $$OUT_PWD/../libs/StereoViewport $$LIBS_TARGET_DIR
    first.depends = $(first) copydeploymentfolders copydata
    export(first.depends)
    export(copydata.commands)
    QMAKE_EXTRA_TARGETS += first copydata
}

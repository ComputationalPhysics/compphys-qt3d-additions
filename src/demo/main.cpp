#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;
#ifdef Q_OS_MACX
    viewer.addImportPath(".");
#else
    viewer.addImportPath("../libs");
#endif
    viewer.setMainQmlFile(QStringLiteral("qml/stereoviewport/main.qml"));
    viewer.showExpanded();

    return app.exec();
}

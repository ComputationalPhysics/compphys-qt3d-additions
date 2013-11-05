#include <QApplication>
#include <QtGui/QGuiApplication>
#include <QQmlContext>
#include <mousemover.h>
#include "qtquick2applicationviewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    MouseMover mouseMover(&viewer);
    viewer.setMainQmlFile(QStringLiteral("qml/viewportnavigator/main.qml"));
    viewer.rootContext()->setContextProperty("mouseMover", &mouseMover);
    viewer.showExpanded();
    mouseMover.setShowCursor(true);

    return app.exec();
}

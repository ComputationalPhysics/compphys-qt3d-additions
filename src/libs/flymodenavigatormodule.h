#ifndef FLYMODENAVIGATORMODULE_H
#define FLYMODENAVIGATORMODULE_H

#include <QQmlExtensionPlugin>
#include <QtQml>
#include <mousemover.h>

class FlyModeNavigatorModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
public:
    virtual void registerTypes(const char *uri) {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("CompPhys.FlyModeNavigator"));
        qmlRegisterType<MouseMover>(uri, 1, 0, "MouseMover");
    }
    void initializeEngine(QQmlEngine*, const char*) {

    }
};

#endif // FLYMODENAVIGATORMODULE_H

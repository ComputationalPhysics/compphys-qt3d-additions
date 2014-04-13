#ifndef MARCHINGCUBESMODULE_H
#define MARCHINGCUBESMODULE_H

#include <QQmlExtensionPlugin>
#include <QtQml>
#include <isosurface.h>

class MarchingCubesModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
public:
    virtual void registerTypes(const char *uri) {
        Q_UNUSED(uri)
        Q_ASSERT(QLatin1String(uri) == QLatin1String("CompPhys.MarchingCubes"));
        qmlRegisterType<IsoSurface>("CompPhys.MarchingCubes", 1, 0, "IsoSurface");
    }
    void initializeEngine(QQmlEngine*, const char*) {

    }
};


#endif // MARCHINGCUBESMODULE_H

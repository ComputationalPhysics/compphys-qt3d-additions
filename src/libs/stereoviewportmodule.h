#ifndef STEREOVIEWPORTMODULE_H
#define STEREOVIEWPORTMODULE_H

#include <QQmlExtensionPlugin>
#include <stereoviewport.h>

class StereoViewportModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface/1.0")
public:
    virtual void registerTypes(const char *uri) {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("StereoViewport"));
        qmlRegisterType<StereoViewport>(uri, 1, 0, "StereoViewport");
    }
    void initializeEngine(QQmlEngine*, const char*) {

    }
};

//#include "stereoviewport.moc"

#endif // STEREOVIEWPORTMODULE_H

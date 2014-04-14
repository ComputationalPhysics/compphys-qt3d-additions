#ifndef ISOSURFACE_H
#define ISOSURFACE_H

#include "datasource.h"
#include <QVector3D>
#include <QArray>
#include <QQuickItem3D>
#include <QGLAbstractScene>
#include <QElapsedTimer>

class IsoSurface : public QQuickItem3D {
    Q_OBJECT
    // Q_PROPERTY(DataSource *dataSource READ dataSource WRITE setDataSource NOTIFY dataSourceChanged)

public:
    IsoSurface(QQuickItem *parent = 0);
    // virtual ~IsoSurface();

//    QGL::DrawingMode drawingMode() const;
//    void setDrawingMode(const QGL::DrawingMode &drawingMode);

//    const QGLVertexBundle vertexBundle();
//    void generateVertexBundle();

//    DataSource * dataSource() const
//    {
//        return m_dataSource;
//    }

public slots:
//    void setDataSource(DataSource * arg)
//    {
//        if (m_dataSource != arg) {
//            qDebug() << "I got thems datasource";
//            m_dataSource = arg;
//            generate();
//            emit dataSourceChanged(arg);
//        }
//    }

signals:
    // void dataSourceChanged(DataSource * arg);

private:
    //void reset();
    //void generate();

    QArray<QVector3D> m_vertices;
    QArray<QVector3D> m_normals;
    QGL::DrawingMode m_drawingMode;
    QGLVertexBundle m_vertexBundle;

    bool m_vertexBundleDirty;

    DataSource * m_dataSource;

protected:
    // void drawItem(QGLPainter *painter);
};

#endif // ISOSURFACE_H

#ifndef ISOSURFACE_H
#define ISOSURFACE_H

#include <QVector3D>
#include <QArray>
#include <QQuickItem3D>
#include <QGLAbstractScene>
#include <QElapsedTimer>

class IsoSurface : public QQuickItem3D {
public:
    explicit IsoSurface(QQuickItem *parent = 0);

    QGL::DrawingMode drawingMode() const;
    void setDrawingMode(const QGL::DrawingMode &drawingMode);

    const QGLVertexBundle vertexBundle();
    void generateVertexBundle();
private:
    QArray<QVector3D> m_vertices;
    QArray<QVector3D> m_normals;
    QGL::DrawingMode m_drawingMode;
    QGLVertexBundle m_vertexBundle;

    bool m_vertexBundleDirty;

protected:
    void drawItem(QGLPainter *painter);
};

#endif // ISOSURFACE_H

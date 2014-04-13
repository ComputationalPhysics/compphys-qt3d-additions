#include "isosurface.h"

QGL::DrawingMode IsoSurface::drawingMode() const
{
    return m_drawingMode;
}

void IsoSurface::setDrawingMode(const QGL::DrawingMode &drawingMode)
{
    m_drawingMode = drawingMode;
}


const QGLVertexBundle IsoSurface::vertexBundle()
{
    if(m_vertexBundleDirty) {
        generateVertexBundle();
    }
    return m_vertexBundle;
}

IsoSurface::IsoSurface(QQuickItem *parent) :
    QQuickItem3D(parent),
    m_vertexBundleDirty(true),
    m_drawingMode(QGL::Points)
{
    m_vertices.append(QVector3D(0,0,0));
    m_vertices.append(QVector3D(10,0,0));
    m_vertices.append(QVector3D(10,10,0));

    m_normals.append(QVector3D(0,0,1));
    m_normals.append(QVector3D(0,0,1));
    m_normals.append(QVector3D(0,0,1));
}

void IsoSurface::generateVertexBundle() {
    m_vertexBundle = QGLVertexBundle();
    m_vertexBundle.addAttribute(QGL::Position, m_vertices);
    m_vertexBundle.addAttribute(QGL::Normal, m_normals);
    m_vertexBundleDirty = false;
}

void IsoSurface::drawItem(QGLPainter *painter) {
    painter->clearAttributes();

    // Set the rest of the vertex bundle (basically only positions)
    painter->setVertexBundle(vertexBundle());
    painter->draw(QGL::DrawingMode(m_drawingMode), m_vertexBundle.vertexCount());
}

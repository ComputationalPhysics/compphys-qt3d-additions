#include "isosurface.h"
#include "marchingcubes.h"

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
    m_drawingMode(QGL::Triangles),
    m_dataSource(0)
{

}

void IsoSurface::generateVertexBundle() {
    m_vertexBundle = QGLVertexBundle();
    m_vertexBundle.addAttribute(QGL::Position, m_vertices);
    m_vertexBundle.addAttribute(QGL::Normal, m_normals);
    m_vertexBundleDirty = false;
}

void IsoSurface::reset(){
    m_vertices.clear();
    m_normals.clear();
}

void IsoSurface::generate() {
    reset();
    if(!m_dataSource) return;

    MarchingCubes<float> marchingCubes;
    marchingCubes.GenerateSurface(m_dataSource->scalarField(), m_dataSource->isoValue(), m_dataSource->gridUnitLength());

    for(int triangle=0; triangle<marchingCubes.m_nTriangles; triangle++) {
        unsigned int p1_index = marchingCubes.m_piTriangleIndices[triangle][0];
        unsigned int p2_index = marchingCubes.m_piTriangleIndices[triangle][1];
        unsigned int p3_index = marchingCubes.m_piTriangleIndices[triangle][2];

        QVector3D &p1 = marchingCubes.m_ppt3dVertices[p1_index];
        QVector3D &p2 = marchingCubes.m_ppt3dVertices[p2_index];
        QVector3D &p3 = marchingCubes.m_ppt3dVertices[p3_index];

        QVector3D &n1 = marchingCubes.m_pvec3dNormals[p1_index];
        QVector3D &n2 = marchingCubes.m_pvec3dNormals[p2_index];
        QVector3D &n3 = marchingCubes.m_pvec3dNormals[p3_index];

        m_vertices.append(p1);
        m_vertices.append(p2);
        m_vertices.append(p3);
        m_normals.append(n1);
        m_normals.append(n2);
        m_normals.append(n3);
    }

    m_vertexBundleDirty = true;
}

void IsoSurface::drawItem(QGLPainter *painter) {
    painter->clearAttributes();

    // Set the rest of the vertex bundle (basically only positions)
    painter->setVertexBundle(vertexBundle());
    painter->draw(QGL::DrawingMode(m_drawingMode), m_vertexBundle.vertexCount());
}

IsoSurface::~IsoSurface()
{
    m_vertices.clear();
    m_normals.clear();
}

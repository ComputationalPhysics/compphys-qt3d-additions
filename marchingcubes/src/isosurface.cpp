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
    m_drawingMode(QGL::Triangles)
{
    int nPoints = 256;
    double systemSize = 20;
    double cellSize = systemSize / (nPoints-1);
    double radius = 5;
    QArray<QArray<QArray<float> > > scalarField;
    scalarField.resize(nPoints);
    for(int i=0; i<nPoints; i++) {
        scalarField[i].resize(nPoints);
        for(int j=0; j<nPoints; j++) {
            scalarField[i][j].resize(nPoints);
            for(int k=0; k<nPoints; k++) {
                double x = (i - nPoints/2)*cellSize;
                double y = (j - nPoints/2)*cellSize;
                double z = (k - nPoints/2)*cellSize;
                double dr2 = x*x + y*y + z*z;
                if(dr2 < radius*radius) scalarField[i][j][k] = 0;
                else scalarField[i][j][k] = 1;
            }
        }
    }

    generateFromScalarField(scalarField, float(0.9), QVector3D(cellSize,cellSize,cellSize));
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
template <typename T>
void IsoSurface::generateFromScalarField(QArray<QArray<QArray<T> > > &scalarField, T isoValue, QVector3D gridUnitLength) {
    reset();

    MarchingCubes<T> marchingCubes;
    qDebug() << "Balle1";
    marchingCubes.GenerateSurface(scalarField, isoValue, gridUnitLength);
    qDebug() << "Balle2";
    for(int triangle=0; triangle<marchingCubes.m_nTriangles; triangle++) {
        unsigned int p1_index = marchingCubes.m_piTriangleIndices[3*triangle+0];
        unsigned int p2_index = marchingCubes.m_piTriangleIndices[3*triangle+1];
        unsigned int p3_index = marchingCubes.m_piTriangleIndices[3*triangle+2];

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
    qDebug() << "Balle3";

    m_vertexBundleDirty = true;
}

void IsoSurface::drawItem(QGLPainter *painter) {
    painter->clearAttributes();

    // Set the rest of the vertex bundle (basically only positions)
    painter->setVertexBundle(vertexBundle());
    painter->draw(QGL::DrawingMode(m_drawingMode), m_vertexBundle.vertexCount());
}

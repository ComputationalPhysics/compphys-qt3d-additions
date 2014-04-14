#include "exampledatasource.h"

QArray<QArray<QArray<float> > > *ExampleDataSource::scalarField()
{
    return &m_scalarField;
}

void ExampleDataSource::setScalarField(const QArray<QArray<QArray<float> > > scalarField)
{
    m_scalarField = scalarField;
}

float ExampleDataSource::isoValue()
{
    return m_isoValue;
}

void ExampleDataSource::setIsoValue(float isoValue)
{
    m_isoValue = isoValue;
}

QVector3D ExampleDataSource::gridUnitLength()
{
    return m_gridUnitLength;
}

void ExampleDataSource::setGridUnitLength(const QVector3D &gridUnitLength)
{
    m_gridUnitLength = gridUnitLength;
}

ExampleDataSource::ExampleDataSource() :
    m_isoValue(0),
    m_gridUnitLength(QVector3D(1,1,1))
{
    qDebug() << "YEAH";
//    int nPoints = 256;
//    double systemSize = 20;
//    double cellSize = systemSize / (nPoints-1);
//    double radius = 5;
//    m_scalarField.resize(nPoints);
//    for(int i=0; i<nPoints; i++) {
//        m_scalarField[i].resize(nPoints);
//        for(int j=0; j<nPoints; j++) {
//            m_scalarField[i][j].resize(nPoints);
//            for(int k=0; k<nPoints; k++) {
//                double x = (i - nPoints/2)*cellSize;
//                double y = (j - nPoints/2)*cellSize;
//                double z = (k - nPoints/2)*cellSize;
//                double dr2 = x*x + y*y + z*z;
//                if(dr2 < radius*radius) m_scalarField[i][j][k] = 0;
//                else m_scalarField[i][j][k] = 1;
//            }
//        }
//    }

//    m_gridUnitLength = QVector3D(cellSize, cellSize, cellSize);
//    m_isoValue = 1.0;
}

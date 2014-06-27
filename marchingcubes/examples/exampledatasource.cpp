#include "exampledatasource.h"
#include "perlinnoise.h"

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
    int octave = 1;
    int frequency = 1;
    int amplitude = 1;
    int seed = 1;
    int numScales = 5;
    float scaleFactor = 3.64341524563;
    float constant = 8.1233135;

    PerlinNoise perlin(octave, frequency, amplitude, seed);


    int nPoints = 128;
    double systemSize = 50;
    double cellSize = systemSize / (nPoints-1);

    m_scalarField.resize(nPoints);
    for(int i=0; i<nPoints; i++) {
        m_scalarField[i].resize(nPoints);
        for(int j=0; j<nPoints; j++) {
            m_scalarField[i][j].resize(nPoints);
            for(int k=0; k<nPoints; k++) {
                double x = (i - nPoints/2.0)/nPoints;
                double y = (j - nPoints/2.0)/nPoints;
                double z = (k - nPoints/2.0)/nPoints;

                float s = 1.0;

                double val = 0;
                for (int a=0; a<numScales; a++) {
                    s = scaleFactor*a + constant;
                    val += perlin.Get(x*s, y*s, z*s);
                }

                m_scalarField[i][j][k] = val;
            }
        }
    }

    m_gridUnitLength = QVector3D(cellSize, cellSize, cellSize);
    m_isoValue = 0.5;
}

#ifndef EXAMPLEDATASOURCE_H
#define EXAMPLEDATASOURCE_H
#include <compphys/marchingcubes/datasource.h>
#include <QObject>

class ExampleDataSource : public DataSource
{
    Q_OBJECT
private:
    QArray<QArray<QArray<float> > > m_scalarField;
    float m_isoValue;
    QVector3D m_gridUnitLength;
public:
    ExampleDataSource();

    QArray<QArray<QArray<float> > > *scalarField();
    void setScalarField(QArray<QArray<QArray<float> > > scalarField);
    float isoValue();
    void setIsoValue(float isoValue);
    QVector3D gridUnitLength();
    void setGridUnitLength(const QVector3D &gridUnitLength);
};

#endif // EXAMPLEDATASOURCE_H

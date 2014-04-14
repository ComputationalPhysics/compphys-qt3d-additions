#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <iostream>
#include <QVector3D>
#include <QArray>
#include <QObject>
using std::cerr;
using std::endl;

class DataSource : public QObject
{
    Q_OBJECT
private:
    QVector3D emptyQVector3D;
public:
    DataSource(QObject *parent = 0);

    virtual const QArray<QArray<QArray<float> > > *scalarField() {
        cerr << "Returning from abstract DataSource.scalarField()."
                "This should not happen." << endl;
        return 0;
    }
    virtual float isoValue() {
        cerr << "Returning from abstract DataSource.isoValue()"
                "This should not happen." << endl;
        return 0;
    }

    virtual QVector3D gridUnitLength() {
        cerr << "Returning from abstract DataSource.gridUnitLength()"
                "This should not happen." << endl;
        return emptyQVector3D;
    }

};

#endif // DATASOURCE_H

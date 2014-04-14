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
        cerr << "Returning from abstract DataSource."
                "This should not happen." << endl;
        return 0;
    }
    virtual float isoValue() {
        cerr << "Returning from abstract DataSource."
                "This should not happen." << endl;
        return 0;
    }

    virtual QVector3D getGridUnitLength() {
        cerr << "Returning from abstract DataSource."
                "This should not happen." << endl;
        return emptyQVector3D;
    }
//    virtual void setGridUnitLength(const QVector3D &value) = 0;
};

#endif // DATASOURCE_H

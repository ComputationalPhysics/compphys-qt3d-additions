#ifndef MARCHINGCUBES_H
#define MARCHINGCUBES_H

// File Name: marchingcubes.h
// Last Modified: 2014-04-13
// Author: Anders Hafreager (basesd on source code
// provided by Raghavendra Chandrashekara)
// Email: anderhaf@fys.uio.no
//
// Description: This is the interface file for the MarchingCubes class.
// MarchingCubes can be used to construct an isosurface from a scalar
// field.

#include <map>
#include <vector>
#include <array>
#include <QArray>
#include <QVector3D>

struct POINT3DID {
    unsigned int newID;
    float x, y, z;
};

typedef std::map<unsigned int, POINT3DID> ID2POINT3DID;

struct TRIANGLE {
    unsigned int pointID[3];
};

typedef std::vector<TRIANGLE> TRIANGLEVECTOR;

template <class T> class MarchingCubes {
public:
    MarchingCubes();
    ~MarchingCubes();

    // Generates the isosurface from the scalar field contained in scalarField array
    void GenerateSurface(const QArray<QArray<QArray<T> > > *scalarField, T isoValue, QVector3D gridUnitLength);

    // Returns true if a valid surface has been generated.
    bool IsSurfaceValid();

    // Deletes the isosurface.
    void DeleteSurface();

    // The number of vertices which make up the isosurface.
    unsigned int m_nVertices;

    // The vertices which make up the isosurface.
    QArray<QVector3D> m_ppt3dVertices;

    // The number of triangles which make up the isosurface.
    unsigned int m_nTriangles;

    // The indices of the vertices which make up the triangles.
    QArray<std::array<unsigned int, 3> > m_piTriangleIndices;

    // The number of normals.
    unsigned int m_nNormals;

    // The normals.
    QArray<QVector3D> m_pvec3dNormals;

    // List of POINT3Ds which form the isosurface.
    ID2POINT3DID m_i2pt3idVertices;

    // List of TRIANGLES which form the triangulation of the isosurface.
    TRIANGLEVECTOR m_trivecTriangles;

    // Returns the edge ID.
    unsigned int GetEdgeID(unsigned int nX, unsigned int nY, unsigned int nZ, unsigned int nEdgeNo);

    // Returns the vertex ID.
    unsigned int GetVertexID(unsigned int nX, unsigned int nY, unsigned int nZ);

    // Calculates the intersection point of the isosurface with an
    // edge.
    POINT3DID CalculateIntersection(unsigned int nX, unsigned int nY, unsigned int nZ, unsigned int nEdgeNo, const QArray<QArray<QArray<T> > > &scalarField);

    // Interpolates between two grid points to produce the point at which
    // the isosurface intersects an edge.
    POINT3DID Interpolate(float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2, T tVal1, T tVal2);

    // Renames vertices and triangles so that they can be accessed more
    // efficiently.
    void RenameVerticesAndTriangles();

    // Calculates the normals.
    void CalculateNormals();

    // No. of cells in x, y, and z directions.
    unsigned int m_nCellsX, m_nCellsY, m_nCellsZ;

    // Cell length in x, y, and z directions.
    float m_fCellLengthX, m_fCellLengthY, m_fCellLengthZ;

    // The isosurface value.
    T m_isoValue;

    // Indicates whether a valid surface is present.
    bool m_bValidSurface;

    // Lookup tables used in the construction of the isosurface.
    static const unsigned int m_edgeTable[256];
    static const int m_triTable[256][16];
};

#endif // MARCHINGCUBES_H

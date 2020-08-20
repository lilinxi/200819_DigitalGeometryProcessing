#ifndef _SPHERICAL_HARMONIC_MAP_MESH_H_
#define _SPHERICAL_HARMONIC_MAP_MESH_H_

#include "Mesh/BaseMesh.h"
#include "Mesh/Edge.h"
#include "Mesh/Face.h"
#include "Mesh/HalfEdge.h"
#include "Mesh/Vertex.h"

#include "Mesh/Boundary.h"
#include "Mesh/Iterators.h"
#include "Parser/parser.h"

namespace MeshLib {
    class MyVertex;

    class MyEdge;

    class MyFace;

    class MyEdge;

    class MyVertex : public CVertex {
    public:
        double &area() { return m_area; };

    protected:
        double m_area;
    };

    class MyEdge : public CEdge {
    };

    class MyFace : public CFace {
    public:
        CPoint &normal() { return m_normal; };

        double &area() { return m_area; };

    protected:
        CPoint m_normal;
        double m_area;
    };

    class MyHalfEdge : public CHalfEdge {
    };

    template<typename V, typename E, typename F, typename H>
    class TMyMesh : public CBaseMesh<V, E, F, H> {
    public:
        typedef V CVertex;
        typedef E CEdge;
        typedef F CFace;
        typedef H CHalfEdge;

        typedef CBoundary<V, E, F, H> CBoundary;
        typedef CLoop<V, E, F, H> CLoop;

        typedef MeshVertexIterator<V, E, F, H> MeshVertexIterator;
        typedef MeshEdgeIterator<V, E, F, H> MeshEdgeIterator;
        typedef MeshFaceIterator<V, E, F, H> MeshFaceIterator;
        typedef MeshHalfEdgeIterator<V, E, F, H> MeshHalfEdgeIterator;

        typedef VertexVertexIterator<V, E, F, H> VertexVertexIterator;
        typedef VertexEdgeIterator<V, E, F, H> VertexEdgeIterator;
        typedef VertexFaceIterator<V, E, F, H> VertexFaceIterator;
        typedef VertexInHalfedgeIterator<V, E, F, H> VertexInHalfedgeIterator;
        typedef VertexOutHalfedgeIterator<V, E, F, H> VertexOutHalfedgeIterator;

        typedef FaceVertexIterator<V, E, F, H> FaceVertexIterator;
        typedef FaceEdgeIterator<V, E, F, H> FaceEdgeIterator;
        typedef FaceHalfedgeIterator<V, E, F, H> FaceHalfedgeIterator;
    };

    typedef TMyMesh<MyVertex, MyEdge, MyFace, MyHalfEdge> MyMesh;
}

#endif // !_SPHERICAL_HARMONIC_MAP_MESH_H_

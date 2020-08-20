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

        double &angles() { return m_angles; };

        double &mean_curvature() { return m_mean_curvature; };

        double &gaussian_curvature() { return m_gaussian_curvature; };

    protected:
        double m_area = 0.0;
        double m_angles = 0.0;
        double m_mean_curvature = 0.0;
        double m_gaussian_curvature = 0.0;
    };

    class MyEdge : public CEdge {
    public:
        double &weight() { return m_weight; };

        double &length() { return m_length; };

    protected:
        double m_weight = 0.0;

        double m_length = 0.0;
    };

    class MyFace : public CFace {
    public:
        CPoint &normal() { return m_normal; };

        double &area() { return m_area; };

        CPoint &center() { return m_center; };

        CPoint &gradients() { return m_gradients; };

    protected:
        CPoint m_normal = CPoint(0, 0, 0);
        double m_area = 0.0;
        CPoint m_center = CPoint(0, 0, 0);
        CPoint m_gradients = CPoint(0, 0, 0);
    };

    class MyHalfEdge : public CHalfEdge {
    public:
        double &angle() { return m_angle; };

    protected:
        double m_angle = 0.0;
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

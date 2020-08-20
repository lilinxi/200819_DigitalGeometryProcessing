#ifndef _SPHERICAL_HARMONIC_MAP_H_
#define _SPHERICAL_HARMONIC_MAP_H_

#include "MyMapMesh.h"

namespace MeshLib {
    class MyMap {
    public:
        MyMap() : m_mesh(nullptr) {};

        void set_mesh(MyMesh *pMesh);

    protected:
        void _calculate_area_and_normal();

        void _calculate_face_center();

        void _calculate_face_gradients();

        void _calculate_edge_weight();

    protected:

        static double _inverse_cosine_law(double a, double b, double c);

    public:
        double getMinGaussianCurvature() const;

        double getMaxGaussianCurvature() const;

        double getMinMeanCurvature() const;

        double getMaxMeanCurvature() const;

    protected:
        MyMesh *m_mesh;
        double min_gaussian_curvature = 1000;
        double max_gaussian_curvature = -1000;
        double min_mean_curvature = 1000;
        double max_mean_curvature = -1000;
    };
}
#endif // !_SPHERICAL_HARMONIC_MAP_H_

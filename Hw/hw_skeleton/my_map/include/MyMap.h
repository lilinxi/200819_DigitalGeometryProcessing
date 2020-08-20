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

    protected:
        MyMesh *m_mesh;
    };
}
#endif // !_SPHERICAL_HARMONIC_MAP_H_

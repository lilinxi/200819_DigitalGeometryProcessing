#include "MyMap.h"

void MeshLib::MyMap::set_mesh(MyMesh *pMesh) {
    this->m_mesh = pMesh;

    this->_calculate_area_and_normal();
}

void MeshLib::MyMap::_calculate_area_and_normal() {
    using M = MyMesh;

    for (M::MeshFaceIterator fiter(this->m_mesh); !fiter.end(); ++fiter) {
        // 遍历模型的每一个面
        M::CFace *pF = *fiter;
        M::CHalfEdge *he = this->m_mesh->faceHalfedge(pF);

        // 获取面的三个点
        CPoint p[3];
        for (auto &k : p) {
            M::CVertex *pv = this->m_mesh->halfedgeTarget(he);
            k = pv->point();
            he = this->m_mesh->halfedgeNext(he);
        }

        // 计算面的面积和法线方向
        CPoint fn = (p[1] - p[0]) ^(p[2] - p[0]);
        pF->area() = fn.norm() / 2.0;
        pF->normal() = fn / fn.norm();
    }

    for (M::MeshVertexIterator viter(this->m_mesh); !viter.end(); ++viter) {
        // 遍历模型的每一个点
        M::CVertex *v = *viter;
        // 加权点周围的面的面积和法线方向
        CPoint n(0, 0, 0);
        double area = 0;
        for (M::VertexFaceIterator vfiter(v); !vfiter.end(); ++vfiter) {
            M::CFace *pF = *vfiter;
            n += pF->normal() * pF->area();
            area += pF->area();
        }
        // 计算点的面积和法线方向
        v->area() = area / 3.0;
        v->normal() = n / n.norm();
    }
}
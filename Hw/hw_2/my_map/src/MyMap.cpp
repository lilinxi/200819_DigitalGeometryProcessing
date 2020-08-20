#include <cmath>
#include "MyMap.h"

void MeshLib::MyMap::set_mesh(MyMesh *pMesh) {
    this->m_mesh = pMesh;

//    this->_calculate_area_and_normal();
//    this->_calculate_face_center();
    this->_calculate_face_gradients();
    this->_calculate_edge_weight();

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

void MeshLib::MyMap::_calculate_face_center() {
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

        CPoint center = (p[0] + p[1] + p[2]) / 3;
        pF->center() = center;
    }
}

void MeshLib::MyMap::_calculate_face_gradients() {
    using M = MyMesh;

    for (M::MeshFaceIterator fiter(this->m_mesh); !fiter.end(); ++fiter) {
        // 遍历模型的每一个面
        M::CFace *pF = *fiter;
        M::CHalfEdge *he = this->m_mesh->faceHalfedge(pF);
        CPoint gradients(0, 0, 0);
        for (int i = 0; i < 3; ++i) {
            CPoint gradient = he->target()->point() - he->source()->point();
            gradient = pF->normal() ^ gradient;
            gradient /= 2 * pF->area();
            gradients += gradient;
        }
        pF->gradients() = gradients;
    }
}

void MeshLib::MyMap::_calculate_edge_weight() {
    using M = MyMesh;

    for (M::MeshEdgeIterator eiter(this->m_mesh); !eiter.end(); ++eiter) {
        // 遍历所有边，计算边的长度
        M::CEdge *pE = *eiter;
        M::CVertex *v1 = this->m_mesh->edgeVertex1(pE);
        M::CVertex *v2 = this->m_mesh->edgeVertex2(pE);
        pE->length() = (v1->point() - v2->point()).norm();
    }

    for (M::MeshFaceIterator fiter(this->m_mesh); !fiter.end(); ++fiter) {
        // 遍历所有面，计算所有半边的角度，叠加所有点对应的角度
        M::CFace *pF = *fiter;
        M::CHalfEdge *pH[3];
        M::CVertex *sources[3];

        pH[0] = this->m_mesh->faceHalfedge(pF);;
        pH[1] = this->m_mesh->halfedgeNext(pH[0]);
        pH[2] = this->m_mesh->halfedgeNext(pH[1]);

        sources[0] = this->m_mesh->halfedgeSource(pH[0]);
        sources[1] = this->m_mesh->halfedgeSource(pH[1]);
        sources[2] = this->m_mesh->halfedgeSource(pH[2]);

        double a = reinterpret_cast<M::CEdge *>(pH[0]->edge())->length();
        double b = reinterpret_cast<M::CEdge *>(pH[1]->edge())->length();
        double c = reinterpret_cast<M::CEdge *>(pH[2]->edge())->length();

        // use inverse cosine law to compute the corner angles
        pH[0]->angle() = MeshLib::MyMap::_inverse_cosine_law(b, c, a);
        pH[1]->angle() = MeshLib::MyMap::_inverse_cosine_law(a, c, b);
        pH[2]->angle() = MeshLib::MyMap::_inverse_cosine_law(a, b, c);

        sources[0]->angles() += pH[1]->angle();
        sources[1]->angles() += pH[2]->angle();
        sources[2]->angles() += pH[0]->angle();
    }

    for (M::MeshEdgeIterator eiter(this->m_mesh); !eiter.end(); ++eiter) {
        // 遍历所有边，计算半边的权重
        M::CEdge *pE = *eiter;

        double weight = 0.0;
        double hE0 = this->m_mesh->edgeHalfedge(pE, 0)->angle();
        weight += 1 / tan(hE0);
        double hE1 = this->m_mesh->edgeHalfedge(pE, 1)->angle();
        weight += 1 / tan(hE1);

        pE->weight() = weight;
    }

    for (M::MeshVertexIterator viter(this->m_mesh); !viter.end(); ++viter) {
        // 遍历所有点，计算点的平均曲率和高斯曲率
        M::CVertex *pV = *viter;

        pV->gaussian_curvature() = 2 * M_PI - pV->angles();
        this->min_gaussian_curvature = std::min(pV->gaussian_curvature(), this->min_gaussian_curvature);
        this->max_gaussian_curvature = std::max(pV->gaussian_curvature(), this->max_gaussian_curvature);

        CPoint laplaceXYZ(0, 0, 0);
        for (M::VertexOutHalfedgeIterator veiter(this->m_mesh, pV); !veiter.end(); ++veiter) {
            M::CHalfEdge *pE = *veiter;
            double weight = this->m_mesh->halfedgeEdge(pE)->weight();
            laplaceXYZ += pE->target()->point() * weight;
        }
        pV->mean_curvature() = laplaceXYZ.norm() / 2;
        this->min_mean_curvature = std::min(pV->mean_curvature(), this->min_mean_curvature);
        this->max_mean_curvature = std::max(pV->mean_curvature(), this->max_mean_curvature);
    }
}

double MeshLib::MyMap::_inverse_cosine_law(double a, double b, double c) {
    double cs = (a * a + b * b - c * c) / (2.0 * a * b);
    assert(cs <= 1.0 && cs >= -1.0);
    return std::acos(cs);
}

double MeshLib::MyMap::getMinGaussianCurvature() const {
    return min_gaussian_curvature;
}

double MeshLib::MyMap::getMaxGaussianCurvature() const {
    return max_gaussian_curvature;
}

double MeshLib::MyMap::getMinMeanCurvature() const {
    return min_mean_curvature;
}

double MeshLib::MyMap::getMaxMeanCurvature() const {
    return max_mean_curvature;
}

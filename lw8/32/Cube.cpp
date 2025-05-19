#include "stdafx.h"
#include "Cube.h"
#include "Intersection.h"
#include "Ray.h"
#include "VectorMath.h"

CCube::CCube(double scale, CVector3d const& center, CMatrix4d const& transform)
    : CGeometryObjectImpl(transform)
    , m_scale(scale)
{
    m_initialTransform.Translate(center.x, center.y, center.z);
    m_initialTransform.Scale(scale, scale, scale);
    OnUpdateTransform();
}

void CCube::OnUpdateTransform()
{
    CGeometryObjectImpl::OnUpdateTransform();

    // ��� ���������� ������� ������������� ������� ���������� �������� ������� ��������� ��������������

    // ����������� ������� ���������� ��������������
    CMatrix4d inverseInitialTransform = m_initialTransform.GetInverseMatrix();

    // �������� �������� ������� �������������� ��������������� ������ � �����
    CMatrix4d const& inverseGeomObjectTransform = CGeometryObjectImpl::GetInverseTransform();

    // ��������� �������������� ������� ��������������, ���������� �������� ������� � �������� �������
    m_inverseTransform = inverseInitialTransform * inverseGeomObjectTransform;
}

/*
���������� ������� ��������� �������������� �������
*/
CMatrix4d const& CCube::GetInverseTransform() const
{
    // ��� ����������� ������� ������ GetInverseTransform() ����� ���������� ����� ����������� ��������������
    return m_inverseTransform;
}

bool CCube::Hit(CRay const& ray, CIntersection& intersection) const
{
    static constexpr double HIT_TIME_EPSILON = 1e-8;
    CRay invRay = Transform(ray, GetInverseTransform());

    // ������ ������: ������� ��������� � ����������� ���������, axis: 0 (x), 1 (y), 2 (z)
    static const std::vector<std::pair<CVector3d, int>> planes = {
        { CVector3d(1, 0, 0), 0 },   // x = 1
        { CVector3d(-1, 0, 0), 0 },  // x = -1
        { CVector3d(0, 1, 0), 1 },   // y = 1
        { CVector3d(0, -1, 0), 1 },  // y = -1
        { CVector3d(0, 0, 1), 2 },   // z = 1
        { CVector3d(0, 0, -1), 2 }   // z = -1
    };

    double t_min = 1e10;
    CVector3d hitPoint, hitPointInObjectSpace, normalInObjectSpace;

    // ����� ������
    for (const auto& [normal, axis] : planes) {
        double coord = normal[axis]; // ���������� ��������� = ���������� �������
        double s = invRay.GetStart()[axis];
        double d = invRay.GetDirection()[axis];

        if (fabs(d) < HIT_TIME_EPSILON) continue;

        double t = (coord - s) / d;
        if (t < HIT_TIME_EPSILON || t >= t_min) continue;

        CVector3d point = invRay.GetPointAtTime(t);
        bool valid = true;
        for (int i = 0; i < 3; ++i) {
            if (i != axis && (point[i] < -1.0 || point[i] > 1.0)) {
                valid = false;
                break;
            }
        }

        if (valid) {
            t_min = t;
            hitPoint = ray.GetPointAtTime(t);
            hitPointInObjectSpace = point;
            normalInObjectSpace = normal;
        }
    }

    // ���� ���� �����������
    if (t_min < 1e10) {
        if (Dot(normalInObjectSpace, invRay.GetDirection()) > 0) {
            normalInObjectSpace = -normalInObjectSpace;
        }

        CVector3d normal = GetNormalMatrix() * normalInObjectSpace;

        intersection.AddHit(CHitInfo(
            t_min, *this,
            hitPoint, hitPointInObjectSpace,
            normal, normalInObjectSpace
        ));

        return true;
    }

    return false;
}
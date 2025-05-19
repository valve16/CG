#include "stdafx.h"
#include "Parab.h"
#include "Intersection.h"
#include "Ray.h"
#include "VectorMath.h"

CParaboloid::CParaboloid(double scale, CVector3d const& center, CMatrix4d const& transform)
    : CGeometryObjectImpl(transform)
    , m_scale(scale)
{
    m_initialTransform.Translate(center.x, center.y, center.z);
    m_initialTransform.Scale(scale, scale, scale);
    OnUpdateTransform();
}

void CParaboloid::OnUpdateTransform()
{
    CGeometryObjectImpl::OnUpdateTransform();

    // При обновлении матрицы трансформации объекта необходимо обновить матрицу обратного преобразования

    // Инвертируем матрицу начального преобразования
    CMatrix4d inverseInitialTransform = m_initialTransform.GetInverseMatrix();

    // Получаем обратную матрицу преобразования геометрического объект в целом
    CMatrix4d const& inverseGeomObjectTransform = CGeometryObjectImpl::GetInverseTransform();

    // Вычисляем результирующую матрицу преобразоваиня, перемножив обратные матрицы в обратном порядке
    m_inverseTransform = inverseInitialTransform * inverseGeomObjectTransform;
}

/*
Вычисление матрицы обратного преобразования объекта
*/
CMatrix4d const& CParaboloid::GetInverseTransform() const
{
    // При последующих вызовах метода GetInverseTransform() будет возвращено ранее вычисленное преобразование
    return m_inverseTransform;
}

bool CParaboloid::Hit(CRay const& ray, CIntersection& intersection) const
{
    CRay invRay = Transform(ray, GetInverseTransform());
    static constexpr double HIT_TIME_EPSILON = 1e-8;


    // Проверка пересечения с боковой поверхностью (x^2 - y^2 - z = 0)
    /*
    A*t^2 + B*t + C
    A = cx^2 - cy2
    B = 2(Sx * cx - Sy * cy) - cz
    C = Sx^2 - Sy^2 - Sz
    */
    double a = invRay.GetDirection().x * invRay.GetDirection().x - invRay.GetDirection().y * invRay.GetDirection().y;
    double b = 2 * (invRay.GetStart().x * invRay.GetDirection().x - invRay.GetStart().y * invRay.GetDirection().y) - invRay.GetDirection().z;
    double c = invRay.GetStart().x * invRay.GetStart().x - invRay.GetStart().y * invRay.GetStart().y - invRay.GetStart().z;

    double disc = b * b - 4 * a * c;

    if (disc >= 0)
    {
        double discRoot = sqrt(disc);

        auto addHit = [&ray, &invRay, this, &intersection](double t) {
            if (t > HIT_TIME_EPSILON)
            {
                CVector3d hitPoint0 = ray.GetPointAtTime(t);
                CVector3d hitPoint0InObjectSpace = invRay.GetPointAtTime(t);
                if (hitPoint0InObjectSpace.x < 1 && hitPoint0InObjectSpace.y < 1 && hitPoint0InObjectSpace.x > -1 && hitPoint0InObjectSpace.y > -1)
                {
                    CVector3d normalInObjectSpace(2 * hitPoint0InObjectSpace.x, -2 * hitPoint0InObjectSpace.y, -1);

                    // Проверяем направление нормали
                    double dot = Dot(normalInObjectSpace, invRay.GetDirection());
                    if (dot > 0) {
                        normalInObjectSpace = -normalInObjectSpace;
                    }

                    CVector3d normal = GetNormalMatrix() * normalInObjectSpace;

                    intersection.AddHit(CHitInfo(
                        t, *this,
                        hitPoint0, hitPoint0InObjectSpace,
                        normal, normalInObjectSpace
                    ));
                }
            }
            };

        addHit(min((-b - discRoot) / (2 * a), (-b + discRoot) / (2 * a)));
        addHit(max((-b - discRoot) / (2 * a), (-b + discRoot) / (2 * a)));
    }

    return intersection.GetHitsCount() > 0;
}
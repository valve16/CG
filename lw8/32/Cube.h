#pragma once
#include "GeometryObjectImpl.h"

/************************************************************************/
/* Геометрический объект "Базовый геометрический параболоид"            */
/************************************************************************/
class CCube : public CGeometryObjectImpl
{
public:
    /*
    Инициализация параболоида с заданной матрицей трансформации
    */
    CCube(
        double scale = 1,
        CVector3d const& center = CVector3d(),
        CMatrix4d const& transform = CMatrix4d());

    /*
    Получение матрицы обратного преобразования объекта
    */
    virtual CMatrix4d const& GetInverseTransform()const;

    /*
    Пересечение луча с параболоидом (боковая поверхность и крышка)
    */
    virtual bool Hit(CRay const& ray, CIntersection& intersection) const override;

protected:
    virtual void OnUpdateTransform() override;

private:
    double m_scale;
    /*
    Параметры обратной матрицы трансформации, построенной с учетом начального
    преобразования базовой сферы и матрицы трансформации сферы
    */
    CMatrix4d m_inverseTransform;

    /*
    Начальная трансформация, выполняющая преобразование базовой сферы единичного радиуса с центром
    в начале координат в сферу заданного радиуса с центром в указанной точке
    */
    CMatrix4d m_initialTransform;
};
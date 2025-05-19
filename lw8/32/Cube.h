#pragma once
#include "GeometryObjectImpl.h"

/************************************************************************/
/* �������������� ������ "������� �������������� ����������"            */
/************************************************************************/
class CCube : public CGeometryObjectImpl
{
public:
    /*
    ������������� ����������� � �������� �������� �������������
    */
    CCube(
        double scale = 1,
        CVector3d const& center = CVector3d(),
        CMatrix4d const& transform = CMatrix4d());

    /*
    ��������� ������� ��������� �������������� �������
    */
    virtual CMatrix4d const& GetInverseTransform()const;

    /*
    ����������� ���� � ������������ (������� ����������� � ������)
    */
    virtual bool Hit(CRay const& ray, CIntersection& intersection) const override;

protected:
    virtual void OnUpdateTransform() override;

private:
    double m_scale;
    /*
    ��������� �������� ������� �������������, ����������� � ������ ����������
    �������������� ������� ����� � ������� ������������� �����
    */
    CMatrix4d m_inverseTransform;

    /*
    ��������� �������������, ����������� �������������� ������� ����� ���������� ������� � �������
    � ������ ��������� � ����� ��������� ������� � ������� � ��������� �����
    */
    CMatrix4d m_initialTransform;
};
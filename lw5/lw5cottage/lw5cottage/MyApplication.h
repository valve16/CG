#pragma once
#include "../libgl/GLApplication.h"
#include "../libgl/OmniLight.h"
#include "../libgl/RotationController.h"
#include "Planet.h"
#include "SkyBox.h"
#include "Cottage.h"
#include "Garage.h"
#include "Fence.h"
#include "Porch.h"
#include "Ground.h"

class CMyApplication : public CGLApplication
{
public:
	CMyApplication(const char* title, int width, int height);

protected:
	virtual void OnInit();
	virtual void OnDisplay();
	virtual void OnIdle();
	virtual void OnReshape(int width, int height);
	virtual void OnMouse(int button, int state, int x, int y);
	virtual void OnMotion(int x, int y);
	virtual void OnKeyboard(unsigned char key, int x, int y);

private:
	// Рисуем космос
	void DrawSkyBox() const;

	void DrawCottage() const;
	// Угол обзора по вертикали
	static const double FIELD_OF_VIEW;

	// Расстояние до ближней и дальней плоскостей отсечения
	static const double ZNEAR;
	static const double ZFAR;

	// Режим визуализации граней
	// (переключается при помощи клавиши Пробел)
	GLenum m_polygonMode;

	// Контроллеры вращения и анимации
	CRotationController m_rotationController;
	//CAnimationController m_animationController;

	// Точечный источник света
	COmniLight m_light;

	// коттедж++ 
	Cottage m_cottage;
	Garage m_garage;
	Fence m_fence;
	Porch m_porch;
	Ground m_ground;
	CSkyBox m_skyBox;

	GLuint m_brickTexture, m_roofTexture, m_windowTexture,
		m_doorTexture, m_grassTexture,
		m_garageDoorTexture, m_sideTexture,
		m_fenceTexture;

	bool m_fogEnabled;
};

#pragma once
#include "Shaders.h"
#include "glapplication.h"
#include "RotationController.h"

class CMyApplication : public CGLApplication
{
public:
	CMyApplication(const char* title, int width, int height);
	~CMyApplication(void);

protected:
	virtual void OnDisplay() override;;
	virtual void OnInit() override;;
	virtual void OnReshape(int width, int height) override;;
	virtual void OnIdle() override;;
	virtual void OnMouse(int button, int state, int x, int y) override;;
	virtual void OnMotion(int x, int y) override;;

private:
	void InitShaders();

private:
	// Шейдерные объекты
	static const double FIELD_OF_VIEW;

	// Расстояние до ближней и дальней плоскостей отсечения
	static const double ZNEAR;
	static const double ZFAR;
	float m_time = 0.0f;

	CRotationController m_rotationController;

	DWORD g_lastTick;
	CProgram m_program;
	CShader m_vertexShader;
	CShader m_fragmentShader;
	// Расположение переменной Size в программном объекте
	//GLint m_sizeLocation;
	GLint m_timeLocation;
};

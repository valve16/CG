#pragma once
#include "Shaders.h"
#include "glapplication.h"

class CMyApplication : public CGLApplication
{
public:
	CMyApplication(const char* title, int width, int height);
	~CMyApplication(void);

protected:
	virtual void OnDisplay();
	virtual void OnInit();
	virtual void OnReshape(int width, int height);

private:
	void InitShaders();

private:
	// Шейдерные объекты
	static const double FIELD_OF_VIEW;

	// Расстояние до ближней и дальней плоскостей отсечения
	static const double ZNEAR;
	static const double ZFAR;

	CProgram m_program;
	CShader m_vertexShader;
	CShader m_fragmentShader;
	// Расположение переменной Size в программном объекте
	GLint m_sizeLocation;
};

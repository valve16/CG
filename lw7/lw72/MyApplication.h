#pragma once
#include "Shaders.h"
#include "glapplication.h"
#include "Texture.h"

class CMyApplication : public CGLApplication
{
public:
	CMyApplication(const char* title, int width, int height);
	~CMyApplication(void);

protected:
	virtual void OnDisplay();
	virtual void OnInit();
	virtual void OnReshape(int width, int height);
	virtual void OnIdle();

private:
	void InitShaders();
	void InitTextures();
private:
	// Шейдерные объекты
	static const double FIELD_OF_VIEW;

	// Расстояние до ближней и дальней плоскостей отсечения
	static const double ZNEAR;
	static const double ZFAR;

	CProgram m_program;
	CShader m_vertexShader;
	CShader m_fragmentShader;
	
	GLint m_timeLocation;

	DWORD g_lastTick;
	float m_time = 0.0f;

	// Текстра
	CTexture2D m_texture1;
	CTexture2D m_texture2;

	// Расположение переменной TextureMap в программном объекте
	GLint m_textureMap1Location;
	GLint m_textureMap2Location;
};

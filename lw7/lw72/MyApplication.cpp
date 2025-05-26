#include "StdAfx.h"
#include "MyApplication.h"
#include "ProgramLinker.h"
#include "ShaderCompiler.h"
#include "ShaderLoader.h"
#include "TextureLoader.h"

const double CMyApplication::ZNEAR = 0.1;
// Расстояние до дальей плоскости отсечения отображаемого объема
const double CMyApplication::ZFAR = 200;
// Угол обзора по вертикалиa
const double CMyApplication::FIELD_OF_VIEW = 70;

CMyApplication::CMyApplication(const char* title, int width, int height)
	: CGLApplication(title, width, height)
{
}

CMyApplication::~CMyApplication(void)
{
}

void CMyApplication::OnInit()
{
	InitShaders();
	InitTextures();
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void CMyApplication::InitTextures()
{
	// Загружаем текстуру
	CTextureLoader loader;
	loader.BuildMipmaps(true);
	loader.SetMagFilter(GL_LINEAR);
	loader.SetMinFilter(GL_LINEAR_MIPMAP_LINEAR);
	m_texture1 = loader.LoadTexture2D(L"car.jpg");
	m_texture2 = loader.LoadTexture2D(L"photo.jpg");
}

void CMyApplication::InitShaders()
{
	// Проверяем поддержку геометрических шейдеров видеокартой
	if (!GLEW_EXT_geometry_shader4)
	{
		throw std::runtime_error(
			"The OpenGL implementation does not support geometry shaders");
	}

	CShaderLoader loader;
	// Загружаем шейдеры
	m_vertexShader = loader.LoadShader(GL_VERTEX_SHADER, "shaders\\vertex_shader.vsh");
	m_fragmentShader = loader.LoadShader(GL_FRAGMENT_SHADER, "shaders\\fragment_shader.fsh");

	// Создаем программный объект и присоединяем шейдеры к нему
	m_program.Create();
	m_program.AttachShader(m_vertexShader);
	m_program.AttachShader(m_fragmentShader);

	// Компилируем шейдеры
	CShaderCompiler compiler;
	compiler.CompileShader(m_vertexShader);
	compiler.CompileShader(m_fragmentShader);
	compiler.CheckStatus();

	// Задаем параметры шейдерной программы
	// тип входных примитивов: точки

	// Компонуем программу и проверяем ее статус
	CProgramLinker linker;
	linker.LinkProgram(m_program);
	linker.CheckStatus();

	// Получаем расположение uniform-переменных, используемых в
	// шейдерной программе
	m_timeLocation = m_program.GetUniformLocation("Time");
	m_textureMap1Location = m_program.GetUniformLocation("TextureMap1");
	m_textureMap2Location = m_program.GetUniformLocation("TextureMap2");
}

void CMyApplication::OnDisplay()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(m_program);
	if (m_textureMap1Location >= 0)
	{
		// задаем номер текстурного модуля 0 для использования дискретизатором
		// TextureMap
		glUniform1i(m_textureMap1Location, 0);
	}
	if (m_textureMap2Location >= 0)
	{
		// задаем номер текстурного модуля 1 для использования дискретизатором
		// TextureMap
		glUniform1i(m_textureMap2Location, 1);
	}

	glUniform1f(m_timeLocation, m_time);

	glEnable(GL_TEXTURE_2D);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 1);
		glVertex2f((GLfloat)(-0.8), (GLfloat)(-0.8));

		glTexCoord2f(1, 1);
		glVertex2f((GLfloat)(0.8), (GLfloat)(-0.8));

		glTexCoord2f(1, 0);
		glVertex2f((GLfloat)(0.8), (GLfloat)(0.8));

		glTexCoord2f(0, 0);
		glVertex2f((GLfloat)(-0.8), (GLfloat)(0.8));
	}
	glEnd();

	glUseProgram(0);
}


void CMyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double aspect = (double)width / height;
	double viewHeight = 2;
	double viewWidth = aspect * viewHeight;

	glOrtho(
		-viewWidth / 2, +viewWidth / 2,
		-viewHeight / 2, +viewHeight / 2,
		-1, 1);

	glMatrixMode(GL_MODELVIEW);
}

void CMyApplication::OnIdle()
{
	DWORD currentTick = GetTickCount();
	float deltaTime = (currentTick - g_lastTick) / 1000.0f;
	g_lastTick = currentTick;
	m_time += deltaTime * 0.3;
	if (m_time >= 1.0f)
	{
		m_time = 0.0f;
	}
	glutPostRedisplay();
}
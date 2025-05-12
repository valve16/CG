#include "StdAfx.h"
#include "MyApplication.h"
#include "ProgramLinker.h"
#include "ShaderCompiler.h"
#include "ShaderLoader.h"

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
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
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
	m_sizeLocation = m_program.GetUniformLocation("Size");
}

void CMyApplication::OnDisplay()
{
	glClearColor(0.3f, 0.4f, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT);


	//glEnable(GL_TEXTURE_2D);
	glUseProgram(m_program);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0, 0);
		glVertex2f((GLfloat)(-0.8), (GLfloat)(-0.4));

		glTexCoord2f(2, 0);
		glVertex2f((GLfloat)(0.8), (GLfloat)(-0.4));

		glTexCoord2f(2, 1);
		glVertex2f((GLfloat)(0.8), (GLfloat)(0.4));

		glTexCoord2f(0, 1);
		glVertex2f((GLfloat)(-0.8), (GLfloat)(0.4));
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
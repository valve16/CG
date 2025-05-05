#include "StdAfx.h"
#include "MyApplication.h"
#include "ProgramLinker.h"
#include "ShaderCompiler.h"
#include "ShaderLoader.h"

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
	glClear(GL_COLOR_BUFFER_BIT);

	// Activate shader program
	glUseProgram(m_program);

	// Draw a rectangle from (0,0) to (2,2)
	glBegin(GL_QUADS);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(1.0f, -1.0f);
	glVertex2f(1.0f, 1.0f);
	glVertex2f(-1.0f, 1.0f);
	glEnd();

	// Switch back to fixed pipeline
	glUseProgram(0);
}


void CMyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-3.0, 3.0,
	//		-3.0, 3.0,
	//		-1.0, 1.0); // Widened to show full curve
	float aspect = (float)width / height;
	if (aspect > 2.0f) {
		float w = 2.0f * aspect;
		glOrtho(-w / 2, w / 2, -1.0, 1.0, -1.0, 1.0);
	}
	else {
		float h = 1.0f / (aspect / 2.0f);
		glOrtho(-1.0, 1.0, -h / 2, h / 2, -1.0, 1.0);
	}
	glMatrixMode(GL_MODELVIEW);
}
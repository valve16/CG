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
	//m_geometryShader = loader.LoadShader(GL_GEOMETRY_SHADER, "shaders\\geometry_shader.gsh");

	// Создаем программный объект и присоединяем шейдеры к нему
	m_program.Create();
	m_program.AttachShader(m_vertexShader);
	m_program.AttachShader(m_fragmentShader);
	//m_program.AttachShader(m_geometryShader);

	// Компилируем шейдеры
	CShaderCompiler compiler;
	compiler.CompileShader(m_vertexShader);
	//compiler.CompileShader(m_geometryShader);
	compiler.CompileShader(m_fragmentShader);
	compiler.CheckStatus();

	// Задаем параметры шейдерной программы
	// тип входных примитивов: точки
	//m_program.SetParameter(GL_GEOMETRY_INPUT_TYPE_ARB, GL_POINTS);
	//// типв выходных примитивов: лента из треугольникков
	//m_program.SetParameter(GL_GEOMETRY_OUTPUT_TYPE_ARB, GL_TRIANGLE_STRIP);
	//// Максимальное количество вершин, порождаемых геометрическим шейдером
	//// за один вызов. Для ленты из двух треугольников оно равно 4
	//m_program.SetParameter(GL_GEOMETRY_VERTICES_OUT_EXT, 4);

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

	// Активируем шейдерную программу и задаем значения ее uniform-переменных
	glUseProgram(m_program);
	glBegin(GL_LINE_STRIP);
	float step = M_PI / 1000.0f;
	int numPoints = static_cast<int>(2.0f * M_PI / step) + 1; // ≈ 2000 points
	for (int i = 0; i < numPoints; ++i)
	{
		float x = i * step; // x from 0 to 2π
		glVertex3f(x, 0.0f, 0.0f);
	}
	glEnd();

	// Переключаемся на стандартный конвейер
	glUseProgram(0);
}

void CMyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0,
			-3.0, 3.0,
			-1.0, 1.0); // Widened to show full curve
	glMatrixMode(GL_MODELVIEW);
}
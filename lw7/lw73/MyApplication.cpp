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
	: CGLApplication(title, width, height),
	m_rotationController(width, height)
{
}

CMyApplication::~CMyApplication(void)
{
}

void CMyApplication::OnInit()
{
	InitShaders();
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gluLookAt(2, 2, 2,
			0, 0, 0,
			0, 0, 1);
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
	//m_sizeLocation = m_program.GetUniformLocation("Size");
	m_timeLocation = m_program.GetUniformLocation("time");
}

void CMyApplication::OnDisplay()
{



	//glClearColor(0.3f, 0.4f, 0.5f, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//glEnable(GL_TEXTURE_2D);
	glUseProgram(m_program);
	glUniform1f(m_timeLocation, m_time);

	// Параметры сетки
	const int gridCount = 50;
	const float step = 4.0f / gridCount;

	for (int i = 0; i < gridCount; ++i) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= gridCount; ++j) {
			float x = -2.0f + j * step;
			float y = -2.0f + i * step;

			glVertex3f(x, y, 0.0f);
			glVertex3f(x, y + step, 0.0f);
		}
		glEnd();
	}

	glUseProgram(0);

}


void CMyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	m_rotationController.ResizeWindow(width, height);
	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FIELD_OF_VIEW, aspect, ZNEAR, ZFAR);
	glMatrixMode(GL_MODELVIEW);
}

void CMyApplication::OnIdle()
{
	DWORD currentTick = GetTickCount();
	float deltaTime = (currentTick - g_lastTick) / 1000.0f;
	m_time += deltaTime;
	g_lastTick = currentTick;

	glutPostRedisplay();
}

void CMyApplication::OnMouse(int button, int state, int x, int y)
{
	m_rotationController.OnMouse(button, state, x, y);
}

void CMyApplication::OnMotion(int x, int y)
{
	if (m_rotationController.LeftButtonIsPressed())
	{
		m_rotationController.OnMotion(x, y);
		PostRedisplay();
	}
}

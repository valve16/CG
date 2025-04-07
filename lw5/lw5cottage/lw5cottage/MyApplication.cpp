#include "MyApplication.h"
#include "../libgl/TextureLoader.h"
#include <iostream>

// Расстояние до ближней плоскости отсечения отображаемого объема
const double CMyApplication::ZNEAR = 0.1;
// Расстояние до дальей плоскости отсечения отображаемого объема
const double CMyApplication::ZFAR = 200;
// Угол обзора по вертикалиa
const double CMyApplication::FIELD_OF_VIEW = 70;

CMyApplication::CMyApplication(const char* title, int width, int height)
	: CGLApplication(title, width, height),
	m_rotationController(width, height),
	m_light(CVector3f(5, 10, 10)),
	m_cottage(5, 4, 3.5),
	m_garage(3.5, 3, 2.5),
	m_fence(20, 1.5),
	m_porch(3, 1, 0.2),
	m_ground(50),
	m_polygonMode(GL_FILL),
	m_skyBox(
		L"assets/Galaxy_LT.png",
		L"assets/Galaxy_RT.png",
		L"assets/Galaxy_DN.png",
		L"assets/Galaxy_UP.png",
		L"assets/Galaxy_BK.png",
		L"assets/Galaxy_FT.png")
{
	m_light.SetDiffuseIntensity(1, 1, 1);
	m_light.SetSpecularIntensity(1, 1, 1);
}

void CMyApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
	gluLookAt(0, 15, 5,
			  0, 0, 0, 
			  0, 0, 1); 

	CTextureLoader textureLoader;
	textureLoader.SetMinFilter(GL_LINEAR_MIPMAP_LINEAR);
	textureLoader.SetMagFilter(GL_LINEAR);
	textureLoader.BuildMipmaps(true);
	textureLoader.SetWrapMode(GL_REPEAT, GL_REPEAT);

	try {
		m_brickTexture = textureLoader.LoadTexture2D(L"assets/bricks.jpg");
		m_roofTexture = textureLoader.LoadTexture2D(L"assets/roof.png");
		m_windowTexture = textureLoader.LoadTexture2D(L"assets/window.png");
		m_doorTexture = textureLoader.LoadTexture2D(L"assets/door.jpg");
		m_grassTexture = textureLoader.LoadTexture2D(L"assets/grass.jpg");
		m_garageDoorTexture = textureLoader.LoadTexture2D(L"assets/garageDoor.jpg");
		m_sideTexture = textureLoader.LoadTexture2D(L"assets/Side.jpg");
		m_fenceTexture = textureLoader.LoadTexture2D(L"assets/fence.jpg");
	}
	catch (const std::runtime_error& e) {
		throw std::runtime_error(std::string("Texture loading failed: ") + e.what());
	}

	m_cottage.SetTextures(m_brickTexture, m_roofTexture, m_windowTexture, m_doorTexture, m_sideTexture);
	m_garage.SetTextures(m_brickTexture, m_roofTexture, m_windowTexture, m_garageDoorTexture);
	m_fence.SetTexture(m_fenceTexture);
	m_porch.SetTexture(m_brickTexture, m_roofTexture);
	m_ground.SetTexture(m_grassTexture);
	
}

//void CMyApplication::OnDisplay()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// Включаем режим наложения текстуры
//	glEnable(GL_TEXTURE_2D);
//
//	glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
//
//	DrawSkyBox();
//	DrawEarth();
//}

void CMyApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_fogEnabled)
	{
		glEnable(GL_FOG);
	}
	else
	{
		glDisable(GL_FOG);
	}

	// Задаем режим тумана
	glFogi(GL_FOG_MODE, GL_EXP2);

	// Задаем цвет тумана
	float fogColor[4] = { 1, 1, 1, 1 };
	glFogfv(GL_FOG_COLOR, fogColor);

	// и его плотность
	glFogf(GL_FOG_DENSITY, 0.1f);


	// Включаем режим наложения текстуры
	glEnable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, m_polygonMode);
	DrawSkyBox();
	DrawCottage();
}

void CMyApplication::DrawCottage() const
{
	glEnable(GL_NORMALIZE);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	m_light.SetLight(GL_LIGHT0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);


	m_ground.Draw();
	m_cottage.Draw();

	glPushMatrix();
	glTranslatef(4, 0, 0);
	glRotatef(-90, 0, 0, 1);
	m_garage.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-1, 2.5, 0);
	m_porch.Draw();
	glPopMatrix();

	// забор 
	//glDisable(GL_CULL_FACE);
	// перед
	glPushMatrix();
	glTranslatef(-3, 8, 0);
	m_fence.Draw();
	glPopMatrix();

	//лево
	glPushMatrix();
	glTranslatef(7, -2, 0);
	glRotatef(90, 0, 0, 1);
	m_fence.Draw();
	glPopMatrix();

	// сзади
	glPushMatrix();
	glTranslatef(-3,-12, 0);
	m_fence.Draw();
	glPopMatrix();

	// право
	glPushMatrix();
	glTranslatef(-13, -2, 0);
	glRotatef(-90, 0, 0, 1);
	m_fence.Draw();
	glPopMatrix();
	//glEnable(GL_CULL_FACE);

}

void CMyApplication::DrawSkyBox() const
{
	glDisable(GL_LIGHTING);
	// Отключим режим отбраковки граней, т.к.
	// мы находимся внутри куба и видим его нелицевую сторону
	glDisable(GL_CULL_FACE);
	m_skyBox.Draw();
}

void CMyApplication::OnIdle()
{
	m_animationController.Tick();
	PostRedisplay();
	Sleep(10);
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

void CMyApplication::OnMouse(int button, int state, int x, int y)
{
	// Событие от левой кнопки мыши
	m_rotationController.OnMouse(button, state, x, y);
}

void CMyApplication::OnMotion(int x, int y)
{
	// Если нажата левая кнопка мыши
	if (m_rotationController.LeftButtonIsPressed())
	{
		m_rotationController.OnMotion(x, y);

		// Инициируем перерисовку окна
		PostRedisplay();
	}
}

void CMyApplication::OnKeyboard(unsigned char key, int /*x*/, int /*y*/)
{
	if (key == ' ')
	{
		if (m_polygonMode == GL_FILL)
		{
			m_polygonMode = GL_LINE;
		}
		else if (m_polygonMode == GL_LINE)
		{
			m_polygonMode = GL_POINT;
		}
		else // polygon mode == GL_POINT
		{
			m_polygonMode = GL_FILL;
		}
		PostRedisplay();
	}
	if ( key == 'f' || key == 'а')
	{
		m_fogEnabled = !m_fogEnabled;
		PostRedisplay();
	}
}


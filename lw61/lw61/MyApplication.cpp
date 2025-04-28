#define _USE_MATH_DEFINES 
#include "StdAfx.h"
#include "MyApplication.h"
#include "ModelLoader.h"
#include "Material.h"
#include "DirectLight.h"
#include "Vector3.h"

#include <cmath>
// Угол обзора по вертикали
const double CMyApplication::FIELD_OF_VIEW = 75;


CMyApplication::CMyApplication(const char * title, int width, int height)
:CGLApplication(title, width, height)
,m_rotationController(width, height)
{
}

CMyApplication::~CMyApplication(void)
{
}

void CMyApplication::OnInit()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(1, 1, 1, 1);
	
	// Включаем свет и задаем его параметры
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	CDirectLight light;
	light.SetAmbientIntensity(0.2f, 0.2f, 0.2f);
	light.SetDiffuseIntensity(0.5f, 0.5f, 0.5f);
	light.SetSpecularIntensity(0.1f, 0.1f, 0.1f);
	light.SetLight(GL_LIGHT0);

	// Загружаем трехмерную модель
	CModelLoader loader;
	//loader.IgnoreMissingTextures(false);
	loader.Load3dsFile("loader.3ds", m_model);
	loader.Load3dsFile("assets/house/house_6.3ds", m_house);
	loader.Load3dsFile("assets/car2/asterion.3ds", m_car1);
	loader.Load3dsFile("assets/arbor.3ds", m_arbor);
	loader.Load3dsFile("assets/tree.3ds", m_tree);
	//loader.Load3dsFile("assets/tree1.3ds", m_tree1);
	loader.Load3dsFile("assets/fence.3ds", m_fence);
	loader.Load3dsFile("assets/trash.3ds", m_trash);
	//loader.Load3dsFile("assets/flowers/Poplar 3.3ds", m_flowers);
	//loader.Load3dsFile("assets/house1.3ds", m_house);

	m_sceneModels.clear();
	m_sceneModels.push_back(ModelInstance{ &m_house, CVector3f{0, 0, 0}, CVector3f{0, 0, 0}, 1.0f });
	m_sceneModels.push_back(ModelInstance{ &m_car1, CVector3f{-140, -150, 0}, CVector3f{0, 0, 30}, 0.65f });
	m_sceneModels.push_back(ModelInstance{ &m_arbor, CVector3f{-600, 200, 0}, CVector3f{0, 0, 0}, 1.2f });

	m_sceneModels.push_back(ModelInstance{ &m_tree, CVector3f{0, 200, 0}, CVector3f{0, 0, -45}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_tree, CVector3f{200, 900, 0}, CVector3f{0, 0, -90}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_tree, CVector3f{600, 750, 0}, CVector3f{0, 0, -90}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_tree, CVector3f{600, 1300, 0}, CVector3f{0, 0, -90}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_tree, CVector3f{600, -700, 0}, CVector3f{0, 0, 0}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_tree, CVector3f{800, -120, 0}, CVector3f{0, 0, 200}, 0.5f });

	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{200, -500, 0}, CVector3f{0, 0, 0}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{-400, -500, 0}, CVector3f{0, 0, 0}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{-750, -500, 0}, CVector3f{0, 0, 0}, 0.5f });

	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{-930, -320, 0}, CVector3f{0, 0, 90}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{-930, 30, 0}, CVector3f{0, 0, 90}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{-930, 380, 0}, CVector3f{0, 0, 90}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{-930, 730, 0}, CVector3f{0, 0, 90}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{-930, 1080, 0}, CVector3f{0, 0, 90}, 0.5f });

	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{-750, 1250, 0}, CVector3f{0, 0, 0}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{-400, 1250, 0}, CVector3f{0, 0, 0}, 0.5f });
	m_sceneModels.push_back(ModelInstance{ &m_fence, CVector3f{-50, 1250, 0}, CVector3f{0, 0, 0}, 0.5f });
	
	m_sceneModels.push_back(ModelInstance{ &m_trash, CVector3f{-400, -580, 0}, CVector3f{0, 0, 0}, 0.08f });
	//m_sceneModels.push_back(ModelInstance{ &m_tree1, CVector3f{0, 200, 0}, CVector3f{0, 0, -45}, 1.2f });

	CBoundingBox const& modelBoundingBox = m_house.GetBoundingBox();

	if (modelBoundingBox.IsEmpty())
	{
		throw std::runtime_error("Model is empty. Nothing to render");
	}

	// Центр bounding box-а модели
	CVector3f modelCenter = modelBoundingBox.GetCenter();
	// Длина диагонали bounding box-а
	float modelDiagonal = modelBoundingBox.GetSize().GetLength();
	// Отодвигаем камеру от центра на расстояние, равное диагонали 
	// bounding box-а
	CVector3f cameraPosition = modelCenter + CVector3f(modelDiagonal, 0, 0);

	// Задаем параметры камеры
	glLoadIdentity();
	gluLookAt(
		//cameraPosition.x, cameraPosition.y, cameraPosition.z, 
		//modelCenter.x, modelCenter.y, modelCenter.z, 
		800, 800, 350,
		0, 0, 0,
		0, 0, 1);
}

void CMyApplication::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3ub(0, 0, 0);
	glEnable(GL_CULL_FACE);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



	// Задаем параметры материала, используемого по умолчанию для 
	// граней, для которых материал не был указан
	CMaterial material;
	material.SetSpecular(0.3f, 0.3f, 0.3f);
	material.SetShininess(20);
	material.SetDiffuse(0.3f, 0.3f, 0.7f);
	material.Activate();

	auto currentTime = std::chrono::steady_clock::now();
	float elapsedTime = std::chrono::duration<float>(currentTime - m_animationStartTime).count();
	UpdateCarAnimation(elapsedTime);

	//m_renderer.RenderModel(m_model);
	for (const auto& instance : m_sceneModels) {
		glPushMatrix();
		glTranslatef(instance.position[0], instance.position[1], instance.position[2]);
		glRotatef(instance.rotation[0], 1, 0, 0);
		glRotatef(instance.rotation[1], 0, 1, 0);
		glRotatef(instance.rotation[2], 0, 0, 1);
		glScalef(instance.scale, instance.scale, instance.scale);
		m_renderer.RenderModel(*instance.model);
		glPopMatrix();
	}
}

void CMyApplication::OnReshape(int width, int height)
{
	glViewport(0, 0, width, height);

	// Вычисляем соотношение сторон клиентской области окна
	double aspect = double(width) / double(height);

	float zFar = m_model.GetBoundingBox().GetSize().GetLength() * 2;
	float zNear = zFar * (float)0.01;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FIELD_OF_VIEW, aspect, zNear, zFar);
	glMatrixMode(GL_MODELVIEW);
}

void CMyApplication::OnMouse(int button, int state, int x, int y)
{
	m_rotationController.OnMouse(button, state, x, y);
}

void CMyApplication::OnIdle()

{
	PostRedisplay();
}

void CMyApplication::OnMotion(int x, int y)
{
	if (m_rotationController.LeftButtonIsPressed())
	{
		m_rotationController.OnMotion(x, y);
		PostRedisplay();
	}
}
void CMyApplication::UpdateCarAnimation(float elapsedTime)
{
	const size_t carIndex = 1;
	if (carIndex >= m_sceneModels.size() || m_sceneModels[carIndex].model != &m_car1)
		return;

	const float totalCycleTime = 30.0f;
	float cycleTime = std::fmod(elapsedTime, totalCycleTime);
	// Сегменты движения
	const float diagonalTime = 4.0f;  // 0-4 сек: диагональ
	const float turnRightTime = 2.0f; // 4-6 сек: поворот направо
	const float straightTime = 3.0f;  // 6-9 сек: прямо 11-14 17-20
	const float turnRightTime2 = 2.0f; // 9-11 направо
	const float reverdTime = 3.0f; // 14-17 разворот

	CVector3f position = { -140, -150, 0 }; // Начальная позиция
	float rotationZ = 30.0f;              // Начальный угол поворота
	float tempY = 0, tempX = 0;

	if (cycleTime < diagonalTime) {
		// Сегмент 1: Движение по диагонали (x+200, y+200)
		float t = cycleTime / diagonalTime;
		position.x += 100.0f * t;
		position.y -= 500.0f * t;
		rotationZ = -90.0f + atan2(500.0f, -40.0f) * (180.0f / M_PI);
	}
	else if (cycleTime < diagonalTime + turnRightTime) {
		// Сегмент 2: Поворот направо (по дуге)
		float t = (cycleTime - diagonalTime) / turnRightTime;

		position.x = -140 + 100.0f;
		position.y = -150 - 500.0f;

		float radius = 80.0f;
		float angle = t * M_PI / 2.0f;
		position.x -= radius * (1 - std::cos(angle));
		position.y -= radius * std::sin(angle);
		rotationZ = (-90.0f + atan2(500.0f, -40.0f) * (180.0f / M_PI)) - 100.0f * t;

	}
	else if (cycleTime < diagonalTime + turnRightTime + straightTime) {
		// Сегмент 3: Прямое движение вдоль X
		float t = (cycleTime - (diagonalTime + turnRightTime)) / straightTime;
		// Начальная точка после поворота

		position.x = -140 + 100.0f - 80.0f;
		position.y = -150 - 500.0f - 80.0f;
		position.x -= 1000.0f * t;
		rotationZ = -90.0f;
	}
	else if (cycleTime < diagonalTime + turnRightTime + straightTime + turnRightTime2) {
		// Сегмент 4: Поворот направо (по дуге)
		float t = (cycleTime - (diagonalTime + turnRightTime + straightTime)) / turnRightTime2;

		position.x = -140 + 100.0f - 80.0f - 1000.0f;
		position.y = -150 - 500.0f - 80.0f;

		float radius = 80.0f;
		float angle = t * M_PI / 2.0f;
		position.x -= radius * std::sin(angle); // -1200
		position.y += radius * (1 - std::cos(angle)); // -650
		rotationZ = -90.0f - 90.0f * t;
	}
	else if (cycleTime < diagonalTime + turnRightTime + (2 * straightTime) + turnRightTime2) {
		// Сегмент 5: Движение прямо
		float t = (cycleTime - (diagonalTime + turnRightTime + straightTime + turnRightTime2)) / straightTime;
		position.x = -1200.0f;
		position.y = -650.0f;

		position.y += 1800.0f * t; //y = 1150
		rotationZ = -180.0f;
	}// 17 сек
	else if (cycleTime < 17.0f) {
		// Сегмент 6: Разворот
		float t = (cycleTime - (diagonalTime + turnRightTime + 2 * straightTime + turnRightTime2)) / reverdTime;
		position.x = -1200.0f;
		position.y = 1150.0f;

		float radius = 100.0f;
		float angle = t * M_PI; // Поворот на 180 градусов
		position.x += radius * (std::cos(angle) - 1.0f); // x = -1400
		position.y += radius * std::sin(angle);
		rotationZ = -180.0f + 180.0f * t;
	}
	// до 20 сек
	else if (cycleTime < 20.0f) {
		// Сегмент 6: прямо
		float t = (cycleTime - 17.0f) / straightTime;
		position.x = -1400.0f;
		position.y = 1150.0f;

		position.y -= 1800.0f * t; //y = -650
		rotationZ = 0.0f;
	}// до 22 сек
	else if (cycleTime < 22.0f) {
		// Сегмент 7: Поворот налево 
		float t = (cycleTime - 20.0f) / turnRightTime;

		position.x = -1400.0f;
		position.y = -650.0f;

		float radius = 100.0f;
		float angle = t * M_PI / 2.0f;
		position.x += radius * (1 - std::cos(angle)); // -1300
		position.y -= radius * std::sin(angle); // -750
		rotationZ = 0.0f + 90.0f * t;
	}
	// до 25 сек
	else if (cycleTime < 25.0f) {
		// Сегмент 8: прямо по X
		float t = (cycleTime - 22.0f) / straightTime;
		position.x = -1300.0f;
		position.y = -750.0f;

		position.x += 1300.0f * t; //x = 0
		rotationZ = 90.0f;
	}
	// до 27 сек
	else if (cycleTime < 27.0f) {
		// Сегмент 9: Поворот направо 
		float t = (cycleTime - 25.0f) / turnRightTime;

		position.x = 0.0f;
		position.y = -750.0f;

		float radius = 100.0f;
		float angle = t * M_PI / 2.0f;
		position.x -= radius * std::sin(angle); //x = -100
		position.y += radius * (1 - std::cos(angle)); // y = -650

		float targetAngle = atan2(500.0f, -40.0f) * (180.0f / M_PI) - 90.0f;
		rotationZ = 90.0f + (targetAngle - 90.0f) * t; // Интерполяция

	}
	// до 30 сек
	else if (cycleTime < 30.0f) {
		// Сегмент 10: движение задом
		float t = (cycleTime - 27.0f) / straightTime;

		position.x = -100.0f;
		position.y = -650.0f;

		position.x += -40.0f * t;
		position.y += 500.0f * t;
		rotationZ = atan2(500.0f, -40.0f) * (180.0f / M_PI) - 90.0f;

	}

	// Обновляем позицию и поворот машины
	m_sceneModels[carIndex].position = position;
	m_sceneModels[carIndex].rotation.z = rotationZ;
}
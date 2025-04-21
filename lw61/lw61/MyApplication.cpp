#include "StdAfx.h"
#include "MyApplication.h"
#include "ModelLoader.h"
#include "Material.h"
#include "DirectLight.h"
#include "Vector3.h"

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
	loader.Load3dsFile("loader.3ds", m_model);
	loader.Load3dsFile("assets/car2/asterion.3ds", m_car1);
	loader.Load3dsFile("assets/house1.3ds", m_house);
	loader.Load3dsFile("assets/arbor.3ds", m_arbor);
	loader.Load3dsFile("assets/tree.3ds", m_tree);
	loader.Load3dsFile("assets/tree1.3ds", m_tree1);
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

void CMyApplication::OnMotion(int x, int y)
{
	if (m_rotationController.LeftButtonIsPressed())
	{
		m_rotationController.OnMotion(x, y);
		PostRedisplay();
	}
}

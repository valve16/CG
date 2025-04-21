#pragma once
#include "glapplication.h"
#include "Buffer.h"
#include "RotationController.h"
#include "Model.h"
#include "ModelRenderer.h"

struct ModelInstance {
	CModel* model;
	CVector3f position;
	CVector3f rotation;
	GLfloat scale;
};


class CMyApplication : public CGLApplication
{
public:
	CMyApplication(const char * title, int width, int height);
	~CMyApplication(void);
protected:
	virtual void OnInit();
	virtual void OnDisplay();
	virtual void OnReshape(int width, int height);
	virtual void OnMotion(int x, int y);
	virtual void OnMouse(int button, int state, int x, int y);
private:
	// Угол обзора по вертикали
	static const double FIELD_OF_VIEW;

	CRotationController m_rotationController;
	CModel m_model, m_tree1, m_car1, m_house, m_arbor, m_tree, m_fence, m_trash;
	CModelRenderer m_renderer;
	std::vector<ModelInstance> m_sceneModels;
};

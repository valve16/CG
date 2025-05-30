#pragma once

#include "common_inc.h"

/*
Вспомогательный класс для управления вращением объектов при помощи мыши
*/
class CRotationController
{
public:
	CRotationController(int windowWidth, int windowHeight);

	// Возвращает состояние левой кнопки мыши
	bool LeftButtonIsPressed() const;
	// Данный метод нужно вызывать при изменении размеров окна
	void ResizeWindow(int windowWidth, int windowHeight);
	// Данный метод нужно вызывать при нажатии/отпускании кнопки мыши
	void OnMouse(int button, int state, int x, int y);
	// Данный метод нужно вызывать при перемещении мыши
	void OnMotion(int x, int y);

private:
	static void NormalizeModelViewMatrix(void);
	static void RotateCamera(GLfloat rotateX, GLfloat rotateY);
	bool m_leftButtonPressed = false;
	int m_mouseX = 0;
	int m_mouseY = 0;
	int m_windowWidth = 0;
	int m_windowHeight = 0;
};

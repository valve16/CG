#include "StdAfx.h"
#include "MainView.h"

BOOL CMainView::PreTranslateMessage(MSG* pMsg) 
{
    return FALSE; 
}
void CMainView::SetModel(std::shared_ptr<EngineModel> model) 
{ 
    m_model = model; 
}

void CMainView::DrawScene() 
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_model) {
        // Получаем текущее время в миллисекундах
        DWORD currentTime = GetTickCount();

        // Если это первый кадр, инициализируем m_lastTime
        if (m_lastTime == 0) {
            m_lastTime = currentTime;
        }

        // Вычисляем реальное время между кадрами (в секундах)
        float deltaTime = (currentTime - m_lastTime) / 1000.0f;
        m_lastTime = currentTime;

        // Обновляем модель с реальным deltaTime
        m_model->Update(deltaTime);
        m_model->Draw(); // Вызов отрисовки всего двигателя
    }

    RedrawWindow(); // Постоянное обновление для анимации
}

void CMainView::OnSize(UINT uMsg, CSize /*size*/)
{
    &uMsg;
    CRect rc;
    GetClientRect(rc);
    int width = rc.Width();
    int height = rc.Height();

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

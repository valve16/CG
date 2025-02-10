#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <math.h>

const TCHAR CLASS_NAME[] = L"MainWndClass";
const TCHAR WINDOW_TITLE[] = L"My first window";

DWORD g_lastTick;
UINT_PTR g_timerId = 0;


const int GRAVITY = 13;  
const int SPEED = 50; 

double t1 = 2.0; 
double t2 = 1.0; 
double t3 = 0.0; 

enum
{
	ANIMATION_TIMER_ID = 1
};



LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int MainLoop();
bool RegisterWndClass(HINSTANCE hInstance);
HWND CreateMainWindow(HINSTANCE hInstance);

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE /*hPrevInstance*/,
	LPSTR /*lpCmdLine*/,
	int nCmdShow)
{
	// Регистрируем класс главного окна
	if (!RegisterWndClass(hInstance))
	{
		return 1;
	}

	// Создаем главное окно приложения
	HWND hMainWindow = CreateMainWindow(hInstance);
	if (hMainWindow == NULL)
	{
		return 1;
	}

	// Показываем главное окно приложения
	ShowWindow(hMainWindow, nCmdShow);
	UpdateWindow(hMainWindow);

	// Запускаем цикл выборки сообщений, пока не получим
	// сигнал о завершении приложения
	return MainLoop();
}

HWND CreateMainWindow(HINSTANCE hInstance)
{
	HWND hMainWindow = CreateWindowEx(
		0, // DWORD dwExStyle;
		CLASS_NAME,
		WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		nullptr,
		NULL,
		hInstance,
		NULL);

	return hMainWindow;
}

int MainLoop()
{
	MSG msg;
	BOOL res;
	while ((res = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (res == -1)
		{
			// произошла ошибка - нужно обработать ее и, вероятно,
			// завершить работу приложения
			break;
		}
		else
		{
			// Если это сообщение о нажатии виртуальной клавиши,
			// то добавляем в очередь сообщений сообщения, несущие информацию о
			// коде вводимого пользователем символа
			TranslateMessage(&msg);
			// передаем сообщение в соответствующую оконную процедуру
			DispatchMessage(&msg);
		}
	}

	// сюда мы попадем только в том случае извлечения сообщения WM_QUIT
	// msg.wParam содержит код возврата, помещенный при помощи функции PostQuitMessage()
	return msg.wParam;
}

void OnDestroy(HWND hWnd)
{
	KillTimer(hWnd, ANIMATION_TIMER_ID);
	PostQuitMessage(0);
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC dc = BeginPaint(hwnd, &ps);

	// Создаем кисть
	LOGBRUSH brushBlueInfo;
	brushBlueInfo.lbStyle = BS_SOLID;
	brushBlueInfo.lbColor = RGB(0, 255, 255); 
	brushBlueInfo.lbHatch = 0;
	HBRUSH blueBrush = CreateBrushIndirect(&brushBlueInfo);


	// Создаем кисть
	LOGBRUSH brushGreenInfo;
	brushGreenInfo.lbStyle = BS_SOLID;
	brushGreenInfo.lbColor = RGB(0, 130, 22);
	brushGreenInfo.lbHatch = 0;
	HBRUSH greenBrush = CreateBrushIndirect(&brushGreenInfo);


	// Создаем кисть
	LOGBRUSH brushRedInfo;
	brushRedInfo.lbStyle = BS_SOLID;
	brushRedInfo.lbColor = RGB(130, 0, 0);
	brushRedInfo.lbHatch = 0;
	HBRUSH redBrush = CreateBrushIndirect(&brushRedInfo);

	// Выбираем кисть в контексте устройства, запоминая старую кисть
	HBRUSH oldBrush = SelectBrush(dc, blueBrush);

	HPEN pen = CreatePen(PS_NULL, 0, 0);
	HPEN oldPen = SelectPen(dc, pen);

	int offsetG = SPEED * t1 - 0.5 * GRAVITY * t1 * t1;
	int offsetO = SPEED * t2 - 0.5 * GRAVITY * t2 * t2;
	int offsetI = SPEED * t3 - 0.5 * GRAVITY * t3 * t3;

	// Г
	POINT pointsG[] = {
		{100, 100 - offsetG},
		{175, 100 - offsetG},
		{175, 120 - offsetG},
		{120, 120 - offsetG},
		{120, 200 - offsetG},
		{100, 200 - offsetG}
	};
	Polygon(dc, pointsG, 6);
	DeleteBrush(blueBrush);

	// O
	SelectBrush(dc, greenBrush);
	Rectangle(dc, 200, 100 - offsetO, 280, 200 - offsetO);
	HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	SelectBrush(dc, whiteBrush);
	Rectangle(dc, 220, 120 - offsetO, 260, 180 - offsetO);
	DeleteBrush(whiteBrush);

	// И
	SelectBrush(dc, redBrush);
	Rectangle(dc, 300, 100 - offsetI, 320, 200 - offsetI);
	Rectangle(dc, 360, 100 - offsetI, 380, 200 - offsetI);
	// Рисуем наклонный прямоугольник (диагональная линия)
	// Для этого используем многоугольник (Polygon)
	POINT points[] = {
		{318, 198 - offsetI},
		{318, 175 - offsetI},
		{360, 100 - offsetI},
		{360, 125 - offsetI}
	};
	Polygon(dc, points, 4);
	DeleteBrush(greenBrush);

	// выбираем ранее сохраненные объекты GDI в контексте устройства
	// при этом pen и brush автоматически становятся в нем не выбраны
	SelectBrush(dc, oldBrush);
	SelectPen(dc, oldPen);

	// объекты GDI можно удалять если они не выбраны ни в одном из контекстов
	DeletePen(pen);
	EndPaint(hwnd, &ps);
}

void Animate(HWND hwnd)
{
	// Определяем промежуток времени (в миллисекундах)
	DWORD currentTick = GetTickCount();
	int delta = currentTick - g_lastTick;
	g_lastTick = currentTick;

	// Разница по времени в секундах
	double deltaSeconds = delta * 0.001;

	t1 += deltaSeconds;
	t2 += deltaSeconds;
	t3 += deltaSeconds;

	// сбрасываем время Ut - 0.5gt^2
	if (SPEED * t1 - 0.5 * GRAVITY * t1 * t1 < 0) t1 = 0.0;
	if (SPEED * t2 - 0.5 * GRAVITY * t2 * t2 < 0) t2 = 0.0;
	if (SPEED * t3 - 0.5 * GRAVITY * t3 * t3 < 0) t3 = 0.0;

	// Перерисовываем окно
	InvalidateRect(hwnd, NULL, TRUE);
	UpdateWindow(hwnd);
}

void OnTimer(HWND hwnd, UINT id)
{
	switch (id)
	{
	case ANIMATION_TIMER_ID:
		Animate(hwnd);
		break;
	}
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT /*lpCreateStruct*/)
{
	// запоминаем текущее значение счетчика миллисекунд
	g_lastTick = GetTickCount();

	g_timerId = SetTimer(hwnd, ANIMATION_TIMER_ID, 20, NULL);

	return (g_timerId != 0);
}

LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (uMsg)
	{
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_TIMER, OnTimer);
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// Обработчик сообщений для окна "О программе".
bool RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASSEX wndClass = {
		sizeof(wndClass), //UINT cbSize;
		CS_HREDRAW | CS_VREDRAW, //UINT style;
		&WndProc, //WNDPROC lpfnWndProc;
		0, //int cbClsExtra;
		0, //int cbWndExtra;
		hInstance, //HINSTANCE hInstance;
		NULL, //HICON hIcon;
		LoadCursor(NULL, IDC_ARROW), //HCURSOR hCursor;
		reinterpret_cast<HBRUSH>(COLOR_WINDOW), //HBRUSH hbrBackground;
		NULL, //LPCTSTR lpszMenuName;
		CLASS_NAME, //LPCTSTR lpszClassName;
		NULL, //HICON hIconSm;
	};

	return RegisterClassEx(&wndClass) != FALSE;
}
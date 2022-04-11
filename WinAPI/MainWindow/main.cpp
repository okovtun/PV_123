#define _CRT_SECURE_NO_WARNINGS
#include<winapifamily.h>
#include<Windows.h>
#include<stdio.h>
#include"resource.h"

#define IDC_MY_STATIC	104

CONST CHAR g_szClassName[] = "My Window Class";
//g  - global
//sz - string zero

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wc;	//wc - Window Class
	ZeroMemory(&wc, sizeof(WNDCLASSEX));	//Зануляем экземпляр 'wc'
	//Инициализируем поля структуры 'wc':
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.lpfnWndProc = WndProc;	//Задаем процедуру окна для данного класса.
	wc.style = 0;	//Стиль окна, определяет его дополнительные свойства.
					//Набор возможных стилей зависит от класса окна
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));	//Иконка, отображаемая в панели задач
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));	//Иконка, отображаемая в строке заголовка (IconSmall)
	//wc.hIcon = (HICON)LoadImage(hInstance, "umbrella.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wc.hIconSm = (HICON)LoadImage(hInstance, "sun.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hInstance = hInstance;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Class registration failed", "Error", MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Сохздание окна:
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_start_x = screen_width / 8;
	int window_start_y = screen_height / 8;
	int window_width = screen_width - screen_width / 4;
	int window_height = screen_height - screen_height / 4;
	HWND hwnd = CreateWindowEx
	(
		NULL,	//Ex-style
		g_szClassName,	//имя класса окна
		"Main Window",	//Заголовок окна
		WS_OVERLAPPEDWINDOW,	//Стиль окна. У главного окна приложения стиль всегда WS_OVERLAPPEDWINDOW
		window_start_x, window_start_y,	//Положение окна на экране
		window_width, window_height,	//Размер окна
		NULL,	//Родительское окно. NULL - отсутсвует
		NULL,	//ID меню окна, если окно главное, или ID ресурса, если окно дочернее. NULL - меню отсутствует.
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", "Info", MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);	//Задаем режим отображения
	UpdateWindow(hwnd);	//Прорисовка окна

	//3) Запуск цикла сообщений:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)	//GetMessage() берет сообщение из очереди сообщений текущего потока
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);	//Отправляет сообщение в процедуру окна
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		//Здесь создаются элементы окна (Кнопки, Меню, значки, и т.д.)
		//Это аналог сообщения WM_INITDIALOG в диалоговом окне
		//Это сообщение отрабатывает один раз - при создании окна.
		CreateWindowEx
		(
			NULL,
			"Static",
			"Это мой статический текст, в котором будет отображаться размер окна и его положение на экране",
			WS_CHILDWINDOW| WS_VISIBLE,
			10, 10,
			1500, 150,
			hwnd,
			(HMENU)IDC_MY_STATIC,
			GetModuleHandle(NULL),
			NULL
		);
		break;
	case WM_MOVE:
	case WM_SIZE:
	{
		CONST INT SIZE = 256;
		CHAR buffer[SIZE] = {};
		RECT rect;	//объявляем прямоугольник
		GetWindowRect(hwnd, &rect);
		int window_width = rect.right - rect.left;
		int window_height = rect.bottom - rect.top;
		sprintf(buffer, "Size: %dx%d, Position: %dx%d", window_width, window_height, rect.left, rect.top);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)buffer);

		HWND hStatic = GetDlgItem(hwnd, IDC_MY_STATIC);
		SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)buffer);
	}
	break;
	case WM_COMMAND:break;
	case WM_CLOSE:
		//Посылает сообщение DestroyWindow своему окну
		if (MessageBox(hwnd, "Вы действительно хотите закрыть окно?", "Шо, внатуре?", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//Посылает сообщение о прекращении работы.
		break;
	default:return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}
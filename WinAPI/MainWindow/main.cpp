#include<Windows.h>

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
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));	//Иконка, отображаемая в панели задач
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));	//Иконка, отображаемая в строке заголовка (IconSmall)
	wc.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_ARROW));
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
	HWND hwnd = CreateWindowEx
	(
		NULL,	//Ex-style
		g_szClassName,	//имя класса окна
		"Main Window",	//Заголовок окна
		WS_OVERLAPPEDWINDOW,	//Стиль окна. У главного окна приложения стиль всегда WS_OVERLAPPEDWINDOW
		CW_USEDEFAULT, CW_USEDEFAULT,	//Положение окна на экране
		CW_USEDEFAULT, CW_USEDEFAULT,	//Размер окна
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
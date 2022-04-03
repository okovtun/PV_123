#include<Windows.h>
#include"resource.h"

CHAR sz_login_invitation[] = "Введеите логин";
CHAR sz_password_invitation[] = "Введеите пароль";

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMgs, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	/*MessageBox(NULL, "HelloWorld", "Info", MB_YESNOCANCEL | MB_ICONERROR | MB_HELP
		| MB_DEFBUTTON4 | MB_SYSTEMMODAL
		//| MB_RTLREADING
		|MB_SETFOREGROUND);*/
		//https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-messagebox

	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc, 0);

	return 0;
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
		SendMessage(GetDlgItem(hwnd, IDC_EDIT_PASSWORD), WM_SETTEXT, 0, (LPARAM)sz_password_invitation);
	}
	break;
	case WM_COMMAND:
	{
		CONST INT SIZE = 256;
		CHAR sz_buffer[SIZE]{};
		HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);	//Получаем ID окна текстового поля по имени ресурса
		HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
		switch (LOWORD(wParam))
		{
		case IDC_EDIT_LOGIN:
		{
			//При выполнении различных действий над каким-либо элементов интерфейса (окном),
			//этот элемент интерфейса (окно) получает уведомления. Уведосления, это самые обычные сообщения.
			//Например, когда мы становимся в текстовое поле, то это текстовое поле получает уведомление EN_SETFOCUS,
			//когда мы "уходим" из текстового поля, то оно получает уведомление EN_KILLFOCUS.
			//EN - Edit Notification
			//Фокус - это часть окна, которая принимает команды с клавиатуры.
			/*CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE]{};*/
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			switch (HIWORD(wParam))
			{
			case EN_SETFOCUS:
				if (strcmp(sz_buffer, sz_login_invitation) == 0)
					SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)""); 
				break;
			case EN_KILLFOCUS:
				if (strlen(sz_buffer) == 0)
					SendMessage(hLogin, WM_SETTEXT, 0, (LPARAM)sz_login_invitation);
				break;
			}
			/*for (int i = 0; i < strlen(sz_buffer); i++)
				sz_buffer[i] += 32;
			int n = strlen(sz_buffer);
			for (int i = 0; i < n; i++)
				sz_buffer[i] += 32;*/

		}
		break;
		case IDC_BUTTON_COPY:
		{
			//CONST INT SIZE = 256;	//Размер буфера
			//CHAR sz_buffer[SIZE] = {};
			HWND hLogin = GetDlgItem(hwnd, IDC_EDIT_LOGIN);	//Получаем ID окна текстового поля по имени ресурса
			SendMessage(hLogin, WM_GETTEXT, SIZE, (LPARAM)sz_buffer);//Копируем текст из текстового поля Password в sz_buffer
			HWND hPassword = GetDlgItem(hwnd, IDC_EDIT_PASSWORD);
			SendMessage(hPassword, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDC_BUTTON_SET_TITLE:
		{
			//CONST INT SIZE = 256;
			//CHAR sz_buffer[SIZE] = {};
			SendMessage(GetDlgItem(hwnd, IDC_EDIT_LOGIN), WM_GETTEXT, SIZE, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			//SendMessage(FindWindow(NULL, "WinAPI - Microsoft Visual Studio"), WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		case IDOK:MessageBox(NULL, "Была нажата кнопка OK", "Info", MB_OK | MB_ICONWARNING); break;
		case IDCANCEL: EndDialog(hwnd, 0); break;
		}
	}
	break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
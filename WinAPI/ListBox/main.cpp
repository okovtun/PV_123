//ListBox
#define _CRT_SECURE_NO_WARNINGS	//для sprintf()
#include<Windows.h>
#include<cstdio>	//для sprintf()
#include"resource.h"

CONST CHAR* string[] =
{
	//Вот эти строки мы добавим в ListBox:
	"Первая строка",
	"Вторая строка",
	"Третья строка",
	"This", "is", "my", "first", "List", "Box"
};

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//type name(parameters);
//type calling_convention name(parameters);
//type - тип возвращаемого значение: bool, char, int......
//calling_convention - конвенция вызовов (соглашение о вызове функции):
//__syscall
//__stdcall	 - WinAPI
//__fastcall - x64
//__cdecl	 - C/C++
//Конвенция вызовов определяет порядок вызова функции:
//	- кто очищает стек, вызывающая функция (caller) или вызываемая функция (callee)
//	- как читается список передаваемых параметров - слева направо, или справа налево,
//	  или же параметры передаются через регистры (__fastcall)
//https://docs.microsoft.com/en-us/cpp/cpp/argument-passing-and-naming-conventions?view=msvc-170
//https://docs.microsoft.com/en-us/cpp/cpp/cdecl?view=msvc-170
//https://docs.microsoft.com/ru-ru/cpp/cpp/cdecl?view=msvc-170
//http://cplusplus.com/reference/cstdarg/

//-----------------------------------------------------------------------------------------------

//HINSTANCE hInstance - экземпляр исполняемого файла (*.exe). Это загруженный в память *.exe-файл нашей программы.
//HINSTANCE рPrevInst - предыдущий экзепляр *.exe-файла. Этот параметр использовался в Windows 98, и оставлен только для совместимости.
//LPSTR lpCmdLine - командная строка, с которой была запущена программа. 
//LPSTR: LP - LongPointer STR - String => LPSTR - LongPointer to String (Указатель на строку - char*)
//int cCmdShow - режим отображения окна: свернуто в окно, развернуто на весь экран, свернуто на панель задач....
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, (DLGPROC)DlgProc, 0);
	return 0;
}


//HWND (Handler to Window) - Handler to Window. ОБРАБОТЧИК ОКНА, дескриптор окна.
//HWND - это идентификатор окна, через который к нему можно обратиться.
//HWND - это как имя переменной, или функции.
//HWND - ЭТО ОКНО!
//UINT uMsg - Message (сообщение). UINT - unsigned int.
//wParam, lParam - это параметры сообщения, они зависят от того, какое именно uMsg мы посылаем окну
BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:	//Это сообщение отправляется в окно при его создании
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
		//GetDlgItem(hwnd, IDC_LIST1); возвращает HWND элемента окна по ID-ресурса нужного элемента
		for (int i = 0; i < sizeof(string) / sizeof(string[0]); i++)
		{
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)string[i]);
			//Сообщение LB_ADDSTRIG добавляет указанную строку в ListBox.
		}
	}
	break;
	case WM_COMMAND:	//Это сообщение обрабатывает нажатие на кнопки, и другие элементы интерфейса окна
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR sz_buffer[SIZE] = {};	//в эту строку мы скопируем выделенную строку ListBox.
			CHAR sz_message[SIZE] = {};	//этy строку мы будем отображать в MessageBox.

			HWND hListBox = GetDlgItem(hwnd, IDC_LIST1);
			int index = SendMessage(hListBox, LB_GETCURSEL, 0, 0);	//Получаем числовой индекс выделенного элемента ListBox
			SendMessage(hListBox, LB_GETTEXT, index, (LPARAM)sz_buffer);
			sprintf(sz_message, "Вы выбрали элемен № %d со значением \"%s\".", index, sz_buffer);
			//Функция sprintf() выполняет форматирование строк
			//sz_message - это буфер, в который сохраниться отформатированная строка
			//"Вы выбрали... - это шаблон строки, т.е. то, как она должна выглядеть
			//%d - вставить в шаблонную строку десятичное целое число (decimal)
			//%s - вставить в шаблонную строку подстроку.
			//Все вставляемые значения перечислены далее в передаваемых параметрах: index, sz_buffer....
			//Количество параметров функции sprintf() неограничено.
			//Функция sprintf() позволяет вставлять в строку какие угодно значения.
			MessageBox(hwnd, sz_message, "Info", MB_OK | MB_ICONINFORMATION | MB_HELP);
			//
		}
			break;
		case IDCANCEL:EndDialog(hwnd, 0); break;
		}
		break;
	case WM_CLOSE: EndDialog(hwnd, 0);
	}
	return FALSE;
}
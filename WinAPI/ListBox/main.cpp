//ListBox
#include<Windows.h>
#include"resource.h"

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
	//HWND - Handler to Window. ОБРАБОТЧИК ОКНА, дескриптор окна.
	//HWND - это идентификатор окна, через который к нему можно обратиться.
	//HWND - это как имя переменной, или функции.
	return 0;
}
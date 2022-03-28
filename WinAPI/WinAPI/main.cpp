#include<Windows.h>
#include"resource.h"

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
	case WM_INITDIALOG:break;
	case WM_COMMAND:break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}
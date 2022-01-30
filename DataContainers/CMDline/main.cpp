#include<iostream>
using namespace std;

int main(int argc, char* argv[])
{
	//int argc (arguments count)	- количество принятых аргументов командной строки
	//char* argv[] (argument values)- массив строк, который содержит значения аргументов
	//Нулевой элемент массива argv[] это всегда полное имя исполняемого файла программы 
	//(включая путь к исполняемому файлу).
	setlocale(LC_ALL, "");

	/*if (argc > 5)
	{
		cerr << "Неправильный синтаксис команды" << endl;
		return 1;
	}*/
	
	for (int i = 0; i < argc; i++)
	{
		cout << "argv[" << i << "]\t" << argv[i] << endl;
	}


	return 0;
}
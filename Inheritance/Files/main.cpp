#include<iostream>
#include<fstream>	//File stream
using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define WRITE_TO_FILE
#define READ_FROM_FILE

void main()
{
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	cout << "Hello World" << endl;

	ofstream fout("file.txt", ios::app);
	//app - append (добавить, дописать)
	fout << "Hello World" << endl;
	fout << "Винни Пух" << endl;
	fout.close();

	system("notepad file.txt");
#endif // WRITE_TO_FILE

#ifdef READ_FROM_FILE
	const int SIZE = 10240;
	char buffer[SIZE]{};

	ifstream fin;	//Создаем поток
	fin.open("file.txt");

	if (fin.is_open())
	{
		//Читаем файл
		while (!fin.eof())//ПОКА НЕ конец файла (end of file)
		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
	}
	else
	{
		cerr << "Error: file not found" << endl;
	}

	fin.close();
#endif // READ_FROM_FILE

}
#include<iostream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	//cout << 1 / 0 << endl;
	int a, b;
	cout << "������� ������� � ��������: ";
	cin >> a >> b;
	try
	{
		cout << a / b << endl;
	}
	catch (...)
	{
		std::cerr << "Something happened" << endl;
	}
}
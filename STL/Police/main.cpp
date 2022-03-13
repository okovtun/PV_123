#include<iostream>
#include<string>
#include<map>
#include<list>
#include<Windows.h>

#include"Crime.h"

using std::cin;
using std::cout;
using std::endl;

void print(const std::map<std::string, std::list<Crime>>& base);

void main()
{
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::map<std::string, std::list<Crime>> base =
	{
		{"a777km", {Crime(1, "улица Ленина"), Crime(2, "ул. Фрунзе")}},
		{"a557ab", {Crime(5, "ул. Космонавтов")}},
		{"a001a", {Crime(4, "перекресток Ленина и Октябрьской"), Crime(3, "ул. Октябрьская")}}
	};
	print(base);

	std::string licence_plate;
	int id;
	std::string place;
	cout << "Введите номер автомобиля: "; cin >> licence_plate;
	cout << "Введите правонарушение (номер статьи): "; cin >> id;
	cout << "Введите место проишествия: "; 
	cin.clear();
	cin.ignore();
	std::getline(cin, place);
	//base[licence_plate].push_back(Crime(id, place));
	std::map<std::string, std::list<Crime>>::iterator it = base.find(licence_plate);
	if (it != base.end())
	{
		it->second.push_back(Crime(id, place));
	}
	else
	{
		base.insert(std::pair<std::string, std::list<Crime>>(licence_plate, { Crime(id, place) }));
	}
	print(base);
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		//cout << std::left;
		cout << it->first + ":\n";
		for (std::list<Crime>::const_iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << "\t" << *jt << ";\n";
		}
		cout << "\n-----------------------------------------------\n";
	}
}
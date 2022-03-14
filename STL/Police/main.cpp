#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<list>
#include<Windows.h>

#include"Crime.h"

using std::cin;
using std::cout;
using std::endl;

void add(std::map<std::string, std::list<Crime>>& base);
void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
void load(std::map<std::string, std::list<Crime>>& base, const std::string& filename);

void main()
{
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::map<std::string, std::list<Crime>> base/* =
	{
		{"a777km", {Crime(1, "улица Ленина"), Crime(2, "ул. Фрунзе")}},
		{"a557ab", {Crime(5, "ул. Космонавтов")}},
		{"a001a", {Crime(4, "перекресток Ленина и Октябрьской"), Crime(3, "ул. Октябрьская")}}
	}*/;
	load(base, "base.txt");
	print(base);
	//save(base, "base.txt");
	//add(base);
	//print(base);
}

void add(std::map<std::string, std::list<Crime>>& base)
{
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
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::pair<std::string, std::list<Crime>> i : base)
	{
		fout << i.first << ":\t";
		for (Crime j : i.second)
		{
			fout << j << ", ";
		}
		fout.seekp(-2, std::ios::cur);	//сдвигаем курсор на 2 позиции влево
		fout << ";\n";
	}
	fout.close();
	std::string command = std::string("start notepad ") + filename;
	system(command.c_str());
	//c_str() возвращает C-string (NULL Terminated Line)
}
void load(std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string licence_plate;
			int id;
			std::string place;
			std::string crimes;
			std::getline(fin, licence_plate, ':');
			std::getline(fin, crimes);
			if (crimes.empty())continue;
			if (crimes.find(',') != std::string::npos)
			{
				for (int start = 0, end = crimes.find(','); end != std::string::npos; start = end)
				{
					end = crimes.find(',', start + 1);
					place = crimes.substr(start + 1, end);//TODO: проверить с большим количеством нарушений
					//https://www.cplusplus.com/reference/string/string/substr/
					place.erase(0, place.find_first_not_of(' '));
					id = std::stoi(place.substr(0, place.find_first_of(' ')));
					place.erase(0, place.find_first_of(' ') + 1);
					base[licence_plate].push_back(Crime(id, place));
				}
			}
			else
			{
				id = std::stoi(crimes.substr(0, crimes.find_first_of(' ')));
				crimes.erase(0, crimes.find_first_of(' '));
				base[licence_plate].push_back(Crime(id, crimes));
			}
		}
		fin.close();
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
}
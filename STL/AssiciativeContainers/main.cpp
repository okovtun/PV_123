//AssociativeContainers
#include<iostream>
#include<string>
#include<list>
#include<set>
#include<map>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//#define STL_SET
//#define STL_MAP

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_SET
	//set - уникальное дерево
	//multiset - неуникальное дерево
	std::set<int> myset = { 50, 25, 75, 16, 32, 64, 80, 5, 50, 7,7,7 };
	/*for (int i = 0; i < myset.size(); i++)
	{
		cout << myset[i] << tab;
	}
	cout << endl;*/
	for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	int value;
	cout << "Введите добавляемое значение: "; cin >> value;
	myset.insert(value);
	for (int i : myset)cout << i << tab; cout << endl;
	cout << "Введите удаляемое значение: "; cin >> value;
	myset.erase(value);
	for (int i : myset)cout << i << tab; cout << endl;
	for (std::set<int>::iterator it = myset.lower_bound(25); it != myset.upper_bound(75); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (std::set<int>::iterator it = myset.find(25); it != myset.find(75); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

#endif // STL_SET

#ifdef STL_MAP
	//map - это контейнер, который зранит значения в виде бинарного дерева поиска.
	//каждым элементом map является пара которая хранит 
	//ключ и значение
	// key	 value
	std::map<int, std::string> week
	{
		std::pair<int, std::string>(0, "Sunday"),
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(4, "Thursday"),
		{5, "Friday"},
		{6, "Saturday"},
		std::pair<int, std::string>(0, "Воскресенье"),
		std::pair<int, std::string>(1, "Sunday"),
	};
	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}
#endif

	std::map<std::string, std::list<std::string>> dictionary
	{
		std::pair<std::string, std::list<std::string>>
		("splice", {"сваривание", "сращивание", "свадьба"}),
		{"reconnaissance", {"разведка", "зондирование"}},
		{"space", {"космос", "пространство", "пробел"}},
		{"pencil", {"карандаш"}},
		{"desk", {"работчий стол", "доска"}},
		{"prohibit", {"запрещать"} },
		{"appreciate", {"быть признательным", "ценить", "быть благодарным"}}
	};

	for (std::map<std::string, std::list<std::string>>::iterator it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		cout.width(20);
		cout << std::left;
		cout << it->first + ":";	//выводим ключ
		//поскольку значение является списком, перебираем этот список, и выводим каждое его значение на экран:
		for (std::list<std::string>::iterator jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << *jt << ", ";
		}
		cout << endl;
	}
	cout << "\n-------------------------------------------\n";
	/*
		for(type i : container)
		{
			cout << i << tab;
		}
		for(int i : arr)
		{
			cout << i << tab;
		}
	*/
	for (std::pair<std::string, std::list<std::string>> i : dictionary)
	{
		cout.width(20);
		cout << std::left;
		cout << i.first + ":";
		for (std::string j : i.second)cout << j << ", ";
		cout << "\b\b;\n";
		//cout << endl;
	}
}
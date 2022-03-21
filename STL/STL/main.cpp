//STL - Standard Template Library
#include<iostream>
#include<array>
#include<vector>
#include<deque>
#include<list>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------\n"

//#define STL_ARRAY
//#define STL_VECTOR
//#define STL_DEQUE

void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_ARRAY
	//array - это контейнер, который хранит данные в виде статического массива.
	std::array<int, 5> arr = { 3,5,8,13,21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	std::array<int, 5>* p_arr = new std::array<int, 5>{3, 5, 8, 13, 21};
	for (int i = 0; i < p_arr->size(); i++)
	{
		cout << p_arr->operator[](i) << tab;
	}
	cout << endl;
#endif //STL_ARRAY

#ifdef STL_VECTOR
	//vector - это контейнер, который хранит данные в виде динамического массива.
	std::vector<int> vec = { 0,1,1,2,3,5,8,13,21,34 };
	try
	{
		for (int i = 0; i < vec.size() * 2; i++)
		{
			cout << vec.at(i) << tab;
			//cout << vec[i] << tab;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	cout << endl;
	cout << "Size:    " << vec.size() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << delimiter << endl;
	vec.push_back(55);
	vec.pop_back();
	vec.pop_back();
	vec.pop_back();
	cout << "Size:    " << vec.size() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << delimiter << endl;

	//vec.shrink_to_fit();
	//vec.reserve(10);
	vec.resize(5);

	cout << "Size:    " << vec.size() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << delimiter << endl;

	try
	{
		//throw "My exaption";
		//throw 4;
		for (int i = 0; i < vec.capacity(); i++)
		{
			//cout << vec[i] << tab;
			cout << vec.at(i) << tab;
		}
		cout << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	catch (const char* e)
	{
		std::cerr << e << endl;
	}
	catch (int e)
	{
		std::cerr << "Error# " << e << endl;
	}
	catch (...)
	{
		//EHa
		std::cerr << "Something happened" << endl;
	}
	cout << "Нулевой элемент вектора: " << vec.front() << endl;
	cout << "Последний элемент вектора: " << vec.back() << endl;
	int* p_arr = vec.data();

	vec.assign({ 1, 2, 4, 8, 16, 32, 64 });
	for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (std::vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); rit++)
	{
		cout << *rit << tab;
	}
	cout << endl;
	cout << "Size:    " << vec.size() << endl;
	cout << "MaxSize: " << vec.max_size() << endl;
	cout << "Capacity:" << vec.capacity() << endl;
	cout << delimiter << endl;

	int index;
	int value;
	int count;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	cout << "Сколько раз добавить значение: "; cin >> count;
	vec.insert(vec.begin() + index, count, value);
	for (int i : vec)cout << i << tab; cout << endl;

	vec.insert(vec.begin() + index, { 3,5,8,13,21 });
	for (int i : vec)cout << i << tab; cout << endl;

#endif // STL_VECTOR

#ifdef STL_DEQUE
	//deque (double ended queue - двунаправленная очередь) это контейнер, 
	//который хранит данный в виде списка динамических массивов.
	std::vector<int> vec;
	std::deque<int> deque = { 3,5,8,13,21 };
	vec.push_back(1);
	deque.push_back(34);
	deque.push_back(55);
	deque.push_back(89);
	for (int i = 0; i < deque.size(); i++)
	{
		cout << deque[i] << tab;
	}
	cout << endl;
	deque.push_front(2);
	deque.push_front(1);
	deque.push_front(1);
	deque.push_front(0);
	for (int i : deque)cout << i << tab; cout << endl;
#endif

	std::list<int> list = { 3,5,8,13,21 };
	for (int i = 0; i < list.size(); i++)
	{
		cout << list[i] << "\t";
	}
	cout << endl;
}
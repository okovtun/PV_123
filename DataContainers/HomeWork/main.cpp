#include <iostream>
#include <Windows.h>
#include <string>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define tab "\t"

using namespace std;
using std::cin;
using std::cout;
using std::endl;

template<typename T> class Iterator;
template<typename T> class ForwardList;
template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
template<typename T>
std::ostream& operator<<(std::ostream& os, ForwardList<T>& fl);

//#define OLD_PRINT
template<typename T>
class Element
{
	T Data;
	Element<T>* pNext;
	static int count;
public:
	T get_Data()const
	{
		return Data;
	}

	Element<T>* get_pNext()const
	{
		return pNext;
	}

	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
#ifdef DEBUG
		cout << "EConstructor : " << this << endl;
#endif // DEBUG

		count++;
	}
	~Element()
	{

#ifdef DEBUG
		cout << "EDestructor : " << this << endl;
#endif // DEBUG

		count--;

	}
	friend class ForwardList<T>;// дружественный класс
	friend class Iterator<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};
template<typename T>
int Element<T>::count = 0;

template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor" << this << endl;
#endif // DEBUG

	}
	/*Iterator(const Element<T>* Temp) :Iterator(Temp)
	{

	}*/
	~Iterator()
	{
#ifdef DEBUG
		cout << "ItDestructor" << this << endl;
#endif // DEBUG

	}

	Iterator<T>& operator ++()//Prefix Increment ++a //for 
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator<T> operator ++(int)//Postfix Increment a++ //for 
	{
		Iterator<T> old = *this;// сохроняем старое значение итератора
		Temp = Temp->pNext;//изменяем итератор
		return old;//возвращаем старое значение 
	}


	bool operator ==(const Iterator<T>& other)const//for 
	{
		return this->Temp == other.Temp;
	}
	bool operator !=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	T& operator*()//for 
	{
		return Temp->Data;
	}
	const T& operator*()const//for 
	{
		return Temp->Data;
	}
	operator bool()const
	{
		return Temp;
	}
};


template<typename T>
class ForwardList //односвязный список
{
	Element<T>* Head;
	unsigned int size;//размер списка
public:
	//--------Geters---------

	unsigned int get_size()const
	{
		return size;
	}
	Element<T>* get_Head()const
	{
		return Head;
	}

	//----------Constructor----------
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor : " << this << endl;

	}
	ForwardList(unsigned int n) : ForwardList()
	{

		for (size_t i = 0; i < n; i++)
		{
			push_front(T());//значение по умолчанию
		}
		cout << "NConstructor : " << this << endl;

	}

	ForwardList(const ForwardList<T>& other) : ForwardList()
	{
		/*for (size_t i = 0; i < other.size; i++)
		{
			push_front(other[other.size-i-1]);
		}*/
		//for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		for (Iterator<T>* it = other.Head; it != nullptr; ++it)push_back(*it);
		cout << "CopyConstructor:\t\t" << this << endl;
	}
	ForwardList(ForwardList<T>&& other)noexcept
	{
		size = other.size;
		Head = other.Head;


		other.Head = nullptr;
		cout << "MoveConstructor" << this << endl;
	}
	ForwardList(const initializer_list<T>& il) : ForwardList()
	{
		//il.begin() - возвращает итератор на начало контейнера
		//il.end()  - возвращает итератор на конец контейнера
		cout << typeid(il.begin()).name() << endl;
		//const int* - константный указатель (НЕ изменяется адрес)
		//int const* - указатель на константу (НЕ изменяется значение по адресу)
		/*for (int const* it = il.begin(); it != il.end(); it++)
		{
			//it - iterator
			push_back(*it);
		}*/
		for (T const* it = il.end() - 1; it != il.begin() - 1; it--)
		{
			push_front(*it);
		}

	}

	~ForwardList()
	{
		while (Head)
		{
			pop_front();
		}
		cout << "LDestructor : " << this << endl;

	};

	//---------------Addingng elements-------------------
	void push_front(T Data)
	{
		/*Element<T>* New = new Element<T>(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		/*if (Head == nullptr)//проверяем является список пустым
			return push_front(Data);
		Element* New = new Element(Data);//создаем новый элемент
		Element* Temp = Head;//итератор
		while (Temp->pNext != nullptr)//доходим до конца списка
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;//присоеденяем новый элемент к последнему
		size++;*/
		if (Head == nullptr)
			return push_front(Data);
		Element<T>* Temp = Head;
		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element<T>(Data);
		size++;
	}

	//--------------Remaving elements--------------------
	void pop_front()
	{
		if (Head == nullptr)return;
		Element<T>* Erased = Head;//итератор
		Head = Erased->pNext;
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			++Temp;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int index, T Data)
	{
		/*if (index == 0|| Head == nullptr) return push_front(Data);
		if (index > size)return;
		Element* New = new Element(Data);
		Element* Temp = Head;
		for (size_t i = 0; i < index-1; i++)Temp = Temp->pNext;
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;*/

		if (index == 0 || Head == nullptr) return push_front(Data);
		if (index > size)return;
		Element<T>* Temp = Head;
		for (size_t i = 0; i < index - 1; i++)++Temp;
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}
	void erase(int index)
	{
		if (index == 0) return pop_front();
		if (index > size)return;
		Element<T>* Temp = Head;
		Element<T>* Ell;
		for (size_t i = 0; i < index - 1; i++)++Temp;
		Ell = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete	Ell;
		size--;
	}
	//----------Metods----------
	void print()const
	{
#ifdef OLD_PRINT
		Element* Temp = Head;//- итератор- это указатель при
		for (size_t i = 0; i < size; i++)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//переход на следующий элемент
		}
		cout << "Общее количество элементов списков : " << Head->count << endl;
		cout << "Количество элементов списка : " << size << endl;
#endif // OLD_PRINT
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Общее количество элементов списков : " << Head->count << endl;
		cout << "Количество элементов списка : " << size << endl;

	}
	void fl_rnd(int begin, int end)
	{
		for (size_t i = 0; i < size; i++)
		{
			(*this)[i] = rand() % (end - begin + 1) + begin;
		}
	}
	void reverse(ForwardList& other)
	{
		for (size_t i = 0; i < other.get_size(); i++)
		{
			push_front(other[i]);
		}
	}
	void reverse()
	{
		int data;
		for (size_t i = 0; i < size / 2; i++)
		{
			data = (*this)[i];
			(*this)[i] = (*this)[size - 1 - i];
			(*this)[size - 1 - i] = data;
		}
	}
	void unique(ForwardList& other)
	{
		bool flag;
		for (size_t i = 0; i < other.get_size(); i++)
		{
			flag = 0;
			for (size_t j = 0; j < other.get_size(); j++)
			{
				if (other[i] == other[j] && i != j)
				{
					flag = 1;
				}

			}
			if (flag == 0)push_front(other[i]);
		}
	}
	void unique()
	{
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				if ((*this)[i] == (*this)[j] && i != j)erase(j);
			}
		}
	}

	//----------Operators----------
	T& operator[](int n)
	{
		Element<T>* temp = Head;

		for (size_t i = 0; i < n; i++)++temp;
		return temp->Data;
	}
	const T& operator[](int n)const
	{
		Element<T>* temp = Head;

		for (size_t i = 0; i < n; i++)++temp;
		return temp->Data;
	}
	ForwardList<T>& operator = (ForwardList<T>& other)
	{
		if (this == &other)return *this;
		while (Head)
		{
			pop_front();
		}
		for (Iterator<T> it = other.Head; it; ++it)push_back(*it);

	}
	Iterator<T> begin()//for 
	{
		return this->Head;
	}
	Iterator<T> end()//for
	{
		return nullptr;
	}


};

//#define BASE CHECK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK_1
//#define COPY_CONSTRACTOR
//#define REVERSE
//#define UNIQUE
//#define HOME_WORK_2
//#define RANGE_BASE_FORARRAY
//#define ARRAY_FORWARDLIST

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

#ifdef BASE CHECK
	int n;
	cout << "Введите размер списка : "; cin >> n;
	ForwardList<T> list;
	for (size_t i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	cout << "------------------" << endl;
	list.push_back(111);
	list.print();
	cout << "------------------" << endl;
	list.pop_back();
	list.print();
	cout << "------------------" << endl;
	list.push_front(111);
	list.print();
	cout << "------------------" << endl;
	list.pop_front();
	list.print();
	cout << "------------------" << endl;
	list.insert(6, 111);
	list.print();
	cout << "------------------" << endl;
	list.erase(2);
	list.print();
	cout << "------------------" << endl;
#endif // BASE CHECK
	/*ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();
	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();*/

#ifdef DESTRUCTOR_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	//cout << "Список заполнен" << endl;
	list.print();
#endif // DESTRUCTOR_CHECK
#ifdef HOME_WORK_1
	int n;
	cout << "Введите размер списка - "; cin >> n;
	ForwardList list(n);
	for (size_t i = 0; i < n; i++)
	{
		list[i] = rand() % 100;
	}
	for (size_t i = 0; i < n; i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;

#endif // HOME_WORK_1
#ifdef COPY_CONSTRACTOR
	ForwardList list1(5);
	ForwardList list2(5);
	for (size_t i = 0; i < 5; i++)
	{
		list1[i] = rand() % 100;
	}
	for (size_t i = 0; i < 5; i++)
	{
		list2[i] = rand() % 100;
	}
	list1.print();
	cout << endl;
	list2.print();
	ForwardList list3 = list1 + list2;
	list3.print();
#endif // COPY_CONSTRACTOR
#ifdef REVERSE
	ForwardList list4(10);
	ForwardList list5(0);
	list4.fl_rnd(1, 10);
	list4.print();
	list5.reverse(list4);
	list5.print();
	list5.reverse();
	list5.print();
	list5.unique();
	list5.print();
#endif // REVERSE
#ifdef UNIQUE
	ForwardList<double> list6(10);
	ForwardList<double> list7(0);
	for (size_t i = 0; i < 10; i++)
	{
		list6[i] = rand() % 10;
	}
	list6.print();
	list7.unique(list6);
	list7.print();
#endif // UNIQUE
#ifdef HOME_WORK_2
	ForwardList<int> list7 = { 3,5,8,13,21 };
	list7.print();
	cout << endl;
	cout << list7;
	for (Iterator<int> it = list7.get_Head(); it != nullptr; it++)
	{
		cout << *it << tab;
	}
#endif // HOME_WORK_2
#ifdef RANGE_BASE_FORARRAY
	int arr[] = { 3,5,8,13,21 };
	/*for (size_t i = 0; i < sizeof(arr)/sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;*/
	for (int i : arr)//
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASE_FORARRAY
#ifdef ARRAY_FORWARDLIST
	ForwardList<int> list9 = { 3,5,8,13,21 };
	for (int i : list9)
	{
		cout << i << tab;
	}
	cout << endl;
#endif //  ARRAY_FORWARDLIST


	/*ForwardList<char>d_list = { 's','d','r'};
	d_list.print();
	cout << d_list;
	for (char i : d_list) cout << i << tab;
	cout << endl;
	ForwardList<char>d_list2= d_list;
	cout << d_list2;
	cout << "\n----------------------------------------------------\n";
	ForwardList<char>d_list3 = d_list+d_list2;
	cout << d_list3;
	cout << "\n----------------------------------------------------\n";
	ForwardList<string>s_list = { "Heloo","World" };
	cout << s_list;*/

	ForwardList<int> list1 = { 3,5,8,13,21 };
	list1.print();
	ForwardList<int> list2 = { 34,55,89 };
	ForwardList<int> list3 = list1;
	cout << list3 << endl;
	list3.print();

	return 0;
}

template<typename T>
ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	/*ForwardList<T> result(left.get_size() + right.get_size());
	for (size_t i = 0; i < left.get_size(); i++)
	{
		result[i] = left[i];
	}
	for (size_t i = 0; i < right.get_size(); i++)
	{
		result[left.get_size()+i] = right[i];
	}*/
	ForwardList<T> result = left;
	for (Element<T>* Temp = right.get_Head(); Temp != nullptr; Temp = Temp->get_pNext())result.push_back(Temp->get_Data());
	return result;
}
template<typename T>
std::ostream& operator <<(std::ostream& os, ForwardList<T>& fl)
{
	Element<T>* temp = fl.get_Head();

	while (temp)
	{
		os << temp->get_Data() << tab;
		temp = temp->get_pNext();
	}
	os << endl;

	os << "Количество элементов списка : " << fl.get_size() << endl;


	return os;
}
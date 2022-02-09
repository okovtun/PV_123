//TemplatedForwardList
#include<iostream>
#include<string>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

#define DEBUG

template<typename T>class ForwardList;
template<typename T>class Iterator;

template<typename T>
class Element
{
	T Data;	//Значение элемента
	Element<T>* pNext;//Адрес следующего элемента
	//Element* - указатель на элемент
	//Element<T>* - указатель на шаблонный элемент
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstrcutor:\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestrcutor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList<T>;
	friend class Iterator<T>;
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
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator<T>& operator++()	//Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator<T> operator++(int)//Postfix increment
	{
		Iterator old = *this;	//Сохраняем старое значение итератора
		Temp = Temp->pNext;		//Изменяем итератор
		return old;	//Возвращаем старое значение
	}

	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}

	const T& operator*()const
	{
		return Temp->Data;
	}
	T& operator*()
	{
		return Temp->Data;
	}

	operator bool()const
	{
		return Temp;
	}
};

template<typename T>
class ForwardList//Односвязный (однонаправленный) список
{
	Element<T>* Head;	//Голова списка - указывает на начальный элемент списка.
	unsigned int size;//Размер списка
public:
	Element<T>* getHead()const
	{
		return Head;
	}
	unsigned int get_size()const
	{
		return this->size;
	}
	Iterator<T> begin()
	{
		return Head;
	}
	Iterator<T> end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;//Если голова указывает на 0, то список пуст.
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(unsigned int size) :ForwardList()
	{
		//this->Head = nullptr;
		//this->size = 0;
		for (int i = 0; i < size; i++)
		{
			push_front(T());
			//T() - значение по умолчанию для шаблонного типа
		}
	}
	ForwardList(const initializer_list<T>& il) :ForwardList()
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
	ForwardList(const ForwardList<T>& other):ForwardList()
	{
		//for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		for (Iterator<T> it = other.Head; it != nullptr; ++it)push_back(*it);
		cout << "CopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//					Operators:
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();	//Очищаем этот список
		//Проходим по тому списку, и вставляем значения его элементов в этот список.
		for (Iterator<T> it = other.Head; it; ++it)push_back(*it);
		cout << "CopyAssignment:\t" << this << endl;
	}
	const T& operator[](int index)const
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	T& operator[](int index)
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}


	//					Addigng elements:
	void push_front(T Data)
	{
		//Element* New = new Element(Data);//Создаем новый элемент и помещаем в него значение Data
		//New->pNext = Head;	//Привязывем новый элемент к началу списка
		//Head = New;	//Переводим Голову на новый элемент

		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		//0) Проверяем, является ли список пустым:
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до конца списка:
		Element<T>* Temp = Head;
		while (Temp->pNext)//Пока, pNext текущего элемента НЕ ноль
			Temp = Temp->pNext;//переходим на следующий элемент
		//Теперь мы находимся в последнем элементе, т.е. Temp->pNext == nullptr
		//3) Присоединяем новый элемент к последнему:
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	void insert(int index, T Data)
	{
		if (index == 0 || Head == nullptr)return push_front(Data);
		if (index > size)return;
		//Element* New = new Element(Data);
		//1) Доходим до нужного элемента:
		Element<T>* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//3) Включаем новый элемент в список:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}

	//					Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		//1) Запоминаем адрес удавляемого элемента:
		Element<T>* Erased = Head;
		//2) Исключаем удаляемый элемент из списка:
		Head = Erased->pNext;
		//3) Удаляем элемен из памяти:
		delete Erased;

		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//1) Доходим до предпоследнего элемента:
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) Удаляем элемент из памяти:
		delete Temp->pNext;
		//3) Затираем адрес удаленного элемента нулем:
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int index)
	{
		if (index > size)return;
		if (index == 0)return pop_front();
		//1) Доходим до нужного элемента:
		Element<T>* Temp = Head;	//Создаем Итератор, и заходим в список через Голову.
		//Теперь в Итераторе адрес головного элемента.
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//2) Запоминаем адрес удаляемого элемента:
		Element<T>* Erased = Temp->pNext;
		//3) Исключаем элемент из списка:
		//Temp->pNext = Temp->pNext->pNext;
		Temp->pNext = Erased->pNext;
		//4) Удаляем элемент из памяти:
		delete Erased;
		size--;
	}

	//					Methods:
	void print()const
	{
#ifdef OLD_PRINT
		int a = 2;
		int* pa = &a;
		Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ 
		//к элементам структуры данных.
		while (Temp)//Пока Итератор содержит ненулевой адрес.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//переход на следующий элемент
		}
#endif // OLD_PRINT

		//		for(Start;		   Stop;	Step)
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		//for (Element* Temp = Head; Temp; Temp++)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов : " << Head->count << endl;
	}
};

//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK_1
//#define HOME_WORK_2
//#define RANGE_BASE_FOR_ARRAY
#define RANGE_BASE_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	list.pop_front();
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	list.insert(index, value);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();

#endif // BASE_CHECK

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
		list.push_front(rand() % 100);
	}
	//cout << "Список заполнен" << endl;
	list.print();
#endif // DESTRUCTOR_CHECK

	/*const int a = 250;
	a = 270;*/
#ifdef HOME_WORK_1
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list(n);
	for (int i = 0; i < n; i++)
	{
		//l-value = r-value;
		list[i] = rand() % 100;
		//			(int)
	}
	print_list(list);
#endif // HOME_WORK_1

#ifdef HOME_WORK_2
	//		 l-value = r-value
	ForwardList list = { 3,5,8,13,21 };
	//(ForwardList)  = (initializer_list)
	//list.print();
	for (Iterator it = list.getHead(); it != nullptr; ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	/*Iterator it = list.getHead();
	Iterator it2 = it++;
	cout << it << endl;
	cout << it2 << endl;*/
#endif // HOME_WORK_2

#ifdef RANGE_BASE_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	/*for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;*/

	//range-based for (for для диапазона.)
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	//Под диапазоном понимается контейнер (массив, список и т.д.)
	//В других языках программирования это называют foreach  
#endif // RANGE_BASE_FOR_ARRAY

#ifdef RANGE_BASE_FOR_LIST
	ForwardList<int> list = { 3,5,8,13,21 };
	for (Iterator<int> it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	//Range-based for
	/*
	------------------------------------------------------
	for(value:container)
	{
		cout << value;
	}
	------------------------------------------------------
	*/

	ForwardList<double> d_list = { 2.5, 3.14, 7, 5.2, 8.3 };
	for (double i : d_list)	cout << i << tab; cout << endl;

	ForwardList<string> s_list = { "Have", "a", "nice", "day" };
	for (string i : s_list)cout << i << tab; cout << endl;

	//ForwardList<string> s_list2 = s_list;	//CopyConstructor
	ForwardList<string> s_list2;
	s_list2 = s_list;
	for (string i : s_list2)cout << i << tab; cout << endl;
#endif // RANGE_BASE_FOR_LIST

}

/*
----------------------------
	Class object;	//создание объекта обычного класса
	Class<type> object;	//создание объекта шаблонного класса

	temaplate<typename T>
----------------------------
*/
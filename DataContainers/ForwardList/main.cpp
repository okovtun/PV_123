#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;	//Значение элемента
	Element* pNext;//Адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		cout << "EConstrcutor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestrcutor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList//Односвязный (однонаправленный) список
{
	Element* Head;	//Голова списка - указывает на начальный элемент списка.
public:
	ForwardList()
	{
		Head = nullptr;//Если голова указывает на 0, то список пуст.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//					Addigng elements:
	void push_front(int Data)
	{
		Element* New = new Element(Data);//Создаем новый элемент и помещаем в него значение Data
		New->pNext = Head;	//Привязывем новый элемент к началу списка
		Head = New;	//Переводим Голову на новый элемент
	}

	//					Methods:
	void print()const
	{
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
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
}
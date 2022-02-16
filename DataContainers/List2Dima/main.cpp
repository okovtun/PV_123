// List2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, *Tail;
	size_t size;
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) : Temp(Temp)
		{
			cout << "ITConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ItDestructor:\t" << this << endl;
		}
		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator& operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}

		Iterator& operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}

		/*bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}

		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}*/
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(unsigned int size) :List()
	{
		for (size_t i = 0; i < size; i++)
		{
			push_front(int());
		}
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end() - 1; it++)
		{
			push_back(*it);
		}
	}

	~List()
	{
		while (Tail)
		{
			pop_back();
		}
		cout << "LDestructor:\t" << this << endl;
	}

	const int& operator[](int index)const
	{
		Element* Temp = Head;
		for (size_t i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}

	int& operator[](int index)
	{
		Element* Temp = Head;
		for (size_t i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
		return Temp->Data;
	}

	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;
		size++;

		/*Head = Head->pPrev = new Element(Data);*/
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;
		size++;
	}

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;

	}

	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;

	}

	void insert(int index, int Data)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++)
			{
				Temp = Temp->pPrev;
			}
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}

	void Erase(int index)
	{
		if (index > size)return;
		if (index == 0)return pop_front();
		if (index == size)return pop_back();
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (size_t i = 0; i < index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (size_t i = 0; i < size - index - 1; i++)
			{
				Temp = Temp->pPrev;
			}
		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
	}

	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << Temp->pPrev << endl;
		}
		cout << "Колличество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << Temp->pPrev << endl;
		}
		cout << "Колличество элементов списка: " << size << endl;
	}
};

//#define BASE_CHECK
//#define CONSTR_CHECK

int main()
{
#ifdef BASE_CHECK
	setlocale(LC_ALL, "rus");
	int n;
	cin >> n;
	List list;
	for (size_t i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.Erase(1);
	list.print();
#endif // BASE_CHECK


#ifdef CONSTR_CHECK
	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)cout << i << tab; cout << endl;
#endif // CONSTR_CHECK

	List list = { 3,5,8,13,21 };
	for (List::Iterator it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	/*for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;*/
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

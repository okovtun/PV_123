#include <iostream>
#include <ctime>
using namespace std;

#define tab "\t"
class Element
{
	int Data;
	Element *pNext;
	static int count;

public:
	Element(int Data, Element *pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;

		cout << "EConstrcutor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestrcutor:\t" << this << endl;
	}
	friend class ForwardList;
	friend std::ostream &operator<<(std::ostream &in, const Element &obj);
};
int Element::count = 0;

class ForwardList
{
	Element *Head;
	unsigned int size;

public:
	ForwardList()
	{
		this->size = 0;
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}

	ForwardList(const std::initializer_list<int> &list)
	{
		this->size = 0;
		Head = nullptr;
		for (auto &Data : list)
		{
			push_front(Data);
		}
	}

	explicit ForwardList(ForwardList &obj)
	{
		if (&obj == this)
			return;

		Head = nullptr;

		while (obj.Head)
		{

			push_front(obj.Head->Data);

			obj.Head = obj.Head->pNext;
		}

		cout << "Copy constructor\t" << this << endl;
	}

	ForwardList &operator=(ForwardList &obj)
	{
		if (&obj == this)
			return *this;
		Head = nullptr;
		while (obj.Head)
		{
			push_front(obj.Head->Data);
			obj.Head = obj.Head->pNext;
		}
		cout << "CopyAssigment\t" << this << endl;
		return *this;
	}

	// desctructor
	~ForwardList()
	{
		// Element *Temp = Head;
		// while (Temp->pNext)
		// {
		//     Element *New = Temp->pNext;
		//     delete Temp;
		//     Temp = New;
		// }
		// cout << "LDestructor:\t" << this << endl;

		while (Head)
			pop_front();

		cout << "Ldesctructor" << endl;
	}

	const Element &operator[](int it) const
	{
		Element *Temp = Head;
		for (int i = 0; i < it; i++)
		{
			Temp = Temp->pNext;
		}
		return *Temp;
	}

	Element &operator[](int it)
	{
		Element *Temp = Head;
		for (size_t i = 0; i < it; i++)
		{
			Temp = Temp->pNext;
		}
		return *Temp;
	}

	void unique()
	{
		int index = 0;
		Element *Temp = Head;

		for (int i = 0; Temp; ++i)
		{
			Element *In = Temp->pNext;
			while (In)
			{
				if (Temp->Data == In->Data)
				{
					erase(i);
				}
				In = In->pNext;
			}

			Temp = Temp->pNext;
		}
	}

	void reverse()
	{
		Element *Temp = Head, *next = nullptr, *prev = nullptr;

		while (Temp)
		{
			next = Temp->pNext; //next element for while loop
			Temp->pNext = prev; // curren next element to pervios element
			prev = Temp; // pervios element for next element
			Temp = next; /// next element to while loop run again!
		}
		Head = prev;
	}

	void push_front(int Data)
	{
		Element *New = new Element(Data);
		New->pNext = Head;
		Head = New;
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			return push_front(Data);
		}
		Element *New = new Element(Data);
		Element *Temp = Head;

		while (Temp->pNext)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New;
		// New->pNext = NULL; Deafult Null
		size++;
	}

	////*removing elements

	void pop_front()
	{
		if (Head == nullptr)
			return;
		Element *Erases = Head;
		Head = Head->pNext;
		delete Erases;
		size++;
	}

	void pop_back()
	{
		if (Head == nullptr)
			return;
		if (Head->pNext == nullptr)
			return pop_front();
		Element *Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}

		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void insert(int index, int Data)
	{
		if (index > size)
			return;
		if (index == 0 || Head == nullptr)
			return push_front(Data);
		Element *New = new Element(Data);
		Element *Temp = Head; //*iterator

		for (int i = 0; i < index - 1; ++i)
		{
			Temp = Temp->pNext;
		}
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	void erase(int index)
	{
		if (index > size)
			return;
		if (index == 0)
			return pop_front();
		Element *Temp = Head;
		for (int i = 0; i < index - 1; ++i)
		{
			Temp = Temp->pNext;
		}
		Element *Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size--;
		// Element *Temp = Head;
		// for (int i = 0; i < index - 1; ++i)
		// {
		//     Temp = Temp->pNext;
		// }
		// Element *next = Temp->pNext->pNext;
		// delete Temp->pNext;
		// Temp->pNext = next;
	}

	void print() const
	{
		Element *Temp = Head;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
		cout << "Count in Forwardlist: " << size << endl;
		cout << "All Count of list: " << Head->count << endl;
	}
};

std::ostream &operator<<(std::ostream &in, const Element &obj)
{
	in << endl;
	in << "Data: " << obj.Data << endl;
	return in;
}

// #define BaseCheck
// #define CONSTRUCTOR_CHECK
// #define LIST_CHECK
int main()
{
	srand(time(0));
#ifdef BaseCheck
	int n;
	cout << "Enter size of list: ";
	cin >> n;
	ForwardList list;
	list.pop_front();
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();

	int index;
	int value;
	cout << "Enter index to add: ";
	cin >> index;
	cout << "Enter element to add: ";
	cin >> value;

	list.insert(index, value);
	list.print();

	cout << "Enter index to delete: ";
	cin >> index;

	list.erase(index);
	list.print();

#endif
#ifdef CONSTRUCTOR_CHECK

	int n;
	cout << "Enter size of list: ";
	cin >> n;

	ForwardList list;

	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}

	for (int i = 0; i < n; i++)
	{
		cout << list[i] << endl;
	}

	cout << "Done" << endl;

#endif // DEBUG
#ifdef LIST_CHECK
	// ForwardList list = {3, 5, 8, 13, 23};
	// list.print();

	// ForwardList list;
	// list.push_front(44);
	// list.push_front(48);
	// list.push_front(77);
	// list.push_front(33);
	// cout << "List 1: " << endl;
	// list.print();
	// cout << endl;
	// for (int i = 0; i < n; i++)
	// {
	//     // list.push_front(rand() % 100);
	//     list.push_back(rand() % 100);
	// }
	// list.push_back(123);
	// list.print();
	// list.pop_front();
	// list.pop_back();
	// int index,value;
	// cout << "Enter index: ";
	// cin >> index;
	// cout << "Enter value: ";
	// cin >> value;
	// list.insert(index,value);
	// list.print();
	// ForwardList list2 = std::move(list);
	// cout << "List 2: " << endl;
	// list2.print();
	// ForwardList list2;
	// list2 = list;
	// cout << "List 2: " << endl;
	// list2.print();
	// ForwardList list2;
	// list2.push_front(44);
	// list2.push_front(48);
	// list2.push_front(77);
	// list2.push_front(33);
	// list2.push_front(55);
	// cout << "List 2: " << endl;
	// list2.print();

#endif // DEBUG

	ForwardList list = { 1, 2, 3, 1, 5, 6 };
	ForwardList list2(list);

	cout << "List2:" << endl;

	for (int i = 0; i < 6; i++)
	{
		cout << list2[i] << endl;
	}

	return 0;
}
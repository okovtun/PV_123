//ForwardList
#include<iostream>
using namespace std;

#define tab "\t"
#define DEBUG
class Element
{
	int Data;	//Çíà÷åíèå ýëåìåíòà
	Element* pNext;//Àäðåñ ñëåäóþùåãî ýëåìåíòà
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
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
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList//Îäíîñâÿçíûé (îäíîíàïðàâëåííûé) ñïèñîê
{
	Element* Head;	//Ãîëîâà ñïèñêà - óêàçûâàåò íà íà÷àëüíûé ýëåìåíò ñïèñêà.
	unsigned int size;//Ðàçìåð ñïèñêà
public:
	ForwardList()
	{
		Head = nullptr;//Åñëè ãîëîâà óêàçûâàåò íà 0, òî ñïèñîê ïóñò.
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(unsigned int size) :ForwardList()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		for (int i = 0; i < size; i++)
		{
			push_front(0);
		}
	}
	ForwardList(const initializer_list<int>& il) : ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		/*	for (int const* it = il.begin(); it != il.end(); it++)
			{
				push_back(*it);
			}*/
		for (int const* it = il.end() - 1; it != il.begin() - 1; it--)
		{
			push_front(*it);
		}
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//                      Operators:

	int& operator[](const int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}
	const int& operator[](const int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)
			Temp = Temp->pNext;
		return Temp->Data;
	}

	//					Addigng elements:
	void push_front(int Data)
	{
		//initializer_list<Element*>{ new Element(Data), New->pNext = Head, Head = New};

		//Element* New = new Element(Data);//Ñîçäàåì íîâûé ýëåìåíò è ïîìåùàåì â íåãî çíà÷åíèå Data
		//New->pNext = Head;	//Ïðèâÿçûâåì íîâûé ýëåìåíò ê íà÷àëó ñïèñêà
		//Head = New;	//Ïåðåâîäèì Ãîëîâó íà íîâûé ýëåìåíò
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		////0) Ïðîâåðÿåì, ÿâëÿåòñÿ ëè ñïèñîê ïóñòûì:
		//if (Head == nullptr)return push_front(Data);
		////1) Ñîçäàåì íîâûé ýëåìåíò:
		//Element* New = new Element(Data);
		////2) Äîõîäèì äî êîíöà ñïèñêà:
		//Element* Temp = Head;
		//while (Temp->pNext)//Ïîêà, pNext òåêóùåãî ýëåìåíòà ÍÅ íîëü
		//	Temp = Temp->pNext;//ïåðåõîäèì íà ñëåäóþùèé ýëåìåíò
		////Òåïåðü ìû íàõîäèìñÿ â ïîñëåäíåì ýëåìåíòå, ò.å. Temp->pNext == nullptr
		////3) Ïðèñîåäèíÿåì íîâûé ýëåìåíò ê ïîñëåäíåìó:
		//Temp->pNext = New;


		/*if (Head == nullptr)return push_front(Data);
		Head = new Element(Data, Head);
		size++;*/
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int index, int Data)
	{
		//if (index == 0 || Head == nullptr)return push_front(Data);
		//if (index > size)return;
		//Element* New = new Element(Data);
		////1) Äîõîäèì äî íóæíîãî ýëåìåíòà:
		//Element* Temp = Head;
		//for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		////3) Âêëþ÷àåì íîâûé ýëåìåíò â ñïèñîê:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		//size++;

		/*if (index == 0 || Head == nullptr)return push_front(Data);
		if (index > size)return;
		Head = new Element(Data,Head);
		for (int i = 0; i < index - 1; i++)Head = Head;
		size++;*/

		if (index == 0 || Head == nullptr)return push_front(Data);
		if (index > size)return;
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;

	}

	//					Removing elements:
	void pop_front()
	{
		if (Head == nullptr)return;
		//1) Çàïîìèíàåì àäðåñ óäàâëÿåìîãî ýëåìåíòà:
		Element* Erased = Head;
		//2) Èñêëþ÷àåì óäàëÿåìûé ýëåìåíò èç ñïèñêà:
		Head = Erased->pNext;
		//3) Óäàëÿåì ýëåìåí èç ïàìÿòè:
		delete Erased;

		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//1) Äîõîäèì äî ïðåäïîñëåäíåãî ýëåìåíòà:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2) Óäàëÿåì ýëåìåíò èç ïàìÿòè:
		delete Temp->pNext;
		//3) Çàòèðàåì àäðåñ óäàëåííîãî ýëåìåíòà íóëåì:
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{
		if (index >= size)return;
		if (index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < index - 1; ++i)
			Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		//Temp->pNext = Temp->pNext->pNext;
		Temp->pNext = Erased->pNext;
		delete Erased;
		size--;
	}
	//					Methods:
	void print()const
	{
		int a = 2;
		int* pa = &a;
		Element* Temp = Head;	//Temp - ýòî èòåðàòîð.
		//Èòåðàòîð - ýòî óêàçàòåëü, ïðè ïîìîùè êîòîðîãî ìîæíî ïîëó÷èòü äîñòóï 
		//ê ýëåìåíòàì ñòðóêòóðû äàííûõ.
		while (Temp)//Ïîêà Èòåðàòîð ñîäåðæèò íåíóëåâîé àäðåñ.
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//ïåðåõîä íà ñëåäóþùèé ýëåìåíò
		}
		cout << "Êîëè÷åñòâî ýëåìåíòîâ ñïèñêà: " << size << endl;
		cout << "Îáùåå êîëè÷åñòâî ýëåìåíòîâ : " << Head->count << endl;
	}
};

#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK_1
//#define HOME_WORK_2

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Ââåäèòå ðàçìåð ñïèñêà: "; cin >> n;
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
	cout << "Ââåäèòå èíäåêñ äîáàâëÿåìîãî ýëåìåíòà: "; cin >> index;
	cout << "Ââåäèòå çíà÷åíèå äîáàâëÿåìîãî ýëåìåíòà: "; cin >> value;

	list.insert(index, value);
	list.print();
	cout << "Ââåäèòå èíäåêñ óäàëÿåìîãî ýëåìåíòà: "; cin >> index;
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
	cout << "Ââåäèòå ðàçìåð ñïèñêà: ";
	cin >> n;
	ForwardList list;

	for (int i = 0; i < n; i++)
	{
		list.push_front(rand());
	}
	cout << "Ñïèñîê çàïîëíåí" << endl;
#endif // DESTRUCTOR_CHECK

#ifdef HOME_WORK_1
	int n;
	cout << "Ââåäèòå ðàçìåð ñïèñêà: ";
	cin >> n;
	ForwardList list(n);
	for (int i = 0; i < n; i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < n; i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // HOME_WORK_1
#ifdef HOME_WORK_2
	ForwardList list = { 3,5,8,13,21 };
	list.print();
#endif // HOME_WORK_2

}
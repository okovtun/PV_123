#include<iostream>
using namespace std;

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
			//cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			//cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		this->Root = nullptr;
		//cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			insert(*it, Root);
		}
	}
	Tree(const Tree& other):Tree()
	{
		copy(other.Root);
		//cout << "CopyConstructor: \t" << this << endl;
	}
	~Tree()
	{
		clear();
		//cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	void print()
	{
		print(Root);
		cout << endl;
	}
	int size()const
	{
		return size(Root);
	}
	int sum()const
	{
		return sum(Root);
	}

	double avg()
	{
		return (double)sum(Root) / size(Root);
	}

private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}

		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element* Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf())
			{
				delete Root;
				Root = nullptr;
			}
		}
	}

	void clear(Element* Root)
	{
		if (Root == nullptr)
			return;
		clear(Root->pLeft); // удаляется вся левая ветка с минимального значения
		clear(Root->pRight); // удаляется вся правая ветка с максимального значения
		delete Root;
	}
	void copy(Element* Root)
	{
		if (Root == nullptr)
			return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
	}

	int minValue(Element* Root)const
	{
		if (Root == nullptr)
			return 0;
		//        else if (Root -> pLeft == nullptr)
		//            return Root -> Data;
		//        else return minValue(Root -> pLeft);

				//return Root -> pLeft == nullptr ? Root -> Data : minValue(Root -> pLeft);
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}

	int maxValue(Element* Root)const
	{
		if (Root == nullptr)
			return 0;
		//        else if (Root -> pRight == nullptr)
		//            return Root -> Data;
		//        else return maxValue(Root -> pRight);

		return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
	}
	int size(Element* Root)const
	{
		if (Root == nullptr)
			return 0;
		return size(Root->pLeft) + size(Root->pRight) + 1;
	}

	int sum(Element* Root)const
	{
		if (Root == nullptr)
		{
			return 0;
		}
		return sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
		//return !Root ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root -> Data;
	}

	void print(Element* Root)const
	{
		if (Root == nullptr) return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree : public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}

		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

public:
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
};

//#define BASE_CHECK

int main()
{
#ifdef BASE_CHECK
	int n;
	cout << "Enter size of the tree: "; cin >> n;

	UniqueTree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;

	cout << "Min value in the tree: " << tree.minValue() << endl;
	cout << "Max value in the tree: " << tree.maxValue() << endl;
	cout << "Size of the tree: " << tree.size() << endl;
	cout << "Sum of elements: " << tree.sum() << endl;
	cout << "Average: " << tree.avg() << endl;
#endif // BASE_CHECK

	Tree tree = { 50, 25, 75, 16, 32, 64, 80 };
	tree.print();

	Tree tree2 = tree;
	tree2.print();


	return 0;
}
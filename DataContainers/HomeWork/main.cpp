#include <iostream>

#define tab "\t"
// #define DEBUG

template <class T>
class ForwardList;

template <class T>
class Element
{
	T data_;
	Element *pNext;

public:
	Element(T data = T{}, Element *pNext = nullptr) : data_(data), pNext(pNext)
	{
#ifdef DEBUG
		std::cout << "EConstrcutor:\t" << this << std::endl;
#endif
	}
	~Element()
	{
#ifdef DEBUG
		std::cout << "EDestrcutor:\t" << this << std::endl;
#endif
	}

	Element const *const &next() const
	{
		return pNext;
	}

	Element *&next()
	{
		return pNext;
	}

	T const &data() const
	{
		return data_;
	}

	T &data()
	{
		return data_;
	}

	friend class ForwardList<T>;
};

template <class T>
class ForwardList
{
	using _node = Element<T>;

	_node *head_;
	size_t size_;

	template <class _FLNodeType, class _FLNodePtr, class _FLNodeRef>
	class iterator_impl
	{
		_FLNodePtr ptr_;

	public:
		using _Self = ForwardList::iterator_impl<_FLNodeType, _FLNodePtr, _FLNodeRef>;

		using difference_type = std::ptrdiff_t; // auto size pointer
		using iterator_category = std::forward_iterator_tag;

		iterator_impl() : ptr_(nullptr) {}
		iterator_impl(_FLNodePtr p) : ptr_(p) {}
		iterator_impl(const _Self &) = default;
		iterator_impl(_Self &&) = default;
		_Self &operator=(_Self &&) = default;
		_Self &operator=(const _Self &) = default;

		_Self &operator++()
		{
			ptr_ = ptr_->next();
			return *this;
		}

		_Self operator++(int)
		{
			_Self temp(*this);
			ptr_ = ptr_->next();
			return temp;
		}

		decltype(ptr_->data()) operator*()
		{
			return ptr_->data();
		}

		decltype(&(ptr_->data())) operator->()
		{
			return &(ptr_->data());
		}

		bool operator!=(const _Self &it) const
		{
			return ptr_ != it.ptr_;
		}

		bool operator==(const _Self &it) const
		{
			return ptr_ == it.ptr_;
		}
	};

	template <class It>
	_node *advance(_node *iter, size_t distance)
	{
		if (distance > size_)
			throw "Forward list out of bounds";

		for (size_t i = 0; i < distance; ++i)
		{
			iter = iter->pNext;
		}
		return iter;
	}

public:
	using iterator = ForwardList::iterator_impl<_node, _node *, _node &>;
	using const_iterator = ForwardList::iterator_impl<const _node, const _node *, const _node &>;

	ForwardList() noexcept : head_(nullptr), size_(0)
	{
#ifdef DEBUG
		std::cout << "LConstructor:\t" << this << std::endl;
#endif
	}

	ForwardList(size_t size) : ForwardList()
	{
		while (size_ != size)
		{
			this->push_front(T());
		}
	}

	ForwardList(std::initializer_list<T> il) : ForwardList()
	{
		for (T val : il)
		{
			this->push_front(val);
		}
	}

	~ForwardList()
	{
		while (head_)
		{
			this->pop_front();
		}
#ifdef DEBUG
		std::cout << "LDestructor:\t" << this << std::endl;
#endif
	}

	ForwardList(ForwardList<T> const &other) : ForwardList()
	{
		for (T i : other)
			this->push_front(i);
		this->reverse();
	}

	ForwardList(ForwardList<T> &&other)
	{
		_node *tmp = this->head_;

		this->head_ = other.head_;
		this->size_ = other.size_;

		other.head_ = tmp;
	}

	ForwardList<T> &operator=(const ForwardList<T> &other)
	{
		if (this == &other)
			return *this;
		ForwardList<T> to_delete = std::move(*this);
		new (this) ForwardList(other);
		return *this;
	}

	ForwardList<T> &operator=(ForwardList<T> &&other)
	{
		if (this == &other)
			return *this;

		_node *tmp = this->head_;

		this->head_ = other.head_;
		this->size_ = other.size_;

		other.head_ = tmp;
		return *this;
	}

	inline void push_front(T data)
	{
		head_ = new Element<T>(data, head_);

		++this->size_;
	}

	void push_back(T data)
	{
		if (head_ == nullptr)
			return this->push_front(data);
		_node *iter = ForwardList::advance(head_, size_ - 1);
		iter->pNext = new Element(data);
		++this->size_;
	}

	inline void pop_front()
	{
		if (head_ == nullptr)
			return;

		_node *temp = head_;
		head_ = head_->pNext;
		delete temp;

		--this->size_;
	}

	void pop_back()
	{
		if (head_ == nullptr)
			return;
		if (head_->pNext == nullptr)
			return this->pop_front();
		_node *iter = ForwardList::advance(head_, size_ - 2);
		delete iter->pNext;
		iter->pNext = nullptr;

		--this->size_;
	}

	void insert(size_t index, T data)
	{
		if (index == 0 or head_ == nullptr)
			return this->push_front(data);
		_node *iter = ForwardList::advance(head_, index - 1);
		_node *temp = iter->pNext;
		iter->pNext = new Element(data, temp);
		++this->size_;
	}

	void erase(size_t index)
	{
		if (index == 0)
			return this->pop_front();
		_node *iter = ForwardList::advance(head_, index - 1);
		if (iter->pNext == nullptr)
			throw "No element at given index";
		_node *temp = iter->pNext->pNext;
		delete iter->pNext;
		iter->pNext = temp;
		--this->size_;
	}

	void unique() //как быстрее?
	{
		Element<T> *to_unique = this->head_;
		Element<T> *to_find = nullptr;

		for (size_t unique_idx = 0; to_unique; ++unique_idx, to_unique = to_unique->pNext)
		{
			to_find = to_unique->pNext;

			for (size_t idx_to_remove = unique_idx + 1; to_find; ++idx_to_remove)
			{
				if (to_unique->data_ == to_find->data_)
				{
					to_find = to_find->pNext;
					this->erase(idx_to_remove);
					--idx_to_remove;
				}
				else
				{
					to_find = to_find->pNext;
				}
			}
		}
	}

	void reverse()
	{
		_node *prev = nullptr;
		_node *next = this->head_;
		_node *temp = nullptr;
		for (size_t idx = 0; idx < size_; ++idx)
		{
			temp = next->pNext;
			next->pNext = prev;
			prev = next;
			next = temp;
		}
		this->head_ = prev;
	}

	T operator[](size_t index) const
	{
		return ForwardList::advance(head_, index)->data_;
	}

	T &operator[](size_t index)
	{
		return ForwardList::advance(head_, index)->data_;
	}

	bool is_empty() const { return !head_; }

	void print() const
	{
		for (auto Temp = head_; Temp; Temp = Temp->pNext)
		{
			std::cout << Temp << tab << Temp->data_ << tab << Temp->pNext << std::endl;
		}
	}

	ForwardList::const_iterator begin() const
	{
		return ForwardList::const_iterator(head_);
	}

	ForwardList::const_iterator end() const
	{
		return ForwardList::const_iterator();
	}

	ForwardList::iterator begin()
	{
		return ForwardList::iterator(head_);
	}

	ForwardList::iterator end()
	{
		return ForwardList::iterator();
	}
};

// #define BASE_CHECK
// #define DESTRUCTOR_CHECK
// #define HOME_WORK_1
// #define HOME_WORK_2
#define RANGE_BASE_FOR_LIST

ForwardList<int> func()
{
	return ForwardList<int>({ 4, 3, 2, 1 });
}

int main()
{
#ifdef BASE_CHECK
	int n;
	std::cout << "Enter list size: ";
	std::cin >> n;
	ForwardList<int> list;
	list.pop_front();
	for (int i = 0; i < n; i++)
	{
		// list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	// list.push_back(123);
	// list.pop_front();
	// list.pop_back();

	int index;
	int value;
	std::cout << "Enter index INSERT element: ";
	std::cin >> index;
	std::cout << "Enter value INSERT element: ";
	std::cin >> value;

	list.insert(index, value);
	list.print();

	std::cout << "Enter index ERASE element: ";
	std::cin >> index;
	list.erase(index);
	list.print();

#endif // BASE_CHECK

	// ForwardList<int> list1;
	// list1.push_back(3);
	// list1.push_back(5);
	// list1.push_back(8);
	// list1.push_back(13);
	// list1.push_back(21);
	// list1.pop_back();
	// list1.pop_front();
	// list1.print();

#ifdef DESTRUCTOR_CHECK
	int n;
	std::cout << "Enter list size: ";
	std::cin >> n;
	ForwardList<int> list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	// std::cout << "Список заполнен" << std::endl;
	list.print();
#endif // DESTRUCTOR_CHECK

#ifdef HOME_WORK_1
	int n;
	std::cout << "Enter list size: ";
	std::cin >> n;
	ForwardList<int> list(n);
	for (int i = 0; i < n; i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < n; i++)
	{
		std::cout << list[i] << tab;
	}
	std::cout << std::endl;
#endif // HOME_WORK_1

#ifdef HOME_WORK_2
	ForwardList<int> list = { 3, 5, 8, 13, 3, 21, 5, 5, 6, 5, 13 };
	list.unique();
	list.reverse();
	list.print();
#endif // HOME_WORK_2

#ifdef RANGE_BASE_FOR_LIST
	ForwardList<int> list = { 3, 5, 8, 13, 21 }; // https://docs.microsoft.com/en-us/cpp/cpp/range-based-for-statement-cpp?view=msvc-160
	for (int i : list)
	{
		std::cout << i << tab;
	}
	std::cout << std::endl;

	ForwardList<int> l2{};
	l2 = func();
	l2 = list;
	for (int i : l2)
	{
		std::cout << i << tab;
	}
	std::cout << std::endl;
#endif // RANGE_BASE_FOR_LIST
}
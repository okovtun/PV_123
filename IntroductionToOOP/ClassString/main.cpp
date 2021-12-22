#include<iostream>
using std::cin;
using std::cout;
using std::endl;
//Move-методы:
//MoveConstructor - Конструктор переноса
//MoveAssignment  - Оператор присваивания-переноса
#define delimiter "\n-------------------------------------------------\n"

class String;
String operator+(const String& left, const String& right);

class String
{
	int size;	//Размер строки в Байтах
	char* str;	//Адрес строки в динамической памяти
public:
	int get_size()const
	{
		return size;
	}
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}

	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};	//Память, выделяемую для строки обязательно нужно занулить
		cout << "SizeConstructor:\t" << this << endl;
	}
	String(const char str[])
	{
		this->size = strlen(str) + 1;
		this->str = new char[size]{};
		for (int i = 0; str[i]; i++)this->str[i] = str[i];
		cout << "Constructor:\t" << this << endl;
	}
	String(const String& other)
	{
		//Deep copy (Побитовое копирование):
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyConstructor:\t" << this << endl;
	}
	String(String&& other)noexcept//никогда не бросает исключение
	{
		//MoveConstructor должен выполнять поверхностное копирование (Shallow copy)
		this->size = other.size;
		this->str = other.str;//просто копируем адрес памяти, пренадлещаей другому объекту
		//Зануляем другой объект, для того, чтобы его память не смог удалить деструктор:
		other.size = 0;
		other.str = nullptr;
		
		cout << "MoveConstructor:\t" << this << endl;
	}
	~String()
	{
		delete[] str;
		cout << "Destructor:\t" << this << endl;
	}

	//					Operators:
	String& operator=(const String& other)
	{

		//l-value = r-value;
		if (this == &other)return *this;	//Проверяем, не являются ли this и other одним и тем же объектом
		delete[] this->str;
		//Deep copy (Побитовое копирование):
		this->size = other.size;
		this->str = new char[size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	String& operator=(String&& other)
	{
		if (this == &other)return *this;
		delete this->str;
		this->size = other.size;
		this->str = other.str;

		other.size = 0;
		other.str = nullptr;
		cout << "MoveAssignment:\t" << this << endl;
		return *this;
	}

	//Class(const Class& other);	//CopyConstructor
	//Class& operator=(const Class& other);	//CopyAssignment

	//Class(Class&& other);			//MoveConstructor
	//Class& operator=(Class&& other);		//MoveAssignment

	String& operator+=(const String& other)
	{
		return *this = *this + other;
	}

	const char& operator[](int i)const 
	{
		return str[i];
	}
	char& operator[](int i)
	{
		return str[i];
	}

	//					Methods
	void print()const
	{
		cout << "Size:\t" << size << endl;
		cout << "Str:\t" << str << endl;
	}
};

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);
	for (int i = 0; i < left.get_size(); i++)
		//l-value = r-value;
		result[i] = left[i];
		//result.get_str()[i] = left.get_str()[i];
	for (int i = 0; i < right.get_size(); i++)
		result[i + left.get_size() - 1] = right[i];
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
std::istream& operator>>(std::istream& is, String& obj)
{
	//return is >> obj.get_str();
	const int SIZE = 1024*1000;
	char buffer[SIZE] = {};
	is >> buffer;
	obj = buffer;
	return is;
}

std::istream& getline(std::istream& is, String& obj)
{
	const int SIZE = 1024 * 1000;
	char buffer[SIZE] = {};
	is.getline(buffer, SIZE);
	obj = buffer;
	return is;//winver
}

//char str[] = { 'S', 't', 'r', 'o', 'k', 'a' };

//#define CONSTRUCTORS_CHECK
#define OPERATORS_CHECK

void main()
{
	//char test[1024 * 1024]{};
	setlocale(LC_ALL, "");

#ifdef CONSTRUCTORS_CHECK
	String str1;		//Default constructor
	str1.print();
	cout << str1 << endl;

	String str2(25);	//Single-argument constructor
	str2.print();

	String str3 = "Hello";
	str3 = str3;
	cout << str3 << endl;

	String str4 = str3;	//CopyConstructor
	//Deep copy
	//Shallow copy
	//Debug Assertion Failed
	cout << str4 << endl;

	String str5;
	str5 = str3;	//CopyAssignment (operator=)
	cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	int a = 2;
	int b = 3;
	int c = a + b;
	
	String str1 = "Hello";
	String str2 = "World";
	cout << delimiter << endl;
	String str3;
	str3 = str1 + str2;
	cout << delimiter << endl;
	cout << str3 << endl;
	cout << delimiter << endl;
	String str4 = str3;	//CopyConstructor - Deep copy
	/*str1 += str2;
	cout << delimiter << endl;
	cout << str1 << endl;
	cout << delimiter << endl;*/
#endif // OPERATORS_CHECK


	//String str;
	//cout << "Введите строку: "; 
	////cin >> str;
	//getline(cin, str);
	//cout << str << endl;
	//str.print();
}
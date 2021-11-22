//IntroductionToOOP
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;;;;

#define tab "\t"

class Point
{
	double x;
	double y;
public:
	//get-методы дожны быть константными
	//константным называется метод, который НЕ изменяет объект, 
	//для которого вызывается.
	//Для константного объекта могут быть вызваны только константные методы
	double get_x()const
	{
		return x;
	}
	double get_y()const
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	//					Constructors:
	/*Point()
	{
		x = y = 0;
		cout << "DefaultConstructor:\t" << this << endl;
	}*/
	//Point(double x)
	//{
	//	this->x = x;
	//	this->y = double();	//double() - значение по умолчанию для типа double
	//	//double() - якобы вызываем конструктор по умолчанию для double
	//	cout << "1argConstrcutor:" << this << endl;
	//}
	Point(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
		cout << "Constructor:\t" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//				Methods:
	void print()const
	{
		cout << "X = " << x << "\tY = " << y << endl;
	}
};

//#define STRUCT_POINT

//Point G;	//Global object (Глобальный объект)
int g;		//Global variable (Глобальная переменная)	DEPRECATED(осуждается)

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef STRUCT_POINT
	//type name;
	int a;	//Объявление переменной 'a' типа 'int'
	Point A;//Объявление переменной 'A' типа 'Point'
			//Объявление объекта 'A' структуры 'Point'
			//Создание экземпляра 'A' структуры 'Point'
	//instance - экземпляр
	//instantiate - создать экземпляр
	A.x = 2;
	A.y = 3;
	cout << A.x << tab << A.y << endl;

	Point* pA = &A;	//Объявляем указатель на Point 'pA', 
					//и инициализируем его адресом объекта 'A'
	cout << pA->x << tab << pA->y << endl;
	cout << (*pA).x << tab << (*pA).y << endl;
#endif // STRUCT_POINT

	Point A;//Default constructor
	/*A.set_x(2);
	A.set_y(3);*/
	//cout << A.get_x() << "\t" << A.get_y() << endl;
	A.print();

	Point B(4, 5);
	B.print();

	Point C = 5;	//Single-argumen constructor
	C.print();
	//cout << C.get_x() << endl;

	Point D(8);	//Single-argument constructor
	D.print();
}

/*
----------------------------------------------
.  - Оператор прямого доступа	(Point operator)
-> - Оператор косвенного доступа(Arrow operator)
----------------------------------------------
*/

/*
----------------------------------------------
1. Инкапсуляция (Encapsulation);
	Модификаторы доступа:
		-private:	закрытые поля, доступны только изнутри класса;
		-public:	открытые поля, доступны из любого места программы;
		-protected: защищенные поля, используются только при наследовании
					доступны внутри нашего класса, и внутри дочерних классов;
	get/set-методы:
	get (взять, получить)
	set (задать, установить)
2. Наследование (Inheritance);
3. Полиморфизм (Polymorphism);
----------------------------------------------
*/

/*
----------------------------------------------
1. Constructor	- это метод, который создает объект;
	Default constructor - это конструктор, который может быть вызван без параметров
2. ~Destructor	- это метод, который уничтожает объект
   по завершении его времени жизни;
   ~ - Tilda.
3. Operator=;

----------------------------------------------
*/
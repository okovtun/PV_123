//IntroductionToOOP
#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

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
	Point(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyConstructor:" << this << endl;
	}
	~Point()
	{
		cout << "Destructor:\t" << this << endl;
	}

	//				Operators:
	void operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		cout << "CopyAssignment:\t" << this << endl;
	}

	//				Methods:
	double distance(Point other)
	{
		//other - дркгой (другая точка)
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double distance = sqrt(x_distance*x_distance + y_distance * y_distance);
		//sqrt - Square Root (Квадратный корень)
		return distance;
	}
	void print()const
	{
		cout << "X = " << x << "\tY = " << y << endl;
	}
};

double distance(Point A, Point B)
{
	double x_distance = A.get_x() - B.get_x();
	double y_distance = A.get_y() - B.get_y();
	return sqrt(x_distance*x_distance + y_distance * y_distance);
}

//Point G;	//Global object (Глобальный объект)
int g;		//Global variable (Глобальная переменная)	DEPRECATED(осуждается)

//#define STRUCT_POINT
//#define CONSTRUCTORS_CHECK
//#define DISTANCE_CHECK
#define ASSIGNMENT_CHECK

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

#ifdef CONSTRUCTORS_CHECK
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

	Point E = D;	//CopyConstructor
	E.print();
	Point F(B);		//CopyConstructor
	F.print();
	/*cout << "\n------------------------------\n";
	cout << Point(123, 234).distance(Point(345, 456)) << endl;
	cout << "\n------------------------------\n";*/

	Point G;//Default constructor
	G = F;	//CopyAssignment (operator=)
	G.print();
#endif 

#ifdef DISTANCE_CHECK
	Point A(2, 3);
	Point B(3, 4);
	cout << "Расстояние от точки A до точки B:" << A.distance(B) << endl;
	cout << "Расстояние от точки B до точки A:" << B.distance(A) << endl;

	cout << "Расстояние между точками A и B:  " << distance(A, B) << endl;
	cout << "Расстояние между точками B и A:  " << distance(B, A) << endl;
#endif // DISTANCE_CHECK

#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;
	cout << a << tab << b << tab << c << endl;

	Point A, B, C;
	A = B = C = Point(2, 3);
	A.print();
	B.print();
	C.print();
#endif // ASSIGNMENT_CHECK

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
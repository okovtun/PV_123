#define _USE_MATH_DEFINES
#pragma warning(disable:4326)

#include<Windows.h>
#include<iostream>
#include<math.h>
using namespace std;

namespace Geometry
{
	/*
------------------------------------------------------
enum (enumeration - перечисление) - это набор именованных констант типа int.
------------------------------------------------------
*/

//Создаем тип данных Color
	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,

		some_colore,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_default = 0x07
	};

	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
	public:
		void set_start_x(unsigned int start_x)
		{
			if (start_x > 300)start_x = 300;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y > 300)start_y = 300;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width > 20)line_width = 20;
			this->line_width = line_width;
		}
		Shape(Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width) :
			color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		virtual void info()const
		{
			cout << "Площадь:\t" << get_area() << endl;
			cout << "Периметр:\t" << get_perimeter() << endl;
			draw();
		}
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		const double& set_side(double side)
		{
			if (side <= 0)side = 10;
			this->side = side;
			return this->side;
		}
		Square(
			double side,
			Color color,
			unsigned int start_x, unsigned int start_y,
			unsigned int line_width)
			:Shape(color, start_x, start_y, line_width)/*,side(set_side(side))*/
		{
			set_side(side);
		}
		~Square() {}

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, color);
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
			SetConsoleTextAttribute(hConsole, Color::console_default);*/

			//H - Handle
			HWND hConsole = GetConsoleWindow();	//Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);//Создаем контекст устройства для полученного окна.
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//Создаем карандаш, который будет рисовать контур
			//PS_SOLID - сплошная линия, 5 - толщина линии 5 пикселов, RGB(...) - цвет.
			SelectObject(hdc, hPen);//Выбираем созданный карандаш, чтобы им можно было рисовать.
			HBRUSH hBrush = CreateSolidBrush(color);//Создаем кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);//Выбираем созданную кисть.
			//Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);//Рисует квадрат

			//Удаляем созданную кисть и карандаш:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			//Освобождаем контекст устройства:
			ReleaseDC(hConsole, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны: " << side << endl;
			Shape::info();
		}
	};

	class Rectangle :public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width <= 0)width = 20;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length <= 0)length = 10;
			this->length = length;
		}
		Rectangle
		(
			double width, double length,
			Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width
		) :Shape(color, start_x, start_y, line_width)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}

		double get_area()const
		{
			return width * length;
		}
		double get_perimeter()const
		{
			return (width + length) * 2;
		}
		void draw()const
		{
			HWND hConsole = GetConsoleWindow();	//Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);//Создаем контекст устройства для полученного окна.
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//Создаем карандаш, который будет рисовать контур
			//PS_SOLID - сплошная линия, 5 - толщина линии 5 пикселов, RGB(...) - цвет.
			SelectObject(hdc, hPen);//Выбираем созданный карандаш, чтобы им можно было рисовать.
			HBRUSH hBrush = CreateSolidBrush(color);//Создаем кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);//Выбираем созданную кисть.
			//Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);//Рисует квадрат

			//Удаляем созданную кисть и карандаш:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			//Освобождаем контекст устройства:
			ReleaseDC(hConsole, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина:\t" << width << endl;
			cout << "Длина:\t" << length << endl;
			Shape::info();
		}
	};
	class Circle :public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return radius * 2;
		}
		void set_radius(double radius)
		{
			if (radius <= 0)radius = 10;
			this->radius = radius;
		}
		Circle
		(
			double radius,
			Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width
		) :Shape(color, start_x, start_y, line_width)
		{
			set_radius(radius);
		}
		~Circle(){}
		double get_area()const
		{
			return M_PI * radius*radius;
		}
		double get_perimeter()const
		{
			return 2 * M_PI*radius;
		}
		void draw()const
		{
			HWND hConsole = GetConsoleWindow();	//Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);//Создаем контекст устройства для полученного окна.
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//Создаем карандаш, который будет рисовать контур
			//PS_SOLID - сплошная линия, 5 - толщина линии 5 пикселов, RGB(...) - цвет.
			SelectObject(hdc, hPen);//Выбираем созданный карандаш, чтобы им можно было рисовать.
			HBRUSH hBrush = CreateSolidBrush(color);//Создаем кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);//Выбираем созданную кисть.
			//Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			::Ellipse(hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());//Рисует квадрат

			//Удаляем созданную кисть и карандаш:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			//Освобождаем контекст устройства:
			ReleaseDC(hConsole, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус:\t" << radius << endl;
			Shape::info();
		}
	};
}

void main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 16,16 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &buffer);
	setlocale(LC_ALL, "");
	//Shape shape(Color::console_blue);
	Geometry::Square square(250, Geometry::Color::green, 150, 300, 5);
	/*cout << "Сторона квадрата:\t" << square.get_side() << endl;
	cout << "Площадь квадрата:\t" << square.get_area() << endl;
	cout << "Периметр квадрата:\t" << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(200, 100, Geometry::Color::red, 300, 400, 5);
	rect.info();

	Geometry::Circle circle(150, Geometry::Color::blue, 300, 400, 5);
	circle.info();
	INT_MAX;
	int arr[] = 
	{ 
		3,
		5,
		8,
		13,
		21
	};
}
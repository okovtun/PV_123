#include <iostream>
#include <math.h>
#include <cmath>
#include <Windows.h>
#include <windowsx.h>
#include <corecrt_math_defines.h>
using namespace std;
#define PI M_PI //for pi = 3.14......
///winapi console docs 
//https://docs.microsoft.com/en-us/windows/win32/gdi/creating-colored-pens-and-brushes

class Window {
private:
	double x, y; /// windows position
public:
	double get_x() {
		return x;
	}

	double get_y() {
		return y;
	}

	void set_x(double x) {
		if (x < 200) {
			x = 200;
		}
		this->x = x;
	}

	void set_y(double y) {
		if (y < 200) {
			y = 200;
		}
		this->y = y;
	}

	Window(double x, double y) {
		set_x(x);
		set_y(y);
		cout << "Wconstrctor\t" << this << endl;
	}

	~Window() {
		cout << "Wdesctrcutor\t" << this << endl;
	}

	void draw_text_to_console() {
		HWND console_handle = GetConsoleWindow();
		HDC device_context = GetDC(console_handle);
		RECT textRect;
		SetBkColor(device_context, RGB(200, 255, 200));
		SetRect(&textRect, 410, 210, 600, 200);
		DrawText(device_context, TEXT("Hello from window class"), -1, &textRect, DT_CENTER | DT_NOCLIP);
		DeleteObject(device_context);
	}

	void print()const {
		cout << "X position: " << x << endl;
		cout << "Y position: " << y << endl;
	}
};


class Square : public Window {
private:
	double side; /// corners of square
public:
	double get_side()const {
		return side;
	}
	void set_side(double side) {
		this->side = side;
	}

	double get_area() {
		return side * side;
	}

	double get_perimetr() {
		return side * 4;
	}

	Square(double x, double y, double side) : Window(x, y) {
		this->side = side;
		cout << "Sconstructor\t" << this << endl;
	}
	~Square() {
		cout << "Sdesctructor\t" << endl;
	}

	void drawtoconsole()const {
		HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
		//https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
		SetConsoleTextAttribute(myconsole, 2); // 2 - color code
		//system("color d1");
		for (int i = 0; i < side; i++)
		{
			for (int j = 0; j < side; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
		SetConsoleTextAttribute(myconsole, 2);////2 - color code green
	}


	void print() {
		//Figure::print();
		cout << "Side: " << side << endl;
		cout << "Perimetr: " << get_perimetr() << endl;
		cout << "Area: " << get_area() << endl;
	}

};

class Rectangel : public Window {
private:
	double height, width;
public:
	double get_width() {
		return this->width;
	}
	double get_height() {
		return this->height;
	}

	void set_width(double width) {
		if (width < 60) {
			width = 60;
		}
		this->width = width;
	}
	void set_height(double height) {
		if (height < 100) {
			height = 100;
		}
		this->height = height;
	}

	//https://www.mathplanet.com/education/pre-algebra/inequalities-and-one-step-equations/calculating-the-area-and-the-perimeter
	double get_perimetr() {
		return (height + width) * 2;
	}

	double get_area() {
		return (height * width);
	}


	Rectangel(double x, double y, double width, double height) : Window(x, y) {
		set_width(width);
		set_height(height);
		cout << "Rconstructor\t" << this << endl;
	}

	~Rectangel() {
		cout << "Rdesctructor\t" << this << endl;
	}

	void draw_to_console() {
		//https://docs.microsoft.com/en-us/windows/win32/gdi/creating-colored-pens-and-brushes
		HWND console_handle = GetConsoleWindow();
		HDC device_context = GetDC(console_handle);
		HPEN hPen = CreatePen(PS_DASHDOT, 1, RGB(255, 0, 0));
		SelectObject(device_context, hPen);
		SetBkColor(device_context, RGB(255, 255, 0));
		SelectObject(device_context, CreateSolidBrush(RGB(100, 200, 255)));
		Rectangle(device_context, Window::get_x(), Window::get_y(), Window::get_x() + width, Window::get_y() + height);
		DeleteObject(device_context);
		DeleteObject(hPen);
	}
	void print() {
		cout << "Perimetr: " << get_perimetr() << endl;
		cout << "Area: " << get_area() << endl;
	}
};

class EqualTriangel : public Window {
private:
	double side; //left right and bottom side of triangel
public:

	double get_side() {
		return side;
	}

	void set_side(double side) {
		this->side = side;
	}


	double get_height() {
		return (sqrt(3) / 2) * side;
	}

	double get_area() {
		return (sqrt(3) / 4) * side * side;
	}

	double get_perimetr() {
		return 3 * side;
	}

	EqualTriangel(double x, double y, double side) : Window(x, y) {
		this->side = side;
		cout << "Tconstructor\t" << this << endl;
	}

	~EqualTriangel() {
		cout << "Tdesctructor\t" << this << endl;
	}

	void print_to_console()const {
		///https://docs.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-polygon
		HWND console_handle = GetConsoleWindow();
		HDC device_context = GetDC(console_handle);
		HPEN hPen = CreatePen(PS_DASHDOTDOT, 1, RGB(0, 255, 255));
		SelectObject(device_context, hPen);
		SetBkColor(device_context, RGB(255, 0, 0));
		SelectObject(device_context, CreateSolidBrush(RGB(0, 0, 0)));
		///vertices not complete yet!!!
		POINT vertices[] = { {200, 100}, {300, 300}, {100, 300} };
		Polygon(device_context, vertices, sizeof(vertices) / sizeof(vertices[0]));
		DeleteObject(device_context);
		DeleteObject(hPen);
	}
	void print() {
		///Figure::print();
		cout << "Side : " << side << endl;
		cout << "Perimetr: " << get_perimetr() << endl;
		cout << "Area: " << get_area() << endl;
		cout << "Height: " << get_height() << endl;
	}
};

class Circle : public Window {
private:
	double radius;
public:

	double get_radius() {
		return radius;
	}
	void set_radius(double radius) {
		if (radius == 0 || radius == 0.0) {
			radius = 1;
		}
		this->radius = radius;
	}

	double get_area()const {
		double area = PI * radius * radius;
		return area;
	}

	double get_diametr()const {
		return 2 * this->radius;
	}

	double get_circumference() const {
		return 2 * PI * radius;
	}

	Circle(double x, double y, double radius) : Window(x, y) {
		this->radius = radius;
		cout << "Cconstructor\t" << this << endl;
	}

	~Circle() {
		cout << "Cdesctructor\t" << this << endl;
	}

	void draw_to_console() {
		HWND console_handle = GetConsoleWindow();
		HDC device_context = GetDC(console_handle);
		HPEN hPen = CreatePen(PS_DASHDOTDOT, 11, RGB(0, 255, 255));
		SelectObject(device_context, hPen);
		SetBkColor(device_context, RGB(255, 0, 0));
		SelectObject(device_context, CreateSolidBrush(RGB(0, 0, 0)));
		Ellipse(device_context, Window::get_x(), Window::get_y(), Window::get_x() + radius, Window::get_y() + radius);
		DeleteObject(device_context);
		DeleteObject(hPen);
		ReleaseDC(console_handle, device_context);
	}
	void print()const {
		cout << "Radius: " << radius << endl;
		cout << "Area: " << get_area() << endl;
		cout << "Radius: " << get_diametr() << endl;
	}
};
int main() {
	int drawop;
	cout << "Enter a draw shape: 1 - square 2 - Rectangel 3 - Triangel 4 - Circle 5 - Exit";
	cin >> drawop;

	while (drawop > 5)
	{
		cout << "Enter again: " << endl;
		cin >> drawop;
	}

	Square a(100, 100, 10);
	Rectangel b(100, 100, 100, 40);
	EqualTriangel c(100, 100, 40);
	Circle d(100, 100, 100);

	while (true)
	{
		if (drawop == 5) {
			break;
		}
		switch (drawop)
		{
		case 1:
			a.print();
			a.drawtoconsole();
			break;
		case 2:
			b.print();
			b.draw_to_console();
			break;
		case 3:
			c.print();
			c.print_to_console();
			break;
		case 4:
			d.print();
			d.draw_to_console();
		default:
			break;
		}
		cout << "Enter again: " << endl;
		cin >> drawop;
	}
	return 0;
}
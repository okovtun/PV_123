#include<iostream>
using namespace std;

/*
------------------------------------------------------
enum (enumeration - перечисление) - это набор именованных констант типа int.

------------------------------------------------------
*/

//Создаем тип данных Color
enum Color
{
	some_colore,
	console_blue	= 0x09,
	console_green	= 0x0A,
	console_red		= 0x0C,
	console_default = 0x07
};

class Shape
{
	Color color;
public:
	Shape(Color color) :color(color){}
	virtual ~Shape(){}

	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
};

void main()
{
	setlocale(LC_ALL, "");

}